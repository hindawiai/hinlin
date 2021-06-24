<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains iSCSI extentions क्रम RDMA (iSER) Verbs
 *
 * (c) Copyright 2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ****************************************************************************/

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>
#समावेश <linux/semaphore.h>

#समावेश "ib_isert.h"

अटल पूर्णांक isert_debug_level;
module_param_named(debug_level, isert_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_level, "Enable debug tracing if > 0 (default:0)");

अटल पूर्णांक isert_sg_tablesize_set(स्थिर अक्षर *val,
				  स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops sg_tablesize_ops = अणु
	.set = isert_sg_tablesize_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल पूर्णांक isert_sg_tablesize = ISCSI_ISER_DEF_SG_TABLESIZE;
module_param_cb(sg_tablesize, &sg_tablesize_ops, &isert_sg_tablesize, 0644);
MODULE_PARM_DESC(sg_tablesize,
		 "Number of gather/scatter entries in a single scsi command, should >= 128 (default: 256, max: 4096)");

अटल DEFINE_MUTEX(device_list_mutex);
अटल LIST_HEAD(device_list);
अटल काष्ठा workqueue_काष्ठा *isert_comp_wq;
अटल काष्ठा workqueue_काष्ठा *isert_release_wq;

अटल पूर्णांक
isert_put_response(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd);
अटल पूर्णांक
isert_login_post_recv(काष्ठा isert_conn *isert_conn);
अटल पूर्णांक
isert_rdma_accept(काष्ठा isert_conn *isert_conn);
काष्ठा rdma_cm_id *isert_setup_id(काष्ठा isert_np *isert_np);

अटल व्योम isert_release_work(काष्ठा work_काष्ठा *work);
अटल व्योम isert_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम isert_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम isert_login_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम isert_login_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

अटल पूर्णांक isert_sg_tablesize_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक n = 0, ret;

	ret = kstrtoपूर्णांक(val, 10, &n);
	अगर (ret != 0 || n < ISCSI_ISER_MIN_SG_TABLESIZE ||
	    n > ISCSI_ISER_MAX_SG_TABLESIZE)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल अंतरभूत bool
isert_prot_cmd(काष्ठा isert_conn *conn, काष्ठा se_cmd *cmd)
अणु
	वापस (conn->pi_support &&
		cmd->prot_op != TARGET_PROT_NORMAL);
पूर्ण

अटल व्योम
isert_qp_event_callback(काष्ठा ib_event *e, व्योम *context)
अणु
	काष्ठा isert_conn *isert_conn = context;

	isert_err("%s (%d): conn %p\n",
		  ib_event_msg(e->event), e->event, isert_conn);

	चयन (e->event) अणु
	हाल IB_EVENT_COMM_EST:
		rdma_notअगरy(isert_conn->cm_id, IB_EVENT_COMM_EST);
		अवरोध;
	हाल IB_EVENT_QP_LAST_WQE_REACHED:
		isert_warn("Reached TX IB_EVENT_QP_LAST_WQE_REACHED\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा ib_qp *
isert_create_qp(काष्ठा isert_conn *isert_conn,
		काष्ठा rdma_cm_id *cma_id)
अणु
	u32 cq_size = ISERT_QP_MAX_REQ_DTOS + ISERT_QP_MAX_RECV_DTOS + 2;
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;
	काष्ठा ib_qp_init_attr attr;
	पूर्णांक ret, factor;

	isert_conn->cq = ib_cq_pool_get(ib_dev, cq_size, -1, IB_POLL_WORKQUEUE);
	अगर (IS_ERR(isert_conn->cq)) अणु
		isert_err("Unable to allocate cq\n");
		ret = PTR_ERR(isert_conn->cq);
		वापस ERR_PTR(ret);
	पूर्ण
	isert_conn->cq_size = cq_size;

	स_रखो(&attr, 0, माप(काष्ठा ib_qp_init_attr));
	attr.event_handler = isert_qp_event_callback;
	attr.qp_context = isert_conn;
	attr.send_cq = isert_conn->cq;
	attr.recv_cq = isert_conn->cq;
	attr.cap.max_send_wr = ISERT_QP_MAX_REQ_DTOS + 1;
	attr.cap.max_recv_wr = ISERT_QP_MAX_RECV_DTOS + 1;
	factor = rdma_rw_mr_factor(device->ib_device, cma_id->port_num,
				   isert_sg_tablesize);
	attr.cap.max_rdma_ctxs = ISCSI_DEF_XMIT_CMDS_MAX * factor;
	attr.cap.max_send_sge = device->ib_device->attrs.max_send_sge;
	attr.cap.max_recv_sge = 1;
	attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	attr.qp_type = IB_QPT_RC;
	अगर (device->pi_capable)
		attr.create_flags |= IB_QP_CREATE_INTEGRITY_EN;

	ret = rdma_create_qp(cma_id, device->pd, &attr);
	अगर (ret) अणु
		isert_err("rdma_create_qp failed for cma_id %d\n", ret);
		ib_cq_pool_put(isert_conn->cq, isert_conn->cq_size);

		वापस ERR_PTR(ret);
	पूर्ण

	वापस cma_id->qp;
पूर्ण

अटल पूर्णांक
isert_alloc_rx_descriptors(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;
	काष्ठा iser_rx_desc *rx_desc;
	काष्ठा ib_sge *rx_sg;
	u64 dma_addr;
	पूर्णांक i, j;

	isert_conn->rx_descs = kसुस्मृति(ISERT_QP_MAX_RECV_DTOS,
				       माप(काष्ठा iser_rx_desc),
				       GFP_KERNEL);
	अगर (!isert_conn->rx_descs)
		वापस -ENOMEM;

	rx_desc = isert_conn->rx_descs;

	क्रम (i = 0; i < ISERT_QP_MAX_RECV_DTOS; i++, rx_desc++)  अणु
		dma_addr = ib_dma_map_single(ib_dev, rx_desc->buf,
					ISER_RX_SIZE, DMA_FROM_DEVICE);
		अगर (ib_dma_mapping_error(ib_dev, dma_addr))
			जाओ dma_map_fail;

		rx_desc->dma_addr = dma_addr;

		rx_sg = &rx_desc->rx_sg;
		rx_sg->addr = rx_desc->dma_addr + isert_get_hdr_offset(rx_desc);
		rx_sg->length = ISER_RX_PAYLOAD_SIZE;
		rx_sg->lkey = device->pd->local_dma_lkey;
		rx_desc->rx_cqe.करोne = isert_recv_करोne;
	पूर्ण

	वापस 0;

dma_map_fail:
	rx_desc = isert_conn->rx_descs;
	क्रम (j = 0; j < i; j++, rx_desc++) अणु
		ib_dma_unmap_single(ib_dev, rx_desc->dma_addr,
				    ISER_RX_SIZE, DMA_FROM_DEVICE);
	पूर्ण
	kमुक्त(isert_conn->rx_descs);
	isert_conn->rx_descs = शून्य;
	isert_err("conn %p failed to allocate rx descriptors\n", isert_conn);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
isert_मुक्त_rx_descriptors(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा ib_device *ib_dev = isert_conn->device->ib_device;
	काष्ठा iser_rx_desc *rx_desc;
	पूर्णांक i;

	अगर (!isert_conn->rx_descs)
		वापस;

	rx_desc = isert_conn->rx_descs;
	क्रम (i = 0; i < ISERT_QP_MAX_RECV_DTOS; i++, rx_desc++)  अणु
		ib_dma_unmap_single(ib_dev, rx_desc->dma_addr,
				    ISER_RX_SIZE, DMA_FROM_DEVICE);
	पूर्ण

	kमुक्त(isert_conn->rx_descs);
	isert_conn->rx_descs = शून्य;
पूर्ण

अटल पूर्णांक
isert_create_device_ib_res(काष्ठा isert_device *device)
अणु
	काष्ठा ib_device *ib_dev = device->ib_device;
	पूर्णांक ret;

	isert_dbg("devattr->max_send_sge: %d devattr->max_recv_sge %d\n",
		  ib_dev->attrs.max_send_sge, ib_dev->attrs.max_recv_sge);
	isert_dbg("devattr->max_sge_rd: %d\n", ib_dev->attrs.max_sge_rd);

	device->pd = ib_alloc_pd(ib_dev, 0);
	अगर (IS_ERR(device->pd)) अणु
		ret = PTR_ERR(device->pd);
		isert_err("failed to allocate pd, device %p, ret=%d\n",
			  device, ret);
		वापस ret;
	पूर्ण

	/* Check signature cap */
	अगर (ib_dev->attrs.device_cap_flags & IB_DEVICE_INTEGRITY_HANDOVER)
		device->pi_capable = true;
	अन्यथा
		device->pi_capable = false;

	वापस 0;
पूर्ण

अटल व्योम
isert_मुक्त_device_ib_res(काष्ठा isert_device *device)
अणु
	isert_info("device %p\n", device);

	ib_dealloc_pd(device->pd);
पूर्ण

अटल व्योम
isert_device_put(काष्ठा isert_device *device)
अणु
	mutex_lock(&device_list_mutex);
	device->refcount--;
	isert_info("device %p refcount %d\n", device, device->refcount);
	अगर (!device->refcount) अणु
		isert_मुक्त_device_ib_res(device);
		list_del(&device->dev_node);
		kमुक्त(device);
	पूर्ण
	mutex_unlock(&device_list_mutex);
पूर्ण

अटल काष्ठा isert_device *
isert_device_get(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा isert_device *device;
	पूर्णांक ret;

	mutex_lock(&device_list_mutex);
	list_क्रम_each_entry(device, &device_list, dev_node) अणु
		अगर (device->ib_device->node_guid == cma_id->device->node_guid) अणु
			device->refcount++;
			isert_info("Found iser device %p refcount %d\n",
				   device, device->refcount);
			mutex_unlock(&device_list_mutex);
			वापस device;
		पूर्ण
	पूर्ण

	device = kzalloc(माप(काष्ठा isert_device), GFP_KERNEL);
	अगर (!device) अणु
		mutex_unlock(&device_list_mutex);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	INIT_LIST_HEAD(&device->dev_node);

	device->ib_device = cma_id->device;
	ret = isert_create_device_ib_res(device);
	अगर (ret) अणु
		kमुक्त(device);
		mutex_unlock(&device_list_mutex);
		वापस ERR_PTR(ret);
	पूर्ण

	device->refcount++;
	list_add_tail(&device->dev_node, &device_list);
	isert_info("Created a new iser device %p refcount %d\n",
		   device, device->refcount);
	mutex_unlock(&device_list_mutex);

	वापस device;
पूर्ण

अटल व्योम
isert_init_conn(काष्ठा isert_conn *isert_conn)
अणु
	isert_conn->state = ISER_CONN_INIT;
	INIT_LIST_HEAD(&isert_conn->node);
	init_completion(&isert_conn->login_comp);
	init_completion(&isert_conn->login_req_comp);
	init_रुकोqueue_head(&isert_conn->rem_रुको);
	kref_init(&isert_conn->kref);
	mutex_init(&isert_conn->mutex);
	INIT_WORK(&isert_conn->release_work, isert_release_work);
पूर्ण

अटल व्योम
isert_मुक्त_login_buf(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा ib_device *ib_dev = isert_conn->device->ib_device;

	ib_dma_unmap_single(ib_dev, isert_conn->login_rsp_dma,
			    ISER_RX_PAYLOAD_SIZE, DMA_TO_DEVICE);
	kमुक्त(isert_conn->login_rsp_buf);

	ib_dma_unmap_single(ib_dev, isert_conn->login_desc->dma_addr,
			    ISER_RX_SIZE, DMA_FROM_DEVICE);
	kमुक्त(isert_conn->login_desc);
पूर्ण

अटल पूर्णांक
isert_alloc_login_buf(काष्ठा isert_conn *isert_conn,
		      काष्ठा ib_device *ib_dev)
अणु
	पूर्णांक ret;

	isert_conn->login_desc = kzalloc(माप(*isert_conn->login_desc),
			GFP_KERNEL);
	अगर (!isert_conn->login_desc)
		वापस -ENOMEM;

	isert_conn->login_desc->dma_addr = ib_dma_map_single(ib_dev,
				isert_conn->login_desc->buf,
				ISER_RX_SIZE, DMA_FROM_DEVICE);
	ret = ib_dma_mapping_error(ib_dev, isert_conn->login_desc->dma_addr);
	अगर (ret) अणु
		isert_err("login_desc dma mapping error: %d\n", ret);
		isert_conn->login_desc->dma_addr = 0;
		जाओ out_मुक्त_login_desc;
	पूर्ण

	isert_conn->login_rsp_buf = kzalloc(ISER_RX_PAYLOAD_SIZE, GFP_KERNEL);
	अगर (!isert_conn->login_rsp_buf) अणु
		ret = -ENOMEM;
		जाओ out_unmap_login_desc;
	पूर्ण

	isert_conn->login_rsp_dma = ib_dma_map_single(ib_dev,
					isert_conn->login_rsp_buf,
					ISER_RX_PAYLOAD_SIZE, DMA_TO_DEVICE);
	ret = ib_dma_mapping_error(ib_dev, isert_conn->login_rsp_dma);
	अगर (ret) अणु
		isert_err("login_rsp_dma mapping error: %d\n", ret);
		isert_conn->login_rsp_dma = 0;
		जाओ out_मुक्त_login_rsp_buf;
	पूर्ण

	वापस 0;

out_मुक्त_login_rsp_buf:
	kमुक्त(isert_conn->login_rsp_buf);
out_unmap_login_desc:
	ib_dma_unmap_single(ib_dev, isert_conn->login_desc->dma_addr,
			    ISER_RX_SIZE, DMA_FROM_DEVICE);
out_मुक्त_login_desc:
	kमुक्त(isert_conn->login_desc);
	वापस ret;
पूर्ण

अटल व्योम
isert_set_nego_params(काष्ठा isert_conn *isert_conn,
		      काष्ठा rdma_conn_param *param)
अणु
	काष्ठा ib_device_attr *attr = &isert_conn->device->ib_device->attrs;

	/* Set max inflight RDMA READ requests */
	isert_conn->initiator_depth = min_t(u8, param->initiator_depth,
				attr->max_qp_init_rd_atom);
	isert_dbg("Using initiator_depth: %u\n", isert_conn->initiator_depth);

	अगर (param->निजी_data) अणु
		u8 flags = *(u8 *)param->निजी_data;

		/*
		 * use remote invalidation अगर the both initiator
		 * and the HCA support it
		 */
		isert_conn->snd_w_inv = !(flags & ISER_SEND_W_INV_NOT_SUP) &&
					  (attr->device_cap_flags &
					   IB_DEVICE_MEM_MGT_EXTENSIONS);
		अगर (isert_conn->snd_w_inv)
			isert_info("Using remote invalidation\n");
	पूर्ण
पूर्ण

अटल व्योम
isert_destroy_qp(काष्ठा isert_conn *isert_conn)
अणु
	ib_destroy_qp(isert_conn->qp);
	ib_cq_pool_put(isert_conn->cq, isert_conn->cq_size);
पूर्ण

अटल पूर्णांक
isert_connect_request(काष्ठा rdma_cm_id *cma_id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा isert_np *isert_np = cma_id->context;
	काष्ठा iscsi_np *np = isert_np->np;
	काष्ठा isert_conn *isert_conn;
	काष्ठा isert_device *device;
	पूर्णांक ret = 0;

	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (!np->enabled) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		isert_dbg("iscsi_np is not enabled, reject connect request\n");
		वापस rdma_reject(cma_id, शून्य, 0, IB_CM_REJ_CONSUMER_DEFINED);
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	isert_dbg("cma_id: %p, portal: %p\n",
		 cma_id, cma_id->context);

	isert_conn = kzalloc(माप(काष्ठा isert_conn), GFP_KERNEL);
	अगर (!isert_conn)
		वापस -ENOMEM;

	isert_init_conn(isert_conn);
	isert_conn->cm_id = cma_id;

	device = isert_device_get(cma_id);
	अगर (IS_ERR(device)) अणु
		ret = PTR_ERR(device);
		जाओ out;
	पूर्ण
	isert_conn->device = device;

	ret = isert_alloc_login_buf(isert_conn, cma_id->device);
	अगर (ret)
		जाओ out_conn_dev;

	isert_set_nego_params(isert_conn, &event->param.conn);

	isert_conn->qp = isert_create_qp(isert_conn, cma_id);
	अगर (IS_ERR(isert_conn->qp)) अणु
		ret = PTR_ERR(isert_conn->qp);
		जाओ out_rsp_dma_map;
	पूर्ण

	ret = isert_login_post_recv(isert_conn);
	अगर (ret)
		जाओ out_destroy_qp;

	ret = isert_rdma_accept(isert_conn);
	अगर (ret)
		जाओ out_destroy_qp;

	mutex_lock(&isert_np->mutex);
	list_add_tail(&isert_conn->node, &isert_np->accepted);
	mutex_unlock(&isert_np->mutex);

	वापस 0;

out_destroy_qp:
	isert_destroy_qp(isert_conn);
out_rsp_dma_map:
	isert_मुक्त_login_buf(isert_conn);
out_conn_dev:
	isert_device_put(device);
out:
	kमुक्त(isert_conn);
	rdma_reject(cma_id, शून्य, 0, IB_CM_REJ_CONSUMER_DEFINED);
	वापस ret;
पूर्ण

अटल व्योम
isert_connect_release(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा isert_device *device = isert_conn->device;

	isert_dbg("conn %p\n", isert_conn);

	BUG_ON(!device);

	isert_मुक्त_rx_descriptors(isert_conn);
	अगर (isert_conn->cm_id &&
	    !isert_conn->dev_हटाओd)
		rdma_destroy_id(isert_conn->cm_id);

	अगर (isert_conn->qp)
		isert_destroy_qp(isert_conn);

	अगर (isert_conn->login_desc)
		isert_मुक्त_login_buf(isert_conn);

	isert_device_put(device);

	अगर (isert_conn->dev_हटाओd)
		wake_up_पूर्णांकerruptible(&isert_conn->rem_रुको);
	अन्यथा
		kमुक्त(isert_conn);
पूर्ण

अटल व्योम
isert_connected_handler(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा isert_conn *isert_conn = cma_id->qp->qp_context;
	काष्ठा isert_np *isert_np = cma_id->context;

	isert_info("conn %p\n", isert_conn);

	mutex_lock(&isert_conn->mutex);
	isert_conn->state = ISER_CONN_UP;
	kref_get(&isert_conn->kref);
	mutex_unlock(&isert_conn->mutex);

	mutex_lock(&isert_np->mutex);
	list_move_tail(&isert_conn->node, &isert_np->pending);
	mutex_unlock(&isert_np->mutex);

	isert_info("np %p: Allow accept_np to continue\n", isert_np);
	up(&isert_np->sem);
पूर्ण

अटल व्योम
isert_release_kref(काष्ठा kref *kref)
अणु
	काष्ठा isert_conn *isert_conn = container_of(kref,
				काष्ठा isert_conn, kref);

	isert_info("conn %p final kref %s/%d\n", isert_conn, current->comm,
		   current->pid);

	isert_connect_release(isert_conn);
पूर्ण

अटल व्योम
isert_put_conn(काष्ठा isert_conn *isert_conn)
अणु
	kref_put(&isert_conn->kref, isert_release_kref);
पूर्ण

अटल व्योम
isert_handle_unbound_conn(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा isert_np *isert_np = isert_conn->cm_id->context;

	mutex_lock(&isert_np->mutex);
	अगर (!list_empty(&isert_conn->node)) अणु
		/*
		 * This means iscsi करोesn't know this connection
		 * so schedule a cleanup ourselves
		 */
		list_del_init(&isert_conn->node);
		isert_put_conn(isert_conn);
		queue_work(isert_release_wq, &isert_conn->release_work);
	पूर्ण
	mutex_unlock(&isert_np->mutex);
पूर्ण

/**
 * isert_conn_terminate() - Initiate connection termination
 * @isert_conn: isert connection काष्ठा
 *
 * Notes:
 * In हाल the connection state is BOUND, move state
 * to TEMINATING and start tearकरोwn sequence (rdma_disconnect).
 * In हाल the connection state is UP, complete flush as well.
 *
 * This routine must be called with mutex held. Thus it is
 * safe to call multiple बार.
 */
अटल व्योम
isert_conn_terminate(काष्ठा isert_conn *isert_conn)
अणु
	पूर्णांक err;

	अगर (isert_conn->state >= ISER_CONN_TERMINATING)
		वापस;

	isert_info("Terminating conn %p state %d\n",
		   isert_conn, isert_conn->state);
	isert_conn->state = ISER_CONN_TERMINATING;
	err = rdma_disconnect(isert_conn->cm_id);
	अगर (err)
		isert_warn("Failed rdma_disconnect isert_conn %p\n",
			   isert_conn);
पूर्ण

अटल पूर्णांक
isert_np_cma_handler(काष्ठा isert_np *isert_np,
		     क्रमागत rdma_cm_event_type event)
अणु
	isert_dbg("%s (%d): isert np %p\n",
		  rdma_event_msg(event), event, isert_np);

	चयन (event) अणु
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		isert_np->cm_id = शून्य;
		अवरोध;
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
		isert_np->cm_id = isert_setup_id(isert_np);
		अगर (IS_ERR(isert_np->cm_id)) अणु
			isert_err("isert np %p setup id failed: %ld\n",
				  isert_np, PTR_ERR(isert_np->cm_id));
			isert_np->cm_id = शून्य;
		पूर्ण
		अवरोध;
	शेष:
		isert_err("isert np %p Unexpected event %d\n",
			  isert_np, event);
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
isert_disconnected_handler(काष्ठा rdma_cm_id *cma_id,
			   क्रमागत rdma_cm_event_type event)
अणु
	काष्ठा isert_conn *isert_conn = cma_id->qp->qp_context;

	mutex_lock(&isert_conn->mutex);
	चयन (isert_conn->state) अणु
	हाल ISER_CONN_TERMINATING:
		अवरोध;
	हाल ISER_CONN_UP:
		isert_conn_terminate(isert_conn);
		ib_drain_qp(isert_conn->qp);
		isert_handle_unbound_conn(isert_conn);
		अवरोध;
	हाल ISER_CONN_BOUND:
	हाल ISER_CONN_FULL_FEATURE: /* FALLTHRU */
		iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		अवरोध;
	शेष:
		isert_warn("conn %p terminating in state %d\n",
			   isert_conn, isert_conn->state);
	पूर्ण
	mutex_unlock(&isert_conn->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
isert_connect_error(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा isert_conn *isert_conn = cma_id->qp->qp_context;

	ib_drain_qp(isert_conn->qp);
	list_del_init(&isert_conn->node);
	isert_conn->cm_id = शून्य;
	isert_put_conn(isert_conn);

	वापस -1;
पूर्ण

अटल पूर्णांक
isert_cma_handler(काष्ठा rdma_cm_id *cma_id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा isert_np *isert_np = cma_id->context;
	काष्ठा isert_conn *isert_conn;
	पूर्णांक ret = 0;

	isert_info("%s (%d): status %d id %p np %p\n",
		   rdma_event_msg(event->event), event->event,
		   event->status, cma_id, cma_id->context);

	अगर (isert_np->cm_id == cma_id)
		वापस isert_np_cma_handler(cma_id->context, event->event);

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = isert_connect_request(cma_id, event);
		अगर (ret)
			isert_err("failed handle connect request %d\n", ret);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		isert_connected_handler(cma_id);
		अवरोध;
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:  /* FALLTHRU */
		ret = isert_disconnected_handler(cma_id, event->event);
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		isert_conn = cma_id->qp->qp_context;
		isert_conn->dev_हटाओd = true;
		isert_disconnected_handler(cma_id, event->event);
		रुको_event_पूर्णांकerruptible(isert_conn->rem_रुको,
					 isert_conn->state == ISER_CONN_DOWN);
		kमुक्त(isert_conn);
		/*
		 * वापस non-zero from the callback to destroy
		 * the rdma cm id
		 */
		वापस 1;
	हाल RDMA_CM_EVENT_REJECTED:
		isert_info("Connection rejected: %s\n",
			   rdma_reject_msg(cma_id, event->status));
		fallthrough;
	हाल RDMA_CM_EVENT_UNREACHABLE:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
		ret = isert_connect_error(cma_id);
		अवरोध;
	शेष:
		isert_err("Unhandled RDMA CMA event: %d\n", event->event);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_post_recvm(काष्ठा isert_conn *isert_conn, u32 count)
अणु
	काष्ठा ib_recv_wr *rx_wr;
	पूर्णांक i, ret;
	काष्ठा iser_rx_desc *rx_desc;

	क्रम (rx_wr = isert_conn->rx_wr, i = 0; i < count; i++, rx_wr++) अणु
		rx_desc = &isert_conn->rx_descs[i];

		rx_wr->wr_cqe = &rx_desc->rx_cqe;
		rx_wr->sg_list = &rx_desc->rx_sg;
		rx_wr->num_sge = 1;
		rx_wr->next = rx_wr + 1;
		rx_desc->in_use = false;
	पूर्ण
	rx_wr--;
	rx_wr->next = शून्य; /* mark end of work requests list */

	ret = ib_post_recv(isert_conn->qp, isert_conn->rx_wr, शून्य);
	अगर (ret)
		isert_err("ib_post_recv() failed with ret: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_post_recv(काष्ठा isert_conn *isert_conn, काष्ठा iser_rx_desc *rx_desc)
अणु
	काष्ठा ib_recv_wr rx_wr;
	पूर्णांक ret;

	अगर (!rx_desc->in_use) अणु
		/*
		 * अगर the descriptor is not in-use we alपढ़ोy reposted it
		 * क्रम recv, so just silently वापस
		 */
		वापस 0;
	पूर्ण

	rx_desc->in_use = false;
	rx_wr.wr_cqe = &rx_desc->rx_cqe;
	rx_wr.sg_list = &rx_desc->rx_sg;
	rx_wr.num_sge = 1;
	rx_wr.next = शून्य;

	ret = ib_post_recv(isert_conn->qp, &rx_wr, शून्य);
	अगर (ret)
		isert_err("ib_post_recv() failed with ret: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_login_post_send(काष्ठा isert_conn *isert_conn, काष्ठा iser_tx_desc *tx_desc)
अणु
	काष्ठा ib_device *ib_dev = isert_conn->cm_id->device;
	काष्ठा ib_send_wr send_wr;
	पूर्णांक ret;

	ib_dma_sync_single_क्रम_device(ib_dev, tx_desc->dma_addr,
				      ISER_HEADERS_LEN, DMA_TO_DEVICE);

	tx_desc->tx_cqe.करोne = isert_login_send_करोne;

	send_wr.next	= शून्य;
	send_wr.wr_cqe	= &tx_desc->tx_cqe;
	send_wr.sg_list	= tx_desc->tx_sg;
	send_wr.num_sge	= tx_desc->num_sge;
	send_wr.opcode	= IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(isert_conn->qp, &send_wr, शून्य);
	अगर (ret)
		isert_err("ib_post_send() failed, ret: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम
__isert_create_send_desc(काष्ठा isert_device *device,
			 काष्ठा iser_tx_desc *tx_desc)
अणु

	स_रखो(&tx_desc->iser_header, 0, माप(काष्ठा iser_ctrl));
	tx_desc->iser_header.flags = ISCSI_CTRL;

	tx_desc->num_sge = 1;

	अगर (tx_desc->tx_sg[0].lkey != device->pd->local_dma_lkey) अणु
		tx_desc->tx_sg[0].lkey = device->pd->local_dma_lkey;
		isert_dbg("tx_desc %p lkey mismatch, fixing\n", tx_desc);
	पूर्ण
पूर्ण

अटल व्योम
isert_create_send_desc(काष्ठा isert_conn *isert_conn,
		       काष्ठा isert_cmd *isert_cmd,
		       काष्ठा iser_tx_desc *tx_desc)
अणु
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;

	ib_dma_sync_single_क्रम_cpu(ib_dev, tx_desc->dma_addr,
				   ISER_HEADERS_LEN, DMA_TO_DEVICE);

	__isert_create_send_desc(device, tx_desc);
पूर्ण

अटल पूर्णांक
isert_init_tx_hdrs(काष्ठा isert_conn *isert_conn,
		   काष्ठा iser_tx_desc *tx_desc)
अणु
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;
	u64 dma_addr;

	dma_addr = ib_dma_map_single(ib_dev, (व्योम *)tx_desc,
			ISER_HEADERS_LEN, DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(ib_dev, dma_addr)) अणु
		isert_err("ib_dma_mapping_error() failed\n");
		वापस -ENOMEM;
	पूर्ण

	tx_desc->dma_addr = dma_addr;
	tx_desc->tx_sg[0].addr	= tx_desc->dma_addr;
	tx_desc->tx_sg[0].length = ISER_HEADERS_LEN;
	tx_desc->tx_sg[0].lkey = device->pd->local_dma_lkey;

	isert_dbg("Setup tx_sg[0].addr: 0x%llx length: %u lkey: 0x%x\n",
		  tx_desc->tx_sg[0].addr, tx_desc->tx_sg[0].length,
		  tx_desc->tx_sg[0].lkey);

	वापस 0;
पूर्ण

अटल व्योम
isert_init_send_wr(काष्ठा isert_conn *isert_conn, काष्ठा isert_cmd *isert_cmd,
		   काष्ठा ib_send_wr *send_wr)
अणु
	काष्ठा iser_tx_desc *tx_desc = &isert_cmd->tx_desc;

	tx_desc->tx_cqe.करोne = isert_send_करोne;
	send_wr->wr_cqe = &tx_desc->tx_cqe;

	अगर (isert_conn->snd_w_inv && isert_cmd->inv_rkey) अणु
		send_wr->opcode  = IB_WR_SEND_WITH_INV;
		send_wr->ex.invalidate_rkey = isert_cmd->inv_rkey;
	पूर्ण अन्यथा अणु
		send_wr->opcode = IB_WR_SEND;
	पूर्ण

	send_wr->sg_list = &tx_desc->tx_sg[0];
	send_wr->num_sge = isert_cmd->tx_desc.num_sge;
	send_wr->send_flags = IB_SEND_SIGNALED;
पूर्ण

अटल पूर्णांक
isert_login_post_recv(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा ib_recv_wr rx_wr;
	काष्ठा ib_sge sge;
	पूर्णांक ret;

	स_रखो(&sge, 0, माप(काष्ठा ib_sge));
	sge.addr = isert_conn->login_desc->dma_addr +
		isert_get_hdr_offset(isert_conn->login_desc);
	sge.length = ISER_RX_PAYLOAD_SIZE;
	sge.lkey = isert_conn->device->pd->local_dma_lkey;

	isert_dbg("Setup sge: addr: %llx length: %d 0x%08x\n",
		sge.addr, sge.length, sge.lkey);

	isert_conn->login_desc->rx_cqe.करोne = isert_login_recv_करोne;

	स_रखो(&rx_wr, 0, माप(काष्ठा ib_recv_wr));
	rx_wr.wr_cqe = &isert_conn->login_desc->rx_cqe;
	rx_wr.sg_list = &sge;
	rx_wr.num_sge = 1;

	ret = ib_post_recv(isert_conn->qp, &rx_wr, शून्य);
	अगर (ret)
		isert_err("ib_post_recv() failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_put_login_tx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login,
		   u32 length)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;
	काष्ठा iser_tx_desc *tx_desc = &isert_conn->login_tx_desc;
	पूर्णांक ret;

	__isert_create_send_desc(device, tx_desc);

	स_नकल(&tx_desc->iscsi_header, &login->rsp[0],
	       माप(काष्ठा iscsi_hdr));

	isert_init_tx_hdrs(isert_conn, tx_desc);

	अगर (length > 0) अणु
		काष्ठा ib_sge *tx_dsg = &tx_desc->tx_sg[1];

		ib_dma_sync_single_क्रम_cpu(ib_dev, isert_conn->login_rsp_dma,
					   length, DMA_TO_DEVICE);

		स_नकल(isert_conn->login_rsp_buf, login->rsp_buf, length);

		ib_dma_sync_single_क्रम_device(ib_dev, isert_conn->login_rsp_dma,
					      length, DMA_TO_DEVICE);

		tx_dsg->addr	= isert_conn->login_rsp_dma;
		tx_dsg->length	= length;
		tx_dsg->lkey	= isert_conn->device->pd->local_dma_lkey;
		tx_desc->num_sge = 2;
	पूर्ण
	अगर (!login->login_failed) अणु
		अगर (login->login_complete) अणु
			ret = isert_alloc_rx_descriptors(isert_conn);
			अगर (ret)
				वापस ret;

			ret = isert_post_recvm(isert_conn,
					       ISERT_QP_MAX_RECV_DTOS);
			अगर (ret)
				वापस ret;

			/* Now we are in FULL_FEATURE phase */
			mutex_lock(&isert_conn->mutex);
			isert_conn->state = ISER_CONN_FULL_FEATURE;
			mutex_unlock(&isert_conn->mutex);
			जाओ post_send;
		पूर्ण

		ret = isert_login_post_recv(isert_conn);
		अगर (ret)
			वापस ret;
	पूर्ण
post_send:
	ret = isert_login_post_send(isert_conn, tx_desc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
isert_rx_login_req(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा iser_rx_desc *rx_desc = isert_conn->login_desc;
	पूर्णांक rx_buflen = isert_conn->login_req_len;
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_login *login = conn->conn_login;
	पूर्णांक size;

	isert_info("conn %p\n", isert_conn);

	WARN_ON_ONCE(!login);

	अगर (login->first_request) अणु
		काष्ठा iscsi_login_req *login_req =
			(काष्ठा iscsi_login_req *)isert_get_iscsi_hdr(rx_desc);
		/*
		 * Setup the initial iscsi_login values from the leading
		 * login request PDU.
		 */
		login->leading_connection = (!login_req->tsih) ? 1 : 0;
		login->current_stage =
			(login_req->flags & ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK)
			 >> 2;
		login->version_min	= login_req->min_version;
		login->version_max	= login_req->max_version;
		स_नकल(login->isid, login_req->isid, 6);
		login->cmd_sn		= be32_to_cpu(login_req->cmdsn);
		login->init_task_tag	= login_req->itt;
		login->initial_exp_statsn = be32_to_cpu(login_req->exp_statsn);
		login->cid		= be16_to_cpu(login_req->cid);
		login->tsih		= be16_to_cpu(login_req->tsih);
	पूर्ण

	स_नकल(&login->req[0], isert_get_iscsi_hdr(rx_desc), ISCSI_HDR_LEN);

	size = min(rx_buflen, MAX_KEY_VALUE_PAIRS);
	isert_dbg("Using login payload size: %d, rx_buflen: %d "
		  "MAX_KEY_VALUE_PAIRS: %d\n", size, rx_buflen,
		  MAX_KEY_VALUE_PAIRS);
	स_नकल(login->req_buf, isert_get_data(rx_desc), size);

	अगर (login->first_request) अणु
		complete(&isert_conn->login_comp);
		वापस;
	पूर्ण
	schedule_delayed_work(&conn->login_work, 0);
पूर्ण

अटल काष्ठा iscsi_cmd
*isert_allocate_cmd(काष्ठा iscsi_conn *conn, काष्ठा iser_rx_desc *rx_desc)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा isert_cmd *isert_cmd;
	काष्ठा iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
	अगर (!cmd) अणु
		isert_err("Unable to allocate iscsi_cmd + isert_cmd\n");
		वापस शून्य;
	पूर्ण
	isert_cmd = iscsit_priv_cmd(cmd);
	isert_cmd->conn = isert_conn;
	isert_cmd->iscsi_cmd = cmd;
	isert_cmd->rx_desc = rx_desc;

	वापस cmd;
पूर्ण

अटल पूर्णांक
isert_handle_scsi_cmd(काष्ठा isert_conn *isert_conn,
		      काष्ठा isert_cmd *isert_cmd, काष्ठा iscsi_cmd *cmd,
		      काष्ठा iser_rx_desc *rx_desc, अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_scsi_req *hdr = (काष्ठा iscsi_scsi_req *)buf;
	पूर्णांक imm_data, imm_data_len, unsol_data, sg_nents, rc;
	bool dump_payload = false;
	अचिन्हित पूर्णांक data_len;

	rc = iscsit_setup_scsi_cmd(conn, cmd, buf);
	अगर (rc < 0)
		वापस rc;

	imm_data = cmd->immediate_data;
	imm_data_len = cmd->first_burst_len;
	unsol_data = cmd->unsolicited_data;
	data_len = cmd->se_cmd.data_length;

	अगर (imm_data && imm_data_len == data_len)
		cmd->se_cmd.se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	rc = iscsit_process_scsi_cmd(conn, cmd, hdr);
	अगर (rc < 0) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (rc > 0) अणु
		dump_payload = true;
		जाओ sequence_cmd;
	पूर्ण

	अगर (!imm_data)
		वापस 0;

	अगर (imm_data_len != data_len) अणु
		sg_nents = max(1UL, DIV_ROUND_UP(imm_data_len, PAGE_SIZE));
		sg_copy_from_buffer(cmd->se_cmd.t_data_sg, sg_nents,
				    isert_get_data(rx_desc), imm_data_len);
		isert_dbg("Copy Immediate sg_nents: %u imm_data_len: %d\n",
			  sg_nents, imm_data_len);
	पूर्ण अन्यथा अणु
		sg_init_table(&isert_cmd->sg, 1);
		cmd->se_cmd.t_data_sg = &isert_cmd->sg;
		cmd->se_cmd.t_data_nents = 1;
		sg_set_buf(&isert_cmd->sg, isert_get_data(rx_desc),
				imm_data_len);
		isert_dbg("Transfer Immediate imm_data_len: %d\n",
			  imm_data_len);
	पूर्ण

	cmd->ग_लिखो_data_करोne += imm_data_len;

	अगर (cmd->ग_लिखो_data_करोne == cmd->se_cmd.data_length) अणु
		spin_lock_bh(&cmd->istate_lock);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);
	पूर्ण

sequence_cmd:
	rc = iscsit_sequence_cmd(conn, cmd, buf, hdr->cmdsn);

	अगर (!rc && !dump_payload && unsol_data)
		iscsit_set_unsolicited_dataout(cmd);
	अन्यथा अगर (dump_payload && imm_data)
		target_put_sess_cmd(&cmd->se_cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक
isert_handle_iscsi_dataout(काष्ठा isert_conn *isert_conn,
			   काष्ठा iser_rx_desc *rx_desc, अचिन्हित अक्षर *buf)
अणु
	काष्ठा scatterlist *sg_start;
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_cmd *cmd = शून्य;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *)buf;
	u32 unsol_data_len = ntoh24(hdr->dlength);
	पूर्णांक rc, sg_nents, sg_off, page_off;

	rc = iscsit_check_dataout_hdr(conn, buf, &cmd);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (!cmd)
		वापस 0;
	/*
	 * FIXME: Unexpected unsolicited_data out
	 */
	अगर (!cmd->unsolicited_data) अणु
		isert_err("Received unexpected solicited data payload\n");
		dump_stack();
		वापस -1;
	पूर्ण

	isert_dbg("Unsolicited DataOut unsol_data_len: %u, "
		  "write_data_done: %u, data_length: %u\n",
		  unsol_data_len,  cmd->ग_लिखो_data_करोne,
		  cmd->se_cmd.data_length);

	sg_off = cmd->ग_लिखो_data_करोne / PAGE_SIZE;
	sg_start = &cmd->se_cmd.t_data_sg[sg_off];
	sg_nents = max(1UL, DIV_ROUND_UP(unsol_data_len, PAGE_SIZE));
	page_off = cmd->ग_लिखो_data_करोne % PAGE_SIZE;
	/*
	 * FIXME: Non page-aligned unsolicited_data out
	 */
	अगर (page_off) अणु
		isert_err("unexpected non-page aligned data payload\n");
		dump_stack();
		वापस -1;
	पूर्ण
	isert_dbg("Copying DataOut: sg_start: %p, sg_off: %u "
		  "sg_nents: %u from %p %u\n", sg_start, sg_off,
		  sg_nents, isert_get_data(rx_desc), unsol_data_len);

	sg_copy_from_buffer(sg_start, sg_nents, isert_get_data(rx_desc),
			    unsol_data_len);

	rc = iscsit_check_dataout_payload(cmd, hdr, false);
	अगर (rc < 0)
		वापस rc;

	/*
	 * multiple data-outs on the same command can arrive -
	 * so post the buffer beक्रमe hand
	 */
	वापस isert_post_recv(isert_conn, rx_desc);
पूर्ण

अटल पूर्णांक
isert_handle_nop_out(काष्ठा isert_conn *isert_conn, काष्ठा isert_cmd *isert_cmd,
		     काष्ठा iscsi_cmd *cmd, काष्ठा iser_rx_desc *rx_desc,
		     अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_nopout *hdr = (काष्ठा iscsi_nopout *)buf;
	पूर्णांक rc;

	rc = iscsit_setup_nop_out(conn, cmd, hdr);
	अगर (rc < 0)
		वापस rc;
	/*
	 * FIXME: Add support क्रम NOPOUT payload using unsolicited RDMA payload
	 */

	वापस iscsit_process_nop_out(conn, cmd, hdr);
पूर्ण

अटल पूर्णांक
isert_handle_text_cmd(काष्ठा isert_conn *isert_conn, काष्ठा isert_cmd *isert_cmd,
		      काष्ठा iscsi_cmd *cmd, काष्ठा iser_rx_desc *rx_desc,
		      काष्ठा iscsi_text *hdr)
अणु
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	u32 payload_length = ntoh24(hdr->dlength);
	पूर्णांक rc;
	अचिन्हित अक्षर *text_in = शून्य;

	rc = iscsit_setup_text_cmd(conn, cmd, hdr);
	अगर (rc < 0)
		वापस rc;

	अगर (payload_length) अणु
		text_in = kzalloc(payload_length, GFP_KERNEL);
		अगर (!text_in)
			वापस -ENOMEM;
	पूर्ण
	cmd->text_in_ptr = text_in;

	स_नकल(cmd->text_in_ptr, isert_get_data(rx_desc), payload_length);

	वापस iscsit_process_text_cmd(conn, cmd, hdr);
पूर्ण

अटल पूर्णांक
isert_rx_opcode(काष्ठा isert_conn *isert_conn, काष्ठा iser_rx_desc *rx_desc,
		uपूर्णांक32_t पढ़ो_stag, uपूर्णांक64_t पढ़ो_va,
		uपूर्णांक32_t ग_लिखो_stag, uपूर्णांक64_t ग_लिखो_va)
अणु
	काष्ठा iscsi_hdr *hdr = isert_get_iscsi_hdr(rx_desc);
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_cmd *cmd;
	काष्ठा isert_cmd *isert_cmd;
	पूर्णांक ret = -EINVAL;
	u8 opcode = (hdr->opcode & ISCSI_OPCODE_MASK);

	अगर (conn->sess->sess_ops->SessionType &&
	   (!(opcode & ISCSI_OP_TEXT) || !(opcode & ISCSI_OP_LOGOUT))) अणु
		isert_err("Got illegal opcode: 0x%02x in SessionType=Discovery,"
			  " ignoring\n", opcode);
		वापस 0;
	पूर्ण

	चयन (opcode) अणु
	हाल ISCSI_OP_SCSI_CMD:
		cmd = isert_allocate_cmd(conn, rx_desc);
		अगर (!cmd)
			अवरोध;

		isert_cmd = iscsit_priv_cmd(cmd);
		isert_cmd->पढ़ो_stag = पढ़ो_stag;
		isert_cmd->पढ़ो_va = पढ़ो_va;
		isert_cmd->ग_लिखो_stag = ग_लिखो_stag;
		isert_cmd->ग_लिखो_va = ग_लिखो_va;
		isert_cmd->inv_rkey = पढ़ो_stag ? पढ़ो_stag : ग_लिखो_stag;

		ret = isert_handle_scsi_cmd(isert_conn, isert_cmd, cmd,
					rx_desc, (अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_NOOP_OUT:
		cmd = isert_allocate_cmd(conn, rx_desc);
		अगर (!cmd)
			अवरोध;

		isert_cmd = iscsit_priv_cmd(cmd);
		ret = isert_handle_nop_out(isert_conn, isert_cmd, cmd,
					   rx_desc, (अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_SCSI_DATA_OUT:
		ret = isert_handle_iscsi_dataout(isert_conn, rx_desc,
						(अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		cmd = isert_allocate_cmd(conn, rx_desc);
		अगर (!cmd)
			अवरोध;

		ret = iscsit_handle_task_mgt_cmd(conn, cmd,
						(अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_LOGOUT:
		cmd = isert_allocate_cmd(conn, rx_desc);
		अगर (!cmd)
			अवरोध;

		ret = iscsit_handle_logout_cmd(conn, cmd, (अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_TEXT:
		अगर (be32_to_cpu(hdr->ttt) != 0xFFFFFFFF)
			cmd = iscsit_find_cmd_from_itt(conn, hdr->itt);
		अन्यथा
			cmd = isert_allocate_cmd(conn, rx_desc);

		अगर (!cmd)
			अवरोध;

		isert_cmd = iscsit_priv_cmd(cmd);
		ret = isert_handle_text_cmd(isert_conn, isert_cmd, cmd,
					    rx_desc, (काष्ठा iscsi_text *)hdr);
		अवरोध;
	शेष:
		isert_err("Got unknown iSCSI OpCode: 0x%02x\n", opcode);
		dump_stack();
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
isert_prपूर्णांक_wc(काष्ठा ib_wc *wc, स्थिर अक्षर *type)
अणु
	अगर (wc->status != IB_WC_WR_FLUSH_ERR)
		isert_err("%s failure: %s (%d) vend_err %x\n", type,
			  ib_wc_status_msg(wc->status), wc->status,
			  wc->venकरोr_err);
	अन्यथा
		isert_dbg("%s failure: %s (%d)\n", type,
			  ib_wc_status_msg(wc->status), wc->status);
पूर्ण

अटल व्योम
isert_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा ib_device *ib_dev = isert_conn->cm_id->device;
	काष्ठा iser_rx_desc *rx_desc = cqe_to_rx_desc(wc->wr_cqe);
	काष्ठा iscsi_hdr *hdr = isert_get_iscsi_hdr(rx_desc);
	काष्ठा iser_ctrl *iser_ctrl = isert_get_iser_hdr(rx_desc);
	uपूर्णांक64_t पढ़ो_va = 0, ग_लिखो_va = 0;
	uपूर्णांक32_t पढ़ो_stag = 0, ग_लिखो_stag = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "recv");
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		वापस;
	पूर्ण

	rx_desc->in_use = true;

	ib_dma_sync_single_क्रम_cpu(ib_dev, rx_desc->dma_addr,
			ISER_RX_SIZE, DMA_FROM_DEVICE);

	isert_dbg("DMA: 0x%llx, iSCSI opcode: 0x%02x, ITT: 0x%08x, flags: 0x%02x dlen: %d\n",
		 rx_desc->dma_addr, hdr->opcode, hdr->itt, hdr->flags,
		 (पूर्णांक)(wc->byte_len - ISER_HEADERS_LEN));

	चयन (iser_ctrl->flags & 0xF0) अणु
	हाल ISCSI_CTRL:
		अगर (iser_ctrl->flags & ISER_RSV) अणु
			पढ़ो_stag = be32_to_cpu(iser_ctrl->पढ़ो_stag);
			पढ़ो_va = be64_to_cpu(iser_ctrl->पढ़ो_va);
			isert_dbg("ISER_RSV: read_stag: 0x%x read_va: 0x%llx\n",
				  पढ़ो_stag, (अचिन्हित दीर्घ दीर्घ)पढ़ो_va);
		पूर्ण
		अगर (iser_ctrl->flags & ISER_WSV) अणु
			ग_लिखो_stag = be32_to_cpu(iser_ctrl->ग_लिखो_stag);
			ग_लिखो_va = be64_to_cpu(iser_ctrl->ग_लिखो_va);
			isert_dbg("ISER_WSV: write_stag: 0x%x write_va: 0x%llx\n",
				  ग_लिखो_stag, (अचिन्हित दीर्घ दीर्घ)ग_लिखो_va);
		पूर्ण

		isert_dbg("ISER ISCSI_CTRL PDU\n");
		अवरोध;
	हाल ISER_HELLO:
		isert_err("iSER Hello message\n");
		अवरोध;
	शेष:
		isert_warn("Unknown iSER hdr flags: 0x%02x\n", iser_ctrl->flags);
		अवरोध;
	पूर्ण

	isert_rx_opcode(isert_conn, rx_desc,
			पढ़ो_stag, पढ़ो_va, ग_लिखो_stag, ग_लिखो_va);

	ib_dma_sync_single_क्रम_device(ib_dev, rx_desc->dma_addr,
			ISER_RX_SIZE, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम
isert_login_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा ib_device *ib_dev = isert_conn->device->ib_device;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "login recv");
		वापस;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(ib_dev, isert_conn->login_desc->dma_addr,
			ISER_RX_SIZE, DMA_FROM_DEVICE);

	isert_conn->login_req_len = wc->byte_len - ISER_HEADERS_LEN;

	अगर (isert_conn->conn) अणु
		काष्ठा iscsi_login *login = isert_conn->conn->conn_login;

		अगर (login && !login->first_request)
			isert_rx_login_req(isert_conn);
	पूर्ण

	mutex_lock(&isert_conn->mutex);
	complete(&isert_conn->login_req_comp);
	mutex_unlock(&isert_conn->mutex);

	ib_dma_sync_single_क्रम_device(ib_dev, isert_conn->login_desc->dma_addr,
				ISER_RX_SIZE, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम
isert_rdma_rw_ctx_destroy(काष्ठा isert_cmd *cmd, काष्ठा isert_conn *conn)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->iscsi_cmd->se_cmd;
	क्रमागत dma_data_direction dir = target_reverse_dma_direction(se_cmd);

	अगर (!cmd->rw.nr_ops)
		वापस;

	अगर (isert_prot_cmd(conn, se_cmd)) अणु
		rdma_rw_ctx_destroy_signature(&cmd->rw, conn->qp,
				conn->cm_id->port_num, se_cmd->t_data_sg,
				se_cmd->t_data_nents, se_cmd->t_prot_sg,
				se_cmd->t_prot_nents, dir);
	पूर्ण अन्यथा अणु
		rdma_rw_ctx_destroy(&cmd->rw, conn->qp, conn->cm_id->port_num,
				se_cmd->t_data_sg, se_cmd->t_data_nents, dir);
	पूर्ण

	cmd->rw.nr_ops = 0;
पूर्ण

अटल व्योम
isert_put_cmd(काष्ठा isert_cmd *isert_cmd, bool comp_err)
अणु
	काष्ठा iscsi_cmd *cmd = isert_cmd->iscsi_cmd;
	काष्ठा isert_conn *isert_conn = isert_cmd->conn;
	काष्ठा iscsi_conn *conn = isert_conn->conn;
	काष्ठा iscsi_text_rsp *hdr;

	isert_dbg("Cmd %p\n", isert_cmd);

	चयन (cmd->iscsi_opcode) अणु
	हाल ISCSI_OP_SCSI_CMD:
		spin_lock_bh(&conn->cmd_lock);
		अगर (!list_empty(&cmd->i_conn_node))
			list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
			iscsit_stop_dataout_समयr(cmd);
			/*
			 * Check क्रम special हाल during comp_err where
			 * WRITE_PENDING has been handed off from core,
			 * but requires an extra target_put_sess_cmd()
			 * beक्रमe transport_generic_मुक्त_cmd() below.
			 */
			अगर (comp_err &&
			    cmd->se_cmd.t_state == TRANSPORT_WRITE_PENDING) अणु
				काष्ठा se_cmd *se_cmd = &cmd->se_cmd;

				target_put_sess_cmd(se_cmd);
			पूर्ण
		पूर्ण

		isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);
		transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		spin_lock_bh(&conn->cmd_lock);
		अगर (!list_empty(&cmd->i_conn_node))
			list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
		अवरोध;
	हाल ISCSI_OP_REJECT:
	हाल ISCSI_OP_NOOP_OUT:
	हाल ISCSI_OP_TEXT:
		hdr = (काष्ठा iscsi_text_rsp *)&isert_cmd->tx_desc.iscsi_header;
		/* If the जारी bit is on, keep the command alive */
		अगर (hdr->flags & ISCSI_FLAG_TEXT_CONTINUE)
			अवरोध;

		spin_lock_bh(&conn->cmd_lock);
		अगर (!list_empty(&cmd->i_conn_node))
			list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		/*
		 * Handle special हाल क्रम REJECT when iscsi_add_reject*() has
		 * overwritten the original iscsi_opcode assignment, and the
		 * associated cmd->se_cmd needs to be released.
		 */
		अगर (cmd->se_cmd.se_tfo != शून्य) अणु
			isert_dbg("Calling transport_generic_free_cmd for 0x%02x\n",
				 cmd->iscsi_opcode);
			transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		iscsit_release_cmd(cmd);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
isert_unmap_tx_desc(काष्ठा iser_tx_desc *tx_desc, काष्ठा ib_device *ib_dev)
अणु
	अगर (tx_desc->dma_addr != 0) अणु
		isert_dbg("unmap single for tx_desc->dma_addr\n");
		ib_dma_unmap_single(ib_dev, tx_desc->dma_addr,
				    ISER_HEADERS_LEN, DMA_TO_DEVICE);
		tx_desc->dma_addr = 0;
	पूर्ण
पूर्ण

अटल व्योम
isert_completion_put(काष्ठा iser_tx_desc *tx_desc, काष्ठा isert_cmd *isert_cmd,
		     काष्ठा ib_device *ib_dev, bool comp_err)
अणु
	अगर (isert_cmd->pdu_buf_dma != 0) अणु
		isert_dbg("unmap single for isert_cmd->pdu_buf_dma\n");
		ib_dma_unmap_single(ib_dev, isert_cmd->pdu_buf_dma,
				    isert_cmd->pdu_buf_len, DMA_TO_DEVICE);
		isert_cmd->pdu_buf_dma = 0;
	पूर्ण

	isert_unmap_tx_desc(tx_desc, ib_dev);
	isert_put_cmd(isert_cmd, comp_err);
पूर्ण

अटल पूर्णांक
isert_check_pi_status(काष्ठा se_cmd *se_cmd, काष्ठा ib_mr *sig_mr)
अणु
	काष्ठा ib_mr_status mr_status;
	पूर्णांक ret;

	ret = ib_check_mr_status(sig_mr, IB_MR_CHECK_SIG_STATUS, &mr_status);
	अगर (ret) अणु
		isert_err("ib_check_mr_status failed, ret %d\n", ret);
		जाओ fail_mr_status;
	पूर्ण

	अगर (mr_status.fail_status & IB_MR_CHECK_SIG_STATUS) अणु
		u64 sec_offset_err;
		u32 block_size = se_cmd->se_dev->dev_attrib.block_size + 8;

		चयन (mr_status.sig_err.err_type) अणु
		हाल IB_SIG_BAD_GUARD:
			se_cmd->pi_err = TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED;
			अवरोध;
		हाल IB_SIG_BAD_REFTAG:
			se_cmd->pi_err = TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED;
			अवरोध;
		हाल IB_SIG_BAD_APPTAG:
			se_cmd->pi_err = TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED;
			अवरोध;
		पूर्ण
		sec_offset_err = mr_status.sig_err.sig_err_offset;
		करो_भाग(sec_offset_err, block_size);
		se_cmd->sense_info = sec_offset_err + se_cmd->t_task_lba;

		isert_err("PI error found type %d at sector 0x%llx "
			  "expected 0x%x vs actual 0x%x\n",
			  mr_status.sig_err.err_type,
			  (अचिन्हित दीर्घ दीर्घ)se_cmd->sense_info,
			  mr_status.sig_err.expected,
			  mr_status.sig_err.actual);
		ret = 1;
	पूर्ण

fail_mr_status:
	वापस ret;
पूर्ण

अटल व्योम
isert_rdma_ग_लिखो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा iser_tx_desc *desc = cqe_to_tx_desc(wc->wr_cqe);
	काष्ठा isert_cmd *isert_cmd = tx_desc_to_cmd(desc);
	काष्ठा se_cmd *cmd = &isert_cmd->iscsi_cmd->se_cmd;
	पूर्णांक ret = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "rdma write");
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		isert_completion_put(desc, isert_cmd, device->ib_device, true);
		वापस;
	पूर्ण

	isert_dbg("Cmd %p\n", isert_cmd);

	ret = isert_check_pi_status(cmd, isert_cmd->rw.reg->mr);
	isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);

	अगर (ret) अणु
		/*
		 * transport_generic_request_failure() expects to have
		 * plus two references to handle queue-full, so re-add
		 * one here as target-core will have alपढ़ोy dropped
		 * it after the first isert_put_datain() callback.
		 */
		kref_get(&cmd->cmd_kref);
		transport_generic_request_failure(cmd, cmd->pi_err);
	पूर्ण अन्यथा अणु
		/*
		 * XXX: isert_put_response() failure is not retried.
		 */
		ret = isert_put_response(isert_conn->conn, isert_cmd->iscsi_cmd);
		अगर (ret)
			pr_warn_ratelimited("isert_put_response() ret: %d\n", ret);
	पूर्ण
पूर्ण

अटल व्योम
isert_rdma_पढ़ो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा iser_tx_desc *desc = cqe_to_tx_desc(wc->wr_cqe);
	काष्ठा isert_cmd *isert_cmd = tx_desc_to_cmd(desc);
	काष्ठा iscsi_cmd *cmd = isert_cmd->iscsi_cmd;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	पूर्णांक ret = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "rdma read");
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		isert_completion_put(desc, isert_cmd, device->ib_device, true);
		वापस;
	पूर्ण

	isert_dbg("Cmd %p\n", isert_cmd);

	iscsit_stop_dataout_समयr(cmd);

	अगर (isert_prot_cmd(isert_conn, se_cmd))
		ret = isert_check_pi_status(se_cmd, isert_cmd->rw.reg->mr);
	isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);
	cmd->ग_लिखो_data_करोne = 0;

	isert_dbg("Cmd: %p RDMA_READ comp calling execute_cmd\n", isert_cmd);
	spin_lock_bh(&cmd->istate_lock);
	cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
	cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
	spin_unlock_bh(&cmd->istate_lock);

	/*
	 * transport_generic_request_failure() will drop the extra
	 * se_cmd->cmd_kref reference after T10-PI error, and handle
	 * any non-zero ->queue_status() callback error retries.
	 */
	अगर (ret)
		transport_generic_request_failure(se_cmd, se_cmd->pi_err);
	अन्यथा
		target_execute_cmd(se_cmd);
पूर्ण

अटल व्योम
isert_करो_control_comp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा isert_cmd *isert_cmd = container_of(work,
			काष्ठा isert_cmd, comp_work);
	काष्ठा isert_conn *isert_conn = isert_cmd->conn;
	काष्ठा ib_device *ib_dev = isert_conn->cm_id->device;
	काष्ठा iscsi_cmd *cmd = isert_cmd->iscsi_cmd;

	isert_dbg("Cmd %p i_state %d\n", isert_cmd, cmd->i_state);

	चयन (cmd->i_state) अणु
	हाल ISTATE_SEND_TASKMGTRSP:
		iscsit_पंचांगr_post_handler(cmd, cmd->conn);
		fallthrough;
	हाल ISTATE_SEND_REJECT:
	हाल ISTATE_SEND_TEXTRSP:
		cmd->i_state = ISTATE_SENT_STATUS;
		isert_completion_put(&isert_cmd->tx_desc, isert_cmd,
				     ib_dev, false);
		अवरोध;
	हाल ISTATE_SEND_LOGOUTRSP:
		iscsit_logout_post_handler(cmd, cmd->conn);
		अवरोध;
	शेष:
		isert_err("Unknown i_state %d\n", cmd->i_state);
		dump_stack();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
isert_login_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा ib_device *ib_dev = isert_conn->cm_id->device;
	काष्ठा iser_tx_desc *tx_desc = cqe_to_tx_desc(wc->wr_cqe);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "login send");
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
	पूर्ण

	isert_unmap_tx_desc(tx_desc, ib_dev);
पूर्ण

अटल व्योम
isert_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा isert_conn *isert_conn = wc->qp->qp_context;
	काष्ठा ib_device *ib_dev = isert_conn->cm_id->device;
	काष्ठा iser_tx_desc *tx_desc = cqe_to_tx_desc(wc->wr_cqe);
	काष्ठा isert_cmd *isert_cmd = tx_desc_to_cmd(tx_desc);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		isert_prपूर्णांक_wc(wc, "send");
		अगर (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		isert_completion_put(tx_desc, isert_cmd, ib_dev, true);
		वापस;
	पूर्ण

	isert_dbg("Cmd %p\n", isert_cmd);

	चयन (isert_cmd->iscsi_cmd->i_state) अणु
	हाल ISTATE_SEND_TASKMGTRSP:
	हाल ISTATE_SEND_LOGOUTRSP:
	हाल ISTATE_SEND_REJECT:
	हाल ISTATE_SEND_TEXTRSP:
		isert_unmap_tx_desc(tx_desc, ib_dev);

		INIT_WORK(&isert_cmd->comp_work, isert_करो_control_comp);
		queue_work(isert_comp_wq, &isert_cmd->comp_work);
		वापस;
	शेष:
		isert_cmd->iscsi_cmd->i_state = ISTATE_SENT_STATUS;
		isert_completion_put(tx_desc, isert_cmd, ib_dev, false);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
isert_post_response(काष्ठा isert_conn *isert_conn, काष्ठा isert_cmd *isert_cmd)
अणु
	पूर्णांक ret;

	ret = isert_post_recv(isert_conn, isert_cmd->rx_desc);
	अगर (ret)
		वापस ret;

	ret = ib_post_send(isert_conn->qp, &isert_cmd->tx_desc.send_wr, शून्य);
	अगर (ret) अणु
		isert_err("ib_post_send failed with %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
isert_put_response(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;
	काष्ठा iscsi_scsi_rsp *hdr = (काष्ठा iscsi_scsi_rsp *)
				&isert_cmd->tx_desc.iscsi_header;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_rsp_pdu(cmd, conn, true, hdr);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
	/*
	 * Attach SENSE DATA payload to iSCSI Response PDU
	 */
	अगर (cmd->se_cmd.sense_buffer &&
	    ((cmd->se_cmd.se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ||
	    (cmd->se_cmd.se_cmd_flags & SCF_EMULATED_TASK_SENSE))) अणु
		काष्ठा isert_device *device = isert_conn->device;
		काष्ठा ib_device *ib_dev = device->ib_device;
		काष्ठा ib_sge *tx_dsg = &isert_cmd->tx_desc.tx_sg[1];
		u32 padding, pdu_len;

		put_unaligned_be16(cmd->se_cmd.scsi_sense_length,
				   cmd->sense_buffer);
		cmd->se_cmd.scsi_sense_length += माप(__be16);

		padding = -(cmd->se_cmd.scsi_sense_length) & 3;
		hton24(hdr->dlength, (u32)cmd->se_cmd.scsi_sense_length);
		pdu_len = cmd->se_cmd.scsi_sense_length + padding;

		isert_cmd->pdu_buf_dma = ib_dma_map_single(ib_dev,
				(व्योम *)cmd->sense_buffer, pdu_len,
				DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(ib_dev, isert_cmd->pdu_buf_dma))
			वापस -ENOMEM;

		isert_cmd->pdu_buf_len = pdu_len;
		tx_dsg->addr	= isert_cmd->pdu_buf_dma;
		tx_dsg->length	= pdu_len;
		tx_dsg->lkey	= device->pd->local_dma_lkey;
		isert_cmd->tx_desc.num_sge = 2;
	पूर्ण

	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("Posting SCSI Response\n");

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल व्योम
isert_पातed_task(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;

	spin_lock_bh(&conn->cmd_lock);
	अगर (!list_empty(&cmd->i_conn_node))
		list_del_init(&cmd->i_conn_node);
	spin_unlock_bh(&conn->cmd_lock);

	अगर (cmd->data_direction == DMA_TO_DEVICE)
		iscsit_stop_dataout_समयr(cmd);
	isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);
पूर्ण

अटल क्रमागत target_prot_op
isert_get_sup_prot_ops(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा isert_device *device = isert_conn->device;

	अगर (conn->tpg->tpg_attrib.t10_pi) अणु
		अगर (device->pi_capable) अणु
			isert_info("conn %p PI offload enabled\n", isert_conn);
			isert_conn->pi_support = true;
			वापस TARGET_PROT_ALL;
		पूर्ण
	पूर्ण

	isert_info("conn %p PI offload disabled\n", isert_conn);
	isert_conn->pi_support = false;

	वापस TARGET_PROT_NORMAL;
पूर्ण

अटल पूर्णांक
isert_put_nopin(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
		bool nopout_response)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_nopin_rsp(cmd, conn, (काष्ठा iscsi_nopin *)
			       &isert_cmd->tx_desc.iscsi_header,
			       nopout_response);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting NOPIN Response\n", isert_conn);

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल पूर्णांक
isert_put_logout_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_logout_rsp(cmd, conn, (काष्ठा iscsi_logout_rsp *)
				&isert_cmd->tx_desc.iscsi_header);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting Logout Response\n", isert_conn);

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल पूर्णांक
isert_put_पंचांग_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_task_mgt_rsp(cmd, conn, (काष्ठा iscsi_पंचांग_rsp *)
				  &isert_cmd->tx_desc.iscsi_header);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting Task Management Response\n", isert_conn);

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल पूर्णांक
isert_put_reject(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;
	काष्ठा isert_device *device = isert_conn->device;
	काष्ठा ib_device *ib_dev = device->ib_device;
	काष्ठा ib_sge *tx_dsg = &isert_cmd->tx_desc.tx_sg[1];
	काष्ठा iscsi_reject *hdr =
		(काष्ठा iscsi_reject *)&isert_cmd->tx_desc.iscsi_header;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_reject(cmd, conn, hdr);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);

	hton24(hdr->dlength, ISCSI_HDR_LEN);
	isert_cmd->pdu_buf_dma = ib_dma_map_single(ib_dev,
			(व्योम *)cmd->buf_ptr, ISCSI_HDR_LEN,
			DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(ib_dev, isert_cmd->pdu_buf_dma))
		वापस -ENOMEM;
	isert_cmd->pdu_buf_len = ISCSI_HDR_LEN;
	tx_dsg->addr	= isert_cmd->pdu_buf_dma;
	tx_dsg->length	= ISCSI_HDR_LEN;
	tx_dsg->lkey	= device->pd->local_dma_lkey;
	isert_cmd->tx_desc.num_sge = 2;

	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting Reject\n", isert_conn);

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल पूर्णांक
isert_put_text_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;
	काष्ठा iscsi_text_rsp *hdr =
		(काष्ठा iscsi_text_rsp *)&isert_cmd->tx_desc.iscsi_header;
	u32 txt_rsp_len;
	पूर्णांक rc;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	rc = iscsit_build_text_rsp(cmd, conn, hdr, ISCSI_INFINIBAND);
	अगर (rc < 0)
		वापस rc;

	txt_rsp_len = rc;
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);

	अगर (txt_rsp_len) अणु
		काष्ठा isert_device *device = isert_conn->device;
		काष्ठा ib_device *ib_dev = device->ib_device;
		काष्ठा ib_sge *tx_dsg = &isert_cmd->tx_desc.tx_sg[1];
		व्योम *txt_rsp_buf = cmd->buf_ptr;

		isert_cmd->pdu_buf_dma = ib_dma_map_single(ib_dev,
				txt_rsp_buf, txt_rsp_len, DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(ib_dev, isert_cmd->pdu_buf_dma))
			वापस -ENOMEM;

		isert_cmd->pdu_buf_len = txt_rsp_len;
		tx_dsg->addr	= isert_cmd->pdu_buf_dma;
		tx_dsg->length	= txt_rsp_len;
		tx_dsg->lkey	= device->pd->local_dma_lkey;
		isert_cmd->tx_desc.num_sge = 2;
	पूर्ण
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Text Response\n", isert_conn);

	वापस isert_post_response(isert_conn, isert_cmd);
पूर्ण

अटल अंतरभूत व्योम
isert_set_dअगर_करोमुख्य(काष्ठा se_cmd *se_cmd, काष्ठा ib_sig_करोमुख्य *करोमुख्य)
अणु
	करोमुख्य->sig_type = IB_SIG_TYPE_T10_DIF;
	करोमुख्य->sig.dअगर.bg_type = IB_T10DIF_CRC;
	करोमुख्य->sig.dअगर.pi_पूर्णांकerval = se_cmd->se_dev->dev_attrib.block_size;
	करोमुख्य->sig.dअगर.ref_tag = se_cmd->reftag_seed;
	/*
	 * At the moment we hard code those, but अगर in the future
	 * the target core would like to use it, we will take it
	 * from se_cmd.
	 */
	करोमुख्य->sig.dअगर.apptag_check_mask = 0xffff;
	करोमुख्य->sig.dअगर.app_escape = true;
	करोमुख्य->sig.dअगर.ref_escape = true;
	अगर (se_cmd->prot_type == TARGET_DIF_TYPE1_PROT ||
	    se_cmd->prot_type == TARGET_DIF_TYPE2_PROT)
		करोमुख्य->sig.dअगर.ref_remap = true;
पूर्ण

अटल पूर्णांक
isert_set_sig_attrs(काष्ठा se_cmd *se_cmd, काष्ठा ib_sig_attrs *sig_attrs)
अणु
	स_रखो(sig_attrs, 0, माप(*sig_attrs));

	चयन (se_cmd->prot_op) अणु
	हाल TARGET_PROT_DIN_INSERT:
	हाल TARGET_PROT_DOUT_STRIP:
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dअगर_करोमुख्य(se_cmd, &sig_attrs->wire);
		अवरोध;
	हाल TARGET_PROT_DOUT_INSERT:
	हाल TARGET_PROT_DIN_STRIP:
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dअगर_करोमुख्य(se_cmd, &sig_attrs->mem);
		अवरोध;
	हाल TARGET_PROT_DIN_PASS:
	हाल TARGET_PROT_DOUT_PASS:
		isert_set_dअगर_करोमुख्य(se_cmd, &sig_attrs->wire);
		isert_set_dअगर_करोमुख्य(se_cmd, &sig_attrs->mem);
		अवरोध;
	शेष:
		isert_err("Unsupported PI operation %d\n", se_cmd->prot_op);
		वापस -EINVAL;
	पूर्ण

	अगर (se_cmd->prot_checks & TARGET_DIF_CHECK_GUARD)
		sig_attrs->check_mask |= IB_SIG_CHECK_GUARD;
	अगर (se_cmd->prot_checks & TARGET_DIF_CHECK_APPTAG)
		sig_attrs->check_mask |= IB_SIG_CHECK_APPTAG;
	अगर (se_cmd->prot_checks & TARGET_DIF_CHECK_REFTAG)
		sig_attrs->check_mask |= IB_SIG_CHECK_REFTAG;

	वापस 0;
पूर्ण

अटल पूर्णांक
isert_rdma_rw_ctx_post(काष्ठा isert_cmd *cmd, काष्ठा isert_conn *conn,
		काष्ठा ib_cqe *cqe, काष्ठा ib_send_wr *chain_wr)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->iscsi_cmd->se_cmd;
	क्रमागत dma_data_direction dir = target_reverse_dma_direction(se_cmd);
	u8 port_num = conn->cm_id->port_num;
	u64 addr;
	u32 rkey, offset;
	पूर्णांक ret;

	अगर (cmd->ctx_init_करोne)
		जाओ rdma_ctx_post;

	अगर (dir == DMA_FROM_DEVICE) अणु
		addr = cmd->ग_लिखो_va;
		rkey = cmd->ग_लिखो_stag;
		offset = cmd->iscsi_cmd->ग_लिखो_data_करोne;
	पूर्ण अन्यथा अणु
		addr = cmd->पढ़ो_va;
		rkey = cmd->पढ़ो_stag;
		offset = 0;
	पूर्ण

	अगर (isert_prot_cmd(conn, se_cmd)) अणु
		काष्ठा ib_sig_attrs sig_attrs;

		ret = isert_set_sig_attrs(se_cmd, &sig_attrs);
		अगर (ret)
			वापस ret;

		WARN_ON_ONCE(offset);
		ret = rdma_rw_ctx_signature_init(&cmd->rw, conn->qp, port_num,
				se_cmd->t_data_sg, se_cmd->t_data_nents,
				se_cmd->t_prot_sg, se_cmd->t_prot_nents,
				&sig_attrs, addr, rkey, dir);
	पूर्ण अन्यथा अणु
		ret = rdma_rw_ctx_init(&cmd->rw, conn->qp, port_num,
				se_cmd->t_data_sg, se_cmd->t_data_nents,
				offset, addr, rkey, dir);
	पूर्ण

	अगर (ret < 0) अणु
		isert_err("Cmd: %p failed to prepare RDMA res\n", cmd);
		वापस ret;
	पूर्ण

	cmd->ctx_init_करोne = true;

rdma_ctx_post:
	ret = rdma_rw_ctx_post(&cmd->rw, conn->qp, port_num, cqe, chain_wr);
	अगर (ret < 0)
		isert_err("Cmd: %p failed to post RDMA res\n", cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक
isert_put_datain(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	काष्ठा isert_conn *isert_conn = conn->context;
	काष्ठा ib_cqe *cqe = शून्य;
	काष्ठा ib_send_wr *chain_wr = शून्य;
	पूर्णांक rc;

	isert_dbg("Cmd: %p RDMA_WRITE data_length: %u\n",
		 isert_cmd, se_cmd->data_length);

	अगर (isert_prot_cmd(isert_conn, se_cmd)) अणु
		isert_cmd->tx_desc.tx_cqe.करोne = isert_rdma_ग_लिखो_करोne;
		cqe = &isert_cmd->tx_desc.tx_cqe;
	पूर्ण अन्यथा अणु
		/*
		 * Build isert_conn->tx_desc क्रम iSCSI response PDU and attach
		 */
		isert_create_send_desc(isert_conn, isert_cmd,
				       &isert_cmd->tx_desc);
		iscsit_build_rsp_pdu(cmd, conn, true, (काष्ठा iscsi_scsi_rsp *)
				     &isert_cmd->tx_desc.iscsi_header);
		isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
		isert_init_send_wr(isert_conn, isert_cmd,
				   &isert_cmd->tx_desc.send_wr);

		rc = isert_post_recv(isert_conn, isert_cmd->rx_desc);
		अगर (rc)
			वापस rc;

		chain_wr = &isert_cmd->tx_desc.send_wr;
	पूर्ण

	rc = isert_rdma_rw_ctx_post(isert_cmd, isert_conn, cqe, chain_wr);
	isert_dbg("Cmd: %p posted RDMA_WRITE for iSER Data READ rc: %d\n",
		  isert_cmd, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक
isert_get_dataout(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd, bool recovery)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	पूर्णांक ret;

	isert_dbg("Cmd: %p RDMA_READ data_length: %u write_data_done: %u\n",
		 isert_cmd, cmd->se_cmd.data_length, cmd->ग_लिखो_data_करोne);

	isert_cmd->tx_desc.tx_cqe.करोne = isert_rdma_पढ़ो_करोne;
	ret = isert_rdma_rw_ctx_post(isert_cmd, conn->context,
				     &isert_cmd->tx_desc.tx_cqe, शून्य);

	isert_dbg("Cmd: %p posted RDMA_READ memory for ISER Data WRITE rc: %d\n",
		 isert_cmd, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
isert_immediate_queue(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd, पूर्णांक state)
अणु
	काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	पूर्णांक ret = 0;

	चयन (state) अणु
	हाल ISTATE_REMOVE:
		spin_lock_bh(&conn->cmd_lock);
		list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);
		isert_put_cmd(isert_cmd, true);
		अवरोध;
	हाल ISTATE_SEND_NOPIN_WANT_RESPONSE:
		ret = isert_put_nopin(cmd, conn, false);
		अवरोध;
	शेष:
		isert_err("Unknown immediate state: 0x%02x\n", state);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_response_queue(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd, पूर्णांक state)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;
	पूर्णांक ret;

	चयन (state) अणु
	हाल ISTATE_SEND_LOGOUTRSP:
		ret = isert_put_logout_rsp(cmd, conn);
		अगर (!ret)
			isert_conn->logout_posted = true;
		अवरोध;
	हाल ISTATE_SEND_NOPIN:
		ret = isert_put_nopin(cmd, conn, true);
		अवरोध;
	हाल ISTATE_SEND_TASKMGTRSP:
		ret = isert_put_पंचांग_rsp(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_REJECT:
		ret = isert_put_reject(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_TEXTRSP:
		ret = isert_put_text_rsp(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_STATUS:
		/*
		 * Special हाल क्रम sending non GOOD SCSI status from TX thपढ़ो
		 * context during pre se_cmd excecution failure.
		 */
		ret = isert_put_response(conn, cmd);
		अवरोध;
	शेष:
		isert_err("Unknown response state: 0x%02x\n", state);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा rdma_cm_id *
isert_setup_id(काष्ठा isert_np *isert_np)
अणु
	काष्ठा iscsi_np *np = isert_np->np;
	काष्ठा rdma_cm_id *id;
	काष्ठा sockaddr *sa;
	पूर्णांक ret;

	sa = (काष्ठा sockaddr *)&np->np_sockaddr;
	isert_dbg("ksockaddr: %p, sa: %p\n", &np->np_sockaddr, sa);

	id = rdma_create_id(&init_net, isert_cma_handler, isert_np,
			    RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(id)) अणु
		isert_err("rdma_create_id() failed: %ld\n", PTR_ERR(id));
		ret = PTR_ERR(id);
		जाओ out;
	पूर्ण
	isert_dbg("id %p context %p\n", id, id->context);

	ret = rdma_bind_addr(id, sa);
	अगर (ret) अणु
		isert_err("rdma_bind_addr() failed: %d\n", ret);
		जाओ out_id;
	पूर्ण

	ret = rdma_listen(id, 0);
	अगर (ret) अणु
		isert_err("rdma_listen() failed: %d\n", ret);
		जाओ out_id;
	पूर्ण

	वापस id;
out_id:
	rdma_destroy_id(id);
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक
isert_setup_np(काष्ठा iscsi_np *np,
	       काष्ठा sockaddr_storage *ksockaddr)
अणु
	काष्ठा isert_np *isert_np;
	काष्ठा rdma_cm_id *isert_lid;
	पूर्णांक ret;

	isert_np = kzalloc(माप(काष्ठा isert_np), GFP_KERNEL);
	अगर (!isert_np)
		वापस -ENOMEM;

	sema_init(&isert_np->sem, 0);
	mutex_init(&isert_np->mutex);
	INIT_LIST_HEAD(&isert_np->accepted);
	INIT_LIST_HEAD(&isert_np->pending);
	isert_np->np = np;

	/*
	 * Setup the np->np_sockaddr from the passed sockaddr setup
	 * in iscsi_target_configfs.c code..
	 */
	स_नकल(&np->np_sockaddr, ksockaddr,
	       माप(काष्ठा sockaddr_storage));

	isert_lid = isert_setup_id(isert_np);
	अगर (IS_ERR(isert_lid)) अणु
		ret = PTR_ERR(isert_lid);
		जाओ out;
	पूर्ण

	isert_np->cm_id = isert_lid;
	np->np_context = isert_np;

	वापस 0;

out:
	kमुक्त(isert_np);

	वापस ret;
पूर्ण

अटल पूर्णांक
isert_rdma_accept(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा rdma_cm_id *cm_id = isert_conn->cm_id;
	काष्ठा rdma_conn_param cp;
	पूर्णांक ret;
	काष्ठा iser_cm_hdr rsp_hdr;

	स_रखो(&cp, 0, माप(काष्ठा rdma_conn_param));
	cp.initiator_depth = isert_conn->initiator_depth;
	cp.retry_count = 7;
	cp.rnr_retry_count = 7;

	स_रखो(&rsp_hdr, 0, माप(rsp_hdr));
	rsp_hdr.flags = ISERT_ZBVA_NOT_USED;
	अगर (!isert_conn->snd_w_inv)
		rsp_hdr.flags = rsp_hdr.flags | ISERT_SEND_W_INV_NOT_USED;
	cp.निजी_data = (व्योम *)&rsp_hdr;
	cp.निजी_data_len = माप(rsp_hdr);

	ret = rdma_accept(cm_id, &cp);
	अगर (ret) अणु
		isert_err("rdma_accept() failed with: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
isert_get_login_rx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;
	पूर्णांक ret;

	isert_info("before login_req comp conn: %p\n", isert_conn);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&isert_conn->login_req_comp);
	अगर (ret) अणु
		isert_err("isert_conn %p interrupted before got login req\n",
			  isert_conn);
		वापस ret;
	पूर्ण
	reinit_completion(&isert_conn->login_req_comp);

	/*
	 * For login requests after the first PDU, isert_rx_login_req() will
	 * kick schedule_delayed_work(&conn->login_work) as the packet is
	 * received, which turns this callback from iscsi_target_करो_login_rx()
	 * पूर्णांकo a NOP.
	 */
	अगर (!login->first_request)
		वापस 0;

	isert_rx_login_req(isert_conn);

	isert_info("before login_comp conn: %p\n", conn);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&isert_conn->login_comp);
	अगर (ret)
		वापस ret;

	isert_info("processing login->req: %p\n", login->req);

	वापस 0;
पूर्ण

अटल व्योम
isert_set_conn_info(काष्ठा iscsi_np *np, काष्ठा iscsi_conn *conn,
		    काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा rdma_cm_id *cm_id = isert_conn->cm_id;
	काष्ठा rdma_route *cm_route = &cm_id->route;

	conn->login_family = np->np_sockaddr.ss_family;

	conn->login_sockaddr = cm_route->addr.dst_addr;
	conn->local_sockaddr = cm_route->addr.src_addr;
पूर्ण

अटल पूर्णांक
isert_accept_np(काष्ठा iscsi_np *np, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_np *isert_np = np->np_context;
	काष्ठा isert_conn *isert_conn;
	पूर्णांक ret;

accept_रुको:
	ret = करोwn_पूर्णांकerruptible(&isert_np->sem);
	अगर (ret)
		वापस -ENODEV;

	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (np->np_thपढ़ो_state >= ISCSI_NP_THREAD_RESET) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		isert_dbg("np_thread_state %d\n",
			 np->np_thपढ़ो_state);
		/**
		 * No poपूर्णांक in stalling here when np_thपढ़ो
		 * is in state RESET/SHUTDOWN/EXIT - bail
		 **/
		वापस -ENODEV;
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	mutex_lock(&isert_np->mutex);
	अगर (list_empty(&isert_np->pending)) अणु
		mutex_unlock(&isert_np->mutex);
		जाओ accept_रुको;
	पूर्ण
	isert_conn = list_first_entry(&isert_np->pending,
			काष्ठा isert_conn, node);
	list_del_init(&isert_conn->node);
	mutex_unlock(&isert_np->mutex);

	conn->context = isert_conn;
	isert_conn->conn = conn;
	isert_conn->state = ISER_CONN_BOUND;

	isert_set_conn_info(np, conn, isert_conn);

	isert_dbg("Processing isert_conn: %p\n", isert_conn);

	वापस 0;
पूर्ण

अटल व्योम
isert_मुक्त_np(काष्ठा iscsi_np *np)
अणु
	काष्ठा isert_np *isert_np = np->np_context;
	काष्ठा isert_conn *isert_conn, *n;

	अगर (isert_np->cm_id)
		rdma_destroy_id(isert_np->cm_id);

	/*
	 * FIXME: At this poपूर्णांक we करोn't have a good way to insure
	 * that at this poपूर्णांक we करोn't have hanging connections that
	 * completed RDMA establishment but didn't start iscsi login
	 * process. So work-around this by cleaning up what ever piled
	 * up in accepted and pending lists.
	 */
	mutex_lock(&isert_np->mutex);
	अगर (!list_empty(&isert_np->pending)) अणु
		isert_info("Still have isert pending connections\n");
		list_क्रम_each_entry_safe(isert_conn, n,
					 &isert_np->pending,
					 node) अणु
			isert_info("cleaning isert_conn %p state (%d)\n",
				   isert_conn, isert_conn->state);
			isert_connect_release(isert_conn);
		पूर्ण
	पूर्ण

	अगर (!list_empty(&isert_np->accepted)) अणु
		isert_info("Still have isert accepted connections\n");
		list_क्रम_each_entry_safe(isert_conn, n,
					 &isert_np->accepted,
					 node) अणु
			isert_info("cleaning isert_conn %p state (%d)\n",
				   isert_conn, isert_conn->state);
			isert_connect_release(isert_conn);
		पूर्ण
	पूर्ण
	mutex_unlock(&isert_np->mutex);

	np->np_context = शून्य;
	kमुक्त(isert_np);
पूर्ण

अटल व्योम isert_release_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा isert_conn *isert_conn = container_of(work,
						     काष्ठा isert_conn,
						     release_work);

	isert_info("Starting release conn %p\n", isert_conn);

	mutex_lock(&isert_conn->mutex);
	isert_conn->state = ISER_CONN_DOWN;
	mutex_unlock(&isert_conn->mutex);

	isert_info("Destroying conn %p\n", isert_conn);
	isert_put_conn(isert_conn);
पूर्ण

अटल व्योम
isert_रुको4logout(काष्ठा isert_conn *isert_conn)
अणु
	काष्ठा iscsi_conn *conn = isert_conn->conn;

	isert_info("conn %p\n", isert_conn);

	अगर (isert_conn->logout_posted) अणु
		isert_info("conn %p wait for conn_logout_comp\n", isert_conn);
		रुको_क्रम_completion_समयout(&conn->conn_logout_comp,
					    SECONDS_FOR_LOGOUT_COMP * HZ);
	पूर्ण
पूर्ण

अटल व्योम
isert_रुको4cmds(काष्ठा iscsi_conn *conn)
अणु
	isert_info("iscsi_conn %p\n", conn);

	अगर (conn->sess) अणु
		target_stop_session(conn->sess->se_sess);
		target_रुको_क्रम_sess_cmds(conn->sess->se_sess);
	पूर्ण
पूर्ण

/**
 * isert_put_unsol_pending_cmds() - Drop commands रुकोing क्रम
 *     unsolicitate dataout
 * @conn:    iscsi connection
 *
 * We might still have commands that are रुकोing क्रम unsolicited
 * dataouts messages. We must put the extra reference on those
 * beक्रमe blocking on the target_रुको_क्रम_session_cmds
 */
अटल व्योम
isert_put_unsol_pending_cmds(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd, *पंचांगp;
	अटल LIST_HEAD(drop_cmd_list);

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry_safe(cmd, पंचांगp, &conn->conn_cmd_list, i_conn_node) अणु
		अगर ((cmd->cmd_flags & ICF_NON_IMMEDIATE_UNSOLICITED_DATA) &&
		    (cmd->ग_लिखो_data_करोne < conn->sess->sess_ops->FirstBurstLength) &&
		    (cmd->ग_लिखो_data_करोne < cmd->se_cmd.data_length))
			list_move_tail(&cmd->i_conn_node, &drop_cmd_list);
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	list_क्रम_each_entry_safe(cmd, पंचांगp, &drop_cmd_list, i_conn_node) अणु
		list_del_init(&cmd->i_conn_node);
		अगर (cmd->i_state != ISTATE_REMOVE) अणु
			काष्ठा isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);

			isert_info("conn %p dropping cmd %p\n", conn, cmd);
			isert_put_cmd(isert_cmd, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम isert_रुको_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;

	isert_info("Starting conn %p\n", isert_conn);

	mutex_lock(&isert_conn->mutex);
	isert_conn_terminate(isert_conn);
	mutex_unlock(&isert_conn->mutex);

	ib_drain_qp(isert_conn->qp);
	isert_put_unsol_pending_cmds(conn);
	isert_रुको4cmds(conn);
	isert_रुको4logout(isert_conn);

	queue_work(isert_release_wq, &isert_conn->release_work);
पूर्ण

अटल व्योम isert_मुक्त_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा isert_conn *isert_conn = conn->context;

	ib_drain_qp(isert_conn->qp);
	isert_put_conn(isert_conn);
पूर्ण

अटल व्योम isert_get_rx_pdu(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा completion comp;

	init_completion(&comp);

	रुको_क्रम_completion_पूर्णांकerruptible(&comp);
पूर्ण

अटल काष्ठा iscsit_transport iser_target_transport = अणु
	.name			= "IB/iSER",
	.transport_type		= ISCSI_INFINIBAND,
	.rdma_shutकरोwn		= true,
	.priv_size		= माप(काष्ठा isert_cmd),
	.owner			= THIS_MODULE,
	.iscsit_setup_np	= isert_setup_np,
	.iscsit_accept_np	= isert_accept_np,
	.iscsit_मुक्त_np		= isert_मुक्त_np,
	.iscsit_रुको_conn	= isert_रुको_conn,
	.iscsit_मुक्त_conn	= isert_मुक्त_conn,
	.iscsit_get_login_rx	= isert_get_login_rx,
	.iscsit_put_login_tx	= isert_put_login_tx,
	.iscsit_immediate_queue	= isert_immediate_queue,
	.iscsit_response_queue	= isert_response_queue,
	.iscsit_get_dataout	= isert_get_dataout,
	.iscsit_queue_data_in	= isert_put_datain,
	.iscsit_queue_status	= isert_put_response,
	.iscsit_पातed_task	= isert_पातed_task,
	.iscsit_get_rx_pdu	= isert_get_rx_pdu,
	.iscsit_get_sup_prot_ops = isert_get_sup_prot_ops,
पूर्ण;

अटल पूर्णांक __init isert_init(व्योम)
अणु
	पूर्णांक ret;

	isert_comp_wq = alloc_workqueue("isert_comp_wq",
					WQ_UNBOUND | WQ_HIGHPRI, 0);
	अगर (!isert_comp_wq) अणु
		isert_err("Unable to allocate isert_comp_wq\n");
		वापस -ENOMEM;
	पूर्ण

	isert_release_wq = alloc_workqueue("isert_release_wq", WQ_UNBOUND,
					WQ_UNBOUND_MAX_ACTIVE);
	अगर (!isert_release_wq) अणु
		isert_err("Unable to allocate isert_release_wq\n");
		ret = -ENOMEM;
		जाओ destroy_comp_wq;
	पूर्ण

	iscsit_रेजिस्टर_transport(&iser_target_transport);
	isert_info("iSER_TARGET[0] - Loaded iser_target_transport\n");

	वापस 0;

destroy_comp_wq:
	destroy_workqueue(isert_comp_wq);

	वापस ret;
पूर्ण

अटल व्योम __निकास isert_निकास(व्योम)
अणु
	flush_scheduled_work();
	destroy_workqueue(isert_release_wq);
	destroy_workqueue(isert_comp_wq);
	iscsit_unरेजिस्टर_transport(&iser_target_transport);
	isert_info("iSER_TARGET[0] - Released iser_target_transport\n");
पूर्ण

MODULE_DESCRIPTION("iSER-Target for mainline target infrastructure");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(isert_init);
module_निकास(isert_निकास);
