<शैली गुरु>
/*
 * Copyright (c) 2004, 2005, 2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
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
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश "iscsi_iser.h"

#घोषणा ISCSI_ISER_MAX_CONN	8
#घोषणा ISER_MAX_RX_LEN		(ISER_QP_MAX_RECV_DTOS * ISCSI_ISER_MAX_CONN)
#घोषणा ISER_MAX_TX_LEN		(ISER_QP_MAX_REQ_DTOS  * ISCSI_ISER_MAX_CONN)
#घोषणा ISER_MAX_CQ_LEN		(ISER_MAX_RX_LEN + ISER_MAX_TX_LEN + \
				 ISCSI_ISER_MAX_CONN)

अटल व्योम iser_qp_event_callback(काष्ठा ib_event *cause, व्योम *context)
अणु
	iser_err("qp event %s (%d)\n",
		 ib_event_msg(cause->event), cause->event);
पूर्ण

अटल व्योम iser_event_handler(काष्ठा ib_event_handler *handler,
				काष्ठा ib_event *event)
अणु
	iser_err("async event %s (%d) on device %s port %d\n",
		 ib_event_msg(event->event), event->event,
		dev_name(&event->device->dev), event->element.port_num);
पूर्ण

/*
 * iser_create_device_ib_res - creates Protection Doमुख्य (PD), Completion
 * Queue (CQ), DMA Memory Region (DMA MR) with the device associated with
 * the adaptor.
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक iser_create_device_ib_res(काष्ठा iser_device *device)
अणु
	काष्ठा ib_device *ib_dev = device->ib_device;

	अगर (!(ib_dev->attrs.device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS)) अणु
		iser_err("IB device does not support memory registrations\n");
		वापस -1;
	पूर्ण

	device->pd = ib_alloc_pd(ib_dev,
		iser_always_reg ? 0 : IB_PD_UNSAFE_GLOBAL_RKEY);
	अगर (IS_ERR(device->pd))
		जाओ pd_err;

	INIT_IB_EVENT_HANDLER(&device->event_handler, ib_dev,
			      iser_event_handler);
	ib_रेजिस्टर_event_handler(&device->event_handler);
	वापस 0;

pd_err:
	iser_err("failed to allocate an IB resource\n");
	वापस -1;
पूर्ण

/*
 * iser_मुक्त_device_ib_res - destroy/dealloc/dereg the DMA MR,
 * CQ and PD created with the device associated with the adaptor.
 */
अटल व्योम iser_मुक्त_device_ib_res(काष्ठा iser_device *device)
अणु
	ib_unरेजिस्टर_event_handler(&device->event_handler);
	ib_dealloc_pd(device->pd);

	device->pd = शून्य;
पूर्ण

अटल काष्ठा iser_fr_desc *
iser_create_fastreg_desc(काष्ठा iser_device *device,
			 काष्ठा ib_pd *pd,
			 bool pi_enable,
			 अचिन्हित पूर्णांक size)
अणु
	काष्ठा iser_fr_desc *desc;
	काष्ठा ib_device *ib_dev = device->ib_device;
	क्रमागत ib_mr_type mr_type;
	पूर्णांक ret;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस ERR_PTR(-ENOMEM);

	अगर (ib_dev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		mr_type = IB_MR_TYPE_SG_GAPS;
	अन्यथा
		mr_type = IB_MR_TYPE_MEM_REG;

	desc->rsc.mr = ib_alloc_mr(pd, mr_type, size);
	अगर (IS_ERR(desc->rsc.mr)) अणु
		ret = PTR_ERR(desc->rsc.mr);
		iser_err("Failed to allocate ib_fast_reg_mr err=%d\n", ret);
		जाओ err_alloc_mr;
	पूर्ण

	अगर (pi_enable) अणु
		desc->rsc.sig_mr = ib_alloc_mr_पूर्णांकegrity(pd, size, size);
		अगर (IS_ERR(desc->rsc.sig_mr)) अणु
			ret = PTR_ERR(desc->rsc.sig_mr);
			iser_err("Failed to allocate sig_mr err=%d\n", ret);
			जाओ err_alloc_mr_पूर्णांकegrity;
		पूर्ण
	पूर्ण
	desc->rsc.mr_valid = 0;

	वापस desc;

err_alloc_mr_पूर्णांकegrity:
	ib_dereg_mr(desc->rsc.mr);
err_alloc_mr:
	kमुक्त(desc);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम iser_destroy_fastreg_desc(काष्ठा iser_fr_desc *desc)
अणु
	काष्ठा iser_reg_resources *res = &desc->rsc;

	ib_dereg_mr(res->mr);
	अगर (res->sig_mr) अणु
		ib_dereg_mr(res->sig_mr);
		res->sig_mr = शून्य;
	पूर्ण
	kमुक्त(desc);
पूर्ण

/**
 * iser_alloc_fastreg_pool - Creates pool of fast_reg descriptors
 * क्रम fast registration work requests.
 * @ib_conn: connection RDMA resources
 * @cmds_max: max number of SCSI commands क्रम this connection
 * @size: max number of pages per map request
 *
 * Return: 0 on success, or त्रुटि_सं code on failure
 */
पूर्णांक iser_alloc_fastreg_pool(काष्ठा ib_conn *ib_conn,
			    अचिन्हित cmds_max,
			    अचिन्हित पूर्णांक size)
अणु
	काष्ठा iser_device *device = ib_conn->device;
	काष्ठा iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	काष्ठा iser_fr_desc *desc;
	पूर्णांक i, ret;

	INIT_LIST_HEAD(&fr_pool->list);
	INIT_LIST_HEAD(&fr_pool->all_list);
	spin_lock_init(&fr_pool->lock);
	fr_pool->size = 0;
	क्रम (i = 0; i < cmds_max; i++) अणु
		desc = iser_create_fastreg_desc(device, device->pd,
						ib_conn->pi_support, size);
		अगर (IS_ERR(desc)) अणु
			ret = PTR_ERR(desc);
			जाओ err;
		पूर्ण

		list_add_tail(&desc->list, &fr_pool->list);
		list_add_tail(&desc->all_list, &fr_pool->all_list);
		fr_pool->size++;
	पूर्ण

	वापस 0;

err:
	iser_मुक्त_fastreg_pool(ib_conn);
	वापस ret;
पूर्ण

/**
 * iser_मुक्त_fastreg_pool - releases the pool of fast_reg descriptors
 * @ib_conn: connection RDMA resources
 */
व्योम iser_मुक्त_fastreg_pool(काष्ठा ib_conn *ib_conn)
अणु
	काष्ठा iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	काष्ठा iser_fr_desc *desc, *पंचांगp;
	पूर्णांक i = 0;

	अगर (list_empty(&fr_pool->all_list))
		वापस;

	iser_info("freeing conn %p fr pool\n", ib_conn);

	list_क्रम_each_entry_safe(desc, पंचांगp, &fr_pool->all_list, all_list) अणु
		list_del(&desc->all_list);
		iser_destroy_fastreg_desc(desc);
		++i;
	पूर्ण

	अगर (i < fr_pool->size)
		iser_warn("pool still has %d regions registered\n",
			  fr_pool->size - i);
पूर्ण

/*
 * iser_create_ib_conn_res - Queue-Pair (QP)
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक iser_create_ib_conn_res(काष्ठा ib_conn *ib_conn)
अणु
	काष्ठा iser_conn *iser_conn = to_iser_conn(ib_conn);
	काष्ठा iser_device	*device;
	काष्ठा ib_device	*ib_dev;
	काष्ठा ib_qp_init_attr	init_attr;
	पूर्णांक			ret = -ENOMEM;
	अचिन्हित पूर्णांक max_send_wr, cq_size;

	BUG_ON(ib_conn->device == शून्य);

	device = ib_conn->device;
	ib_dev = device->ib_device;

	अगर (ib_conn->pi_support)
		max_send_wr = ISER_QP_SIG_MAX_REQ_DTOS + 1;
	अन्यथा
		max_send_wr = ISER_QP_MAX_REQ_DTOS + 1;
	max_send_wr = min_t(अचिन्हित पूर्णांक, max_send_wr,
			    (अचिन्हित पूर्णांक)ib_dev->attrs.max_qp_wr);

	cq_size = max_send_wr + ISER_QP_MAX_RECV_DTOS;
	ib_conn->cq = ib_cq_pool_get(ib_dev, cq_size, -1, IB_POLL_SOFTIRQ);
	अगर (IS_ERR(ib_conn->cq)) अणु
		ret = PTR_ERR(ib_conn->cq);
		जाओ cq_err;
	पूर्ण
	ib_conn->cq_size = cq_size;

	स_रखो(&init_attr, 0, माप(init_attr));

	init_attr.event_handler = iser_qp_event_callback;
	init_attr.qp_context	= (व्योम *)ib_conn;
	init_attr.send_cq	= ib_conn->cq;
	init_attr.recv_cq	= ib_conn->cq;
	init_attr.cap.max_recv_wr  = ISER_QP_MAX_RECV_DTOS;
	init_attr.cap.max_send_sge = 2;
	init_attr.cap.max_recv_sge = 1;
	init_attr.sq_sig_type	= IB_SIGNAL_REQ_WR;
	init_attr.qp_type	= IB_QPT_RC;
	init_attr.cap.max_send_wr = max_send_wr;
	अगर (ib_conn->pi_support)
		init_attr.create_flags |= IB_QP_CREATE_INTEGRITY_EN;
	iser_conn->max_cmds = ISER_GET_MAX_XMIT_CMDS(max_send_wr - 1);

	ret = rdma_create_qp(ib_conn->cma_id, device->pd, &init_attr);
	अगर (ret)
		जाओ out_err;

	ib_conn->qp = ib_conn->cma_id->qp;
	iser_info("setting conn %p cma_id %p qp %p max_send_wr %d\n",
		  ib_conn, ib_conn->cma_id,
		  ib_conn->cma_id->qp, max_send_wr);
	वापस ret;

out_err:
	ib_cq_pool_put(ib_conn->cq, ib_conn->cq_size);
cq_err:
	iser_err("unable to alloc mem or create resource, err %d\n", ret);

	वापस ret;
पूर्ण

/*
 * based on the resolved device node GUID see अगर there alपढ़ोy allocated
 * device क्रम this device. If there's no such, create one.
 */
अटल
काष्ठा iser_device *iser_device_find_by_ib_device(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा iser_device *device;

	mutex_lock(&ig.device_list_mutex);

	list_क्रम_each_entry(device, &ig.device_list, ig_list)
		/* find अगर there's a match using the node GUID */
		अगर (device->ib_device->node_guid == cma_id->device->node_guid)
			जाओ inc_refcnt;

	device = kzalloc(माप *device, GFP_KERNEL);
	अगर (device == शून्य)
		जाओ out;

	/* assign this device to the device */
	device->ib_device = cma_id->device;
	/* init the device and link it पूर्णांकo ig device list */
	अगर (iser_create_device_ib_res(device)) अणु
		kमुक्त(device);
		device = शून्य;
		जाओ out;
	पूर्ण
	list_add(&device->ig_list, &ig.device_list);

inc_refcnt:
	device->refcount++;
out:
	mutex_unlock(&ig.device_list_mutex);
	वापस device;
पूर्ण

/* अगर there's no demand क्रम this device, release it */
अटल व्योम iser_device_try_release(काष्ठा iser_device *device)
अणु
	mutex_lock(&ig.device_list_mutex);
	device->refcount--;
	iser_info("device %p refcount %d\n", device, device->refcount);
	अगर (!device->refcount) अणु
		iser_मुक्त_device_ib_res(device);
		list_del(&device->ig_list);
		kमुक्त(device);
	पूर्ण
	mutex_unlock(&ig.device_list_mutex);
पूर्ण

/*
 * Called with state mutex held
 */
अटल पूर्णांक iser_conn_state_comp_exch(काष्ठा iser_conn *iser_conn,
				     क्रमागत iser_conn_state comp,
				     क्रमागत iser_conn_state exch)
अणु
	पूर्णांक ret;

	ret = (iser_conn->state == comp);
	अगर (ret)
		iser_conn->state = exch;

	वापस ret;
पूर्ण

व्योम iser_release_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iser_conn *iser_conn;

	iser_conn = container_of(work, काष्ठा iser_conn, release_work);

	/* Wait क्रम conn_stop to complete */
	रुको_क्रम_completion(&iser_conn->stop_completion);
	/* Wait क्रम IB resouces cleanup to complete */
	रुको_क्रम_completion(&iser_conn->ib_completion);

	mutex_lock(&iser_conn->state_mutex);
	iser_conn->state = ISER_CONN_DOWN;
	mutex_unlock(&iser_conn->state_mutex);

	iser_conn_release(iser_conn);
पूर्ण

/**
 * iser_मुक्त_ib_conn_res - release IB related resources
 * @iser_conn: iser connection काष्ठा
 * @destroy: indicator अगर we need to try to release the
 *     iser device and memory regoins pool (only iscsi
 *     shutकरोwn and DEVICE_REMOVAL will use this).
 *
 * This routine is called with the iser state mutex held
 * so the cm_id removal is out of here. It is Safe to
 * be invoked multiple बार.
 */
अटल व्योम iser_मुक्त_ib_conn_res(काष्ठा iser_conn *iser_conn,
				  bool destroy)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा iser_device *device = ib_conn->device;

	iser_info("freeing conn %p cma_id %p qp %p\n",
		  iser_conn, ib_conn->cma_id, ib_conn->qp);

	अगर (ib_conn->qp != शून्य) अणु
		rdma_destroy_qp(ib_conn->cma_id);
		ib_cq_pool_put(ib_conn->cq, ib_conn->cq_size);
		ib_conn->qp = शून्य;
	पूर्ण

	अगर (destroy) अणु
		अगर (iser_conn->rx_descs)
			iser_मुक्त_rx_descriptors(iser_conn);

		अगर (device != शून्य) अणु
			iser_device_try_release(device);
			ib_conn->device = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * iser_conn_release - Frees all conn objects and deallocs conn descriptor
 * @iser_conn: iSER connection context
 */
व्योम iser_conn_release(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;

	mutex_lock(&ig.connlist_mutex);
	list_del(&iser_conn->conn_list);
	mutex_unlock(&ig.connlist_mutex);

	mutex_lock(&iser_conn->state_mutex);
	/* In हाल we endup here without ep_disconnect being invoked. */
	अगर (iser_conn->state != ISER_CONN_DOWN) अणु
		iser_warn("iser conn %p state %d, expected state down.\n",
			  iser_conn, iser_conn->state);
		iscsi_destroy_endpoपूर्णांक(iser_conn->ep);
		iser_conn->state = ISER_CONN_DOWN;
	पूर्ण
	/*
	 * In हाल we never got to bind stage, we still need to
	 * release IB resources (which is safe to call more than once).
	 */
	iser_मुक्त_ib_conn_res(iser_conn, true);
	mutex_unlock(&iser_conn->state_mutex);

	अगर (ib_conn->cma_id != शून्य) अणु
		rdma_destroy_id(ib_conn->cma_id);
		ib_conn->cma_id = शून्य;
	पूर्ण

	kमुक्त(iser_conn);
पूर्ण

/**
 * iser_conn_terminate - triggers start of the disconnect procedures and
 * रुकोs क्रम them to be करोne
 * @iser_conn: iSER connection context
 *
 * Called with state mutex held
 */
पूर्णांक iser_conn_terminate(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	पूर्णांक err = 0;

	/* terminate the iser conn only अगर the conn state is UP */
	अगर (!iser_conn_state_comp_exch(iser_conn, ISER_CONN_UP,
				       ISER_CONN_TERMINATING))
		वापस 0;

	iser_info("iser_conn %p state %d\n", iser_conn, iser_conn->state);

	/* suspend queuing of new iscsi commands */
	अगर (iser_conn->iscsi_conn)
		iscsi_suspend_queue(iser_conn->iscsi_conn);

	/*
	 * In हाल we didn't alपढ़ोy clean up the cma_id (peer initiated
	 * a disconnection), we need to Cause the CMA to change the QP
	 * state to ERROR.
	 */
	अगर (ib_conn->cma_id) अणु
		err = rdma_disconnect(ib_conn->cma_id);
		अगर (err)
			iser_err("Failed to disconnect, conn: 0x%p err %d\n",
				 iser_conn, err);

		/* block until all flush errors are consumed */
		ib_drain_sq(ib_conn->qp);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Called with state mutex held
 */
अटल व्योम iser_connect_error(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा iser_conn *iser_conn;

	iser_conn = (काष्ठा iser_conn *)cma_id->context;
	iser_conn->state = ISER_CONN_TERMINATING;
पूर्ण

अटल व्योम
iser_calc_scsi_params(काष्ठा iser_conn *iser_conn,
		      अचिन्हित पूर्णांक max_sectors)
अणु
	काष्ठा iser_device *device = iser_conn->ib_conn.device;
	काष्ठा ib_device_attr *attr = &device->ib_device->attrs;
	अचिन्हित लघु sg_tablesize, sup_sg_tablesize;
	अचिन्हित लघु reserved_mr_pages;
	u32 max_num_sg;

	/*
	 * FRs without SG_GAPS can only map up to a (device) page per entry,
	 * but अगर the first entry is misaligned we'll end up using two entries
	 * (head and tail) क्रम a single page worth data, so one additional
	 * entry is required.
	 */
	अगर (attr->device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		reserved_mr_pages = 0;
	अन्यथा
		reserved_mr_pages = 1;

	अगर (iser_conn->ib_conn.pi_support)
		max_num_sg = attr->max_pi_fast_reg_page_list_len;
	अन्यथा
		max_num_sg = attr->max_fast_reg_page_list_len;

	sg_tablesize = DIV_ROUND_UP(max_sectors * SECTOR_SIZE, SZ_4K);
	sup_sg_tablesize = min_t(uपूर्णांक, ISCSI_ISER_MAX_SG_TABLESIZE,
				 max_num_sg - reserved_mr_pages);
	iser_conn->scsi_sg_tablesize = min(sg_tablesize, sup_sg_tablesize);
	iser_conn->pages_per_mr =
		iser_conn->scsi_sg_tablesize + reserved_mr_pages;
पूर्ण

/*
 * Called with state mutex held
 */
अटल व्योम iser_addr_handler(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा iser_device *device;
	काष्ठा iser_conn   *iser_conn;
	काष्ठा ib_conn   *ib_conn;
	पूर्णांक    ret;

	iser_conn = (काष्ठा iser_conn *)cma_id->context;
	अगर (iser_conn->state != ISER_CONN_PENDING)
		/* bailout */
		वापस;

	ib_conn = &iser_conn->ib_conn;
	device = iser_device_find_by_ib_device(cma_id);
	अगर (!device) अणु
		iser_err("device lookup/creation failed\n");
		iser_connect_error(cma_id);
		वापस;
	पूर्ण

	ib_conn->device = device;

	/* connection T10-PI support */
	अगर (iser_pi_enable) अणु
		अगर (!(device->ib_device->attrs.device_cap_flags &
		      IB_DEVICE_INTEGRITY_HANDOVER)) अणु
			iser_warn("T10-PI requested but not supported on %s, "
				  "continue without T10-PI\n",
				  dev_name(&ib_conn->device->ib_device->dev));
			ib_conn->pi_support = false;
		पूर्ण अन्यथा अणु
			ib_conn->pi_support = true;
		पूर्ण
	पूर्ण

	iser_calc_scsi_params(iser_conn, iser_max_sectors);

	ret = rdma_resolve_route(cma_id, 1000);
	अगर (ret) अणु
		iser_err("resolve route failed: %d\n", ret);
		iser_connect_error(cma_id);
		वापस;
	पूर्ण
पूर्ण

/*
 * Called with state mutex held
 */
अटल व्योम iser_route_handler(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा rdma_conn_param conn_param;
	पूर्णांक    ret;
	काष्ठा iser_cm_hdr req_hdr;
	काष्ठा iser_conn *iser_conn = (काष्ठा iser_conn *)cma_id->context;
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा ib_device *ib_dev = ib_conn->device->ib_device;

	अगर (iser_conn->state != ISER_CONN_PENDING)
		/* bailout */
		वापस;

	ret = iser_create_ib_conn_res(ib_conn);
	अगर (ret)
		जाओ failure;

	स_रखो(&conn_param, 0, माप conn_param);
	conn_param.responder_resources = ib_dev->attrs.max_qp_rd_atom;
	conn_param.initiator_depth     = 1;
	conn_param.retry_count	       = 7;
	conn_param.rnr_retry_count     = 6;

	स_रखो(&req_hdr, 0, माप(req_hdr));
	req_hdr.flags = ISER_ZBVA_NOT_SUP;
	अगर (!iser_always_reg)
		req_hdr.flags |= ISER_SEND_W_INV_NOT_SUP;
	conn_param.निजी_data	= (व्योम *)&req_hdr;
	conn_param.निजी_data_len = माप(काष्ठा iser_cm_hdr);

	ret = rdma_connect_locked(cma_id, &conn_param);
	अगर (ret) अणु
		iser_err("failure connecting: %d\n", ret);
		जाओ failure;
	पूर्ण

	वापस;
failure:
	iser_connect_error(cma_id);
पूर्ण

अटल व्योम iser_connected_handler(काष्ठा rdma_cm_id *cma_id,
				   स्थिर व्योम *निजी_data)
अणु
	काष्ठा iser_conn *iser_conn;
	काष्ठा ib_qp_attr attr;
	काष्ठा ib_qp_init_attr init_attr;

	iser_conn = (काष्ठा iser_conn *)cma_id->context;
	अगर (iser_conn->state != ISER_CONN_PENDING)
		/* bailout */
		वापस;

	(व्योम)ib_query_qp(cma_id->qp, &attr, ~0, &init_attr);
	iser_info("remote qpn:%x my qpn:%x\n", attr.dest_qp_num, cma_id->qp->qp_num);

	अगर (निजी_data) अणु
		u8 flags = *(u8 *)निजी_data;

		iser_conn->snd_w_inv = !(flags & ISER_SEND_W_INV_NOT_SUP);
	पूर्ण

	iser_info("conn %p: negotiated %s invalidation\n",
		  iser_conn, iser_conn->snd_w_inv ? "remote" : "local");

	iser_conn->state = ISER_CONN_UP;
	complete(&iser_conn->up_completion);
पूर्ण

अटल व्योम iser_disconnected_handler(काष्ठा rdma_cm_id *cma_id)
अणु
	काष्ठा iser_conn *iser_conn = (काष्ठा iser_conn *)cma_id->context;

	अगर (iser_conn_terminate(iser_conn)) अणु
		अगर (iser_conn->iscsi_conn)
			iscsi_conn_failure(iser_conn->iscsi_conn,
					   ISCSI_ERR_CONN_FAILED);
		अन्यथा
			iser_err("iscsi_iser connection isn't bound\n");
	पूर्ण
पूर्ण

अटल व्योम iser_cleanup_handler(काष्ठा rdma_cm_id *cma_id,
				 bool destroy)
अणु
	काष्ठा iser_conn *iser_conn = (काष्ठा iser_conn *)cma_id->context;

	/*
	 * We are not guaranteed that we visited disconnected_handler
	 * by now, call it here to be safe that we handle CM drep
	 * and flush errors.
	 */
	iser_disconnected_handler(cma_id);
	iser_मुक्त_ib_conn_res(iser_conn, destroy);
	complete(&iser_conn->ib_completion);
पूर्ण

अटल पूर्णांक iser_cma_handler(काष्ठा rdma_cm_id *cma_id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा iser_conn *iser_conn;
	पूर्णांक ret = 0;

	iser_conn = (काष्ठा iser_conn *)cma_id->context;
	iser_info("%s (%d): status %d conn %p id %p\n",
		  rdma_event_msg(event->event), event->event,
		  event->status, cma_id->context, cma_id);

	mutex_lock(&iser_conn->state_mutex);
	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		iser_addr_handler(cma_id);
		अवरोध;
	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		iser_route_handler(cma_id);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		iser_connected_handler(cma_id, event->param.conn.निजी_data);
		अवरोध;
	हाल RDMA_CM_EVENT_REJECTED:
		iser_info("Connection rejected: %s\n",
			 rdma_reject_msg(cma_id, event->status));
		fallthrough;
	हाल RDMA_CM_EVENT_ADDR_ERROR:
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
		iser_connect_error(cma_id);
		अवरोध;
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		iser_cleanup_handler(cma_id, false);
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		/*
		 * we *must* destroy the device as we cannot rely
		 * on iscsid to be around to initiate error handling.
		 * also अगर we are not in state DOWN implicitly destroy
		 * the cma_id.
		 */
		iser_cleanup_handler(cma_id, true);
		अगर (iser_conn->state != ISER_CONN_DOWN) अणु
			iser_conn->ib_conn.cma_id = शून्य;
			ret = 1;
		पूर्ण
		अवरोध;
	शेष:
		iser_err("Unexpected RDMA CM event: %s (%d)\n",
			 rdma_event_msg(event->event), event->event);
		अवरोध;
	पूर्ण
	mutex_unlock(&iser_conn->state_mutex);

	वापस ret;
पूर्ण

व्योम iser_conn_init(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;

	iser_conn->state = ISER_CONN_INIT;
	init_completion(&iser_conn->stop_completion);
	init_completion(&iser_conn->ib_completion);
	init_completion(&iser_conn->up_completion);
	INIT_LIST_HEAD(&iser_conn->conn_list);
	mutex_init(&iser_conn->state_mutex);

	ib_conn->post_recv_buf_count = 0;
	ib_conn->reg_cqe.करोne = iser_reg_comp;
पूर्ण

 /**
 * starts the process of connecting to the target
 * sleeps until the connection is established or rejected
 */
पूर्णांक iser_connect(काष्ठा iser_conn   *iser_conn,
		 काष्ठा sockaddr    *src_addr,
		 काष्ठा sockaddr    *dst_addr,
		 पूर्णांक                 non_blocking)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	पूर्णांक err = 0;

	mutex_lock(&iser_conn->state_mutex);

	प्र_लिखो(iser_conn->name, "%pISp", dst_addr);

	iser_info("connecting to: %s\n", iser_conn->name);

	/* the device is known only --after-- address resolution */
	ib_conn->device = शून्य;

	iser_conn->state = ISER_CONN_PENDING;

	ib_conn->cma_id = rdma_create_id(&init_net, iser_cma_handler,
					 (व्योम *)iser_conn,
					 RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(ib_conn->cma_id)) अणु
		err = PTR_ERR(ib_conn->cma_id);
		iser_err("rdma_create_id failed: %d\n", err);
		जाओ id_failure;
	पूर्ण

	err = rdma_resolve_addr(ib_conn->cma_id, src_addr, dst_addr, 1000);
	अगर (err) अणु
		iser_err("rdma_resolve_addr failed: %d\n", err);
		जाओ addr_failure;
	पूर्ण

	अगर (!non_blocking) अणु
		रुको_क्रम_completion_पूर्णांकerruptible(&iser_conn->up_completion);

		अगर (iser_conn->state != ISER_CONN_UP) अणु
			err =  -EIO;
			जाओ connect_failure;
		पूर्ण
	पूर्ण
	mutex_unlock(&iser_conn->state_mutex);

	mutex_lock(&ig.connlist_mutex);
	list_add(&iser_conn->conn_list, &ig.connlist);
	mutex_unlock(&ig.connlist_mutex);
	वापस 0;

id_failure:
	ib_conn->cma_id = शून्य;
addr_failure:
	iser_conn->state = ISER_CONN_DOWN;
connect_failure:
	mutex_unlock(&iser_conn->state_mutex);
	iser_conn_release(iser_conn);
	वापस err;
पूर्ण

पूर्णांक iser_post_recvl(काष्ठा iser_conn *iser_conn)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	काष्ठा iser_login_desc *desc = &iser_conn->login_desc;
	काष्ठा ib_recv_wr wr;
	पूर्णांक ib_ret;

	desc->sge.addr = desc->rsp_dma;
	desc->sge.length = ISER_RX_LOGIN_SIZE;
	desc->sge.lkey = ib_conn->device->pd->local_dma_lkey;

	desc->cqe.करोne = iser_login_rsp;
	wr.wr_cqe = &desc->cqe;
	wr.sg_list = &desc->sge;
	wr.num_sge = 1;
	wr.next = शून्य;

	ib_conn->post_recv_buf_count++;
	ib_ret = ib_post_recv(ib_conn->qp, &wr, शून्य);
	अगर (ib_ret) अणु
		iser_err("ib_post_recv failed ret=%d\n", ib_ret);
		ib_conn->post_recv_buf_count--;
	पूर्ण

	वापस ib_ret;
पूर्ण

पूर्णांक iser_post_recvm(काष्ठा iser_conn *iser_conn, पूर्णांक count)
अणु
	काष्ठा ib_conn *ib_conn = &iser_conn->ib_conn;
	अचिन्हित पूर्णांक my_rx_head = iser_conn->rx_desc_head;
	काष्ठा iser_rx_desc *rx_desc;
	काष्ठा ib_recv_wr *wr;
	पूर्णांक i, ib_ret;

	क्रम (wr = ib_conn->rx_wr, i = 0; i < count; i++, wr++) अणु
		rx_desc = &iser_conn->rx_descs[my_rx_head];
		rx_desc->cqe.करोne = iser_task_rsp;
		wr->wr_cqe = &rx_desc->cqe;
		wr->sg_list = &rx_desc->rx_sg;
		wr->num_sge = 1;
		wr->next = wr + 1;
		my_rx_head = (my_rx_head + 1) & iser_conn->qp_max_recv_dtos_mask;
	पूर्ण

	wr--;
	wr->next = शून्य; /* mark end of work requests list */

	ib_conn->post_recv_buf_count += count;
	ib_ret = ib_post_recv(ib_conn->qp, ib_conn->rx_wr, शून्य);
	अगर (unlikely(ib_ret)) अणु
		iser_err("ib_post_recv failed ret=%d\n", ib_ret);
		ib_conn->post_recv_buf_count -= count;
	पूर्ण अन्यथा
		iser_conn->rx_desc_head = my_rx_head;

	वापस ib_ret;
पूर्ण


/**
 * iser_post_send - Initiate a Send DTO operation
 * @ib_conn: connection RDMA resources
 * @tx_desc: iSER TX descriptor
 * @संकेत: true to send work request as SIGNALED
 *
 * Return: 0 on success, -1 on failure
 */
पूर्णांक iser_post_send(काष्ठा ib_conn *ib_conn, काष्ठा iser_tx_desc *tx_desc,
		   bool संकेत)
अणु
	काष्ठा ib_send_wr *wr = &tx_desc->send_wr;
	काष्ठा ib_send_wr *first_wr;
	पूर्णांक ib_ret;

	ib_dma_sync_single_क्रम_device(ib_conn->device->ib_device,
				      tx_desc->dma_addr, ISER_HEADERS_LEN,
				      DMA_TO_DEVICE);

	wr->next = शून्य;
	wr->wr_cqe = &tx_desc->cqe;
	wr->sg_list = tx_desc->tx_sg;
	wr->num_sge = tx_desc->num_sge;
	wr->opcode = IB_WR_SEND;
	wr->send_flags = संकेत ? IB_SEND_SIGNALED : 0;

	अगर (tx_desc->inv_wr.next)
		first_wr = &tx_desc->inv_wr;
	अन्यथा अगर (tx_desc->reg_wr.wr.next)
		first_wr = &tx_desc->reg_wr.wr;
	अन्यथा
		first_wr = wr;

	ib_ret = ib_post_send(ib_conn->qp, first_wr, शून्य);
	अगर (unlikely(ib_ret))
		iser_err("ib_post_send failed, ret:%d opcode:%d\n",
			 ib_ret, wr->opcode);

	वापस ib_ret;
पूर्ण

u8 iser_check_task_pi_status(काष्ठा iscsi_iser_task *iser_task,
			     क्रमागत iser_data_dir cmd_dir, sector_t *sector)
अणु
	काष्ठा iser_mem_reg *reg = &iser_task->rdma_reg[cmd_dir];
	काष्ठा iser_fr_desc *desc = reg->mem_h;
	अचिन्हित दीर्घ sector_size = iser_task->sc->device->sector_size;
	काष्ठा ib_mr_status mr_status;
	पूर्णांक ret;

	अगर (desc && desc->sig_रक्षित) अणु
		desc->sig_रक्षित = false;
		ret = ib_check_mr_status(desc->rsc.sig_mr,
					 IB_MR_CHECK_SIG_STATUS, &mr_status);
		अगर (ret) अणु
			iser_err("ib_check_mr_status failed, ret %d\n", ret);
			/* Not a lot we can करो, वापस ambiguous guard error */
			*sector = 0;
			वापस 0x1;
		पूर्ण

		अगर (mr_status.fail_status & IB_MR_CHECK_SIG_STATUS) अणु
			sector_t sector_off = mr_status.sig_err.sig_err_offset;

			sector_भाग(sector_off, sector_size + 8);
			*sector = scsi_get_lba(iser_task->sc) + sector_off;

			iser_err("PI error found type %d at sector %llx "
			       "expected %x vs actual %x\n",
			       mr_status.sig_err.err_type,
			       (अचिन्हित दीर्घ दीर्घ)*sector,
			       mr_status.sig_err.expected,
			       mr_status.sig_err.actual);

			चयन (mr_status.sig_err.err_type) अणु
			हाल IB_SIG_BAD_GUARD:
				वापस 0x1;
			हाल IB_SIG_BAD_REFTAG:
				वापस 0x3;
			हाल IB_SIG_BAD_APPTAG:
				वापस 0x2;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम iser_err_comp(काष्ठा ib_wc *wc, स्थिर अक्षर *type)
अणु
	अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
		काष्ठा iser_conn *iser_conn = to_iser_conn(wc->qp->qp_context);

		iser_err("%s failure: %s (%d) vend_err %#x\n", type,
			 ib_wc_status_msg(wc->status), wc->status,
			 wc->venकरोr_err);

		अगर (iser_conn->iscsi_conn)
			iscsi_conn_failure(iser_conn->iscsi_conn,
					   ISCSI_ERR_CONN_FAILED);
	पूर्ण अन्यथा अणु
		iser_dbg("%s failure: %s (%d)\n", type,
			 ib_wc_status_msg(wc->status), wc->status);
	पूर्ण
पूर्ण
