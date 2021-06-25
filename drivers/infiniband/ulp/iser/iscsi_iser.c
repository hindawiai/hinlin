<शैली गुरु>
/*
 * iSCSI Initiator over iSER Data-Path
 *
 * Copyright (C) 2004 Dmitry Yusupov
 * Copyright (C) 2004 Alex Aizman
 * Copyright (C) 2005 Mike Christie
 * Copyright (c) 2005, 2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2013-2014 Mellanox Technologies. All rights reserved.
 * मुख्यtained by खोलोib-general@खोलोib.org
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
 *
 * Credits:
 *	Christoph Hellwig
 *	FUJITA Tomonori
 *	Arne Redlich
 *	Zhenyu Wang
 * Modअगरied by:
 *      Erez Zilber
 */

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/cdev.h>
#समावेश <linux/in.h>
#समावेश <linux/net.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <net/sock.h>

#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>

#समावेश "iscsi_iser.h"

MODULE_DESCRIPTION("iSER (iSCSI Extensions for RDMA) Datamover");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Alex Nezhinsky, Dan Bar Dov, Or Gerlitz");

अटल काष्ठा scsi_host_ढाँचा iscsi_iser_sht;
अटल काष्ठा iscsi_transport iscsi_iser_transport;
अटल काष्ठा scsi_transport_ढाँचा *iscsi_iser_scsi_transport;
अटल काष्ठा workqueue_काष्ठा *release_wq;
अटल DEFINE_MUTEX(unbind_iser_conn_mutex);
काष्ठा iser_global ig;

पूर्णांक iser_debug_level = 0;
module_param_named(debug_level, iser_debug_level, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_level, "Enable debug tracing if > 0 (default:disabled)");

अटल पूर्णांक iscsi_iser_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops iscsi_iser_size_ops = अणु
	.set = iscsi_iser_set,
	.get = param_get_uपूर्णांक,
पूर्ण;

अटल अचिन्हित पूर्णांक iscsi_max_lun = 512;
module_param_cb(max_lun, &iscsi_iser_size_ops, &iscsi_max_lun, S_IRUGO);
MODULE_PARM_DESC(max_lun, "Max LUNs to allow per session, should > 0 (default:512)");

अचिन्हित पूर्णांक iser_max_sectors = ISER_DEF_MAX_SECTORS;
module_param_cb(max_sectors, &iscsi_iser_size_ops, &iser_max_sectors,
		S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_sectors, "Max number of sectors in a single scsi command, should > 0 (default:1024)");

bool iser_always_reg = true;
module_param_named(always_रेजिस्टर, iser_always_reg, bool, S_IRUGO);
MODULE_PARM_DESC(always_रेजिस्टर,
		 "Always register memory, even for continuous memory regions (default:true)");

bool iser_pi_enable = false;
module_param_named(pi_enable, iser_pi_enable, bool, S_IRUGO);
MODULE_PARM_DESC(pi_enable, "Enable T10-PI offload support (default:disabled)");

पूर्णांक iser_pi_guard;
module_param_named(pi_guard, iser_pi_guard, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pi_guard, "T10-PI guard_type [deprecated]");

अटल पूर्णांक iscsi_iser_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक n = 0;

	ret = kstrtouपूर्णांक(val, 10, &n);
	अगर (ret != 0 || n == 0)
		वापस -EINVAL;

	वापस param_set_uपूर्णांक(val, kp);
पूर्ण

/*
 * iscsi_iser_recv() - Process a successful recv completion
 * @conn:         iscsi connection
 * @hdr:          iscsi header
 * @rx_data:      buffer containing receive data payload
 * @rx_data_len:  length of rx_data
 *
 * Notes: In हाल of data length errors or iscsi PDU completion failures
 *        this routine will संकेत iscsi layer of connection failure.
 */
व्योम
iscsi_iser_recv(काष्ठा iscsi_conn *conn, काष्ठा iscsi_hdr *hdr,
		अक्षर *rx_data, पूर्णांक rx_data_len)
अणु
	पूर्णांक rc = 0;
	पूर्णांक datalen;

	/* verअगरy PDU length */
	datalen = ntoh24(hdr->dlength);
	अगर (datalen > rx_data_len || (datalen + 4) < rx_data_len) अणु
		iser_err("wrong datalen %d (hdr), %d (IB)\n",
			datalen, rx_data_len);
		rc = ISCSI_ERR_DATALEN;
		जाओ error;
	पूर्ण

	अगर (datalen != rx_data_len)
		iser_dbg("aligned datalen (%d) hdr, %d (IB)\n",
			datalen, rx_data_len);

	rc = iscsi_complete_pdu(conn, hdr, rx_data, rx_data_len);
	अगर (rc && rc != ISCSI_ERR_NO_SCSI_CMD)
		जाओ error;

	वापस;
error:
	iscsi_conn_failure(conn, rc);
पूर्ण

/**
 * iscsi_iser_pdu_alloc() - allocate an iscsi-iser PDU
 * @task:     iscsi task
 * @opcode:   iscsi command opcode
 *
 * Netes: This routine can't fail, just assign iscsi task
 *        hdr and max hdr size.
 */
अटल पूर्णांक
iscsi_iser_pdu_alloc(काष्ठा iscsi_task *task, uपूर्णांक8_t opcode)
अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;

	task->hdr = (काष्ठा iscsi_hdr *)&iser_task->desc.iscsi_header;
	task->hdr_max = माप(iser_task->desc.iscsi_header);

	वापस 0;
पूर्ण

/**
 * iser_initialize_task_headers() - Initialize task headers
 * @task:       iscsi task
 * @tx_desc:    iser tx descriptor
 *
 * Notes:
 * This routine may race with iser tearकरोwn flow क्रम scsi
 * error handling TMFs. So क्रम TMF we should acquire the
 * state mutex to aव्योम dereferencing the IB device which
 * may have alपढ़ोy been terminated.
 */
पूर्णांक
iser_initialize_task_headers(काष्ठा iscsi_task *task,
			     काष्ठा iser_tx_desc *tx_desc)
अणु
	काष्ठा iser_conn *iser_conn = task->conn->dd_data;
	काष्ठा iser_device *device = iser_conn->ib_conn.device;
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	u64 dma_addr;

	अगर (unlikely(iser_conn->state != ISER_CONN_UP))
		वापस -ENODEV;

	dma_addr = ib_dma_map_single(device->ib_device, (व्योम *)tx_desc,
				ISER_HEADERS_LEN, DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(device->ib_device, dma_addr))
		वापस -ENOMEM;

	tx_desc->inv_wr.next = शून्य;
	tx_desc->reg_wr.wr.next = शून्य;
	tx_desc->mapped = true;
	tx_desc->dma_addr = dma_addr;
	tx_desc->tx_sg[0].addr   = tx_desc->dma_addr;
	tx_desc->tx_sg[0].length = ISER_HEADERS_LEN;
	tx_desc->tx_sg[0].lkey   = device->pd->local_dma_lkey;

	iser_task->iser_conn = iser_conn;

	वापस 0;
पूर्ण

/**
 * iscsi_iser_task_init() - Initialize iscsi-iser task
 * @task: iscsi task
 *
 * Initialize the task क्रम the scsi command or mgmt command.
 *
 * Return: Returns zero on success or -ENOMEM when failing
 *         to init task headers (dma mapping error).
 */
अटल पूर्णांक
iscsi_iser_task_init(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	पूर्णांक ret;

	ret = iser_initialize_task_headers(task, &iser_task->desc);
	अगर (ret) अणु
		iser_err("Failed to init task %p, err = %d\n",
			 iser_task, ret);
		वापस ret;
	पूर्ण

	/* mgmt task */
	अगर (!task->sc)
		वापस 0;

	iser_task->command_sent = 0;
	iser_task_rdma_init(iser_task);
	iser_task->sc = task->sc;

	वापस 0;
पूर्ण

/**
 * iscsi_iser_mtask_xmit() - xmit management (immediate) task
 * @conn: iscsi connection
 * @task: task management task
 *
 * Notes:
 *	The function can वापस -EAGAIN in which हाल caller must
 *	call it again later, or recover. '0' वापस code means successful
 *	xmit.
 *
 **/
अटल पूर्णांक
iscsi_iser_mtask_xmit(काष्ठा iscsi_conn *conn, काष्ठा iscsi_task *task)
अणु
	पूर्णांक error = 0;

	iser_dbg("mtask xmit [cid %d itt 0x%x]\n", conn->id, task->itt);

	error = iser_send_control(conn, task);

	/* since iser xmits control with zero copy, tasks can not be recycled
	 * right after sending them.
	 * The recycling scheme is based on whether a response is expected
	 * - अगर yes, the task is recycled at iscsi_complete_pdu
	 * - अगर no,  the task is recycled at iser_snd_completion
	 */
	वापस error;
पूर्ण

अटल पूर्णांक
iscsi_iser_task_xmit_unsol_data(काष्ठा iscsi_conn *conn,
				 काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_r2t_info *r2t = &task->unsol_r2t;
	काष्ठा iscsi_data hdr;
	पूर्णांक error = 0;

	/* Send data-out PDUs जबतक there's still unsolicited data to send */
	जबतक (iscsi_task_has_unsol_data(task)) अणु
		iscsi_prep_data_out_pdu(task, r2t, &hdr);
		iser_dbg("Sending data-out: itt 0x%x, data count %d\n",
			   hdr.itt, r2t->data_count);

		/* the buffer description has been passed with the command */
		/* Send the command */
		error = iser_send_data_out(conn, task, &hdr);
		अगर (error) अणु
			r2t->datasn--;
			जाओ iscsi_iser_task_xmit_unsol_data_निकास;
		पूर्ण
		r2t->sent += r2t->data_count;
		iser_dbg("Need to send %d more as data-out PDUs\n",
			   r2t->data_length - r2t->sent);
	पूर्ण

iscsi_iser_task_xmit_unsol_data_निकास:
	वापस error;
पूर्ण

/**
 * iscsi_iser_task_xmit() - xmit iscsi-iser task
 * @task: iscsi task
 *
 * Return: zero on success or escalates $error on failure.
 */
अटल पूर्णांक
iscsi_iser_task_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	पूर्णांक error = 0;

	अगर (!task->sc)
		वापस iscsi_iser_mtask_xmit(conn, task);

	अगर (task->sc->sc_data_direction == DMA_TO_DEVICE) अणु
		BUG_ON(scsi_bufflen(task->sc) == 0);

		iser_dbg("cmd [itt %x total %d imm %d unsol_data %d\n",
			   task->itt, scsi_bufflen(task->sc),
			   task->imm_count, task->unsol_r2t.data_length);
	पूर्ण

	iser_dbg("ctask xmit [cid %d itt 0x%x]\n",
		   conn->id, task->itt);

	/* Send the cmd PDU */
	अगर (!iser_task->command_sent) अणु
		error = iser_send_command(conn, task);
		अगर (error)
			जाओ iscsi_iser_task_xmit_निकास;
		iser_task->command_sent = 1;
	पूर्ण

	/* Send unsolicited data-out PDU(s) अगर necessary */
	अगर (iscsi_task_has_unsol_data(task))
		error = iscsi_iser_task_xmit_unsol_data(conn, task);

 iscsi_iser_task_xmit_निकास:
	वापस error;
पूर्ण

/**
 * iscsi_iser_cleanup_task() - cleanup an iscsi-iser task
 * @task: iscsi task
 *
 * Notes: In हाल the RDMA device is alपढ़ोy शून्य (might have
 *        been हटाओd in DEVICE_REMOVAL CM event it will bail-out
 *        without करोing dma unmapping.
 */
अटल व्योम iscsi_iser_cleanup_task(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	काष्ठा iser_tx_desc *tx_desc = &iser_task->desc;
	काष्ठा iser_conn *iser_conn = task->conn->dd_data;
	काष्ठा iser_device *device = iser_conn->ib_conn.device;

	/* DEVICE_REMOVAL event might have alपढ़ोy released the device */
	अगर (!device)
		वापस;

	अगर (likely(tx_desc->mapped)) अणु
		ib_dma_unmap_single(device->ib_device, tx_desc->dma_addr,
				    ISER_HEADERS_LEN, DMA_TO_DEVICE);
		tx_desc->mapped = false;
	पूर्ण

	/* mgmt tasks करो not need special cleanup */
	अगर (!task->sc)
		वापस;

	अगर (iser_task->status == ISER_TASK_STATUS_STARTED) अणु
		iser_task->status = ISER_TASK_STATUS_COMPLETED;
		iser_task_rdma_finalize(iser_task);
	पूर्ण
पूर्ण

/**
 * iscsi_iser_check_protection() - check protection inक्रमmation status of task.
 * @task:     iscsi task
 * @sector:   error sector अगर exsists (output)
 *
 * Return: zero अगर no data-पूर्णांकegrity errors have occured
 *         0x1: data-पूर्णांकegrity error occured in the guard-block
 *         0x2: data-पूर्णांकegrity error occured in the reference tag
 *         0x3: data-पूर्णांकegrity error occured in the application tag
 *
 *         In addition the error sector is marked.
 */
अटल u8
iscsi_iser_check_protection(काष्ठा iscsi_task *task, sector_t *sector)
अणु
	काष्ठा iscsi_iser_task *iser_task = task->dd_data;
	क्रमागत iser_data_dir dir = iser_task->dir[ISER_सूची_IN] ?
					ISER_सूची_IN : ISER_सूची_OUT;

	वापस iser_check_task_pi_status(iser_task, dir, sector);
पूर्ण

/**
 * iscsi_iser_conn_create() - create a new iscsi-iser connection
 * @cls_session: iscsi class connection
 * @conn_idx:    connection index within the session (क्रम MCS)
 *
 * Return: iscsi_cls_conn when iscsi_conn_setup succeeds or शून्य
 *         otherwise.
 */
अटल काष्ठा iscsi_cls_conn *
iscsi_iser_conn_create(काष्ठा iscsi_cls_session *cls_session,
		       uपूर्णांक32_t conn_idx)
अणु
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_cls_conn *cls_conn;

	cls_conn = iscsi_conn_setup(cls_session, 0, conn_idx);
	अगर (!cls_conn)
		वापस शून्य;
	conn = cls_conn->dd_data;

	/*
	 * due to issues with the login code re iser sematics
	 * this not set in iscsi_conn_setup - FIXME
	 */
	conn->max_recv_dlength = ISER_RECV_DATA_SEG_LEN;

	वापस cls_conn;
पूर्ण

/**
 * iscsi_iser_conn_bind() - bind iscsi and iser connection काष्ठाures
 * @cls_session:     iscsi class session
 * @cls_conn:        iscsi class connection
 * @transport_eph:   transport end-poपूर्णांक handle
 * @is_leading:      indicate अगर this is the session leading connection (MCS)
 *
 * Return: zero on success, $error अगर iscsi_conn_bind fails and
 *         -EINVAL in हाल end-poपूर्णांक करोesn't exsits anymore or iser connection
 *         state is not UP (tearकरोwn alपढ़ोy started).
 */
अटल पूर्णांक
iscsi_iser_conn_bind(काष्ठा iscsi_cls_session *cls_session,
		     काष्ठा iscsi_cls_conn *cls_conn,
		     uपूर्णांक64_t transport_eph,
		     पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iser_conn *iser_conn;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	पूर्णांक error;

	error = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	अगर (error)
		वापस error;

	/* the transport ep handle comes from user space so it must be
	 * verअगरied against the global ib connections list */
	ep = iscsi_lookup_endpoपूर्णांक(transport_eph);
	अगर (!ep) अणु
		iser_err("can't bind eph %llx\n",
			 (अचिन्हित दीर्घ दीर्घ)transport_eph);
		वापस -EINVAL;
	पूर्ण
	iser_conn = ep->dd_data;

	mutex_lock(&iser_conn->state_mutex);
	अगर (iser_conn->state != ISER_CONN_UP) अणु
		error = -EINVAL;
		iser_err("iser_conn %p state is %d, teardown started\n",
			 iser_conn, iser_conn->state);
		जाओ out;
	पूर्ण

	error = iser_alloc_rx_descriptors(iser_conn, conn->session);
	अगर (error)
		जाओ out;

	/* binds the iSER connection retrieved from the previously
	 * connected ep_handle to the iSCSI layer connection. exchanges
	 * connection poपूर्णांकers */
	iser_info("binding iscsi conn %p to iser_conn %p\n", conn, iser_conn);

	conn->dd_data = iser_conn;
	iser_conn->iscsi_conn = conn;

out:
	mutex_unlock(&iser_conn->state_mutex);
	वापस error;
पूर्ण

/**
 * iscsi_iser_conn_start() - start iscsi-iser connection
 * @cls_conn: iscsi class connection
 *
 * Notes: Here iser पूर्णांकialize (or re-initialize) stop_completion as
 *        from this poपूर्णांक iscsi must call conn_stop in session/connection
 *        tearकरोwn so iser transport must रुको क्रम it.
 */
अटल पूर्णांक
iscsi_iser_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *iscsi_conn;
	काष्ठा iser_conn *iser_conn;

	iscsi_conn = cls_conn->dd_data;
	iser_conn = iscsi_conn->dd_data;
	reinit_completion(&iser_conn->stop_completion);

	वापस iscsi_conn_start(cls_conn);
पूर्ण

/**
 * iscsi_iser_conn_stop() - stop iscsi-iser connection
 * @cls_conn:  iscsi class connection
 * @flag:      indicate अगर recover or terminate (passed as is)
 *
 * Notes: Calling iscsi_conn_stop might theoretically race with
 *        DEVICE_REMOVAL event and dereference a previously मुक्तd RDMA device
 *        handle, so we call it under iser the state lock to protect against
 *        this kind of race.
 */
अटल व्योम
iscsi_iser_conn_stop(काष्ठा iscsi_cls_conn *cls_conn, पूर्णांक flag)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा iser_conn *iser_conn = conn->dd_data;

	iser_info("stopping iscsi_conn: %p, iser_conn: %p\n", conn, iser_conn);

	/*
	 * Userspace may have goofed up and not bound the connection or
	 * might have only partially setup the connection.
	 */
	अगर (iser_conn) अणु
		mutex_lock(&iser_conn->state_mutex);
		mutex_lock(&unbind_iser_conn_mutex);
		iser_conn_terminate(iser_conn);
		iscsi_conn_stop(cls_conn, flag);

		/* unbind */
		iser_conn->iscsi_conn = शून्य;
		conn->dd_data = शून्य;
		mutex_unlock(&unbind_iser_conn_mutex);

		complete(&iser_conn->stop_completion);
		mutex_unlock(&iser_conn->state_mutex);
	पूर्ण अन्यथा अणु
		iscsi_conn_stop(cls_conn, flag);
	पूर्ण
पूर्ण

/**
 * iscsi_iser_session_destroy() - destroy iscsi-iser session
 * @cls_session: iscsi class session
 *
 * Removes and मुक्त iscsi host.
 */
अटल व्योम
iscsi_iser_session_destroy(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);

	iscsi_session_tearकरोwn(cls_session);
	iscsi_host_हटाओ(shost);
	iscsi_host_मुक्त(shost);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
iser_dअगर_prot_caps(पूर्णांक prot_caps)
अणु
	पूर्णांक ret = 0;

	अगर (prot_caps & IB_PROT_T10DIF_TYPE_1)
		ret |= SHOST_DIF_TYPE1_PROTECTION |
		       SHOST_DIX_TYPE0_PROTECTION |
		       SHOST_DIX_TYPE1_PROTECTION;
	अगर (prot_caps & IB_PROT_T10DIF_TYPE_2)
		ret |= SHOST_DIF_TYPE2_PROTECTION |
		       SHOST_DIX_TYPE2_PROTECTION;
	अगर (prot_caps & IB_PROT_T10DIF_TYPE_3)
		ret |= SHOST_DIF_TYPE3_PROTECTION |
		       SHOST_DIX_TYPE3_PROTECTION;

	वापस ret;
पूर्ण

/**
 * iscsi_iser_session_create() - create an iscsi-iser session
 * @ep:             iscsi end-poपूर्णांक handle
 * @cmds_max:       maximum commands in this session
 * @qdepth:         session command queue depth
 * @initial_cmdsn:  initiator command sequnce number
 *
 * Allocates and adds a scsi host, expose DIF supprot अगर
 * exists, and sets up an iscsi session.
 */
अटल काष्ठा iscsi_cls_session *
iscsi_iser_session_create(काष्ठा iscsi_endpoपूर्णांक *ep,
			  uपूर्णांक16_t cmds_max, uपूर्णांक16_t qdepth,
			  uपूर्णांक32_t initial_cmdsn)
अणु
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा Scsi_Host *shost;
	काष्ठा iser_conn *iser_conn = शून्य;
	काष्ठा ib_conn *ib_conn;
	काष्ठा ib_device *ib_dev;
	u32 max_fr_sectors;

	shost = iscsi_host_alloc(&iscsi_iser_sht, 0, 0);
	अगर (!shost)
		वापस शून्य;
	shost->transportt = iscsi_iser_scsi_transport;
	shost->cmd_per_lun = qdepth;
	shost->max_lun = iscsi_max_lun;
	shost->max_id = 0;
	shost->max_channel = 0;
	shost->max_cmd_len = 16;

	/*
	 * older userspace tools (beक्रमe 2.0-870) did not pass us
	 * the leading conn's ep so this will be शून्य;
	 */
	अगर (ep) अणु
		iser_conn = ep->dd_data;
		shost->sg_tablesize = iser_conn->scsi_sg_tablesize;
		shost->can_queue = min_t(u16, cmds_max, iser_conn->max_cmds);

		mutex_lock(&iser_conn->state_mutex);
		अगर (iser_conn->state != ISER_CONN_UP) अणु
			iser_err("iser conn %p already started teardown\n",
				 iser_conn);
			mutex_unlock(&iser_conn->state_mutex);
			जाओ मुक्त_host;
		पूर्ण

		ib_conn = &iser_conn->ib_conn;
		ib_dev = ib_conn->device->ib_device;
		अगर (ib_conn->pi_support) अणु
			u32 sig_caps = ib_dev->attrs.sig_prot_cap;

			shost->sg_prot_tablesize = shost->sg_tablesize;
			scsi_host_set_prot(shost, iser_dअगर_prot_caps(sig_caps));
			scsi_host_set_guard(shost, SHOST_DIX_GUARD_IP |
						   SHOST_DIX_GUARD_CRC);
		पूर्ण

		अगर (!(ib_dev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG))
			shost->virt_boundary_mask = SZ_4K - 1;

		अगर (iscsi_host_add(shost, ib_dev->dev.parent)) अणु
			mutex_unlock(&iser_conn->state_mutex);
			जाओ मुक्त_host;
		पूर्ण
		mutex_unlock(&iser_conn->state_mutex);
	पूर्ण अन्यथा अणु
		shost->can_queue = min_t(u16, cmds_max, ISER_DEF_XMIT_CMDS_MAX);
		अगर (iscsi_host_add(shost, शून्य))
			जाओ मुक्त_host;
	पूर्ण

	max_fr_sectors = (shost->sg_tablesize * PAGE_SIZE) >> 9;
	shost->max_sectors = min(iser_max_sectors, max_fr_sectors);

	iser_dbg("iser_conn %p, sg_tablesize %u, max_sectors %u\n",
		 iser_conn, shost->sg_tablesize,
		 shost->max_sectors);

	अगर (shost->max_sectors < iser_max_sectors)
		iser_warn("max_sectors was reduced from %u to %u\n",
			  iser_max_sectors, shost->max_sectors);

	cls_session = iscsi_session_setup(&iscsi_iser_transport, shost,
					  shost->can_queue, 0,
					  माप(काष्ठा iscsi_iser_task),
					  initial_cmdsn, 0);
	अगर (!cls_session)
		जाओ हटाओ_host;

	वापस cls_session;

हटाओ_host:
	iscsi_host_हटाओ(shost);
मुक्त_host:
	iscsi_host_मुक्त(shost);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
iscsi_iser_set_param(काष्ठा iscsi_cls_conn *cls_conn,
		     क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक value;

	चयन (param) अणु
	हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		/* TBD */
		अवरोध;
	हाल ISCSI_PARAM_HDRDGST_EN:
		माला_पूछो(buf, "%d", &value);
		अगर (value) अणु
			iser_err("DataDigest wasn't negotiated to None\n");
			वापस -EPROTO;
		पूर्ण
		अवरोध;
	हाल ISCSI_PARAM_DATADGST_EN:
		माला_पूछो(buf, "%d", &value);
		अगर (value) अणु
			iser_err("DataDigest wasn't negotiated to None\n");
			वापस -EPROTO;
		पूर्ण
		अवरोध;
	हाल ISCSI_PARAM_IFMARKER_EN:
		माला_पूछो(buf, "%d", &value);
		अगर (value) अणु
			iser_err("IFMarker wasn't negotiated to No\n");
			वापस -EPROTO;
		पूर्ण
		अवरोध;
	हाल ISCSI_PARAM_OFMARKER_EN:
		माला_पूछो(buf, "%d", &value);
		अगर (value) अणु
			iser_err("OFMarker wasn't negotiated to No\n");
			वापस -EPROTO;
		पूर्ण
		अवरोध;
	शेष:
		वापस iscsi_set_param(cls_conn, param, buf, buflen);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iscsi_iser_conn_get_stats() - get iscsi connection statistics
 * @cls_conn:    iscsi class connection
 * @stats:       iscsi stats to output
 *
 * Output connection statistics.
 */
अटल व्योम
iscsi_iser_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn, काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt; /* always 0 */
	stats->r2t_pdus = conn->r2t_pdus_cnt; /* always 0 */
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
	stats->custom_length = 0;
पूर्ण

अटल पूर्णांक iscsi_iser_get_ep_param(काष्ठा iscsi_endpoपूर्णांक *ep,
				   क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा iser_conn *iser_conn = ep->dd_data;

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
	हाल ISCSI_PARAM_CONN_ADDRESS:
		अगर (!iser_conn || !iser_conn->ib_conn.cma_id)
			वापस -ENOTCONN;

		वापस iscsi_conn_get_addr_param((काष्ठा sockaddr_storage *)
				&iser_conn->ib_conn.cma_id->route.addr.dst_addr,
				param, buf);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

/**
 * iscsi_iser_ep_connect() - Initiate iSER connection establishment
 * @shost:          scsi_host
 * @dst_addr:       destination address
 * @non_blocking:   indicate अगर routine can block
 *
 * Allocate an iscsi endpoपूर्णांक, an iser_conn काष्ठाure and bind them.
 * After that start RDMA connection establishment via rdma_cm. We
 * करोn't allocate iser_conn embedded in iscsi_endpoपूर्णांक since in tearकरोwn
 * the endpoपूर्णांक will be destroyed at ep_disconnect जबतक iser_conn will
 * cleanup its resources asynchronuously.
 *
 * Return: iscsi_endpoपूर्णांक created by iscsi layer or ERR_PTR(error)
 *         अगर fails.
 */
अटल काष्ठा iscsi_endpoपूर्णांक *
iscsi_iser_ep_connect(काष्ठा Scsi_Host *shost, काष्ठा sockaddr *dst_addr,
		      पूर्णांक non_blocking)
अणु
	पूर्णांक err;
	काष्ठा iser_conn *iser_conn;
	काष्ठा iscsi_endpoपूर्णांक *ep;

	ep = iscsi_create_endpoपूर्णांक(0);
	अगर (!ep)
		वापस ERR_PTR(-ENOMEM);

	iser_conn = kzalloc(माप(*iser_conn), GFP_KERNEL);
	अगर (!iser_conn) अणु
		err = -ENOMEM;
		जाओ failure;
	पूर्ण

	ep->dd_data = iser_conn;
	iser_conn->ep = ep;
	iser_conn_init(iser_conn);

	err = iser_connect(iser_conn, शून्य, dst_addr, non_blocking);
	अगर (err)
		जाओ failure;

	वापस ep;
failure:
	iscsi_destroy_endpoपूर्णांक(ep);
	वापस ERR_PTR(err);
पूर्ण

/**
 * iscsi_iser_ep_poll() - poll क्रम iser connection establishment to complete
 * @ep:            iscsi endpoपूर्णांक (created at ep_connect)
 * @समयout_ms:    polling समयout allowed in ms.
 *
 * This routine boils करोwn to रुकोing क्रम up_completion संकेतing
 * that cma_id got CONNECTED event.
 *
 * Return: 1 अगर succeeded in connection establishment, 0 अगर समयout expired
 *         (libiscsi will retry will kick in) or -1 अगर पूर्णांकerrupted by संकेत
 *         or more likely iser connection state transitioned to TEMINATING or
 *         DOWN during the रुको period.
 */
अटल पूर्णांक
iscsi_iser_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा iser_conn *iser_conn = ep->dd_data;
	पूर्णांक rc;

	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&iser_conn->up_completion,
						       msecs_to_jअगरfies(समयout_ms));
	/* अगर conn establishment failed, वापस error code to iscsi */
	अगर (rc == 0) अणु
		mutex_lock(&iser_conn->state_mutex);
		अगर (iser_conn->state == ISER_CONN_TERMINATING ||
		    iser_conn->state == ISER_CONN_DOWN)
			rc = -1;
		mutex_unlock(&iser_conn->state_mutex);
	पूर्ण

	iser_info("iser conn %p rc = %d\n", iser_conn, rc);

	अगर (rc > 0)
		वापस 1; /* success, this is the equivalent of EPOLLOUT */
	अन्यथा अगर (!rc)
		वापस 0; /* समयout */
	अन्यथा
		वापस rc; /* संकेत */
पूर्ण

/**
 * iscsi_iser_ep_disconnect() - Initiate connection tearकरोwn process
 * @ep:    iscsi endpoपूर्णांक handle
 *
 * This routine is not blocked by iser and RDMA termination process
 * completion as we queue a deffered work क्रम iser/RDMA deकाष्ठाion
 * and cleanup or actually call it immediately in हाल we didn't pass
 * iscsi conn bind/start stage, thus it is safe.
 */
अटल व्योम
iscsi_iser_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा iser_conn *iser_conn = ep->dd_data;

	iser_info("ep %p iser conn %p\n", ep, iser_conn);

	mutex_lock(&iser_conn->state_mutex);
	iser_conn_terminate(iser_conn);

	/*
	 * अगर iser_conn and iscsi_conn are bound, we must रुको क्रम
	 * iscsi_conn_stop and flush errors completion beक्रमe मुक्तing
	 * the iser resources. Otherwise we are safe to मुक्त resources
	 * immediately.
	 */
	अगर (iser_conn->iscsi_conn) अणु
		INIT_WORK(&iser_conn->release_work, iser_release_work);
		queue_work(release_wq, &iser_conn->release_work);
		mutex_unlock(&iser_conn->state_mutex);
	पूर्ण अन्यथा अणु
		iser_conn->state = ISER_CONN_DOWN;
		mutex_unlock(&iser_conn->state_mutex);
		iser_conn_release(iser_conn);
	पूर्ण

	iscsi_destroy_endpoपूर्णांक(ep);
पूर्ण

अटल umode_t iser_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_INITIATOR_NAME:
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
		हाल ISCSI_PARAM_DISCOVERY_SESS:
			वापस S_IRUGO;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा iscsi_iser_sht = अणु
	.module                 = THIS_MODULE,
	.name                   = "iSCSI Initiator over iSER",
	.queuecommand           = iscsi_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.sg_tablesize           = ISCSI_ISER_DEF_SG_TABLESIZE,
	.cmd_per_lun            = ISER_DEF_CMD_PER_LUN,
	.eh_समयd_out		= iscsi_eh_cmd_समयd_out,
	.eh_पात_handler       = iscsi_eh_पात,
	.eh_device_reset_handler= iscsi_eh_device_reset,
	.eh_target_reset_handler = iscsi_eh_recover_target,
	.target_alloc		= iscsi_target_alloc,
	.proc_name              = "iscsi_iser",
	.this_id                = -1,
	.track_queue_depth	= 1,
पूर्ण;

अटल काष्ठा iscsi_transport iscsi_iser_transport = अणु
	.owner                  = THIS_MODULE,
	.name                   = "iser",
	.caps                   = CAP_RECOVERY_L0 | CAP_MULTI_R2T | CAP_TEXT_NEGO,
	/* session management */
	.create_session         = iscsi_iser_session_create,
	.destroy_session        = iscsi_iser_session_destroy,
	/* connection management */
	.create_conn            = iscsi_iser_conn_create,
	.bind_conn              = iscsi_iser_conn_bind,
	.destroy_conn           = iscsi_conn_tearकरोwn,
	.attr_is_visible	= iser_attr_is_visible,
	.set_param              = iscsi_iser_set_param,
	.get_conn_param		= iscsi_conn_get_param,
	.get_ep_param		= iscsi_iser_get_ep_param,
	.get_session_param	= iscsi_session_get_param,
	.start_conn             = iscsi_iser_conn_start,
	.stop_conn              = iscsi_iser_conn_stop,
	/* iscsi host params */
	.get_host_param		= iscsi_host_get_param,
	.set_host_param		= iscsi_host_set_param,
	/* IO */
	.send_pdu		= iscsi_conn_send_pdu,
	.get_stats		= iscsi_iser_conn_get_stats,
	.init_task		= iscsi_iser_task_init,
	.xmit_task		= iscsi_iser_task_xmit,
	.cleanup_task		= iscsi_iser_cleanup_task,
	.alloc_pdu		= iscsi_iser_pdu_alloc,
	.check_protection	= iscsi_iser_check_protection,
	/* recovery */
	.session_recovery_समयकरोut = iscsi_session_recovery_समयकरोut,

	.ep_connect             = iscsi_iser_ep_connect,
	.ep_poll                = iscsi_iser_ep_poll,
	.ep_disconnect          = iscsi_iser_ep_disconnect
पूर्ण;

अटल पूर्णांक __init iser_init(व्योम)
अणु
	पूर्णांक err;

	iser_dbg("Starting iSER datamover...\n");

	स_रखो(&ig, 0, माप(काष्ठा iser_global));

	ig.desc_cache = kmem_cache_create("iser_descriptors",
					  माप(काष्ठा iser_tx_desc),
					  0, SLAB_HWCACHE_ALIGN,
					  शून्य);
	अगर (ig.desc_cache == शून्य)
		वापस -ENOMEM;

	/* device init is called only after the first addr resolution */
	mutex_init(&ig.device_list_mutex);
	INIT_LIST_HEAD(&ig.device_list);
	mutex_init(&ig.connlist_mutex);
	INIT_LIST_HEAD(&ig.connlist);

	release_wq = alloc_workqueue("release workqueue", 0, 0);
	अगर (!release_wq) अणु
		iser_err("failed to allocate release workqueue\n");
		err = -ENOMEM;
		जाओ err_alloc_wq;
	पूर्ण

	iscsi_iser_scsi_transport = iscsi_रेजिस्टर_transport(
							&iscsi_iser_transport);
	अगर (!iscsi_iser_scsi_transport) अणु
		iser_err("iscsi_register_transport failed\n");
		err = -EINVAL;
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	destroy_workqueue(release_wq);
err_alloc_wq:
	kmem_cache_destroy(ig.desc_cache);

	वापस err;
पूर्ण

अटल व्योम __निकास iser_निकास(व्योम)
अणु
	काष्ठा iser_conn *iser_conn, *n;
	पूर्णांक connlist_empty;

	iser_dbg("Removing iSER datamover...\n");
	destroy_workqueue(release_wq);

	mutex_lock(&ig.connlist_mutex);
	connlist_empty = list_empty(&ig.connlist);
	mutex_unlock(&ig.connlist_mutex);

	अगर (!connlist_empty) अणु
		iser_err("Error cleanup stage completed but we still have iser "
			 "connections, destroying them anyway\n");
		list_क्रम_each_entry_safe(iser_conn, n, &ig.connlist,
					 conn_list) अणु
			iser_conn_release(iser_conn);
		पूर्ण
	पूर्ण

	iscsi_unरेजिस्टर_transport(&iscsi_iser_transport);
	kmem_cache_destroy(ig.desc_cache);
पूर्ण

module_init(iser_init);
module_निकास(iser_निकास);
