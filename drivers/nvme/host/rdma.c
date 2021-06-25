<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics RDMA host code.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <rdma/mr_pool.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/atomic.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-mq-rdma.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/nvme.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <linux/nvme-rdma.h>

#समावेश "nvme.h"
#समावेश "fabrics.h"


#घोषणा NVME_RDMA_CONNECT_TIMEOUT_MS	3000		/* 3 second */

#घोषणा NVME_RDMA_MAX_SEGMENTS		256

#घोषणा NVME_RDMA_MAX_INLINE_SEGMENTS	4

#घोषणा NVME_RDMA_DATA_SGL_SIZE \
	(माप(काष्ठा scatterlist) * NVME_INLINE_SG_CNT)
#घोषणा NVME_RDMA_METADATA_SGL_SIZE \
	(माप(काष्ठा scatterlist) * NVME_INLINE_METADATA_SG_CNT)

काष्ठा nvme_rdma_device अणु
	काष्ठा ib_device	*dev;
	काष्ठा ib_pd		*pd;
	काष्ठा kref		ref;
	काष्ठा list_head	entry;
	अचिन्हित पूर्णांक		num_अंतरभूत_segments;
पूर्ण;

काष्ठा nvme_rdma_qe अणु
	काष्ठा ib_cqe		cqe;
	व्योम			*data;
	u64			dma;
पूर्ण;

काष्ठा nvme_rdma_sgl अणु
	पूर्णांक			nents;
	काष्ठा sg_table		sg_table;
पूर्ण;

काष्ठा nvme_rdma_queue;
काष्ठा nvme_rdma_request अणु
	काष्ठा nvme_request	req;
	काष्ठा ib_mr		*mr;
	काष्ठा nvme_rdma_qe	sqe;
	जोड़ nvme_result	result;
	__le16			status;
	refcount_t		ref;
	काष्ठा ib_sge		sge[1 + NVME_RDMA_MAX_INLINE_SEGMENTS];
	u32			num_sge;
	काष्ठा ib_reg_wr	reg_wr;
	काष्ठा ib_cqe		reg_cqe;
	काष्ठा nvme_rdma_queue  *queue;
	काष्ठा nvme_rdma_sgl	data_sgl;
	काष्ठा nvme_rdma_sgl	*metadata_sgl;
	bool			use_sig_mr;
पूर्ण;

क्रमागत nvme_rdma_queue_flags अणु
	NVME_RDMA_Q_ALLOCATED		= 0,
	NVME_RDMA_Q_LIVE		= 1,
	NVME_RDMA_Q_TR_READY		= 2,
पूर्ण;

काष्ठा nvme_rdma_queue अणु
	काष्ठा nvme_rdma_qe	*rsp_ring;
	पूर्णांक			queue_size;
	माप_प्रकार			cmnd_capsule_len;
	काष्ठा nvme_rdma_ctrl	*ctrl;
	काष्ठा nvme_rdma_device	*device;
	काष्ठा ib_cq		*ib_cq;
	काष्ठा ib_qp		*qp;

	अचिन्हित दीर्घ		flags;
	काष्ठा rdma_cm_id	*cm_id;
	पूर्णांक			cm_error;
	काष्ठा completion	cm_करोne;
	bool			pi_support;
	पूर्णांक			cq_size;
	काष्ठा mutex		queue_lock;
पूर्ण;

काष्ठा nvme_rdma_ctrl अणु
	/* पढ़ो only in the hot path */
	काष्ठा nvme_rdma_queue	*queues;

	/* other member variables */
	काष्ठा blk_mq_tag_set	tag_set;
	काष्ठा work_काष्ठा	err_work;

	काष्ठा nvme_rdma_qe	async_event_sqe;

	काष्ठा delayed_work	reconnect_work;

	काष्ठा list_head	list;

	काष्ठा blk_mq_tag_set	admin_tag_set;
	काष्ठा nvme_rdma_device	*device;

	u32			max_fr_pages;

	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_storage src_addr;

	काष्ठा nvme_ctrl	ctrl;
	bool			use_अंतरभूत_data;
	u32			io_queues[HCTX_MAX_TYPES];
पूर्ण;

अटल अंतरभूत काष्ठा nvme_rdma_ctrl *to_rdma_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा nvme_rdma_ctrl, ctrl);
पूर्ण

अटल LIST_HEAD(device_list);
अटल DEFINE_MUTEX(device_list_mutex);

अटल LIST_HEAD(nvme_rdma_ctrl_list);
अटल DEFINE_MUTEX(nvme_rdma_ctrl_mutex);

/*
 * Disabling this option makes small I/O goes faster, but is fundamentally
 * unsafe.  With it turned off we will have to रेजिस्टर a global rkey that
 * allows पढ़ो and ग_लिखो access to all physical memory.
 */
अटल bool रेजिस्टर_always = true;
module_param(रेजिस्टर_always, bool, 0444);
MODULE_PARM_DESC(रेजिस्टर_always,
	 "Use memory registration even for contiguous memory regions");

अटल पूर्णांक nvme_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
		काष्ठा rdma_cm_event *event);
अटल व्योम nvme_rdma_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम nvme_rdma_complete_rq(काष्ठा request *rq);

अटल स्थिर काष्ठा blk_mq_ops nvme_rdma_mq_ops;
अटल स्थिर काष्ठा blk_mq_ops nvme_rdma_admin_mq_ops;

अटल अंतरभूत पूर्णांक nvme_rdma_queue_idx(काष्ठा nvme_rdma_queue *queue)
अणु
	वापस queue - queue->ctrl->queues;
पूर्ण

अटल bool nvme_rdma_poll_queue(काष्ठा nvme_rdma_queue *queue)
अणु
	वापस nvme_rdma_queue_idx(queue) >
		queue->ctrl->io_queues[HCTX_TYPE_DEFAULT] +
		queue->ctrl->io_queues[HCTX_TYPE_READ];
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_rdma_अंतरभूत_data_size(काष्ठा nvme_rdma_queue *queue)
अणु
	वापस queue->cmnd_capsule_len - माप(काष्ठा nvme_command);
पूर्ण

अटल व्योम nvme_rdma_मुक्त_qe(काष्ठा ib_device *ibdev, काष्ठा nvme_rdma_qe *qe,
		माप_प्रकार capsule_size, क्रमागत dma_data_direction dir)
अणु
	ib_dma_unmap_single(ibdev, qe->dma, capsule_size, dir);
	kमुक्त(qe->data);
पूर्ण

अटल पूर्णांक nvme_rdma_alloc_qe(काष्ठा ib_device *ibdev, काष्ठा nvme_rdma_qe *qe,
		माप_प्रकार capsule_size, क्रमागत dma_data_direction dir)
अणु
	qe->data = kzalloc(capsule_size, GFP_KERNEL);
	अगर (!qe->data)
		वापस -ENOMEM;

	qe->dma = ib_dma_map_single(ibdev, qe->data, capsule_size, dir);
	अगर (ib_dma_mapping_error(ibdev, qe->dma)) अणु
		kमुक्त(qe->data);
		qe->data = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvme_rdma_मुक्त_ring(काष्ठा ib_device *ibdev,
		काष्ठा nvme_rdma_qe *ring, माप_प्रकार ib_queue_size,
		माप_प्रकार capsule_size, क्रमागत dma_data_direction dir)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ib_queue_size; i++)
		nvme_rdma_मुक्त_qe(ibdev, &ring[i], capsule_size, dir);
	kमुक्त(ring);
पूर्ण

अटल काष्ठा nvme_rdma_qe *nvme_rdma_alloc_ring(काष्ठा ib_device *ibdev,
		माप_प्रकार ib_queue_size, माप_प्रकार capsule_size,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा nvme_rdma_qe *ring;
	पूर्णांक i;

	ring = kसुस्मृति(ib_queue_size, माप(काष्ठा nvme_rdma_qe), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	/*
	 * Bind the CQEs (post recv buffers) DMA mapping to the RDMA queue
	 * lअगरeसमय. It's safe, since any chage in the underlying RDMA device
	 * will issue error recovery and queue re-creation.
	 */
	क्रम (i = 0; i < ib_queue_size; i++) अणु
		अगर (nvme_rdma_alloc_qe(ibdev, &ring[i], capsule_size, dir))
			जाओ out_मुक्त_ring;
	पूर्ण

	वापस ring;

out_मुक्त_ring:
	nvme_rdma_मुक्त_ring(ibdev, ring, i, capsule_size, dir);
	वापस शून्य;
पूर्ण

अटल व्योम nvme_rdma_qp_event(काष्ठा ib_event *event, व्योम *context)
अणु
	pr_debug("QP event %s (%d)\n",
		 ib_event_msg(event->event), event->event);

पूर्ण

अटल पूर्णांक nvme_rdma_रुको_क्रम_cm(काष्ठा nvme_rdma_queue *queue)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&queue->cm_करोne,
			msecs_to_jअगरfies(NVME_RDMA_CONNECT_TIMEOUT_MS) + 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -ETIMEDOUT;
	WARN_ON_ONCE(queue->cm_error > 0);
	वापस queue->cm_error;
पूर्ण

अटल पूर्णांक nvme_rdma_create_qp(काष्ठा nvme_rdma_queue *queue, स्थिर पूर्णांक factor)
अणु
	काष्ठा nvme_rdma_device *dev = queue->device;
	काष्ठा ib_qp_init_attr init_attr;
	पूर्णांक ret;

	स_रखो(&init_attr, 0, माप(init_attr));
	init_attr.event_handler = nvme_rdma_qp_event;
	/* +1 क्रम drain */
	init_attr.cap.max_send_wr = factor * queue->queue_size + 1;
	/* +1 क्रम drain */
	init_attr.cap.max_recv_wr = queue->queue_size + 1;
	init_attr.cap.max_recv_sge = 1;
	init_attr.cap.max_send_sge = 1 + dev->num_अंतरभूत_segments;
	init_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	init_attr.qp_type = IB_QPT_RC;
	init_attr.send_cq = queue->ib_cq;
	init_attr.recv_cq = queue->ib_cq;
	अगर (queue->pi_support)
		init_attr.create_flags |= IB_QP_CREATE_INTEGRITY_EN;
	init_attr.qp_context = queue;

	ret = rdma_create_qp(queue->cm_id, dev->pd, &init_attr);

	queue->qp = queue->cm_id->qp;
	वापस ret;
पूर्ण

अटल व्योम nvme_rdma_निकास_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *rq, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);

	kमुक्त(req->sqe.data);
पूर्ण

अटल पूर्णांक nvme_rdma_init_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *rq, अचिन्हित पूर्णांक hctx_idx,
		अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = set->driver_data;
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	पूर्णांक queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	काष्ठा nvme_rdma_queue *queue = &ctrl->queues[queue_idx];

	nvme_req(rq)->ctrl = &ctrl->ctrl;
	req->sqe.data = kzalloc(माप(काष्ठा nvme_command), GFP_KERNEL);
	अगर (!req->sqe.data)
		वापस -ENOMEM;

	/* metadata nvme_rdma_sgl काष्ठा is located after command's data SGL */
	अगर (queue->pi_support)
		req->metadata_sgl = (व्योम *)nvme_req(rq) +
			माप(काष्ठा nvme_rdma_request) +
			NVME_RDMA_DATA_SGL_SIZE;

	req->queue = queue;
	nvme_req(rq)->cmd = req->sqe.data;

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = data;
	काष्ठा nvme_rdma_queue *queue = &ctrl->queues[hctx_idx + 1];

	BUG_ON(hctx_idx >= ctrl->ctrl.queue_count);

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_init_admin_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = data;
	काष्ठा nvme_rdma_queue *queue = &ctrl->queues[0];

	BUG_ON(hctx_idx != 0);

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल व्योम nvme_rdma_मुक्त_dev(काष्ठा kref *ref)
अणु
	काष्ठा nvme_rdma_device *ndev =
		container_of(ref, काष्ठा nvme_rdma_device, ref);

	mutex_lock(&device_list_mutex);
	list_del(&ndev->entry);
	mutex_unlock(&device_list_mutex);

	ib_dealloc_pd(ndev->pd);
	kमुक्त(ndev);
पूर्ण

अटल व्योम nvme_rdma_dev_put(काष्ठा nvme_rdma_device *dev)
अणु
	kref_put(&dev->ref, nvme_rdma_मुक्त_dev);
पूर्ण

अटल पूर्णांक nvme_rdma_dev_get(काष्ठा nvme_rdma_device *dev)
अणु
	वापस kref_get_unless_zero(&dev->ref);
पूर्ण

अटल काष्ठा nvme_rdma_device *
nvme_rdma_find_get_device(काष्ठा rdma_cm_id *cm_id)
अणु
	काष्ठा nvme_rdma_device *ndev;

	mutex_lock(&device_list_mutex);
	list_क्रम_each_entry(ndev, &device_list, entry) अणु
		अगर (ndev->dev->node_guid == cm_id->device->node_guid &&
		    nvme_rdma_dev_get(ndev))
			जाओ out_unlock;
	पूर्ण

	ndev = kzalloc(माप(*ndev), GFP_KERNEL);
	अगर (!ndev)
		जाओ out_err;

	ndev->dev = cm_id->device;
	kref_init(&ndev->ref);

	ndev->pd = ib_alloc_pd(ndev->dev,
		रेजिस्टर_always ? 0 : IB_PD_UNSAFE_GLOBAL_RKEY);
	अगर (IS_ERR(ndev->pd))
		जाओ out_मुक्त_dev;

	अगर (!(ndev->dev->attrs.device_cap_flags &
	      IB_DEVICE_MEM_MGT_EXTENSIONS)) अणु
		dev_err(&ndev->dev->dev,
			"Memory registrations not supported.\n");
		जाओ out_मुक्त_pd;
	पूर्ण

	ndev->num_अंतरभूत_segments = min(NVME_RDMA_MAX_INLINE_SEGMENTS,
					ndev->dev->attrs.max_send_sge - 1);
	list_add(&ndev->entry, &device_list);
out_unlock:
	mutex_unlock(&device_list_mutex);
	वापस ndev;

out_मुक्त_pd:
	ib_dealloc_pd(ndev->pd);
out_मुक्त_dev:
	kमुक्त(ndev);
out_err:
	mutex_unlock(&device_list_mutex);
	वापस शून्य;
पूर्ण

अटल व्योम nvme_rdma_मुक्त_cq(काष्ठा nvme_rdma_queue *queue)
अणु
	अगर (nvme_rdma_poll_queue(queue))
		ib_मुक्त_cq(queue->ib_cq);
	अन्यथा
		ib_cq_pool_put(queue->ib_cq, queue->cq_size);
पूर्ण

अटल व्योम nvme_rdma_destroy_queue_ib(काष्ठा nvme_rdma_queue *queue)
अणु
	काष्ठा nvme_rdma_device *dev;
	काष्ठा ib_device *ibdev;

	अगर (!test_and_clear_bit(NVME_RDMA_Q_TR_READY, &queue->flags))
		वापस;

	dev = queue->device;
	ibdev = dev->dev;

	अगर (queue->pi_support)
		ib_mr_pool_destroy(queue->qp, &queue->qp->sig_mrs);
	ib_mr_pool_destroy(queue->qp, &queue->qp->rdma_mrs);

	/*
	 * The cm_id object might have been destroyed during RDMA connection
	 * establishment error flow to aव्योम getting other cma events, thus
	 * the deकाष्ठाion of the QP shouldn't use rdma_cm API.
	 */
	ib_destroy_qp(queue->qp);
	nvme_rdma_मुक्त_cq(queue);

	nvme_rdma_मुक्त_ring(ibdev, queue->rsp_ring, queue->queue_size,
			माप(काष्ठा nvme_completion), DMA_FROM_DEVICE);

	nvme_rdma_dev_put(dev);
पूर्ण

अटल पूर्णांक nvme_rdma_get_max_fr_pages(काष्ठा ib_device *ibdev, bool pi_support)
अणु
	u32 max_page_list_len;

	अगर (pi_support)
		max_page_list_len = ibdev->attrs.max_pi_fast_reg_page_list_len;
	अन्यथा
		max_page_list_len = ibdev->attrs.max_fast_reg_page_list_len;

	वापस min_t(u32, NVME_RDMA_MAX_SEGMENTS, max_page_list_len - 1);
पूर्ण

अटल पूर्णांक nvme_rdma_create_cq(काष्ठा ib_device *ibdev,
		काष्ठा nvme_rdma_queue *queue)
अणु
	पूर्णांक ret, comp_vector, idx = nvme_rdma_queue_idx(queue);
	क्रमागत ib_poll_context poll_ctx;

	/*
	 * Spपढ़ो I/O queues completion vectors according their queue index.
	 * Admin queues can always go on completion vector 0.
	 */
	comp_vector = (idx == 0 ? idx : idx - 1) % ibdev->num_comp_vectors;

	/* Polling queues need direct cq polling context */
	अगर (nvme_rdma_poll_queue(queue)) अणु
		poll_ctx = IB_POLL_सूचीECT;
		queue->ib_cq = ib_alloc_cq(ibdev, queue, queue->cq_size,
					   comp_vector, poll_ctx);
	पूर्ण अन्यथा अणु
		poll_ctx = IB_POLL_SOFTIRQ;
		queue->ib_cq = ib_cq_pool_get(ibdev, queue->cq_size,
					      comp_vector, poll_ctx);
	पूर्ण

	अगर (IS_ERR(queue->ib_cq)) अणु
		ret = PTR_ERR(queue->ib_cq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_create_queue_ib(काष्ठा nvme_rdma_queue *queue)
अणु
	काष्ठा ib_device *ibdev;
	स्थिर पूर्णांक send_wr_factor = 3;			/* MR, SEND, INV */
	स्थिर पूर्णांक cq_factor = send_wr_factor + 1;	/* + RECV */
	पूर्णांक ret, pages_per_mr;

	queue->device = nvme_rdma_find_get_device(queue->cm_id);
	अगर (!queue->device) अणु
		dev_err(queue->cm_id->device->dev.parent,
			"no client data found!\n");
		वापस -ECONNREFUSED;
	पूर्ण
	ibdev = queue->device->dev;

	/* +1 क्रम ib_stop_cq */
	queue->cq_size = cq_factor * queue->queue_size + 1;

	ret = nvme_rdma_create_cq(ibdev, queue);
	अगर (ret)
		जाओ out_put_dev;

	ret = nvme_rdma_create_qp(queue, send_wr_factor);
	अगर (ret)
		जाओ out_destroy_ib_cq;

	queue->rsp_ring = nvme_rdma_alloc_ring(ibdev, queue->queue_size,
			माप(काष्ठा nvme_completion), DMA_FROM_DEVICE);
	अगर (!queue->rsp_ring) अणु
		ret = -ENOMEM;
		जाओ out_destroy_qp;
	पूर्ण

	/*
	 * Currently we करोn't use SG_GAPS MR's so अगर the first entry is
	 * misaligned we'll end up using two entries क्रम a single data page,
	 * so one additional entry is required.
	 */
	pages_per_mr = nvme_rdma_get_max_fr_pages(ibdev, queue->pi_support) + 1;
	ret = ib_mr_pool_init(queue->qp, &queue->qp->rdma_mrs,
			      queue->queue_size,
			      IB_MR_TYPE_MEM_REG,
			      pages_per_mr, 0);
	अगर (ret) अणु
		dev_err(queue->ctrl->ctrl.device,
			"failed to initialize MR pool sized %d for QID %d\n",
			queue->queue_size, nvme_rdma_queue_idx(queue));
		जाओ out_destroy_ring;
	पूर्ण

	अगर (queue->pi_support) अणु
		ret = ib_mr_pool_init(queue->qp, &queue->qp->sig_mrs,
				      queue->queue_size, IB_MR_TYPE_INTEGRITY,
				      pages_per_mr, pages_per_mr);
		अगर (ret) अणु
			dev_err(queue->ctrl->ctrl.device,
				"failed to initialize PI MR pool sized %d for QID %d\n",
				queue->queue_size, nvme_rdma_queue_idx(queue));
			जाओ out_destroy_mr_pool;
		पूर्ण
	पूर्ण

	set_bit(NVME_RDMA_Q_TR_READY, &queue->flags);

	वापस 0;

out_destroy_mr_pool:
	ib_mr_pool_destroy(queue->qp, &queue->qp->rdma_mrs);
out_destroy_ring:
	nvme_rdma_मुक्त_ring(ibdev, queue->rsp_ring, queue->queue_size,
			    माप(काष्ठा nvme_completion), DMA_FROM_DEVICE);
out_destroy_qp:
	rdma_destroy_qp(queue->cm_id);
out_destroy_ib_cq:
	nvme_rdma_मुक्त_cq(queue);
out_put_dev:
	nvme_rdma_dev_put(queue->device);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_alloc_queue(काष्ठा nvme_rdma_ctrl *ctrl,
		पूर्णांक idx, माप_प्रकार queue_size)
अणु
	काष्ठा nvme_rdma_queue *queue;
	काष्ठा sockaddr *src_addr = शून्य;
	पूर्णांक ret;

	queue = &ctrl->queues[idx];
	mutex_init(&queue->queue_lock);
	queue->ctrl = ctrl;
	अगर (idx && ctrl->ctrl.max_पूर्णांकegrity_segments)
		queue->pi_support = true;
	अन्यथा
		queue->pi_support = false;
	init_completion(&queue->cm_करोne);

	अगर (idx > 0)
		queue->cmnd_capsule_len = ctrl->ctrl.ioccsz * 16;
	अन्यथा
		queue->cmnd_capsule_len = माप(काष्ठा nvme_command);

	queue->queue_size = queue_size;

	queue->cm_id = rdma_create_id(&init_net, nvme_rdma_cm_handler, queue,
			RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(queue->cm_id)) अणु
		dev_info(ctrl->ctrl.device,
			"failed to create CM ID: %ld\n", PTR_ERR(queue->cm_id));
		ret = PTR_ERR(queue->cm_id);
		जाओ out_destroy_mutex;
	पूर्ण

	अगर (ctrl->ctrl.opts->mask & NVMF_OPT_HOST_TRADDR)
		src_addr = (काष्ठा sockaddr *)&ctrl->src_addr;

	queue->cm_error = -ETIMEDOUT;
	ret = rdma_resolve_addr(queue->cm_id, src_addr,
			(काष्ठा sockaddr *)&ctrl->addr,
			NVME_RDMA_CONNECT_TIMEOUT_MS);
	अगर (ret) अणु
		dev_info(ctrl->ctrl.device,
			"rdma_resolve_addr failed (%d).\n", ret);
		जाओ out_destroy_cm_id;
	पूर्ण

	ret = nvme_rdma_रुको_क्रम_cm(queue);
	अगर (ret) अणु
		dev_info(ctrl->ctrl.device,
			"rdma connection establishment failed (%d)\n", ret);
		जाओ out_destroy_cm_id;
	पूर्ण

	set_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags);

	वापस 0;

out_destroy_cm_id:
	rdma_destroy_id(queue->cm_id);
	nvme_rdma_destroy_queue_ib(queue);
out_destroy_mutex:
	mutex_destroy(&queue->queue_lock);
	वापस ret;
पूर्ण

अटल व्योम __nvme_rdma_stop_queue(काष्ठा nvme_rdma_queue *queue)
अणु
	rdma_disconnect(queue->cm_id);
	ib_drain_qp(queue->qp);
पूर्ण

अटल व्योम nvme_rdma_stop_queue(काष्ठा nvme_rdma_queue *queue)
अणु
	mutex_lock(&queue->queue_lock);
	अगर (test_and_clear_bit(NVME_RDMA_Q_LIVE, &queue->flags))
		__nvme_rdma_stop_queue(queue);
	mutex_unlock(&queue->queue_lock);
पूर्ण

अटल व्योम nvme_rdma_मुक्त_queue(काष्ठा nvme_rdma_queue *queue)
अणु
	अगर (!test_and_clear_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags))
		वापस;

	nvme_rdma_destroy_queue_ib(queue);
	rdma_destroy_id(queue->cm_id);
	mutex_destroy(&queue->queue_lock);
पूर्ण

अटल व्योम nvme_rdma_मुक्त_io_queues(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++)
		nvme_rdma_मुक्त_queue(&ctrl->queues[i]);
पूर्ण

अटल व्योम nvme_rdma_stop_io_queues(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++)
		nvme_rdma_stop_queue(&ctrl->queues[i]);
पूर्ण

अटल पूर्णांक nvme_rdma_start_queue(काष्ठा nvme_rdma_ctrl *ctrl, पूर्णांक idx)
अणु
	काष्ठा nvme_rdma_queue *queue = &ctrl->queues[idx];
	bool poll = nvme_rdma_poll_queue(queue);
	पूर्णांक ret;

	अगर (idx)
		ret = nvmf_connect_io_queue(&ctrl->ctrl, idx, poll);
	अन्यथा
		ret = nvmf_connect_admin_queue(&ctrl->ctrl);

	अगर (!ret) अणु
		set_bit(NVME_RDMA_Q_LIVE, &queue->flags);
	पूर्ण अन्यथा अणु
		अगर (test_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags))
			__nvme_rdma_stop_queue(queue);
		dev_info(ctrl->ctrl.device,
			"failed to connect queue: %d ret=%d\n", idx, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_start_io_queues(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++) अणु
		ret = nvme_rdma_start_queue(ctrl, i);
		अगर (ret)
			जाओ out_stop_queues;
	पूर्ण

	वापस 0;

out_stop_queues:
	क्रम (i--; i >= 1; i--)
		nvme_rdma_stop_queue(&ctrl->queues[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_alloc_io_queues(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	काष्ठा ib_device *ibdev = ctrl->device->dev;
	अचिन्हित पूर्णांक nr_io_queues, nr_शेष_queues;
	अचिन्हित पूर्णांक nr_पढ़ो_queues, nr_poll_queues;
	पूर्णांक i, ret;

	nr_पढ़ो_queues = min_t(अचिन्हित पूर्णांक, ibdev->num_comp_vectors,
				min(opts->nr_io_queues, num_online_cpus()));
	nr_शेष_queues =  min_t(अचिन्हित पूर्णांक, ibdev->num_comp_vectors,
				min(opts->nr_ग_लिखो_queues, num_online_cpus()));
	nr_poll_queues = min(opts->nr_poll_queues, num_online_cpus());
	nr_io_queues = nr_पढ़ो_queues + nr_शेष_queues + nr_poll_queues;

	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	अगर (ret)
		वापस ret;

	ctrl->ctrl.queue_count = nr_io_queues + 1;
	अगर (ctrl->ctrl.queue_count < 2) अणु
		dev_err(ctrl->ctrl.device,
			"unable to set any I/O queues\n");
		वापस -ENOMEM;
	पूर्ण

	dev_info(ctrl->ctrl.device,
		"creating %d I/O queues.\n", nr_io_queues);

	अगर (opts->nr_ग_लिखो_queues && nr_पढ़ो_queues < nr_io_queues) अणु
		/*
		 * separate पढ़ो/ग_लिखो queues
		 * hand out dedicated शेष queues only after we have
		 * sufficient पढ़ो queues.
		 */
		ctrl->io_queues[HCTX_TYPE_READ] = nr_पढ़ो_queues;
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_READ];
		ctrl->io_queues[HCTX_TYPE_DEFAULT] =
			min(nr_शेष_queues, nr_io_queues);
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_DEFAULT];
	पूर्ण अन्यथा अणु
		/*
		 * shared पढ़ो/ग_लिखो queues
		 * either no ग_लिखो queues were requested, or we करोn't have
		 * sufficient queue count to have dedicated शेष queues.
		 */
		ctrl->io_queues[HCTX_TYPE_DEFAULT] =
			min(nr_पढ़ो_queues, nr_io_queues);
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_DEFAULT];
	पूर्ण

	अगर (opts->nr_poll_queues && nr_io_queues) अणु
		/* map dedicated poll queues only अगर we have queues left */
		ctrl->io_queues[HCTX_TYPE_POLL] =
			min(nr_poll_queues, nr_io_queues);
	पूर्ण

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++) अणु
		ret = nvme_rdma_alloc_queue(ctrl, i,
				ctrl->ctrl.sqsize + 1);
		अगर (ret)
			जाओ out_मुक्त_queues;
	पूर्ण

	वापस 0;

out_मुक्त_queues:
	क्रम (i--; i >= 1; i--)
		nvme_rdma_मुक्त_queue(&ctrl->queues[i]);

	वापस ret;
पूर्ण

अटल काष्ठा blk_mq_tag_set *nvme_rdma_alloc_tagset(काष्ठा nvme_ctrl *nctrl,
		bool admin)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = to_rdma_ctrl(nctrl);
	काष्ठा blk_mq_tag_set *set;
	पूर्णांक ret;

	अगर (admin) अणु
		set = &ctrl->admin_tag_set;
		स_रखो(set, 0, माप(*set));
		set->ops = &nvme_rdma_admin_mq_ops;
		set->queue_depth = NVME_AQ_MQ_TAG_DEPTH;
		set->reserved_tags = NVMF_RESERVED_TAGS;
		set->numa_node = nctrl->numa_node;
		set->cmd_size = माप(काष्ठा nvme_rdma_request) +
				NVME_RDMA_DATA_SGL_SIZE;
		set->driver_data = ctrl;
		set->nr_hw_queues = 1;
		set->समयout = NVME_ADMIN_TIMEOUT;
		set->flags = BLK_MQ_F_NO_SCHED;
	पूर्ण अन्यथा अणु
		set = &ctrl->tag_set;
		स_रखो(set, 0, माप(*set));
		set->ops = &nvme_rdma_mq_ops;
		set->queue_depth = nctrl->sqsize + 1;
		set->reserved_tags = NVMF_RESERVED_TAGS;
		set->numa_node = nctrl->numa_node;
		set->flags = BLK_MQ_F_SHOULD_MERGE;
		set->cmd_size = माप(काष्ठा nvme_rdma_request) +
				NVME_RDMA_DATA_SGL_SIZE;
		अगर (nctrl->max_पूर्णांकegrity_segments)
			set->cmd_size += माप(काष्ठा nvme_rdma_sgl) +
					 NVME_RDMA_METADATA_SGL_SIZE;
		set->driver_data = ctrl;
		set->nr_hw_queues = nctrl->queue_count - 1;
		set->समयout = NVME_IO_TIMEOUT;
		set->nr_maps = nctrl->opts->nr_poll_queues ? HCTX_MAX_TYPES : 2;
	पूर्ण

	ret = blk_mq_alloc_tag_set(set);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस set;
पूर्ण

अटल व्योम nvme_rdma_destroy_admin_queue(काष्ठा nvme_rdma_ctrl *ctrl,
		bool हटाओ)
अणु
	अगर (हटाओ) अणु
		blk_cleanup_queue(ctrl->ctrl.admin_q);
		blk_cleanup_queue(ctrl->ctrl.fabrics_q);
		blk_mq_मुक्त_tag_set(ctrl->ctrl.admin_tagset);
	पूर्ण
	अगर (ctrl->async_event_sqe.data) अणु
		cancel_work_sync(&ctrl->ctrl.async_event_work);
		nvme_rdma_मुक्त_qe(ctrl->device->dev, &ctrl->async_event_sqe,
				माप(काष्ठा nvme_command), DMA_TO_DEVICE);
		ctrl->async_event_sqe.data = शून्य;
	पूर्ण
	nvme_rdma_मुक्त_queue(&ctrl->queues[0]);
पूर्ण

अटल पूर्णांक nvme_rdma_configure_admin_queue(काष्ठा nvme_rdma_ctrl *ctrl,
		bool new)
अणु
	bool pi_capable = false;
	पूर्णांक error;

	error = nvme_rdma_alloc_queue(ctrl, 0, NVME_AQ_DEPTH);
	अगर (error)
		वापस error;

	ctrl->device = ctrl->queues[0].device;
	ctrl->ctrl.numa_node = ibdev_to_node(ctrl->device->dev);

	/* T10-PI support */
	अगर (ctrl->device->dev->attrs.device_cap_flags &
	    IB_DEVICE_INTEGRITY_HANDOVER)
		pi_capable = true;

	ctrl->max_fr_pages = nvme_rdma_get_max_fr_pages(ctrl->device->dev,
							pi_capable);

	/*
	 * Bind the async event SQE DMA mapping to the admin queue lअगरeसमय.
	 * It's safe, since any chage in the underlying RDMA device will issue
	 * error recovery and queue re-creation.
	 */
	error = nvme_rdma_alloc_qe(ctrl->device->dev, &ctrl->async_event_sqe,
			माप(काष्ठा nvme_command), DMA_TO_DEVICE);
	अगर (error)
		जाओ out_मुक्त_queue;

	अगर (new) अणु
		ctrl->ctrl.admin_tagset = nvme_rdma_alloc_tagset(&ctrl->ctrl, true);
		अगर (IS_ERR(ctrl->ctrl.admin_tagset)) अणु
			error = PTR_ERR(ctrl->ctrl.admin_tagset);
			जाओ out_मुक्त_async_qe;
		पूर्ण

		ctrl->ctrl.fabrics_q = blk_mq_init_queue(&ctrl->admin_tag_set);
		अगर (IS_ERR(ctrl->ctrl.fabrics_q)) अणु
			error = PTR_ERR(ctrl->ctrl.fabrics_q);
			जाओ out_मुक्त_tagset;
		पूर्ण

		ctrl->ctrl.admin_q = blk_mq_init_queue(&ctrl->admin_tag_set);
		अगर (IS_ERR(ctrl->ctrl.admin_q)) अणु
			error = PTR_ERR(ctrl->ctrl.admin_q);
			जाओ out_cleanup_fabrics_q;
		पूर्ण
	पूर्ण

	error = nvme_rdma_start_queue(ctrl, 0);
	अगर (error)
		जाओ out_cleanup_queue;

	error = nvme_enable_ctrl(&ctrl->ctrl);
	अगर (error)
		जाओ out_stop_queue;

	ctrl->ctrl.max_segments = ctrl->max_fr_pages;
	ctrl->ctrl.max_hw_sectors = ctrl->max_fr_pages << (ilog2(SZ_4K) - 9);
	अगर (pi_capable)
		ctrl->ctrl.max_पूर्णांकegrity_segments = ctrl->max_fr_pages;
	अन्यथा
		ctrl->ctrl.max_पूर्णांकegrity_segments = 0;

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	error = nvme_init_ctrl_finish(&ctrl->ctrl);
	अगर (error)
		जाओ out_quiesce_queue;

	वापस 0;

out_quiesce_queue:
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	blk_sync_queue(ctrl->ctrl.admin_q);
out_stop_queue:
	nvme_rdma_stop_queue(&ctrl->queues[0]);
	nvme_cancel_admin_tagset(&ctrl->ctrl);
out_cleanup_queue:
	अगर (new)
		blk_cleanup_queue(ctrl->ctrl.admin_q);
out_cleanup_fabrics_q:
	अगर (new)
		blk_cleanup_queue(ctrl->ctrl.fabrics_q);
out_मुक्त_tagset:
	अगर (new)
		blk_mq_मुक्त_tag_set(ctrl->ctrl.admin_tagset);
out_मुक्त_async_qe:
	अगर (ctrl->async_event_sqe.data) अणु
		nvme_rdma_मुक्त_qe(ctrl->device->dev, &ctrl->async_event_sqe,
			माप(काष्ठा nvme_command), DMA_TO_DEVICE);
		ctrl->async_event_sqe.data = शून्य;
	पूर्ण
out_मुक्त_queue:
	nvme_rdma_मुक्त_queue(&ctrl->queues[0]);
	वापस error;
पूर्ण

अटल व्योम nvme_rdma_destroy_io_queues(काष्ठा nvme_rdma_ctrl *ctrl,
		bool हटाओ)
अणु
	अगर (हटाओ) अणु
		blk_cleanup_queue(ctrl->ctrl.connect_q);
		blk_mq_मुक्त_tag_set(ctrl->ctrl.tagset);
	पूर्ण
	nvme_rdma_मुक्त_io_queues(ctrl);
पूर्ण

अटल पूर्णांक nvme_rdma_configure_io_queues(काष्ठा nvme_rdma_ctrl *ctrl, bool new)
अणु
	पूर्णांक ret;

	ret = nvme_rdma_alloc_io_queues(ctrl);
	अगर (ret)
		वापस ret;

	अगर (new) अणु
		ctrl->ctrl.tagset = nvme_rdma_alloc_tagset(&ctrl->ctrl, false);
		अगर (IS_ERR(ctrl->ctrl.tagset)) अणु
			ret = PTR_ERR(ctrl->ctrl.tagset);
			जाओ out_मुक्त_io_queues;
		पूर्ण

		ctrl->ctrl.connect_q = blk_mq_init_queue(&ctrl->tag_set);
		अगर (IS_ERR(ctrl->ctrl.connect_q)) अणु
			ret = PTR_ERR(ctrl->ctrl.connect_q);
			जाओ out_मुक्त_tag_set;
		पूर्ण
	पूर्ण

	ret = nvme_rdma_start_io_queues(ctrl);
	अगर (ret)
		जाओ out_cleanup_connect_q;

	अगर (!new) अणु
		nvme_start_queues(&ctrl->ctrl);
		अगर (!nvme_रुको_मुक्तze_समयout(&ctrl->ctrl, NVME_IO_TIMEOUT)) अणु
			/*
			 * If we समयd out रुकोing क्रम मुक्तze we are likely to
			 * be stuck.  Fail the controller initialization just
			 * to be safe.
			 */
			ret = -ENODEV;
			जाओ out_रुको_मुक्तze_समयd_out;
		पूर्ण
		blk_mq_update_nr_hw_queues(ctrl->ctrl.tagset,
			ctrl->ctrl.queue_count - 1);
		nvme_unमुक्तze(&ctrl->ctrl);
	पूर्ण

	वापस 0;

out_रुको_मुक्तze_समयd_out:
	nvme_stop_queues(&ctrl->ctrl);
	nvme_sync_io_queues(&ctrl->ctrl);
	nvme_rdma_stop_io_queues(ctrl);
out_cleanup_connect_q:
	nvme_cancel_tagset(&ctrl->ctrl);
	अगर (new)
		blk_cleanup_queue(ctrl->ctrl.connect_q);
out_मुक्त_tag_set:
	अगर (new)
		blk_mq_मुक्त_tag_set(ctrl->ctrl.tagset);
out_मुक्त_io_queues:
	nvme_rdma_मुक्त_io_queues(ctrl);
	वापस ret;
पूर्ण

अटल व्योम nvme_rdma_tearकरोwn_admin_queue(काष्ठा nvme_rdma_ctrl *ctrl,
		bool हटाओ)
अणु
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	blk_sync_queue(ctrl->ctrl.admin_q);
	nvme_rdma_stop_queue(&ctrl->queues[0]);
	nvme_cancel_admin_tagset(&ctrl->ctrl);
	अगर (हटाओ)
		blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);
	nvme_rdma_destroy_admin_queue(ctrl, हटाओ);
पूर्ण

अटल व्योम nvme_rdma_tearकरोwn_io_queues(काष्ठा nvme_rdma_ctrl *ctrl,
		bool हटाओ)
अणु
	अगर (ctrl->ctrl.queue_count > 1) अणु
		nvme_start_मुक्तze(&ctrl->ctrl);
		nvme_stop_queues(&ctrl->ctrl);
		nvme_sync_io_queues(&ctrl->ctrl);
		nvme_rdma_stop_io_queues(ctrl);
		nvme_cancel_tagset(&ctrl->ctrl);
		अगर (हटाओ)
			nvme_start_queues(&ctrl->ctrl);
		nvme_rdma_destroy_io_queues(ctrl, हटाओ);
	पूर्ण
पूर्ण

अटल व्योम nvme_rdma_मुक्त_ctrl(काष्ठा nvme_ctrl *nctrl)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = to_rdma_ctrl(nctrl);

	अगर (list_empty(&ctrl->list))
		जाओ मुक्त_ctrl;

	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_del(&ctrl->list);
	mutex_unlock(&nvme_rdma_ctrl_mutex);

	nvmf_मुक्त_options(nctrl->opts);
मुक्त_ctrl:
	kमुक्त(ctrl->queues);
	kमुक्त(ctrl);
पूर्ण

अटल व्योम nvme_rdma_reconnect_or_हटाओ(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	/* If we are resetting/deleting then करो nothing */
	अगर (ctrl->ctrl.state != NVME_CTRL_CONNECTING) अणु
		WARN_ON_ONCE(ctrl->ctrl.state == NVME_CTRL_NEW ||
			ctrl->ctrl.state == NVME_CTRL_LIVE);
		वापस;
	पूर्ण

	अगर (nvmf_should_reconnect(&ctrl->ctrl)) अणु
		dev_info(ctrl->ctrl.device, "Reconnecting in %d seconds...\n",
			ctrl->ctrl.opts->reconnect_delay);
		queue_delayed_work(nvme_wq, &ctrl->reconnect_work,
				ctrl->ctrl.opts->reconnect_delay * HZ);
	पूर्ण अन्यथा अणु
		nvme_delete_ctrl(&ctrl->ctrl);
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_rdma_setup_ctrl(काष्ठा nvme_rdma_ctrl *ctrl, bool new)
अणु
	पूर्णांक ret = -EINVAL;
	bool changed;

	ret = nvme_rdma_configure_admin_queue(ctrl, new);
	अगर (ret)
		वापस ret;

	अगर (ctrl->ctrl.icकरोff) अणु
		dev_err(ctrl->ctrl.device, "icdoff is not supported!\n");
		जाओ destroy_admin;
	पूर्ण

	अगर (!(ctrl->ctrl.sgls & (1 << 2))) अणु
		dev_err(ctrl->ctrl.device,
			"Mandatory keyed sgls are not supported!\n");
		जाओ destroy_admin;
	पूर्ण

	अगर (ctrl->ctrl.opts->queue_size > ctrl->ctrl.sqsize + 1) अणु
		dev_warn(ctrl->ctrl.device,
			"queue_size %zu > ctrl sqsize %u, clamping down\n",
			ctrl->ctrl.opts->queue_size, ctrl->ctrl.sqsize + 1);
	पूर्ण

	अगर (ctrl->ctrl.sqsize + 1 > ctrl->ctrl.maxcmd) अणु
		dev_warn(ctrl->ctrl.device,
			"sqsize %u > ctrl maxcmd %u, clamping down\n",
			ctrl->ctrl.sqsize + 1, ctrl->ctrl.maxcmd);
		ctrl->ctrl.sqsize = ctrl->ctrl.maxcmd - 1;
	पूर्ण

	अगर (ctrl->ctrl.sgls & (1 << 20))
		ctrl->use_अंतरभूत_data = true;

	अगर (ctrl->ctrl.queue_count > 1) अणु
		ret = nvme_rdma_configure_io_queues(ctrl, new);
		अगर (ret)
			जाओ destroy_admin;
	पूर्ण

	changed = nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_LIVE);
	अगर (!changed) अणु
		/*
		 * state change failure is ok अगर we started ctrl delete,
		 * unless we're during creation of a new controller to
		 * aव्योम races with tearकरोwn flow.
		 */
		WARN_ON_ONCE(ctrl->ctrl.state != NVME_CTRL_DELETING &&
			     ctrl->ctrl.state != NVME_CTRL_DELETING_NOIO);
		WARN_ON_ONCE(new);
		ret = -EINVAL;
		जाओ destroy_io;
	पूर्ण

	nvme_start_ctrl(&ctrl->ctrl);
	वापस 0;

destroy_io:
	अगर (ctrl->ctrl.queue_count > 1) अणु
		nvme_stop_queues(&ctrl->ctrl);
		nvme_sync_io_queues(&ctrl->ctrl);
		nvme_rdma_stop_io_queues(ctrl);
		nvme_cancel_tagset(&ctrl->ctrl);
		nvme_rdma_destroy_io_queues(ctrl, new);
	पूर्ण
destroy_admin:
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	blk_sync_queue(ctrl->ctrl.admin_q);
	nvme_rdma_stop_queue(&ctrl->queues[0]);
	nvme_cancel_admin_tagset(&ctrl->ctrl);
	nvme_rdma_destroy_admin_queue(ctrl, new);
	वापस ret;
पूर्ण

अटल व्योम nvme_rdma_reconnect_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = container_of(to_delayed_work(work),
			काष्ठा nvme_rdma_ctrl, reconnect_work);

	++ctrl->ctrl.nr_reconnects;

	अगर (nvme_rdma_setup_ctrl(ctrl, false))
		जाओ requeue;

	dev_info(ctrl->ctrl.device, "Successfully reconnected (%d attempts)\n",
			ctrl->ctrl.nr_reconnects);

	ctrl->ctrl.nr_reconnects = 0;

	वापस;

requeue:
	dev_info(ctrl->ctrl.device, "Failed reconnect attempt %d\n",
			ctrl->ctrl.nr_reconnects);
	nvme_rdma_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल व्योम nvme_rdma_error_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = container_of(work,
			काष्ठा nvme_rdma_ctrl, err_work);

	nvme_stop_keep_alive(&ctrl->ctrl);
	nvme_rdma_tearकरोwn_io_queues(ctrl, false);
	nvme_start_queues(&ctrl->ctrl);
	nvme_rdma_tearकरोwn_admin_queue(ctrl, false);
	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING)) अणु
		/* state change failure is ok अगर we started ctrl delete */
		WARN_ON_ONCE(ctrl->ctrl.state != NVME_CTRL_DELETING &&
			     ctrl->ctrl.state != NVME_CTRL_DELETING_NOIO);
		वापस;
	पूर्ण

	nvme_rdma_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल व्योम nvme_rdma_error_recovery(काष्ठा nvme_rdma_ctrl *ctrl)
अणु
	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_RESETTING))
		वापस;

	dev_warn(ctrl->ctrl.device, "starting error recovery\n");
	queue_work(nvme_reset_wq, &ctrl->err_work);
पूर्ण

अटल व्योम nvme_rdma_end_request(काष्ठा nvme_rdma_request *req)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(req);

	अगर (!refcount_dec_and_test(&req->ref))
		वापस;
	अगर (!nvme_try_complete_req(rq, req->status, req->result))
		nvme_rdma_complete_rq(rq);
पूर्ण

अटल व्योम nvme_rdma_wr_error(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc,
		स्थिर अक्षर *op)
अणु
	काष्ठा nvme_rdma_queue *queue = wc->qp->qp_context;
	काष्ठा nvme_rdma_ctrl *ctrl = queue->ctrl;

	अगर (ctrl->ctrl.state == NVME_CTRL_LIVE)
		dev_info(ctrl->ctrl.device,
			     "%s for CQE 0x%p failed with status %s (%d)\n",
			     op, wc->wr_cqe,
			     ib_wc_status_msg(wc->status), wc->status);
	nvme_rdma_error_recovery(ctrl);
पूर्ण

अटल व्योम nvme_rdma_memreg_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "MEMREG");
पूर्ण

अटल व्योम nvme_rdma_inv_rkey_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvme_rdma_request *req =
		container_of(wc->wr_cqe, काष्ठा nvme_rdma_request, reg_cqe);

	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "LOCAL_INV");
	अन्यथा
		nvme_rdma_end_request(req);
पूर्ण

अटल पूर्णांक nvme_rdma_inv_rkey(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_request *req)
अणु
	काष्ठा ib_send_wr wr = अणु
		.opcode		    = IB_WR_LOCAL_INV,
		.next		    = शून्य,
		.num_sge	    = 0,
		.send_flags	    = IB_SEND_SIGNALED,
		.ex.invalidate_rkey = req->mr->rkey,
	पूर्ण;

	req->reg_cqe.करोne = nvme_rdma_inv_rkey_करोne;
	wr.wr_cqe = &req->reg_cqe;

	वापस ib_post_send(queue->qp, &wr, शून्य);
पूर्ण

अटल व्योम nvme_rdma_unmap_data(काष्ठा nvme_rdma_queue *queue,
		काष्ठा request *rq)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_device *dev = queue->device;
	काष्ठा ib_device *ibdev = dev->dev;
	काष्ठा list_head *pool = &queue->qp->rdma_mrs;

	अगर (!blk_rq_nr_phys_segments(rq))
		वापस;

	अगर (blk_पूर्णांकegrity_rq(rq)) अणु
		ib_dma_unmap_sg(ibdev, req->metadata_sgl->sg_table.sgl,
				req->metadata_sgl->nents, rq_dma_dir(rq));
		sg_मुक्त_table_chained(&req->metadata_sgl->sg_table,
				      NVME_INLINE_METADATA_SG_CNT);
	पूर्ण

	अगर (req->use_sig_mr)
		pool = &queue->qp->sig_mrs;

	अगर (req->mr) अणु
		ib_mr_pool_put(queue->qp, pool, req->mr);
		req->mr = शून्य;
	पूर्ण

	ib_dma_unmap_sg(ibdev, req->data_sgl.sg_table.sgl, req->data_sgl.nents,
			rq_dma_dir(rq));
	sg_मुक्त_table_chained(&req->data_sgl.sg_table, NVME_INLINE_SG_CNT);
पूर्ण

अटल पूर्णांक nvme_rdma_set_sg_null(काष्ठा nvme_command *c)
अणु
	काष्ठा nvme_keyed_sgl_desc *sg = &c->common.dptr.ksgl;

	sg->addr = 0;
	put_unaligned_le24(0, sg->length);
	put_unaligned_le32(0, sg->key);
	sg->type = NVME_KEY_SGL_FMT_DATA_DESC << 4;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_map_sg_अंतरभूत(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_request *req, काष्ठा nvme_command *c,
		पूर्णांक count)
अणु
	काष्ठा nvme_sgl_desc *sg = &c->common.dptr.sgl;
	काष्ठा ib_sge *sge = &req->sge[1];
	काष्ठा scatterlist *sgl;
	u32 len = 0;
	पूर्णांक i;

	क्रम_each_sg(req->data_sgl.sg_table.sgl, sgl, count, i) अणु
		sge->addr = sg_dma_address(sgl);
		sge->length = sg_dma_len(sgl);
		sge->lkey = queue->device->pd->local_dma_lkey;
		len += sge->length;
		sge++;
	पूर्ण

	sg->addr = cpu_to_le64(queue->ctrl->ctrl.icकरोff);
	sg->length = cpu_to_le32(len);
	sg->type = (NVME_SGL_FMT_DATA_DESC << 4) | NVME_SGL_FMT_OFFSET;

	req->num_sge += count;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_map_sg_single(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_request *req, काष्ठा nvme_command *c)
अणु
	काष्ठा nvme_keyed_sgl_desc *sg = &c->common.dptr.ksgl;

	sg->addr = cpu_to_le64(sg_dma_address(req->data_sgl.sg_table.sgl));
	put_unaligned_le24(sg_dma_len(req->data_sgl.sg_table.sgl), sg->length);
	put_unaligned_le32(queue->device->pd->unsafe_global_rkey, sg->key);
	sg->type = NVME_KEY_SGL_FMT_DATA_DESC << 4;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_rdma_map_sg_fr(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_request *req, काष्ठा nvme_command *c,
		पूर्णांक count)
अणु
	काष्ठा nvme_keyed_sgl_desc *sg = &c->common.dptr.ksgl;
	पूर्णांक nr;

	req->mr = ib_mr_pool_get(queue->qp, &queue->qp->rdma_mrs);
	अगर (WARN_ON_ONCE(!req->mr))
		वापस -EAGAIN;

	/*
	 * Align the MR to a 4K page size to match the ctrl page size and
	 * the block भव boundary.
	 */
	nr = ib_map_mr_sg(req->mr, req->data_sgl.sg_table.sgl, count, शून्य,
			  SZ_4K);
	अगर (unlikely(nr < count)) अणु
		ib_mr_pool_put(queue->qp, &queue->qp->rdma_mrs, req->mr);
		req->mr = शून्य;
		अगर (nr < 0)
			वापस nr;
		वापस -EINVAL;
	पूर्ण

	ib_update_fast_reg_key(req->mr, ib_inc_rkey(req->mr->rkey));

	req->reg_cqe.करोne = nvme_rdma_memreg_करोne;
	स_रखो(&req->reg_wr, 0, माप(req->reg_wr));
	req->reg_wr.wr.opcode = IB_WR_REG_MR;
	req->reg_wr.wr.wr_cqe = &req->reg_cqe;
	req->reg_wr.wr.num_sge = 0;
	req->reg_wr.mr = req->mr;
	req->reg_wr.key = req->mr->rkey;
	req->reg_wr.access = IB_ACCESS_LOCAL_WRITE |
			     IB_ACCESS_REMOTE_READ |
			     IB_ACCESS_REMOTE_WRITE;

	sg->addr = cpu_to_le64(req->mr->iova);
	put_unaligned_le24(req->mr->length, sg->length);
	put_unaligned_le32(req->mr->rkey, sg->key);
	sg->type = (NVME_KEY_SGL_FMT_DATA_DESC << 4) |
			NVME_SGL_FMT_INVALIDATE;

	वापस 0;
पूर्ण

अटल व्योम nvme_rdma_set_sig_करोमुख्य(काष्ठा blk_पूर्णांकegrity *bi,
		काष्ठा nvme_command *cmd, काष्ठा ib_sig_करोमुख्य *करोमुख्य,
		u16 control, u8 pi_type)
अणु
	करोमुख्य->sig_type = IB_SIG_TYPE_T10_DIF;
	करोमुख्य->sig.dअगर.bg_type = IB_T10DIF_CRC;
	करोमुख्य->sig.dअगर.pi_पूर्णांकerval = 1 << bi->पूर्णांकerval_exp;
	करोमुख्य->sig.dअगर.ref_tag = le32_to_cpu(cmd->rw.reftag);
	अगर (control & NVME_RW_PRINFO_PRCHK_REF)
		करोमुख्य->sig.dअगर.ref_remap = true;

	करोमुख्य->sig.dअगर.app_tag = le16_to_cpu(cmd->rw.apptag);
	करोमुख्य->sig.dअगर.apptag_check_mask = le16_to_cpu(cmd->rw.appmask);
	करोमुख्य->sig.dअगर.app_escape = true;
	अगर (pi_type == NVME_NS_DPS_PI_TYPE3)
		करोमुख्य->sig.dअगर.ref_escape = true;
पूर्ण

अटल व्योम nvme_rdma_set_sig_attrs(काष्ठा blk_पूर्णांकegrity *bi,
		काष्ठा nvme_command *cmd, काष्ठा ib_sig_attrs *sig_attrs,
		u8 pi_type)
अणु
	u16 control = le16_to_cpu(cmd->rw.control);

	स_रखो(sig_attrs, 0, माप(*sig_attrs));
	अगर (control & NVME_RW_PRINFO_PRACT) अणु
		/* क्रम WRITE_INSERT/READ_STRIP no memory करोमुख्य */
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		nvme_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->wire, control,
					 pi_type);
		/* Clear the PRACT bit since HCA will generate/verअगरy the PI */
		control &= ~NVME_RW_PRINFO_PRACT;
		cmd->rw.control = cpu_to_le16(control);
	पूर्ण अन्यथा अणु
		/* क्रम WRITE_PASS/READ_PASS both wire/memory करोमुख्यs exist */
		nvme_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->wire, control,
					 pi_type);
		nvme_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->mem, control,
					 pi_type);
	पूर्ण
पूर्ण

अटल व्योम nvme_rdma_set_prot_checks(काष्ठा nvme_command *cmd, u8 *mask)
अणु
	*mask = 0;
	अगर (le16_to_cpu(cmd->rw.control) & NVME_RW_PRINFO_PRCHK_REF)
		*mask |= IB_SIG_CHECK_REFTAG;
	अगर (le16_to_cpu(cmd->rw.control) & NVME_RW_PRINFO_PRCHK_GUARD)
		*mask |= IB_SIG_CHECK_GUARD;
पूर्ण

अटल व्योम nvme_rdma_sig_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "SIG");
पूर्ण

अटल पूर्णांक nvme_rdma_map_sg_pi(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_request *req, काष्ठा nvme_command *c,
		पूर्णांक count, पूर्णांक pi_count)
अणु
	काष्ठा nvme_rdma_sgl *sgl = &req->data_sgl;
	काष्ठा ib_reg_wr *wr = &req->reg_wr;
	काष्ठा request *rq = blk_mq_rq_from_pdu(req);
	काष्ठा nvme_ns *ns = rq->q->queuedata;
	काष्ठा bio *bio = rq->bio;
	काष्ठा nvme_keyed_sgl_desc *sg = &c->common.dptr.ksgl;
	पूर्णांक nr;

	req->mr = ib_mr_pool_get(queue->qp, &queue->qp->sig_mrs);
	अगर (WARN_ON_ONCE(!req->mr))
		वापस -EAGAIN;

	nr = ib_map_mr_sg_pi(req->mr, sgl->sg_table.sgl, count, शून्य,
			     req->metadata_sgl->sg_table.sgl, pi_count, शून्य,
			     SZ_4K);
	अगर (unlikely(nr))
		जाओ mr_put;

	nvme_rdma_set_sig_attrs(blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk), c,
				req->mr->sig_attrs, ns->pi_type);
	nvme_rdma_set_prot_checks(c, &req->mr->sig_attrs->check_mask);

	ib_update_fast_reg_key(req->mr, ib_inc_rkey(req->mr->rkey));

	req->reg_cqe.करोne = nvme_rdma_sig_करोne;
	स_रखो(wr, 0, माप(*wr));
	wr->wr.opcode = IB_WR_REG_MR_INTEGRITY;
	wr->wr.wr_cqe = &req->reg_cqe;
	wr->wr.num_sge = 0;
	wr->wr.send_flags = 0;
	wr->mr = req->mr;
	wr->key = req->mr->rkey;
	wr->access = IB_ACCESS_LOCAL_WRITE |
		     IB_ACCESS_REMOTE_READ |
		     IB_ACCESS_REMOTE_WRITE;

	sg->addr = cpu_to_le64(req->mr->iova);
	put_unaligned_le24(req->mr->length, sg->length);
	put_unaligned_le32(req->mr->rkey, sg->key);
	sg->type = NVME_KEY_SGL_FMT_DATA_DESC << 4;

	वापस 0;

mr_put:
	ib_mr_pool_put(queue->qp, &queue->qp->sig_mrs, req->mr);
	req->mr = शून्य;
	अगर (nr < 0)
		वापस nr;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nvme_rdma_map_data(काष्ठा nvme_rdma_queue *queue,
		काष्ठा request *rq, काष्ठा nvme_command *c)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_device *dev = queue->device;
	काष्ठा ib_device *ibdev = dev->dev;
	पूर्णांक pi_count = 0;
	पूर्णांक count, ret;

	req->num_sge = 1;
	refcount_set(&req->ref, 2); /* send and recv completions */

	c->common.flags |= NVME_CMD_SGL_METABUF;

	अगर (!blk_rq_nr_phys_segments(rq))
		वापस nvme_rdma_set_sg_null(c);

	req->data_sgl.sg_table.sgl = (काष्ठा scatterlist *)(req + 1);
	ret = sg_alloc_table_chained(&req->data_sgl.sg_table,
			blk_rq_nr_phys_segments(rq), req->data_sgl.sg_table.sgl,
			NVME_INLINE_SG_CNT);
	अगर (ret)
		वापस -ENOMEM;

	req->data_sgl.nents = blk_rq_map_sg(rq->q, rq,
					    req->data_sgl.sg_table.sgl);

	count = ib_dma_map_sg(ibdev, req->data_sgl.sg_table.sgl,
			      req->data_sgl.nents, rq_dma_dir(rq));
	अगर (unlikely(count <= 0)) अणु
		ret = -EIO;
		जाओ out_मुक्त_table;
	पूर्ण

	अगर (blk_पूर्णांकegrity_rq(rq)) अणु
		req->metadata_sgl->sg_table.sgl =
			(काष्ठा scatterlist *)(req->metadata_sgl + 1);
		ret = sg_alloc_table_chained(&req->metadata_sgl->sg_table,
				blk_rq_count_पूर्णांकegrity_sg(rq->q, rq->bio),
				req->metadata_sgl->sg_table.sgl,
				NVME_INLINE_METADATA_SG_CNT);
		अगर (unlikely(ret)) अणु
			ret = -ENOMEM;
			जाओ out_unmap_sg;
		पूर्ण

		req->metadata_sgl->nents = blk_rq_map_पूर्णांकegrity_sg(rq->q,
				rq->bio, req->metadata_sgl->sg_table.sgl);
		pi_count = ib_dma_map_sg(ibdev,
					 req->metadata_sgl->sg_table.sgl,
					 req->metadata_sgl->nents,
					 rq_dma_dir(rq));
		अगर (unlikely(pi_count <= 0)) अणु
			ret = -EIO;
			जाओ out_मुक्त_pi_table;
		पूर्ण
	पूर्ण

	अगर (req->use_sig_mr) अणु
		ret = nvme_rdma_map_sg_pi(queue, req, c, count, pi_count);
		जाओ out;
	पूर्ण

	अगर (count <= dev->num_अंतरभूत_segments) अणु
		अगर (rq_data_dir(rq) == WRITE && nvme_rdma_queue_idx(queue) &&
		    queue->ctrl->use_अंतरभूत_data &&
		    blk_rq_payload_bytes(rq) <=
				nvme_rdma_अंतरभूत_data_size(queue)) अणु
			ret = nvme_rdma_map_sg_अंतरभूत(queue, req, c, count);
			जाओ out;
		पूर्ण

		अगर (count == 1 && dev->pd->flags & IB_PD_UNSAFE_GLOBAL_RKEY) अणु
			ret = nvme_rdma_map_sg_single(queue, req, c);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = nvme_rdma_map_sg_fr(queue, req, c, count);
out:
	अगर (unlikely(ret))
		जाओ out_unmap_pi_sg;

	वापस 0;

out_unmap_pi_sg:
	अगर (blk_पूर्णांकegrity_rq(rq))
		ib_dma_unmap_sg(ibdev, req->metadata_sgl->sg_table.sgl,
				req->metadata_sgl->nents, rq_dma_dir(rq));
out_मुक्त_pi_table:
	अगर (blk_पूर्णांकegrity_rq(rq))
		sg_मुक्त_table_chained(&req->metadata_sgl->sg_table,
				      NVME_INLINE_METADATA_SG_CNT);
out_unmap_sg:
	ib_dma_unmap_sg(ibdev, req->data_sgl.sg_table.sgl, req->data_sgl.nents,
			rq_dma_dir(rq));
out_मुक्त_table:
	sg_मुक्त_table_chained(&req->data_sgl.sg_table, NVME_INLINE_SG_CNT);
	वापस ret;
पूर्ण

अटल व्योम nvme_rdma_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvme_rdma_qe *qe =
		container_of(wc->wr_cqe, काष्ठा nvme_rdma_qe, cqe);
	काष्ठा nvme_rdma_request *req =
		container_of(qe, काष्ठा nvme_rdma_request, sqe);

	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "SEND");
	अन्यथा
		nvme_rdma_end_request(req);
पूर्ण

अटल पूर्णांक nvme_rdma_post_send(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_qe *qe, काष्ठा ib_sge *sge, u32 num_sge,
		काष्ठा ib_send_wr *first)
अणु
	काष्ठा ib_send_wr wr;
	पूर्णांक ret;

	sge->addr   = qe->dma;
	sge->length = माप(काष्ठा nvme_command);
	sge->lkey   = queue->device->pd->local_dma_lkey;

	wr.next       = शून्य;
	wr.wr_cqe     = &qe->cqe;
	wr.sg_list    = sge;
	wr.num_sge    = num_sge;
	wr.opcode     = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	अगर (first)
		first->next = &wr;
	अन्यथा
		first = &wr;

	ret = ib_post_send(queue->qp, first, शून्य);
	अगर (unlikely(ret)) अणु
		dev_err(queue->ctrl->ctrl.device,
			     "%s failed with error code %d\n", __func__, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_post_recv(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_rdma_qe *qe)
अणु
	काष्ठा ib_recv_wr wr;
	काष्ठा ib_sge list;
	पूर्णांक ret;

	list.addr   = qe->dma;
	list.length = माप(काष्ठा nvme_completion);
	list.lkey   = queue->device->pd->local_dma_lkey;

	qe->cqe.करोne = nvme_rdma_recv_करोne;

	wr.next     = शून्य;
	wr.wr_cqe   = &qe->cqe;
	wr.sg_list  = &list;
	wr.num_sge  = 1;

	ret = ib_post_recv(queue->qp, &wr, शून्य);
	अगर (unlikely(ret)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"%s failed with error code %d\n", __func__, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा blk_mq_tags *nvme_rdma_tagset(काष्ठा nvme_rdma_queue *queue)
अणु
	u32 queue_idx = nvme_rdma_queue_idx(queue);

	अगर (queue_idx == 0)
		वापस queue->ctrl->admin_tag_set.tags[queue_idx];
	वापस queue->ctrl->tag_set.tags[queue_idx - 1];
पूर्ण

अटल व्योम nvme_rdma_async_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		nvme_rdma_wr_error(cq, wc, "ASYNC");
पूर्ण

अटल व्योम nvme_rdma_submit_async_event(काष्ठा nvme_ctrl *arg)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = to_rdma_ctrl(arg);
	काष्ठा nvme_rdma_queue *queue = &ctrl->queues[0];
	काष्ठा ib_device *dev = queue->device->dev;
	काष्ठा nvme_rdma_qe *sqe = &ctrl->async_event_sqe;
	काष्ठा nvme_command *cmd = sqe->data;
	काष्ठा ib_sge sge;
	पूर्णांक ret;

	ib_dma_sync_single_क्रम_cpu(dev, sqe->dma, माप(*cmd), DMA_TO_DEVICE);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->common.opcode = nvme_admin_async_event;
	cmd->common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	cmd->common.flags |= NVME_CMD_SGL_METABUF;
	nvme_rdma_set_sg_null(cmd);

	sqe->cqe.करोne = nvme_rdma_async_करोne;

	ib_dma_sync_single_क्रम_device(dev, sqe->dma, माप(*cmd),
			DMA_TO_DEVICE);

	ret = nvme_rdma_post_send(queue, sqe, &sge, 1, शून्य);
	WARN_ON_ONCE(ret);
पूर्ण

अटल व्योम nvme_rdma_process_nvme_rsp(काष्ठा nvme_rdma_queue *queue,
		काष्ठा nvme_completion *cqe, काष्ठा ib_wc *wc)
अणु
	काष्ठा request *rq;
	काष्ठा nvme_rdma_request *req;

	rq = blk_mq_tag_to_rq(nvme_rdma_tagset(queue), cqe->command_id);
	अगर (!rq) अणु
		dev_err(queue->ctrl->ctrl.device,
			"tag 0x%x on QP %#x not found\n",
			cqe->command_id, queue->qp->qp_num);
		nvme_rdma_error_recovery(queue->ctrl);
		वापस;
	पूर्ण
	req = blk_mq_rq_to_pdu(rq);

	req->status = cqe->status;
	req->result = cqe->result;

	अगर (wc->wc_flags & IB_WC_WITH_INVALIDATE) अणु
		अगर (unlikely(!req->mr ||
			     wc->ex.invalidate_rkey != req->mr->rkey)) अणु
			dev_err(queue->ctrl->ctrl.device,
				"Bogus remote invalidation for rkey %#x\n",
				req->mr ? req->mr->rkey : 0);
			nvme_rdma_error_recovery(queue->ctrl);
		पूर्ण
	पूर्ण अन्यथा अगर (req->mr) अणु
		पूर्णांक ret;

		ret = nvme_rdma_inv_rkey(queue, req);
		अगर (unlikely(ret < 0)) अणु
			dev_err(queue->ctrl->ctrl.device,
				"Queueing INV WR for rkey %#x failed (%d)\n",
				req->mr->rkey, ret);
			nvme_rdma_error_recovery(queue->ctrl);
		पूर्ण
		/* the local invalidation completion will end the request */
		वापस;
	पूर्ण

	nvme_rdma_end_request(req);
पूर्ण

अटल व्योम nvme_rdma_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvme_rdma_qe *qe =
		container_of(wc->wr_cqe, काष्ठा nvme_rdma_qe, cqe);
	काष्ठा nvme_rdma_queue *queue = wc->qp->qp_context;
	काष्ठा ib_device *ibdev = queue->device->dev;
	काष्ठा nvme_completion *cqe = qe->data;
	स्थिर माप_प्रकार len = माप(काष्ठा nvme_completion);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		nvme_rdma_wr_error(cq, wc, "RECV");
		वापस;
	पूर्ण

	/* sanity checking क्रम received data length */
	अगर (unlikely(wc->byte_len < len)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"Unexpected nvme completion length(%d)\n", wc->byte_len);
		nvme_rdma_error_recovery(queue->ctrl);
		वापस;
	पूर्ण

	ib_dma_sync_single_क्रम_cpu(ibdev, qe->dma, len, DMA_FROM_DEVICE);
	/*
	 * AEN requests are special as they करोn't समय out and can
	 * survive any kind of queue मुक्तze and often करोn't respond to
	 * पातs.  We करोn't even bother to allocate a काष्ठा request
	 * क्रम them but rather special हाल them here.
	 */
	अगर (unlikely(nvme_is_aen_req(nvme_rdma_queue_idx(queue),
				     cqe->command_id)))
		nvme_complete_async_event(&queue->ctrl->ctrl, cqe->status,
				&cqe->result);
	अन्यथा
		nvme_rdma_process_nvme_rsp(queue, cqe, wc);
	ib_dma_sync_single_क्रम_device(ibdev, qe->dma, len, DMA_FROM_DEVICE);

	nvme_rdma_post_recv(queue, qe);
पूर्ण

अटल पूर्णांक nvme_rdma_conn_established(काष्ठा nvme_rdma_queue *queue)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < queue->queue_size; i++) अणु
		ret = nvme_rdma_post_recv(queue, &queue->rsp_ring[i]);
		अगर (ret)
			जाओ out_destroy_queue_ib;
	पूर्ण

	वापस 0;

out_destroy_queue_ib:
	nvme_rdma_destroy_queue_ib(queue);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_conn_rejected(काष्ठा nvme_rdma_queue *queue,
		काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा rdma_cm_id *cm_id = queue->cm_id;
	पूर्णांक status = ev->status;
	स्थिर अक्षर *rej_msg;
	स्थिर काष्ठा nvme_rdma_cm_rej *rej_data;
	u8 rej_data_len;

	rej_msg = rdma_reject_msg(cm_id, status);
	rej_data = rdma_consumer_reject_data(cm_id, ev, &rej_data_len);

	अगर (rej_data && rej_data_len >= माप(u16)) अणु
		u16 sts = le16_to_cpu(rej_data->sts);

		dev_err(queue->ctrl->ctrl.device,
		      "Connect rejected: status %d (%s) nvme status %d (%s).\n",
		      status, rej_msg, sts, nvme_rdma_cm_msg(sts));
	पूर्ण अन्यथा अणु
		dev_err(queue->ctrl->ctrl.device,
			"Connect rejected: status %d (%s).\n", status, rej_msg);
	पूर्ण

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक nvme_rdma_addr_resolved(काष्ठा nvme_rdma_queue *queue)
अणु
	काष्ठा nvme_ctrl *ctrl = &queue->ctrl->ctrl;
	पूर्णांक ret;

	ret = nvme_rdma_create_queue_ib(queue);
	अगर (ret)
		वापस ret;

	अगर (ctrl->opts->tos >= 0)
		rdma_set_service_type(queue->cm_id, ctrl->opts->tos);
	ret = rdma_resolve_route(queue->cm_id, NVME_RDMA_CONNECT_TIMEOUT_MS);
	अगर (ret) अणु
		dev_err(ctrl->device, "rdma_resolve_route failed (%d).\n",
			queue->cm_error);
		जाओ out_destroy_queue;
	पूर्ण

	वापस 0;

out_destroy_queue:
	nvme_rdma_destroy_queue_ib(queue);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_route_resolved(काष्ठा nvme_rdma_queue *queue)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = queue->ctrl;
	काष्ठा rdma_conn_param param = अणु पूर्ण;
	काष्ठा nvme_rdma_cm_req priv = अणु पूर्ण;
	पूर्णांक ret;

	param.qp_num = queue->qp->qp_num;
	param.flow_control = 1;

	param.responder_resources = queue->device->dev->attrs.max_qp_rd_atom;
	/* maximum retry count */
	param.retry_count = 7;
	param.rnr_retry_count = 7;
	param.निजी_data = &priv;
	param.निजी_data_len = माप(priv);

	priv.recfmt = cpu_to_le16(NVME_RDMA_CM_FMT_1_0);
	priv.qid = cpu_to_le16(nvme_rdma_queue_idx(queue));
	/*
	 * set the admin queue depth to the minimum size
	 * specअगरied by the Fabrics standard.
	 */
	अगर (priv.qid == 0) अणु
		priv.hrqsize = cpu_to_le16(NVME_AQ_DEPTH);
		priv.hsqsize = cpu_to_le16(NVME_AQ_DEPTH - 1);
	पूर्ण अन्यथा अणु
		/*
		 * current पूर्णांकerpretation of the fabrics spec
		 * is at minimum you make hrqsize sqsize+1, or a
		 * 1's based representation of sqsize.
		 */
		priv.hrqsize = cpu_to_le16(queue->queue_size);
		priv.hsqsize = cpu_to_le16(queue->ctrl->ctrl.sqsize);
	पूर्ण

	ret = rdma_connect_locked(queue->cm_id, &param);
	अगर (ret) अणु
		dev_err(ctrl->ctrl.device,
			"rdma_connect_locked failed (%d).\n", ret);
		जाओ out_destroy_queue_ib;
	पूर्ण

	वापस 0;

out_destroy_queue_ib:
	nvme_rdma_destroy_queue_ib(queue);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
		काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा nvme_rdma_queue *queue = cm_id->context;
	पूर्णांक cm_error = 0;

	dev_dbg(queue->ctrl->ctrl.device, "%s (%d): status %d id %p\n",
		rdma_event_msg(ev->event), ev->event,
		ev->status, cm_id);

	चयन (ev->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		cm_error = nvme_rdma_addr_resolved(queue);
		अवरोध;
	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		cm_error = nvme_rdma_route_resolved(queue);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		queue->cm_error = nvme_rdma_conn_established(queue);
		/* complete cm_करोne regardless of success/failure */
		complete(&queue->cm_करोne);
		वापस 0;
	हाल RDMA_CM_EVENT_REJECTED:
		cm_error = nvme_rdma_conn_rejected(queue, ev);
		अवरोध;
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
		nvme_rdma_destroy_queue_ib(queue);
		fallthrough;
	हाल RDMA_CM_EVENT_ADDR_ERROR:
		dev_dbg(queue->ctrl->ctrl.device,
			"CM error event %d\n", ev->event);
		cm_error = -ECONNRESET;
		अवरोध;
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		dev_dbg(queue->ctrl->ctrl.device,
			"disconnect received - connection closed\n");
		nvme_rdma_error_recovery(queue->ctrl);
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		/* device removal is handled via the ib_client API */
		अवरोध;
	शेष:
		dev_err(queue->ctrl->ctrl.device,
			"Unexpected RDMA CM event (%d)\n", ev->event);
		nvme_rdma_error_recovery(queue->ctrl);
		अवरोध;
	पूर्ण

	अगर (cm_error) अणु
		queue->cm_error = cm_error;
		complete(&queue->cm_करोne);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvme_rdma_complete_समयd_out(काष्ठा request *rq)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_queue *queue = req->queue;

	nvme_rdma_stop_queue(queue);
	अगर (blk_mq_request_started(rq) && !blk_mq_request_completed(rq)) अणु
		nvme_req(rq)->status = NVME_SC_HOST_ABORTED_CMD;
		blk_mq_complete_request(rq);
	पूर्ण
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस
nvme_rdma_समयout(काष्ठा request *rq, bool reserved)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_queue *queue = req->queue;
	काष्ठा nvme_rdma_ctrl *ctrl = queue->ctrl;

	dev_warn(ctrl->ctrl.device, "I/O %d QID %d timeout\n",
		 rq->tag, nvme_rdma_queue_idx(queue));

	अगर (ctrl->ctrl.state != NVME_CTRL_LIVE) अणु
		/*
		 * If we are resetting, connecting or deleting we should
		 * complete immediately because we may block controller
		 * tearकरोwn or setup sequence
		 * - ctrl disable/shutकरोwn fabrics requests
		 * - connect requests
		 * - initialization admin requests
		 * - I/O requests that entered after unquiescing and
		 *   the controller stopped responding
		 *
		 * All other requests should be cancelled by the error
		 * recovery work, so it's fine that we fail it here.
		 */
		nvme_rdma_complete_समयd_out(rq);
		वापस BLK_EH_DONE;
	पूर्ण

	/*
	 * LIVE state should trigger the normal error recovery which will
	 * handle completing this request.
	 */
	nvme_rdma_error_recovery(ctrl);
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल blk_status_t nvme_rdma_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
		स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nvme_ns *ns = hctx->queue->queuedata;
	काष्ठा nvme_rdma_queue *queue = hctx->driver_data;
	काष्ठा request *rq = bd->rq;
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_qe *sqe = &req->sqe;
	काष्ठा nvme_command *c = nvme_req(rq)->cmd;
	काष्ठा ib_device *dev;
	bool queue_पढ़ोy = test_bit(NVME_RDMA_Q_LIVE, &queue->flags);
	blk_status_t ret;
	पूर्णांक err;

	WARN_ON_ONCE(rq->tag < 0);

	अगर (!nvme_check_पढ़ोy(&queue->ctrl->ctrl, rq, queue_पढ़ोy))
		वापस nvme_fail_nonपढ़ोy_command(&queue->ctrl->ctrl, rq);

	dev = queue->device->dev;

	req->sqe.dma = ib_dma_map_single(dev, req->sqe.data,
					 माप(काष्ठा nvme_command),
					 DMA_TO_DEVICE);
	err = ib_dma_mapping_error(dev, req->sqe.dma);
	अगर (unlikely(err))
		वापस BLK_STS_RESOURCE;

	ib_dma_sync_single_क्रम_cpu(dev, sqe->dma,
			माप(काष्ठा nvme_command), DMA_TO_DEVICE);

	ret = nvme_setup_cmd(ns, rq);
	अगर (ret)
		जाओ unmap_qe;

	blk_mq_start_request(rq);

	अगर (IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY) &&
	    queue->pi_support &&
	    (c->common.opcode == nvme_cmd_ग_लिखो ||
	     c->common.opcode == nvme_cmd_पढ़ो) &&
	    nvme_ns_has_pi(ns))
		req->use_sig_mr = true;
	अन्यथा
		req->use_sig_mr = false;

	err = nvme_rdma_map_data(queue, rq, c);
	अगर (unlikely(err < 0)) अणु
		dev_err(queue->ctrl->ctrl.device,
			     "Failed to map data (%d)\n", err);
		जाओ err;
	पूर्ण

	sqe->cqe.करोne = nvme_rdma_send_करोne;

	ib_dma_sync_single_क्रम_device(dev, sqe->dma,
			माप(काष्ठा nvme_command), DMA_TO_DEVICE);

	err = nvme_rdma_post_send(queue, sqe, req->sge, req->num_sge,
			req->mr ? &req->reg_wr.wr : शून्य);
	अगर (unlikely(err))
		जाओ err_unmap;

	वापस BLK_STS_OK;

err_unmap:
	nvme_rdma_unmap_data(queue, rq);
err:
	अगर (err == -EIO)
		ret = nvme_host_path_error(rq);
	अन्यथा अगर (err == -ENOMEM || err == -EAGAIN)
		ret = BLK_STS_RESOURCE;
	अन्यथा
		ret = BLK_STS_IOERR;
	nvme_cleanup_cmd(rq);
unmap_qe:
	ib_dma_unmap_single(dev, req->sqe.dma, माप(काष्ठा nvme_command),
			    DMA_TO_DEVICE);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_rdma_poll(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा nvme_rdma_queue *queue = hctx->driver_data;

	वापस ib_process_cq_direct(queue->ib_cq, -1);
पूर्ण

अटल व्योम nvme_rdma_check_pi_status(काष्ठा nvme_rdma_request *req)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(req);
	काष्ठा ib_mr_status mr_status;
	पूर्णांक ret;

	ret = ib_check_mr_status(req->mr, IB_MR_CHECK_SIG_STATUS, &mr_status);
	अगर (ret) अणु
		pr_err("ib_check_mr_status failed, ret %d\n", ret);
		nvme_req(rq)->status = NVME_SC_INVALID_PI;
		वापस;
	पूर्ण

	अगर (mr_status.fail_status & IB_MR_CHECK_SIG_STATUS) अणु
		चयन (mr_status.sig_err.err_type) अणु
		हाल IB_SIG_BAD_GUARD:
			nvme_req(rq)->status = NVME_SC_GUARD_CHECK;
			अवरोध;
		हाल IB_SIG_BAD_REFTAG:
			nvme_req(rq)->status = NVME_SC_REFTAG_CHECK;
			अवरोध;
		हाल IB_SIG_BAD_APPTAG:
			nvme_req(rq)->status = NVME_SC_APPTAG_CHECK;
			अवरोध;
		पूर्ण
		pr_err("PI error found type %d expected 0x%x vs actual 0x%x\n",
		       mr_status.sig_err.err_type, mr_status.sig_err.expected,
		       mr_status.sig_err.actual);
	पूर्ण
पूर्ण

अटल व्योम nvme_rdma_complete_rq(काष्ठा request *rq)
अणु
	काष्ठा nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_rdma_queue *queue = req->queue;
	काष्ठा ib_device *ibdev = queue->device->dev;

	अगर (req->use_sig_mr)
		nvme_rdma_check_pi_status(req);

	nvme_rdma_unmap_data(queue, rq);
	ib_dma_unmap_single(ibdev, req->sqe.dma, माप(काष्ठा nvme_command),
			    DMA_TO_DEVICE);
	nvme_complete_rq(rq);
पूर्ण

अटल पूर्णांक nvme_rdma_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl = set->driver_data;
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;

	अगर (opts->nr_ग_लिखो_queues && ctrl->io_queues[HCTX_TYPE_READ]) अणु
		/* separate पढ़ो/ग_लिखो queues */
		set->map[HCTX_TYPE_DEFAULT].nr_queues =
			ctrl->io_queues[HCTX_TYPE_DEFAULT];
		set->map[HCTX_TYPE_DEFAULT].queue_offset = 0;
		set->map[HCTX_TYPE_READ].nr_queues =
			ctrl->io_queues[HCTX_TYPE_READ];
		set->map[HCTX_TYPE_READ].queue_offset =
			ctrl->io_queues[HCTX_TYPE_DEFAULT];
	पूर्ण अन्यथा अणु
		/* shared पढ़ो/ग_लिखो queues */
		set->map[HCTX_TYPE_DEFAULT].nr_queues =
			ctrl->io_queues[HCTX_TYPE_DEFAULT];
		set->map[HCTX_TYPE_DEFAULT].queue_offset = 0;
		set->map[HCTX_TYPE_READ].nr_queues =
			ctrl->io_queues[HCTX_TYPE_DEFAULT];
		set->map[HCTX_TYPE_READ].queue_offset = 0;
	पूर्ण
	blk_mq_rdma_map_queues(&set->map[HCTX_TYPE_DEFAULT],
			ctrl->device->dev, 0);
	blk_mq_rdma_map_queues(&set->map[HCTX_TYPE_READ],
			ctrl->device->dev, 0);

	अगर (opts->nr_poll_queues && ctrl->io_queues[HCTX_TYPE_POLL]) अणु
		/* map dedicated poll queues only अगर we have queues left */
		set->map[HCTX_TYPE_POLL].nr_queues =
				ctrl->io_queues[HCTX_TYPE_POLL];
		set->map[HCTX_TYPE_POLL].queue_offset =
			ctrl->io_queues[HCTX_TYPE_DEFAULT] +
			ctrl->io_queues[HCTX_TYPE_READ];
		blk_mq_map_queues(&set->map[HCTX_TYPE_POLL]);
	पूर्ण

	dev_info(ctrl->ctrl.device,
		"mapped %d/%d/%d default/read/poll queues.\n",
		ctrl->io_queues[HCTX_TYPE_DEFAULT],
		ctrl->io_queues[HCTX_TYPE_READ],
		ctrl->io_queues[HCTX_TYPE_POLL]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops nvme_rdma_mq_ops = अणु
	.queue_rq	= nvme_rdma_queue_rq,
	.complete	= nvme_rdma_complete_rq,
	.init_request	= nvme_rdma_init_request,
	.निकास_request	= nvme_rdma_निकास_request,
	.init_hctx	= nvme_rdma_init_hctx,
	.समयout	= nvme_rdma_समयout,
	.map_queues	= nvme_rdma_map_queues,
	.poll		= nvme_rdma_poll,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops nvme_rdma_admin_mq_ops = अणु
	.queue_rq	= nvme_rdma_queue_rq,
	.complete	= nvme_rdma_complete_rq,
	.init_request	= nvme_rdma_init_request,
	.निकास_request	= nvme_rdma_निकास_request,
	.init_hctx	= nvme_rdma_init_admin_hctx,
	.समयout	= nvme_rdma_समयout,
पूर्ण;

अटल व्योम nvme_rdma_shutकरोwn_ctrl(काष्ठा nvme_rdma_ctrl *ctrl, bool shutकरोwn)
अणु
	cancel_work_sync(&ctrl->err_work);
	cancel_delayed_work_sync(&ctrl->reconnect_work);

	nvme_rdma_tearकरोwn_io_queues(ctrl, shutकरोwn);
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	अगर (shutकरोwn)
		nvme_shutकरोwn_ctrl(&ctrl->ctrl);
	अन्यथा
		nvme_disable_ctrl(&ctrl->ctrl);
	nvme_rdma_tearकरोwn_admin_queue(ctrl, shutकरोwn);
पूर्ण

अटल व्योम nvme_rdma_delete_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_rdma_shutकरोwn_ctrl(to_rdma_ctrl(ctrl), true);
पूर्ण

अटल व्योम nvme_rdma_reset_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl =
		container_of(work, काष्ठा nvme_rdma_ctrl, ctrl.reset_work);

	nvme_stop_ctrl(&ctrl->ctrl);
	nvme_rdma_shutकरोwn_ctrl(ctrl, false);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING)) अणु
		/* state change failure should never happen */
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (nvme_rdma_setup_ctrl(ctrl, false))
		जाओ out_fail;

	वापस;

out_fail:
	++ctrl->ctrl.nr_reconnects;
	nvme_rdma_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल स्थिर काष्ठा nvme_ctrl_ops nvme_rdma_ctrl_ops = अणु
	.name			= "rdma",
	.module			= THIS_MODULE,
	.flags			= NVME_F_FABRICS | NVME_F_METADATA_SUPPORTED,
	.reg_पढ़ो32		= nvmf_reg_पढ़ो32,
	.reg_पढ़ो64		= nvmf_reg_पढ़ो64,
	.reg_ग_लिखो32		= nvmf_reg_ग_लिखो32,
	.मुक्त_ctrl		= nvme_rdma_मुक्त_ctrl,
	.submit_async_event	= nvme_rdma_submit_async_event,
	.delete_ctrl		= nvme_rdma_delete_ctrl,
	.get_address		= nvmf_get_address,
पूर्ण;

/*
 * Fails a connection request अगर it matches an existing controller
 * (association) with the same tuple:
 * <Host NQN, Host ID, local address, remote address, remote port, SUBSYS NQN>
 *
 * अगर local address is not specअगरied in the request, it will match an
 * existing controller with all the other parameters the same and no
 * local port address specअगरied as well.
 *
 * The ports करोn't need to be compared as they are पूर्णांकrinsically
 * alपढ़ोy matched by the port poपूर्णांकers supplied.
 */
अटल bool
nvme_rdma_existing_controller(काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl;
	bool found = false;

	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_rdma_ctrl_list, list) अणु
		found = nvmf_ip_options_match(&ctrl->ctrl, opts);
		अगर (found)
			अवरोध;
	पूर्ण
	mutex_unlock(&nvme_rdma_ctrl_mutex);

	वापस found;
पूर्ण

अटल काष्ठा nvme_ctrl *nvme_rdma_create_ctrl(काष्ठा device *dev,
		काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl;
	पूर्णांक ret;
	bool changed;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);
	ctrl->ctrl.opts = opts;
	INIT_LIST_HEAD(&ctrl->list);

	अगर (!(opts->mask & NVMF_OPT_TRSVCID)) अणु
		opts->trsvcid =
			kstrdup(__stringअगरy(NVME_RDMA_IP_PORT), GFP_KERNEL);
		अगर (!opts->trsvcid) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_ctrl;
		पूर्ण
		opts->mask |= NVMF_OPT_TRSVCID;
	पूर्ण

	ret = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->traddr, opts->trsvcid, &ctrl->addr);
	अगर (ret) अणु
		pr_err("malformed address passed: %s:%s\n",
			opts->traddr, opts->trsvcid);
		जाओ out_मुक्त_ctrl;
	पूर्ण

	अगर (opts->mask & NVMF_OPT_HOST_TRADDR) अणु
		ret = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->host_traddr, शून्य, &ctrl->src_addr);
		अगर (ret) अणु
			pr_err("malformed src address passed: %s\n",
			       opts->host_traddr);
			जाओ out_मुक्त_ctrl;
		पूर्ण
	पूर्ण

	अगर (!opts->duplicate_connect && nvme_rdma_existing_controller(opts)) अणु
		ret = -EALREADY;
		जाओ out_मुक्त_ctrl;
	पूर्ण

	INIT_DELAYED_WORK(&ctrl->reconnect_work,
			nvme_rdma_reconnect_ctrl_work);
	INIT_WORK(&ctrl->err_work, nvme_rdma_error_recovery_work);
	INIT_WORK(&ctrl->ctrl.reset_work, nvme_rdma_reset_ctrl_work);

	ctrl->ctrl.queue_count = opts->nr_io_queues + opts->nr_ग_लिखो_queues +
				opts->nr_poll_queues + 1;
	ctrl->ctrl.sqsize = opts->queue_size - 1;
	ctrl->ctrl.kato = opts->kato;

	ret = -ENOMEM;
	ctrl->queues = kसुस्मृति(ctrl->ctrl.queue_count, माप(*ctrl->queues),
				GFP_KERNEL);
	अगर (!ctrl->queues)
		जाओ out_मुक्त_ctrl;

	ret = nvme_init_ctrl(&ctrl->ctrl, dev, &nvme_rdma_ctrl_ops,
				0 /* no quirks, we're perfect! */);
	अगर (ret)
		जाओ out_kमुक्त_queues;

	changed = nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING);
	WARN_ON_ONCE(!changed);

	ret = nvme_rdma_setup_ctrl(ctrl, true);
	अगर (ret)
		जाओ out_uninit_ctrl;

	dev_info(ctrl->ctrl.device, "new ctrl: NQN \"%s\", addr %pISpcs\n",
		ctrl->ctrl.opts->subsysnqn, &ctrl->addr);

	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_add_tail(&ctrl->list, &nvme_rdma_ctrl_list);
	mutex_unlock(&nvme_rdma_ctrl_mutex);

	वापस &ctrl->ctrl;

out_uninit_ctrl:
	nvme_uninit_ctrl(&ctrl->ctrl);
	nvme_put_ctrl(&ctrl->ctrl);
	अगर (ret > 0)
		ret = -EIO;
	वापस ERR_PTR(ret);
out_kमुक्त_queues:
	kमुक्त(ctrl->queues);
out_मुक्त_ctrl:
	kमुक्त(ctrl);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा nvmf_transport_ops nvme_rdma_transport = अणु
	.name		= "rdma",
	.module		= THIS_MODULE,
	.required_opts	= NVMF_OPT_TRADDR,
	.allowed_opts	= NVMF_OPT_TRSVCID | NVMF_OPT_RECONNECT_DELAY |
			  NVMF_OPT_HOST_TRADDR | NVMF_OPT_CTRL_LOSS_TMO |
			  NVMF_OPT_NR_WRITE_QUEUES | NVMF_OPT_NR_POLL_QUEUES |
			  NVMF_OPT_TOS,
	.create_ctrl	= nvme_rdma_create_ctrl,
पूर्ण;

अटल व्योम nvme_rdma_हटाओ_one(काष्ठा ib_device *ib_device, व्योम *client_data)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl;
	काष्ठा nvme_rdma_device *ndev;
	bool found = false;

	mutex_lock(&device_list_mutex);
	list_क्रम_each_entry(ndev, &device_list, entry) अणु
		अगर (ndev->dev == ib_device) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&device_list_mutex);

	अगर (!found)
		वापस;

	/* Delete all controllers using this device */
	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_rdma_ctrl_list, list) अणु
		अगर (ctrl->device->dev != ib_device)
			जारी;
		nvme_delete_ctrl(&ctrl->ctrl);
	पूर्ण
	mutex_unlock(&nvme_rdma_ctrl_mutex);

	flush_workqueue(nvme_delete_wq);
पूर्ण

अटल काष्ठा ib_client nvme_rdma_ib_client = अणु
	.name   = "nvme_rdma",
	.हटाओ = nvme_rdma_हटाओ_one
पूर्ण;

अटल पूर्णांक __init nvme_rdma_init_module(व्योम)
अणु
	पूर्णांक ret;

	ret = ib_रेजिस्टर_client(&nvme_rdma_ib_client);
	अगर (ret)
		वापस ret;

	ret = nvmf_रेजिस्टर_transport(&nvme_rdma_transport);
	अगर (ret)
		जाओ err_unreg_client;

	वापस 0;

err_unreg_client:
	ib_unरेजिस्टर_client(&nvme_rdma_ib_client);
	वापस ret;
पूर्ण

अटल व्योम __निकास nvme_rdma_cleanup_module(व्योम)
अणु
	काष्ठा nvme_rdma_ctrl *ctrl;

	nvmf_unरेजिस्टर_transport(&nvme_rdma_transport);
	ib_unरेजिस्टर_client(&nvme_rdma_ib_client);

	mutex_lock(&nvme_rdma_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_rdma_ctrl_list, list)
		nvme_delete_ctrl(&ctrl->ctrl);
	mutex_unlock(&nvme_rdma_ctrl_mutex);
	flush_workqueue(nvme_delete_wq);
पूर्ण

module_init(nvme_rdma_init_module);
module_निकास(nvme_rdma_cleanup_module);

MODULE_LICENSE("GPL v2");
