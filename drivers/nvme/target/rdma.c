<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics RDMA target.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/atomic.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/nvme.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/inet.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rw.h>
#समावेश <rdma/ib_cm.h>

#समावेश <linux/nvme-rdma.h>
#समावेश "nvmet.h"

/*
 * We allow at least 1 page, up to 4 SGEs, and up to 16KB of अंतरभूत data
 */
#घोषणा NVMET_RDMA_DEFAULT_INLINE_DATA_SIZE	PAGE_SIZE
#घोषणा NVMET_RDMA_MAX_INLINE_SGE		4
#घोषणा NVMET_RDMA_MAX_INLINE_DATA_SIZE		max_t(पूर्णांक, SZ_16K, PAGE_SIZE)

/* Assume mpsmin == device_page_size == 4KB */
#घोषणा NVMET_RDMA_MAX_MDTS			8
#घोषणा NVMET_RDMA_MAX_METADATA_MDTS		5

काष्ठा nvmet_rdma_srq;

काष्ठा nvmet_rdma_cmd अणु
	काष्ठा ib_sge		sge[NVMET_RDMA_MAX_INLINE_SGE + 1];
	काष्ठा ib_cqe		cqe;
	काष्ठा ib_recv_wr	wr;
	काष्ठा scatterlist	अंतरभूत_sg[NVMET_RDMA_MAX_INLINE_SGE];
	काष्ठा nvme_command     *nvme_cmd;
	काष्ठा nvmet_rdma_queue	*queue;
	काष्ठा nvmet_rdma_srq   *nsrq;
पूर्ण;

क्रमागत अणु
	NVMET_RDMA_REQ_INLINE_DATA	= (1 << 0),
	NVMET_RDMA_REQ_INVALIDATE_RKEY	= (1 << 1),
पूर्ण;

काष्ठा nvmet_rdma_rsp अणु
	काष्ठा ib_sge		send_sge;
	काष्ठा ib_cqe		send_cqe;
	काष्ठा ib_send_wr	send_wr;

	काष्ठा nvmet_rdma_cmd	*cmd;
	काष्ठा nvmet_rdma_queue	*queue;

	काष्ठा ib_cqe		पढ़ो_cqe;
	काष्ठा ib_cqe		ग_लिखो_cqe;
	काष्ठा rdma_rw_ctx	rw;

	काष्ठा nvmet_req	req;

	bool			allocated;
	u8			n_rdma;
	u32			flags;
	u32			invalidate_rkey;

	काष्ठा list_head	रुको_list;
	काष्ठा list_head	मुक्त_list;
पूर्ण;

क्रमागत nvmet_rdma_queue_state अणु
	NVMET_RDMA_Q_CONNECTING,
	NVMET_RDMA_Q_LIVE,
	NVMET_RDMA_Q_DISCONNECTING,
पूर्ण;

काष्ठा nvmet_rdma_queue अणु
	काष्ठा rdma_cm_id	*cm_id;
	काष्ठा ib_qp		*qp;
	काष्ठा nvmet_port	*port;
	काष्ठा ib_cq		*cq;
	atomic_t		sq_wr_avail;
	काष्ठा nvmet_rdma_device *dev;
	काष्ठा nvmet_rdma_srq   *nsrq;
	spinlock_t		state_lock;
	क्रमागत nvmet_rdma_queue_state state;
	काष्ठा nvmet_cq		nvme_cq;
	काष्ठा nvmet_sq		nvme_sq;

	काष्ठा nvmet_rdma_rsp	*rsps;
	काष्ठा list_head	मुक्त_rsps;
	spinlock_t		rsps_lock;
	काष्ठा nvmet_rdma_cmd	*cmds;

	काष्ठा work_काष्ठा	release_work;
	काष्ठा list_head	rsp_रुको_list;
	काष्ठा list_head	rsp_wr_रुको_list;
	spinlock_t		rsp_wr_रुको_lock;

	पूर्णांक			idx;
	पूर्णांक			host_qid;
	पूर्णांक			comp_vector;
	पूर्णांक			recv_queue_size;
	पूर्णांक			send_queue_size;

	काष्ठा list_head	queue_list;
पूर्ण;

काष्ठा nvmet_rdma_port अणु
	काष्ठा nvmet_port	*nport;
	काष्ठा sockaddr_storage addr;
	काष्ठा rdma_cm_id	*cm_id;
	काष्ठा delayed_work	repair_work;
पूर्ण;

काष्ठा nvmet_rdma_srq अणु
	काष्ठा ib_srq            *srq;
	काष्ठा nvmet_rdma_cmd    *cmds;
	काष्ठा nvmet_rdma_device *ndev;
पूर्ण;

काष्ठा nvmet_rdma_device अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_pd		*pd;
	काष्ठा nvmet_rdma_srq	**srqs;
	पूर्णांक			srq_count;
	माप_प्रकार			srq_size;
	काष्ठा kref		ref;
	काष्ठा list_head	entry;
	पूर्णांक			अंतरभूत_data_size;
	पूर्णांक			अंतरभूत_page_count;
पूर्ण;

अटल bool nvmet_rdma_use_srq;
module_param_named(use_srq, nvmet_rdma_use_srq, bool, 0444);
MODULE_PARM_DESC(use_srq, "Use shared receive queue.");

अटल पूर्णांक srq_size_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops srq_size_ops = अणु
	.set = srq_size_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल पूर्णांक nvmet_rdma_srq_size = 1024;
module_param_cb(srq_size, &srq_size_ops, &nvmet_rdma_srq_size, 0644);
MODULE_PARM_DESC(srq_size, "set Shared Receive Queue (SRQ) size, should >= 256 (default: 1024)");

अटल DEFINE_IDA(nvmet_rdma_queue_ida);
अटल LIST_HEAD(nvmet_rdma_queue_list);
अटल DEFINE_MUTEX(nvmet_rdma_queue_mutex);

अटल LIST_HEAD(device_list);
अटल DEFINE_MUTEX(device_list_mutex);

अटल bool nvmet_rdma_execute_command(काष्ठा nvmet_rdma_rsp *rsp);
अटल व्योम nvmet_rdma_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम nvmet_rdma_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम nvmet_rdma_पढ़ो_data_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम nvmet_rdma_ग_लिखो_data_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम nvmet_rdma_qp_event(काष्ठा ib_event *event, व्योम *priv);
अटल व्योम nvmet_rdma_queue_disconnect(काष्ठा nvmet_rdma_queue *queue);
अटल व्योम nvmet_rdma_मुक्त_rsp(काष्ठा nvmet_rdma_device *ndev,
				काष्ठा nvmet_rdma_rsp *r);
अटल पूर्णांक nvmet_rdma_alloc_rsp(काष्ठा nvmet_rdma_device *ndev,
				काष्ठा nvmet_rdma_rsp *r);

अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_rdma_ops;

अटल पूर्णांक srq_size_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक n = 0, ret;

	ret = kstrtoपूर्णांक(val, 10, &n);
	अगर (ret != 0 || n < 256)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल पूर्णांक num_pages(पूर्णांक len)
अणु
	वापस 1 + (((len - 1) & PAGE_MASK) >> PAGE_SHIFT);
पूर्ण

अटल अंतरभूत bool nvmet_rdma_need_data_in(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	वापस nvme_is_ग_लिखो(rsp->req.cmd) &&
		rsp->req.transfer_len &&
		!(rsp->flags & NVMET_RDMA_REQ_INLINE_DATA);
पूर्ण

अटल अंतरभूत bool nvmet_rdma_need_data_out(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	वापस !nvme_is_ग_लिखो(rsp->req.cmd) &&
		rsp->req.transfer_len &&
		!rsp->req.cqe->status &&
		!(rsp->flags & NVMET_RDMA_REQ_INLINE_DATA);
पूर्ण

अटल अंतरभूत काष्ठा nvmet_rdma_rsp *
nvmet_rdma_get_rsp(काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा nvmet_rdma_rsp *rsp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->rsps_lock, flags);
	rsp = list_first_entry_or_null(&queue->मुक्त_rsps,
				काष्ठा nvmet_rdma_rsp, मुक्त_list);
	अगर (likely(rsp))
		list_del(&rsp->मुक्त_list);
	spin_unlock_irqrestore(&queue->rsps_lock, flags);

	अगर (unlikely(!rsp)) अणु
		पूर्णांक ret;

		rsp = kzalloc(माप(*rsp), GFP_KERNEL);
		अगर (unlikely(!rsp))
			वापस शून्य;
		ret = nvmet_rdma_alloc_rsp(queue->dev, rsp);
		अगर (unlikely(ret)) अणु
			kमुक्त(rsp);
			वापस शून्य;
		पूर्ण

		rsp->allocated = true;
	पूर्ण

	वापस rsp;
पूर्ण

अटल अंतरभूत व्योम
nvmet_rdma_put_rsp(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(rsp->allocated)) अणु
		nvmet_rdma_मुक्त_rsp(rsp->queue->dev, rsp);
		kमुक्त(rsp);
		वापस;
	पूर्ण

	spin_lock_irqsave(&rsp->queue->rsps_lock, flags);
	list_add_tail(&rsp->मुक्त_list, &rsp->queue->मुक्त_rsps);
	spin_unlock_irqrestore(&rsp->queue->rsps_lock, flags);
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_अंतरभूत_pages(काष्ठा nvmet_rdma_device *ndev,
				काष्ठा nvmet_rdma_cmd *c)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ib_sge *sge;
	पूर्णांक i;

	अगर (!ndev->अंतरभूत_data_size)
		वापस;

	sg = c->अंतरभूत_sg;
	sge = &c->sge[1];

	क्रम (i = 0; i < ndev->अंतरभूत_page_count; i++, sg++, sge++) अणु
		अगर (sge->length)
			ib_dma_unmap_page(ndev->device, sge->addr,
					sge->length, DMA_FROM_DEVICE);
		अगर (sg_page(sg))
			__मुक्त_page(sg_page(sg));
	पूर्ण
पूर्ण

अटल पूर्णांक nvmet_rdma_alloc_अंतरभूत_pages(काष्ठा nvmet_rdma_device *ndev,
				काष्ठा nvmet_rdma_cmd *c)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ib_sge *sge;
	काष्ठा page *pg;
	पूर्णांक len;
	पूर्णांक i;

	अगर (!ndev->अंतरभूत_data_size)
		वापस 0;

	sg = c->अंतरभूत_sg;
	sg_init_table(sg, ndev->अंतरभूत_page_count);
	sge = &c->sge[1];
	len = ndev->अंतरभूत_data_size;

	क्रम (i = 0; i < ndev->अंतरभूत_page_count; i++, sg++, sge++) अणु
		pg = alloc_page(GFP_KERNEL);
		अगर (!pg)
			जाओ out_err;
		sg_assign_page(sg, pg);
		sge->addr = ib_dma_map_page(ndev->device,
			pg, 0, PAGE_SIZE, DMA_FROM_DEVICE);
		अगर (ib_dma_mapping_error(ndev->device, sge->addr))
			जाओ out_err;
		sge->length = min_t(पूर्णांक, len, PAGE_SIZE);
		sge->lkey = ndev->pd->local_dma_lkey;
		len -= sge->length;
	पूर्ण

	वापस 0;
out_err:
	क्रम (; i >= 0; i--, sg--, sge--) अणु
		अगर (sge->length)
			ib_dma_unmap_page(ndev->device, sge->addr,
					sge->length, DMA_FROM_DEVICE);
		अगर (sg_page(sg))
			__मुक्त_page(sg_page(sg));
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nvmet_rdma_alloc_cmd(काष्ठा nvmet_rdma_device *ndev,
			काष्ठा nvmet_rdma_cmd *c, bool admin)
अणु
	/* NVMe command / RDMA RECV */
	c->nvme_cmd = kदो_स्मृति(माप(*c->nvme_cmd), GFP_KERNEL);
	अगर (!c->nvme_cmd)
		जाओ out;

	c->sge[0].addr = ib_dma_map_single(ndev->device, c->nvme_cmd,
			माप(*c->nvme_cmd), DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(ndev->device, c->sge[0].addr))
		जाओ out_मुक्त_cmd;

	c->sge[0].length = माप(*c->nvme_cmd);
	c->sge[0].lkey = ndev->pd->local_dma_lkey;

	अगर (!admin && nvmet_rdma_alloc_अंतरभूत_pages(ndev, c))
		जाओ out_unmap_cmd;

	c->cqe.करोne = nvmet_rdma_recv_करोne;

	c->wr.wr_cqe = &c->cqe;
	c->wr.sg_list = c->sge;
	c->wr.num_sge = admin ? 1 : ndev->अंतरभूत_page_count + 1;

	वापस 0;

out_unmap_cmd:
	ib_dma_unmap_single(ndev->device, c->sge[0].addr,
			माप(*c->nvme_cmd), DMA_FROM_DEVICE);
out_मुक्त_cmd:
	kमुक्त(c->nvme_cmd);

out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_cmd(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा nvmet_rdma_cmd *c, bool admin)
अणु
	अगर (!admin)
		nvmet_rdma_मुक्त_अंतरभूत_pages(ndev, c);
	ib_dma_unmap_single(ndev->device, c->sge[0].addr,
				माप(*c->nvme_cmd), DMA_FROM_DEVICE);
	kमुक्त(c->nvme_cmd);
पूर्ण

अटल काष्ठा nvmet_rdma_cmd *
nvmet_rdma_alloc_cmds(काष्ठा nvmet_rdma_device *ndev,
		पूर्णांक nr_cmds, bool admin)
अणु
	काष्ठा nvmet_rdma_cmd *cmds;
	पूर्णांक ret = -EINVAL, i;

	cmds = kसुस्मृति(nr_cmds, माप(काष्ठा nvmet_rdma_cmd), GFP_KERNEL);
	अगर (!cmds)
		जाओ out;

	क्रम (i = 0; i < nr_cmds; i++) अणु
		ret = nvmet_rdma_alloc_cmd(ndev, cmds + i, admin);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	वापस cmds;

out_मुक्त:
	जबतक (--i >= 0)
		nvmet_rdma_मुक्त_cmd(ndev, cmds + i, admin);
	kमुक्त(cmds);
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_cmds(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा nvmet_rdma_cmd *cmds, पूर्णांक nr_cmds, bool admin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_cmds; i++)
		nvmet_rdma_मुक्त_cmd(ndev, cmds + i, admin);
	kमुक्त(cmds);
पूर्ण

अटल पूर्णांक nvmet_rdma_alloc_rsp(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा nvmet_rdma_rsp *r)
अणु
	/* NVMe CQE / RDMA SEND */
	r->req.cqe = kदो_स्मृति(माप(*r->req.cqe), GFP_KERNEL);
	अगर (!r->req.cqe)
		जाओ out;

	r->send_sge.addr = ib_dma_map_single(ndev->device, r->req.cqe,
			माप(*r->req.cqe), DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(ndev->device, r->send_sge.addr))
		जाओ out_मुक्त_rsp;

	अगर (!ib_uses_virt_dma(ndev->device))
		r->req.p2p_client = &ndev->device->dev;
	r->send_sge.length = माप(*r->req.cqe);
	r->send_sge.lkey = ndev->pd->local_dma_lkey;

	r->send_cqe.करोne = nvmet_rdma_send_करोne;

	r->send_wr.wr_cqe = &r->send_cqe;
	r->send_wr.sg_list = &r->send_sge;
	r->send_wr.num_sge = 1;
	r->send_wr.send_flags = IB_SEND_SIGNALED;

	/* Data In / RDMA READ */
	r->पढ़ो_cqe.करोne = nvmet_rdma_पढ़ो_data_करोne;
	/* Data Out / RDMA WRITE */
	r->ग_लिखो_cqe.करोne = nvmet_rdma_ग_लिखो_data_करोne;

	वापस 0;

out_मुक्त_rsp:
	kमुक्त(r->req.cqe);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_rsp(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा nvmet_rdma_rsp *r)
अणु
	ib_dma_unmap_single(ndev->device, r->send_sge.addr,
				माप(*r->req.cqe), DMA_TO_DEVICE);
	kमुक्त(r->req.cqe);
पूर्ण

अटल पूर्णांक
nvmet_rdma_alloc_rsps(काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा nvmet_rdma_device *ndev = queue->dev;
	पूर्णांक nr_rsps = queue->recv_queue_size * 2;
	पूर्णांक ret = -EINVAL, i;

	queue->rsps = kसुस्मृति(nr_rsps, माप(काष्ठा nvmet_rdma_rsp),
			GFP_KERNEL);
	अगर (!queue->rsps)
		जाओ out;

	क्रम (i = 0; i < nr_rsps; i++) अणु
		काष्ठा nvmet_rdma_rsp *rsp = &queue->rsps[i];

		ret = nvmet_rdma_alloc_rsp(ndev, rsp);
		अगर (ret)
			जाओ out_मुक्त;

		list_add_tail(&rsp->मुक्त_list, &queue->मुक्त_rsps);
	पूर्ण

	वापस 0;

out_मुक्त:
	जबतक (--i >= 0) अणु
		काष्ठा nvmet_rdma_rsp *rsp = &queue->rsps[i];

		list_del(&rsp->मुक्त_list);
		nvmet_rdma_मुक्त_rsp(ndev, rsp);
	पूर्ण
	kमुक्त(queue->rsps);
out:
	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_rsps(काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा nvmet_rdma_device *ndev = queue->dev;
	पूर्णांक i, nr_rsps = queue->recv_queue_size * 2;

	क्रम (i = 0; i < nr_rsps; i++) अणु
		काष्ठा nvmet_rdma_rsp *rsp = &queue->rsps[i];

		list_del(&rsp->मुक्त_list);
		nvmet_rdma_मुक्त_rsp(ndev, rsp);
	पूर्ण
	kमुक्त(queue->rsps);
पूर्ण

अटल पूर्णांक nvmet_rdma_post_recv(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा nvmet_rdma_cmd *cmd)
अणु
	पूर्णांक ret;

	ib_dma_sync_single_क्रम_device(ndev->device,
		cmd->sge[0].addr, cmd->sge[0].length,
		DMA_FROM_DEVICE);

	अगर (cmd->nsrq)
		ret = ib_post_srq_recv(cmd->nsrq->srq, &cmd->wr, शून्य);
	अन्यथा
		ret = ib_post_recv(cmd->queue->qp, &cmd->wr, शून्य);

	अगर (unlikely(ret))
		pr_err("post_recv cmd failed\n");

	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_process_wr_रुको_list(काष्ठा nvmet_rdma_queue *queue)
अणु
	spin_lock(&queue->rsp_wr_रुको_lock);
	जबतक (!list_empty(&queue->rsp_wr_रुको_list)) अणु
		काष्ठा nvmet_rdma_rsp *rsp;
		bool ret;

		rsp = list_entry(queue->rsp_wr_रुको_list.next,
				काष्ठा nvmet_rdma_rsp, रुको_list);
		list_del(&rsp->रुको_list);

		spin_unlock(&queue->rsp_wr_रुको_lock);
		ret = nvmet_rdma_execute_command(rsp);
		spin_lock(&queue->rsp_wr_रुको_lock);

		अगर (!ret) अणु
			list_add(&rsp->रुको_list, &queue->rsp_wr_रुको_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&queue->rsp_wr_रुको_lock);
पूर्ण

अटल u16 nvmet_rdma_check_pi_status(काष्ठा ib_mr *sig_mr)
अणु
	काष्ठा ib_mr_status mr_status;
	पूर्णांक ret;
	u16 status = 0;

	ret = ib_check_mr_status(sig_mr, IB_MR_CHECK_SIG_STATUS, &mr_status);
	अगर (ret) अणु
		pr_err("ib_check_mr_status failed, ret %d\n", ret);
		वापस NVME_SC_INVALID_PI;
	पूर्ण

	अगर (mr_status.fail_status & IB_MR_CHECK_SIG_STATUS) अणु
		चयन (mr_status.sig_err.err_type) अणु
		हाल IB_SIG_BAD_GUARD:
			status = NVME_SC_GUARD_CHECK;
			अवरोध;
		हाल IB_SIG_BAD_REFTAG:
			status = NVME_SC_REFTAG_CHECK;
			अवरोध;
		हाल IB_SIG_BAD_APPTAG:
			status = NVME_SC_APPTAG_CHECK;
			अवरोध;
		पूर्ण
		pr_err("PI error found type %d expected 0x%x vs actual 0x%x\n",
		       mr_status.sig_err.err_type,
		       mr_status.sig_err.expected,
		       mr_status.sig_err.actual);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम nvmet_rdma_set_sig_करोमुख्य(काष्ठा blk_पूर्णांकegrity *bi,
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

अटल व्योम nvmet_rdma_set_sig_attrs(काष्ठा nvmet_req *req,
				     काष्ठा ib_sig_attrs *sig_attrs)
अणु
	काष्ठा nvme_command *cmd = req->cmd;
	u16 control = le16_to_cpu(cmd->rw.control);
	u8 pi_type = req->ns->pi_type;
	काष्ठा blk_पूर्णांकegrity *bi;

	bi = bdev_get_पूर्णांकegrity(req->ns->bdev);

	स_रखो(sig_attrs, 0, माप(*sig_attrs));

	अगर (control & NVME_RW_PRINFO_PRACT) अणु
		/* क्रम WRITE_INSERT/READ_STRIP no wire करोमुख्य */
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		nvmet_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->mem, control,
					  pi_type);
		/* Clear the PRACT bit since HCA will generate/verअगरy the PI */
		control &= ~NVME_RW_PRINFO_PRACT;
		cmd->rw.control = cpu_to_le16(control);
		/* PI is added by the HW */
		req->transfer_len += req->metadata_len;
	पूर्ण अन्यथा अणु
		/* क्रम WRITE_PASS/READ_PASS both wire/memory करोमुख्यs exist */
		nvmet_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->wire, control,
					  pi_type);
		nvmet_rdma_set_sig_करोमुख्य(bi, cmd, &sig_attrs->mem, control,
					  pi_type);
	पूर्ण

	अगर (control & NVME_RW_PRINFO_PRCHK_REF)
		sig_attrs->check_mask |= IB_SIG_CHECK_REFTAG;
	अगर (control & NVME_RW_PRINFO_PRCHK_GUARD)
		sig_attrs->check_mask |= IB_SIG_CHECK_GUARD;
	अगर (control & NVME_RW_PRINFO_PRCHK_APP)
		sig_attrs->check_mask |= IB_SIG_CHECK_APPTAG;
पूर्ण

अटल पूर्णांक nvmet_rdma_rw_ctx_init(काष्ठा nvmet_rdma_rsp *rsp, u64 addr, u32 key,
				  काष्ठा ib_sig_attrs *sig_attrs)
अणु
	काष्ठा rdma_cm_id *cm_id = rsp->queue->cm_id;
	काष्ठा nvmet_req *req = &rsp->req;
	पूर्णांक ret;

	अगर (req->metadata_len)
		ret = rdma_rw_ctx_signature_init(&rsp->rw, cm_id->qp,
			cm_id->port_num, req->sg, req->sg_cnt,
			req->metadata_sg, req->metadata_sg_cnt, sig_attrs,
			addr, key, nvmet_data_dir(req));
	अन्यथा
		ret = rdma_rw_ctx_init(&rsp->rw, cm_id->qp, cm_id->port_num,
				       req->sg, req->sg_cnt, 0, addr, key,
				       nvmet_data_dir(req));

	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_rw_ctx_destroy(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	काष्ठा rdma_cm_id *cm_id = rsp->queue->cm_id;
	काष्ठा nvmet_req *req = &rsp->req;

	अगर (req->metadata_len)
		rdma_rw_ctx_destroy_signature(&rsp->rw, cm_id->qp,
			cm_id->port_num, req->sg, req->sg_cnt,
			req->metadata_sg, req->metadata_sg_cnt,
			nvmet_data_dir(req));
	अन्यथा
		rdma_rw_ctx_destroy(&rsp->rw, cm_id->qp, cm_id->port_num,
				    req->sg, req->sg_cnt, nvmet_data_dir(req));
पूर्ण

अटल व्योम nvmet_rdma_release_rsp(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	काष्ठा nvmet_rdma_queue *queue = rsp->queue;

	atomic_add(1 + rsp->n_rdma, &queue->sq_wr_avail);

	अगर (rsp->n_rdma)
		nvmet_rdma_rw_ctx_destroy(rsp);

	अगर (rsp->req.sg != rsp->cmd->अंतरभूत_sg)
		nvmet_req_मुक्त_sgls(&rsp->req);

	अगर (unlikely(!list_empty_careful(&queue->rsp_wr_रुको_list)))
		nvmet_rdma_process_wr_रुको_list(queue);

	nvmet_rdma_put_rsp(rsp);
पूर्ण

अटल व्योम nvmet_rdma_error_comp(काष्ठा nvmet_rdma_queue *queue)
अणु
	अगर (queue->nvme_sq.ctrl) अणु
		nvmet_ctrl_fatal_error(queue->nvme_sq.ctrl);
	पूर्ण अन्यथा अणु
		/*
		 * we didn't setup the controller yet in हाल
		 * of admin connect error, just disconnect and
		 * cleanup the queue
		 */
		nvmet_rdma_queue_disconnect(queue);
	पूर्ण
पूर्ण

अटल व्योम nvmet_rdma_send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvmet_rdma_rsp *rsp =
		container_of(wc->wr_cqe, काष्ठा nvmet_rdma_rsp, send_cqe);
	काष्ठा nvmet_rdma_queue *queue = wc->qp->qp_context;

	nvmet_rdma_release_rsp(rsp);

	अगर (unlikely(wc->status != IB_WC_SUCCESS &&
		     wc->status != IB_WC_WR_FLUSH_ERR)) अणु
		pr_err("SEND for CQE 0x%p failed with status %s (%d).\n",
			wc->wr_cqe, ib_wc_status_msg(wc->status), wc->status);
		nvmet_rdma_error_comp(queue);
	पूर्ण
पूर्ण

अटल व्योम nvmet_rdma_queue_response(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_rdma_rsp *rsp =
		container_of(req, काष्ठा nvmet_rdma_rsp, req);
	काष्ठा rdma_cm_id *cm_id = rsp->queue->cm_id;
	काष्ठा ib_send_wr *first_wr;

	अगर (rsp->flags & NVMET_RDMA_REQ_INVALIDATE_RKEY) अणु
		rsp->send_wr.opcode = IB_WR_SEND_WITH_INV;
		rsp->send_wr.ex.invalidate_rkey = rsp->invalidate_rkey;
	पूर्ण अन्यथा अणु
		rsp->send_wr.opcode = IB_WR_SEND;
	पूर्ण

	अगर (nvmet_rdma_need_data_out(rsp)) अणु
		अगर (rsp->req.metadata_len)
			first_wr = rdma_rw_ctx_wrs(&rsp->rw, cm_id->qp,
					cm_id->port_num, &rsp->ग_लिखो_cqe, शून्य);
		अन्यथा
			first_wr = rdma_rw_ctx_wrs(&rsp->rw, cm_id->qp,
					cm_id->port_num, शून्य, &rsp->send_wr);
	पूर्ण अन्यथा अणु
		first_wr = &rsp->send_wr;
	पूर्ण

	nvmet_rdma_post_recv(rsp->queue->dev, rsp->cmd);

	ib_dma_sync_single_क्रम_device(rsp->queue->dev->device,
		rsp->send_sge.addr, rsp->send_sge.length,
		DMA_TO_DEVICE);

	अगर (unlikely(ib_post_send(cm_id->qp, first_wr, शून्य))) अणु
		pr_err("sending cmd response failed\n");
		nvmet_rdma_release_rsp(rsp);
	पूर्ण
पूर्ण

अटल व्योम nvmet_rdma_पढ़ो_data_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvmet_rdma_rsp *rsp =
		container_of(wc->wr_cqe, काष्ठा nvmet_rdma_rsp, पढ़ो_cqe);
	काष्ठा nvmet_rdma_queue *queue = wc->qp->qp_context;
	u16 status = 0;

	WARN_ON(rsp->n_rdma <= 0);
	atomic_add(rsp->n_rdma, &queue->sq_wr_avail);
	rsp->n_rdma = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		nvmet_rdma_rw_ctx_destroy(rsp);
		nvmet_req_uninit(&rsp->req);
		nvmet_rdma_release_rsp(rsp);
		अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
			pr_info("RDMA READ for CQE 0x%p failed with status %s (%d).\n",
				wc->wr_cqe, ib_wc_status_msg(wc->status), wc->status);
			nvmet_rdma_error_comp(queue);
		पूर्ण
		वापस;
	पूर्ण

	अगर (rsp->req.metadata_len)
		status = nvmet_rdma_check_pi_status(rsp->rw.reg->mr);
	nvmet_rdma_rw_ctx_destroy(rsp);

	अगर (unlikely(status))
		nvmet_req_complete(&rsp->req, status);
	अन्यथा
		rsp->req.execute(&rsp->req);
पूर्ण

अटल व्योम nvmet_rdma_ग_लिखो_data_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvmet_rdma_rsp *rsp =
		container_of(wc->wr_cqe, काष्ठा nvmet_rdma_rsp, ग_लिखो_cqe);
	काष्ठा nvmet_rdma_queue *queue = wc->qp->qp_context;
	काष्ठा rdma_cm_id *cm_id = rsp->queue->cm_id;
	u16 status;

	अगर (!IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY))
		वापस;

	WARN_ON(rsp->n_rdma <= 0);
	atomic_add(rsp->n_rdma, &queue->sq_wr_avail);
	rsp->n_rdma = 0;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		nvmet_rdma_rw_ctx_destroy(rsp);
		nvmet_req_uninit(&rsp->req);
		nvmet_rdma_release_rsp(rsp);
		अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
			pr_info("RDMA WRITE for CQE failed with status %s (%d).\n",
				ib_wc_status_msg(wc->status), wc->status);
			nvmet_rdma_error_comp(queue);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Upon RDMA completion check the signature status
	 * - अगर succeeded send good NVMe response
	 * - अगर failed send bad NVMe response with appropriate error
	 */
	status = nvmet_rdma_check_pi_status(rsp->rw.reg->mr);
	अगर (unlikely(status))
		rsp->req.cqe->status = cpu_to_le16(status << 1);
	nvmet_rdma_rw_ctx_destroy(rsp);

	अगर (unlikely(ib_post_send(cm_id->qp, &rsp->send_wr, शून्य))) अणु
		pr_err("sending cmd response failed\n");
		nvmet_rdma_release_rsp(rsp);
	पूर्ण
पूर्ण

अटल व्योम nvmet_rdma_use_अंतरभूत_sg(काष्ठा nvmet_rdma_rsp *rsp, u32 len,
		u64 off)
अणु
	पूर्णांक sg_count = num_pages(len);
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	sg = rsp->cmd->अंतरभूत_sg;
	क्रम (i = 0; i < sg_count; i++, sg++) अणु
		अगर (i < sg_count - 1)
			sg_unmark_end(sg);
		अन्यथा
			sg_mark_end(sg);
		sg->offset = off;
		sg->length = min_t(पूर्णांक, len, PAGE_SIZE - off);
		len -= sg->length;
		अगर (!i)
			off = 0;
	पूर्ण

	rsp->req.sg = rsp->cmd->अंतरभूत_sg;
	rsp->req.sg_cnt = sg_count;
पूर्ण

अटल u16 nvmet_rdma_map_sgl_अंतरभूत(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	काष्ठा nvme_sgl_desc *sgl = &rsp->req.cmd->common.dptr.sgl;
	u64 off = le64_to_cpu(sgl->addr);
	u32 len = le32_to_cpu(sgl->length);

	अगर (!nvme_is_ग_लिखो(rsp->req.cmd)) अणु
		rsp->req.error_loc =
			दुरत्व(काष्ठा nvme_common_command, opcode);
		वापस NVME_SC_INVALID_FIELD | NVME_SC_DNR;
	पूर्ण

	अगर (off + len > rsp->queue->dev->अंतरभूत_data_size) अणु
		pr_err("invalid inline data offset!\n");
		वापस NVME_SC_SGL_INVALID_OFFSET | NVME_SC_DNR;
	पूर्ण

	/* no data command? */
	अगर (!len)
		वापस 0;

	nvmet_rdma_use_अंतरभूत_sg(rsp, len, off);
	rsp->flags |= NVMET_RDMA_REQ_INLINE_DATA;
	rsp->req.transfer_len += len;
	वापस 0;
पूर्ण

अटल u16 nvmet_rdma_map_sgl_keyed(काष्ठा nvmet_rdma_rsp *rsp,
		काष्ठा nvme_keyed_sgl_desc *sgl, bool invalidate)
अणु
	u64 addr = le64_to_cpu(sgl->addr);
	u32 key = get_unaligned_le32(sgl->key);
	काष्ठा ib_sig_attrs sig_attrs;
	पूर्णांक ret;

	rsp->req.transfer_len = get_unaligned_le24(sgl->length);

	/* no data command? */
	अगर (!rsp->req.transfer_len)
		वापस 0;

	अगर (rsp->req.metadata_len)
		nvmet_rdma_set_sig_attrs(&rsp->req, &sig_attrs);

	ret = nvmet_req_alloc_sgls(&rsp->req);
	अगर (unlikely(ret < 0))
		जाओ error_out;

	ret = nvmet_rdma_rw_ctx_init(rsp, addr, key, &sig_attrs);
	अगर (unlikely(ret < 0))
		जाओ error_out;
	rsp->n_rdma += ret;

	अगर (invalidate) अणु
		rsp->invalidate_rkey = key;
		rsp->flags |= NVMET_RDMA_REQ_INVALIDATE_RKEY;
	पूर्ण

	वापस 0;

error_out:
	rsp->req.transfer_len = 0;
	वापस NVME_SC_INTERNAL;
पूर्ण

अटल u16 nvmet_rdma_map_sgl(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	काष्ठा nvme_keyed_sgl_desc *sgl = &rsp->req.cmd->common.dptr.ksgl;

	चयन (sgl->type >> 4) अणु
	हाल NVME_SGL_FMT_DATA_DESC:
		चयन (sgl->type & 0xf) अणु
		हाल NVME_SGL_FMT_OFFSET:
			वापस nvmet_rdma_map_sgl_अंतरभूत(rsp);
		शेष:
			pr_err("invalid SGL subtype: %#x\n", sgl->type);
			rsp->req.error_loc =
				दुरत्व(काष्ठा nvme_common_command, dptr);
			वापस NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		पूर्ण
	हाल NVME_KEY_SGL_FMT_DATA_DESC:
		चयन (sgl->type & 0xf) अणु
		हाल NVME_SGL_FMT_ADDRESS | NVME_SGL_FMT_INVALIDATE:
			वापस nvmet_rdma_map_sgl_keyed(rsp, sgl, true);
		हाल NVME_SGL_FMT_ADDRESS:
			वापस nvmet_rdma_map_sgl_keyed(rsp, sgl, false);
		शेष:
			pr_err("invalid SGL subtype: %#x\n", sgl->type);
			rsp->req.error_loc =
				दुरत्व(काष्ठा nvme_common_command, dptr);
			वापस NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		पूर्ण
	शेष:
		pr_err("invalid SGL type: %#x\n", sgl->type);
		rsp->req.error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		वापस NVME_SC_SGL_INVALID_TYPE | NVME_SC_DNR;
	पूर्ण
पूर्ण

अटल bool nvmet_rdma_execute_command(काष्ठा nvmet_rdma_rsp *rsp)
अणु
	काष्ठा nvmet_rdma_queue *queue = rsp->queue;

	अगर (unlikely(atomic_sub_वापस(1 + rsp->n_rdma,
			&queue->sq_wr_avail) < 0)) अणु
		pr_debug("IB send queue full (needed %d): queue %u cntlid %u\n",
				1 + rsp->n_rdma, queue->idx,
				queue->nvme_sq.ctrl->cntlid);
		atomic_add(1 + rsp->n_rdma, &queue->sq_wr_avail);
		वापस false;
	पूर्ण

	अगर (nvmet_rdma_need_data_in(rsp)) अणु
		अगर (rdma_rw_ctx_post(&rsp->rw, queue->qp,
				queue->cm_id->port_num, &rsp->पढ़ो_cqe, शून्य))
			nvmet_req_complete(&rsp->req, NVME_SC_DATA_XFER_ERROR);
	पूर्ण अन्यथा अणु
		rsp->req.execute(&rsp->req);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम nvmet_rdma_handle_command(काष्ठा nvmet_rdma_queue *queue,
		काष्ठा nvmet_rdma_rsp *cmd)
अणु
	u16 status;

	ib_dma_sync_single_क्रम_cpu(queue->dev->device,
		cmd->cmd->sge[0].addr, cmd->cmd->sge[0].length,
		DMA_FROM_DEVICE);
	ib_dma_sync_single_क्रम_cpu(queue->dev->device,
		cmd->send_sge.addr, cmd->send_sge.length,
		DMA_TO_DEVICE);

	अगर (!nvmet_req_init(&cmd->req, &queue->nvme_cq,
			&queue->nvme_sq, &nvmet_rdma_ops))
		वापस;

	status = nvmet_rdma_map_sgl(cmd);
	अगर (status)
		जाओ out_err;

	अगर (unlikely(!nvmet_rdma_execute_command(cmd))) अणु
		spin_lock(&queue->rsp_wr_रुको_lock);
		list_add_tail(&cmd->रुको_list, &queue->rsp_wr_रुको_list);
		spin_unlock(&queue->rsp_wr_रुको_lock);
	पूर्ण

	वापस;

out_err:
	nvmet_req_complete(&cmd->req, status);
पूर्ण

अटल व्योम nvmet_rdma_recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा nvmet_rdma_cmd *cmd =
		container_of(wc->wr_cqe, काष्ठा nvmet_rdma_cmd, cqe);
	काष्ठा nvmet_rdma_queue *queue = wc->qp->qp_context;
	काष्ठा nvmet_rdma_rsp *rsp;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
			pr_err("RECV for CQE 0x%p failed with status %s (%d)\n",
				wc->wr_cqe, ib_wc_status_msg(wc->status),
				wc->status);
			nvmet_rdma_error_comp(queue);
		पूर्ण
		वापस;
	पूर्ण

	अगर (unlikely(wc->byte_len < माप(काष्ठा nvme_command))) अणु
		pr_err("Ctrl Fatal Error: capsule size less than 64 bytes\n");
		nvmet_rdma_error_comp(queue);
		वापस;
	पूर्ण

	cmd->queue = queue;
	rsp = nvmet_rdma_get_rsp(queue);
	अगर (unlikely(!rsp)) अणु
		/*
		 * we get here only under memory pressure,
		 * silently drop and have the host retry
		 * as we can't even fail it.
		 */
		nvmet_rdma_post_recv(queue->dev, cmd);
		वापस;
	पूर्ण
	rsp->queue = queue;
	rsp->cmd = cmd;
	rsp->flags = 0;
	rsp->req.cmd = cmd->nvme_cmd;
	rsp->req.port = queue->port;
	rsp->n_rdma = 0;

	अगर (unlikely(queue->state != NVMET_RDMA_Q_LIVE)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&queue->state_lock, flags);
		अगर (queue->state == NVMET_RDMA_Q_CONNECTING)
			list_add_tail(&rsp->रुको_list, &queue->rsp_रुको_list);
		अन्यथा
			nvmet_rdma_put_rsp(rsp);
		spin_unlock_irqrestore(&queue->state_lock, flags);
		वापस;
	पूर्ण

	nvmet_rdma_handle_command(queue, rsp);
पूर्ण

अटल व्योम nvmet_rdma_destroy_srq(काष्ठा nvmet_rdma_srq *nsrq)
अणु
	nvmet_rdma_मुक्त_cmds(nsrq->ndev, nsrq->cmds, nsrq->ndev->srq_size,
			     false);
	ib_destroy_srq(nsrq->srq);

	kमुक्त(nsrq);
पूर्ण

अटल व्योम nvmet_rdma_destroy_srqs(काष्ठा nvmet_rdma_device *ndev)
अणु
	पूर्णांक i;

	अगर (!ndev->srqs)
		वापस;

	क्रम (i = 0; i < ndev->srq_count; i++)
		nvmet_rdma_destroy_srq(ndev->srqs[i]);

	kमुक्त(ndev->srqs);
पूर्ण

अटल काष्ठा nvmet_rdma_srq *
nvmet_rdma_init_srq(काष्ठा nvmet_rdma_device *ndev)
अणु
	काष्ठा ib_srq_init_attr srq_attr = अणु शून्य, पूर्ण;
	माप_प्रकार srq_size = ndev->srq_size;
	काष्ठा nvmet_rdma_srq *nsrq;
	काष्ठा ib_srq *srq;
	पूर्णांक ret, i;

	nsrq = kzalloc(माप(*nsrq), GFP_KERNEL);
	अगर (!nsrq)
		वापस ERR_PTR(-ENOMEM);

	srq_attr.attr.max_wr = srq_size;
	srq_attr.attr.max_sge = 1 + ndev->अंतरभूत_page_count;
	srq_attr.attr.srq_limit = 0;
	srq_attr.srq_type = IB_SRQT_BASIC;
	srq = ib_create_srq(ndev->pd, &srq_attr);
	अगर (IS_ERR(srq)) अणु
		ret = PTR_ERR(srq);
		जाओ out_मुक्त;
	पूर्ण

	nsrq->cmds = nvmet_rdma_alloc_cmds(ndev, srq_size, false);
	अगर (IS_ERR(nsrq->cmds)) अणु
		ret = PTR_ERR(nsrq->cmds);
		जाओ out_destroy_srq;
	पूर्ण

	nsrq->srq = srq;
	nsrq->ndev = ndev;

	क्रम (i = 0; i < srq_size; i++) अणु
		nsrq->cmds[i].nsrq = nsrq;
		ret = nvmet_rdma_post_recv(ndev, &nsrq->cmds[i]);
		अगर (ret)
			जाओ out_मुक्त_cmds;
	पूर्ण

	वापस nsrq;

out_मुक्त_cmds:
	nvmet_rdma_मुक्त_cmds(ndev, nsrq->cmds, srq_size, false);
out_destroy_srq:
	ib_destroy_srq(srq);
out_मुक्त:
	kमुक्त(nsrq);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक nvmet_rdma_init_srqs(काष्ठा nvmet_rdma_device *ndev)
अणु
	पूर्णांक i, ret;

	अगर (!ndev->device->attrs.max_srq_wr || !ndev->device->attrs.max_srq) अणु
		/*
		 * If SRQs aren't supported we just go ahead and use normal
		 * non-shared receive queues.
		 */
		pr_info("SRQ requested but not supported.\n");
		वापस 0;
	पूर्ण

	ndev->srq_size = min(ndev->device->attrs.max_srq_wr,
			     nvmet_rdma_srq_size);
	ndev->srq_count = min(ndev->device->num_comp_vectors,
			      ndev->device->attrs.max_srq);

	ndev->srqs = kसुस्मृति(ndev->srq_count, माप(*ndev->srqs), GFP_KERNEL);
	अगर (!ndev->srqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < ndev->srq_count; i++) अणु
		ndev->srqs[i] = nvmet_rdma_init_srq(ndev);
		अगर (IS_ERR(ndev->srqs[i])) अणु
			ret = PTR_ERR(ndev->srqs[i]);
			जाओ err_srq;
		पूर्ण
	पूर्ण

	वापस 0;

err_srq:
	जबतक (--i >= 0)
		nvmet_rdma_destroy_srq(ndev->srqs[i]);
	kमुक्त(ndev->srqs);
	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_dev(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_rdma_device *ndev =
		container_of(ref, काष्ठा nvmet_rdma_device, ref);

	mutex_lock(&device_list_mutex);
	list_del(&ndev->entry);
	mutex_unlock(&device_list_mutex);

	nvmet_rdma_destroy_srqs(ndev);
	ib_dealloc_pd(ndev->pd);

	kमुक्त(ndev);
पूर्ण

अटल काष्ठा nvmet_rdma_device *
nvmet_rdma_find_get_device(काष्ठा rdma_cm_id *cm_id)
अणु
	काष्ठा nvmet_rdma_port *port = cm_id->context;
	काष्ठा nvmet_port *nport = port->nport;
	काष्ठा nvmet_rdma_device *ndev;
	पूर्णांक अंतरभूत_page_count;
	पूर्णांक अंतरभूत_sge_count;
	पूर्णांक ret;

	mutex_lock(&device_list_mutex);
	list_क्रम_each_entry(ndev, &device_list, entry) अणु
		अगर (ndev->device->node_guid == cm_id->device->node_guid &&
		    kref_get_unless_zero(&ndev->ref))
			जाओ out_unlock;
	पूर्ण

	ndev = kzalloc(माप(*ndev), GFP_KERNEL);
	अगर (!ndev)
		जाओ out_err;

	अंतरभूत_page_count = num_pages(nport->अंतरभूत_data_size);
	अंतरभूत_sge_count = max(cm_id->device->attrs.max_sge_rd,
				cm_id->device->attrs.max_recv_sge) - 1;
	अगर (अंतरभूत_page_count > अंतरभूत_sge_count) अणु
		pr_warn("inline_data_size %d cannot be supported by device %s. Reducing to %lu.\n",
			nport->अंतरभूत_data_size, cm_id->device->name,
			अंतरभूत_sge_count * PAGE_SIZE);
		nport->अंतरभूत_data_size = अंतरभूत_sge_count * PAGE_SIZE;
		अंतरभूत_page_count = अंतरभूत_sge_count;
	पूर्ण
	ndev->अंतरभूत_data_size = nport->अंतरभूत_data_size;
	ndev->अंतरभूत_page_count = अंतरभूत_page_count;

	अगर (nport->pi_enable && !(cm_id->device->attrs.device_cap_flags &
				  IB_DEVICE_INTEGRITY_HANDOVER)) अणु
		pr_warn("T10-PI is not supported by device %s. Disabling it\n",
			cm_id->device->name);
		nport->pi_enable = false;
	पूर्ण

	ndev->device = cm_id->device;
	kref_init(&ndev->ref);

	ndev->pd = ib_alloc_pd(ndev->device, 0);
	अगर (IS_ERR(ndev->pd))
		जाओ out_मुक्त_dev;

	अगर (nvmet_rdma_use_srq) अणु
		ret = nvmet_rdma_init_srqs(ndev);
		अगर (ret)
			जाओ out_मुक्त_pd;
	पूर्ण

	list_add(&ndev->entry, &device_list);
out_unlock:
	mutex_unlock(&device_list_mutex);
	pr_debug("added %s.\n", ndev->device->name);
	वापस ndev;

out_मुक्त_pd:
	ib_dealloc_pd(ndev->pd);
out_मुक्त_dev:
	kमुक्त(ndev);
out_err:
	mutex_unlock(&device_list_mutex);
	वापस शून्य;
पूर्ण

अटल पूर्णांक nvmet_rdma_create_queue_ib(काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा ib_qp_init_attr qp_attr;
	काष्ठा nvmet_rdma_device *ndev = queue->dev;
	पूर्णांक nr_cqe, ret, i, factor;

	/*
	 * Reserve CQ slots क्रम RECV + RDMA_READ/RDMA_WRITE + RDMA_SEND.
	 */
	nr_cqe = queue->recv_queue_size + 2 * queue->send_queue_size;

	queue->cq = ib_cq_pool_get(ndev->device, nr_cqe + 1,
				   queue->comp_vector, IB_POLL_WORKQUEUE);
	अगर (IS_ERR(queue->cq)) अणु
		ret = PTR_ERR(queue->cq);
		pr_err("failed to create CQ cqe= %d ret= %d\n",
		       nr_cqe + 1, ret);
		जाओ out;
	पूर्ण

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.qp_context = queue;
	qp_attr.event_handler = nvmet_rdma_qp_event;
	qp_attr.send_cq = queue->cq;
	qp_attr.recv_cq = queue->cq;
	qp_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	qp_attr.qp_type = IB_QPT_RC;
	/* +1 क्रम drain */
	qp_attr.cap.max_send_wr = queue->send_queue_size + 1;
	factor = rdma_rw_mr_factor(ndev->device, queue->cm_id->port_num,
				   1 << NVMET_RDMA_MAX_MDTS);
	qp_attr.cap.max_rdma_ctxs = queue->send_queue_size * factor;
	qp_attr.cap.max_send_sge = max(ndev->device->attrs.max_sge_rd,
					ndev->device->attrs.max_send_sge);

	अगर (queue->nsrq) अणु
		qp_attr.srq = queue->nsrq->srq;
	पूर्ण अन्यथा अणु
		/* +1 क्रम drain */
		qp_attr.cap.max_recv_wr = 1 + queue->recv_queue_size;
		qp_attr.cap.max_recv_sge = 1 + ndev->अंतरभूत_page_count;
	पूर्ण

	अगर (queue->port->pi_enable && queue->host_qid)
		qp_attr.create_flags |= IB_QP_CREATE_INTEGRITY_EN;

	ret = rdma_create_qp(queue->cm_id, ndev->pd, &qp_attr);
	अगर (ret) अणु
		pr_err("failed to create_qp ret= %d\n", ret);
		जाओ err_destroy_cq;
	पूर्ण
	queue->qp = queue->cm_id->qp;

	atomic_set(&queue->sq_wr_avail, qp_attr.cap.max_send_wr);

	pr_debug("%s: max_cqe= %d max_sge= %d sq_size = %d cm_id= %p\n",
		 __func__, queue->cq->cqe, qp_attr.cap.max_send_sge,
		 qp_attr.cap.max_send_wr, queue->cm_id);

	अगर (!queue->nsrq) अणु
		क्रम (i = 0; i < queue->recv_queue_size; i++) अणु
			queue->cmds[i].queue = queue;
			ret = nvmet_rdma_post_recv(ndev, &queue->cmds[i]);
			अगर (ret)
				जाओ err_destroy_qp;
		पूर्ण
	पूर्ण

out:
	वापस ret;

err_destroy_qp:
	rdma_destroy_qp(queue->cm_id);
err_destroy_cq:
	ib_cq_pool_put(queue->cq, nr_cqe + 1);
	जाओ out;
पूर्ण

अटल व्योम nvmet_rdma_destroy_queue_ib(काष्ठा nvmet_rdma_queue *queue)
अणु
	ib_drain_qp(queue->qp);
	अगर (queue->cm_id)
		rdma_destroy_id(queue->cm_id);
	ib_destroy_qp(queue->qp);
	ib_cq_pool_put(queue->cq, queue->recv_queue_size + 2 *
		       queue->send_queue_size + 1);
पूर्ण

अटल व्योम nvmet_rdma_मुक्त_queue(काष्ठा nvmet_rdma_queue *queue)
अणु
	pr_debug("freeing queue %d\n", queue->idx);

	nvmet_sq_destroy(&queue->nvme_sq);

	nvmet_rdma_destroy_queue_ib(queue);
	अगर (!queue->nsrq) अणु
		nvmet_rdma_मुक्त_cmds(queue->dev, queue->cmds,
				queue->recv_queue_size,
				!queue->host_qid);
	पूर्ण
	nvmet_rdma_मुक्त_rsps(queue);
	ida_simple_हटाओ(&nvmet_rdma_queue_ida, queue->idx);
	kमुक्त(queue);
पूर्ण

अटल व्योम nvmet_rdma_release_queue_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_rdma_queue *queue =
		container_of(w, काष्ठा nvmet_rdma_queue, release_work);
	काष्ठा nvmet_rdma_device *dev = queue->dev;

	nvmet_rdma_मुक्त_queue(queue);

	kref_put(&dev->ref, nvmet_rdma_मुक्त_dev);
पूर्ण

अटल पूर्णांक
nvmet_rdma_parse_cm_connect_req(काष्ठा rdma_conn_param *conn,
				काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा nvme_rdma_cm_req *req;

	req = (काष्ठा nvme_rdma_cm_req *)conn->निजी_data;
	अगर (!req || conn->निजी_data_len == 0)
		वापस NVME_RDMA_CM_INVALID_LEN;

	अगर (le16_to_cpu(req->recfmt) != NVME_RDMA_CM_FMT_1_0)
		वापस NVME_RDMA_CM_INVALID_RECFMT;

	queue->host_qid = le16_to_cpu(req->qid);

	/*
	 * req->hsqsize corresponds to our recv queue size plus 1
	 * req->hrqsize corresponds to our send queue size
	 */
	queue->recv_queue_size = le16_to_cpu(req->hsqsize) + 1;
	queue->send_queue_size = le16_to_cpu(req->hrqsize);

	अगर (!queue->host_qid && queue->recv_queue_size > NVME_AQ_DEPTH)
		वापस NVME_RDMA_CM_INVALID_HSQSIZE;

	/* XXX: Should we enक्रमce some kind of max क्रम IO queues? */

	वापस 0;
पूर्ण

अटल पूर्णांक nvmet_rdma_cm_reject(काष्ठा rdma_cm_id *cm_id,
				क्रमागत nvme_rdma_cm_status status)
अणु
	काष्ठा nvme_rdma_cm_rej rej;

	pr_debug("rejecting connect request: status %d (%s)\n",
		 status, nvme_rdma_cm_msg(status));

	rej.recfmt = cpu_to_le16(NVME_RDMA_CM_FMT_1_0);
	rej.sts = cpu_to_le16(status);

	वापस rdma_reject(cm_id, (व्योम *)&rej, माप(rej),
			   IB_CM_REJ_CONSUMER_DEFINED);
पूर्ण

अटल काष्ठा nvmet_rdma_queue *
nvmet_rdma_alloc_queue(काष्ठा nvmet_rdma_device *ndev,
		काष्ठा rdma_cm_id *cm_id,
		काष्ठा rdma_cm_event *event)
अणु
	काष्ठा nvmet_rdma_port *port = cm_id->context;
	काष्ठा nvmet_rdma_queue *queue;
	पूर्णांक ret;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue) अणु
		ret = NVME_RDMA_CM_NO_RSC;
		जाओ out_reject;
	पूर्ण

	ret = nvmet_sq_init(&queue->nvme_sq);
	अगर (ret) अणु
		ret = NVME_RDMA_CM_NO_RSC;
		जाओ out_मुक्त_queue;
	पूर्ण

	ret = nvmet_rdma_parse_cm_connect_req(&event->param.conn, queue);
	अगर (ret)
		जाओ out_destroy_sq;

	/*
	 * Schedules the actual release because calling rdma_destroy_id from
	 * inside a CM callback would trigger a deadlock. (great API design..)
	 */
	INIT_WORK(&queue->release_work, nvmet_rdma_release_queue_work);
	queue->dev = ndev;
	queue->cm_id = cm_id;
	queue->port = port->nport;

	spin_lock_init(&queue->state_lock);
	queue->state = NVMET_RDMA_Q_CONNECTING;
	INIT_LIST_HEAD(&queue->rsp_रुको_list);
	INIT_LIST_HEAD(&queue->rsp_wr_रुको_list);
	spin_lock_init(&queue->rsp_wr_रुको_lock);
	INIT_LIST_HEAD(&queue->मुक्त_rsps);
	spin_lock_init(&queue->rsps_lock);
	INIT_LIST_HEAD(&queue->queue_list);

	queue->idx = ida_simple_get(&nvmet_rdma_queue_ida, 0, 0, GFP_KERNEL);
	अगर (queue->idx < 0) अणु
		ret = NVME_RDMA_CM_NO_RSC;
		जाओ out_destroy_sq;
	पूर्ण

	/*
	 * Spपढ़ो the io queues across completion vectors,
	 * but still keep all admin queues on vector 0.
	 */
	queue->comp_vector = !queue->host_qid ? 0 :
		queue->idx % ndev->device->num_comp_vectors;


	ret = nvmet_rdma_alloc_rsps(queue);
	अगर (ret) अणु
		ret = NVME_RDMA_CM_NO_RSC;
		जाओ out_ida_हटाओ;
	पूर्ण

	अगर (ndev->srqs) अणु
		queue->nsrq = ndev->srqs[queue->comp_vector % ndev->srq_count];
	पूर्ण अन्यथा अणु
		queue->cmds = nvmet_rdma_alloc_cmds(ndev,
				queue->recv_queue_size,
				!queue->host_qid);
		अगर (IS_ERR(queue->cmds)) अणु
			ret = NVME_RDMA_CM_NO_RSC;
			जाओ out_मुक्त_responses;
		पूर्ण
	पूर्ण

	ret = nvmet_rdma_create_queue_ib(queue);
	अगर (ret) अणु
		pr_err("%s: creating RDMA queue failed (%d).\n",
			__func__, ret);
		ret = NVME_RDMA_CM_NO_RSC;
		जाओ out_मुक्त_cmds;
	पूर्ण

	वापस queue;

out_मुक्त_cmds:
	अगर (!queue->nsrq) अणु
		nvmet_rdma_मुक्त_cmds(queue->dev, queue->cmds,
				queue->recv_queue_size,
				!queue->host_qid);
	पूर्ण
out_मुक्त_responses:
	nvmet_rdma_मुक्त_rsps(queue);
out_ida_हटाओ:
	ida_simple_हटाओ(&nvmet_rdma_queue_ida, queue->idx);
out_destroy_sq:
	nvmet_sq_destroy(&queue->nvme_sq);
out_मुक्त_queue:
	kमुक्त(queue);
out_reject:
	nvmet_rdma_cm_reject(cm_id, ret);
	वापस शून्य;
पूर्ण

अटल व्योम nvmet_rdma_qp_event(काष्ठा ib_event *event, व्योम *priv)
अणु
	काष्ठा nvmet_rdma_queue *queue = priv;

	चयन (event->event) अणु
	हाल IB_EVENT_COMM_EST:
		rdma_notअगरy(queue->cm_id, event->event);
		अवरोध;
	हाल IB_EVENT_QP_LAST_WQE_REACHED:
		pr_debug("received last WQE reached event for queue=0x%p\n",
			 queue);
		अवरोध;
	शेष:
		pr_err("received IB QP event: %s (%d)\n",
		       ib_event_msg(event->event), event->event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nvmet_rdma_cm_accept(काष्ठा rdma_cm_id *cm_id,
		काष्ठा nvmet_rdma_queue *queue,
		काष्ठा rdma_conn_param *p)
अणु
	काष्ठा rdma_conn_param  param = अणु पूर्ण;
	काष्ठा nvme_rdma_cm_rep priv = अणु पूर्ण;
	पूर्णांक ret = -ENOMEM;

	param.rnr_retry_count = 7;
	param.flow_control = 1;
	param.initiator_depth = min_t(u8, p->initiator_depth,
		queue->dev->device->attrs.max_qp_init_rd_atom);
	param.निजी_data = &priv;
	param.निजी_data_len = माप(priv);
	priv.recfmt = cpu_to_le16(NVME_RDMA_CM_FMT_1_0);
	priv.crqsize = cpu_to_le16(queue->recv_queue_size);

	ret = rdma_accept(cm_id, &param);
	अगर (ret)
		pr_err("rdma_accept failed (error code = %d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक nvmet_rdma_queue_connect(काष्ठा rdma_cm_id *cm_id,
		काष्ठा rdma_cm_event *event)
अणु
	काष्ठा nvmet_rdma_device *ndev;
	काष्ठा nvmet_rdma_queue *queue;
	पूर्णांक ret = -EINVAL;

	ndev = nvmet_rdma_find_get_device(cm_id);
	अगर (!ndev) अणु
		nvmet_rdma_cm_reject(cm_id, NVME_RDMA_CM_NO_RSC);
		वापस -ECONNREFUSED;
	पूर्ण

	queue = nvmet_rdma_alloc_queue(ndev, cm_id, event);
	अगर (!queue) अणु
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	अगर (queue->host_qid == 0) अणु
		/* Let inflight controller tearकरोwn complete */
		flush_scheduled_work();
	पूर्ण

	ret = nvmet_rdma_cm_accept(cm_id, queue, &event->param.conn);
	अगर (ret) अणु
		/*
		 * Don't destroy the cm_id in मुक्त path, as we implicitly
		 * destroy the cm_id here with non-zero ret code.
		 */
		queue->cm_id = शून्य;
		जाओ मुक्त_queue;
	पूर्ण

	mutex_lock(&nvmet_rdma_queue_mutex);
	list_add_tail(&queue->queue_list, &nvmet_rdma_queue_list);
	mutex_unlock(&nvmet_rdma_queue_mutex);

	वापस 0;

मुक्त_queue:
	nvmet_rdma_मुक्त_queue(queue);
put_device:
	kref_put(&ndev->ref, nvmet_rdma_मुक्त_dev);

	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_queue_established(काष्ठा nvmet_rdma_queue *queue)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->state_lock, flags);
	अगर (queue->state != NVMET_RDMA_Q_CONNECTING) अणु
		pr_warn("trying to establish a connected queue\n");
		जाओ out_unlock;
	पूर्ण
	queue->state = NVMET_RDMA_Q_LIVE;

	जबतक (!list_empty(&queue->rsp_रुको_list)) अणु
		काष्ठा nvmet_rdma_rsp *cmd;

		cmd = list_first_entry(&queue->rsp_रुको_list,
					काष्ठा nvmet_rdma_rsp, रुको_list);
		list_del(&cmd->रुको_list);

		spin_unlock_irqrestore(&queue->state_lock, flags);
		nvmet_rdma_handle_command(queue, cmd);
		spin_lock_irqsave(&queue->state_lock, flags);
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&queue->state_lock, flags);
पूर्ण

अटल व्योम __nvmet_rdma_queue_disconnect(काष्ठा nvmet_rdma_queue *queue)
अणु
	bool disconnect = false;
	अचिन्हित दीर्घ flags;

	pr_debug("cm_id= %p queue->state= %d\n", queue->cm_id, queue->state);

	spin_lock_irqsave(&queue->state_lock, flags);
	चयन (queue->state) अणु
	हाल NVMET_RDMA_Q_CONNECTING:
		जबतक (!list_empty(&queue->rsp_रुको_list)) अणु
			काष्ठा nvmet_rdma_rsp *rsp;

			rsp = list_first_entry(&queue->rsp_रुको_list,
					       काष्ठा nvmet_rdma_rsp,
					       रुको_list);
			list_del(&rsp->रुको_list);
			nvmet_rdma_put_rsp(rsp);
		पूर्ण
		fallthrough;
	हाल NVMET_RDMA_Q_LIVE:
		queue->state = NVMET_RDMA_Q_DISCONNECTING;
		disconnect = true;
		अवरोध;
	हाल NVMET_RDMA_Q_DISCONNECTING:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&queue->state_lock, flags);

	अगर (disconnect) अणु
		rdma_disconnect(queue->cm_id);
		schedule_work(&queue->release_work);
	पूर्ण
पूर्ण

अटल व्योम nvmet_rdma_queue_disconnect(काष्ठा nvmet_rdma_queue *queue)
अणु
	bool disconnect = false;

	mutex_lock(&nvmet_rdma_queue_mutex);
	अगर (!list_empty(&queue->queue_list)) अणु
		list_del_init(&queue->queue_list);
		disconnect = true;
	पूर्ण
	mutex_unlock(&nvmet_rdma_queue_mutex);

	अगर (disconnect)
		__nvmet_rdma_queue_disconnect(queue);
पूर्ण

अटल व्योम nvmet_rdma_queue_connect_fail(काष्ठा rdma_cm_id *cm_id,
		काष्ठा nvmet_rdma_queue *queue)
अणु
	WARN_ON_ONCE(queue->state != NVMET_RDMA_Q_CONNECTING);

	mutex_lock(&nvmet_rdma_queue_mutex);
	अगर (!list_empty(&queue->queue_list))
		list_del_init(&queue->queue_list);
	mutex_unlock(&nvmet_rdma_queue_mutex);

	pr_err("failed to connect queue %d\n", queue->idx);
	schedule_work(&queue->release_work);
पूर्ण

/**
 * nvme_rdma_device_removal() - Handle RDMA device removal
 * @cm_id:	rdma_cm id, used क्रम nvmet port
 * @queue:      nvmet rdma queue (cm id qp_context)
 *
 * DEVICE_REMOVAL event notअगरies us that the RDMA device is about
 * to unplug. Note that this event can be generated on a normal
 * queue cm_id and/or a device bound listener cm_id (where in this
 * हाल queue will be null).
 *
 * We रेजिस्टरed an ib_client to handle device removal क्रम queues,
 * so we only need to handle the listening port cm_ids. In this हाल
 * we nullअगरy the priv to prevent द्विगुन cm_id deकाष्ठाion and destroying
 * the cm_id implicitely by वापसing a non-zero rc to the callout.
 */
अटल पूर्णांक nvmet_rdma_device_removal(काष्ठा rdma_cm_id *cm_id,
		काष्ठा nvmet_rdma_queue *queue)
अणु
	काष्ठा nvmet_rdma_port *port;

	अगर (queue) अणु
		/*
		 * This is a queue cm_id. we have रेजिस्टरed
		 * an ib_client to handle queues removal
		 * so करोn't पूर्णांकerfear and just वापस.
		 */
		वापस 0;
	पूर्ण

	port = cm_id->context;

	/*
	 * This is a listener cm_id. Make sure that
	 * future हटाओ_port won't invoke a द्विगुन
	 * cm_id destroy. use atomic xchg to make sure
	 * we करोn't compete with हटाओ_port.
	 */
	अगर (xchg(&port->cm_id, शून्य) != cm_id)
		वापस 0;

	/*
	 * We need to वापस 1 so that the core will destroy
	 * it's own ID.  What a great API design..
	 */
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
		काष्ठा rdma_cm_event *event)
अणु
	काष्ठा nvmet_rdma_queue *queue = शून्य;
	पूर्णांक ret = 0;

	अगर (cm_id->qp)
		queue = cm_id->qp->qp_context;

	pr_debug("%s (%d): status %d id %p\n",
		rdma_event_msg(event->event), event->event,
		event->status, cm_id);

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = nvmet_rdma_queue_connect(cm_id, event);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		nvmet_rdma_queue_established(queue);
		अवरोध;
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
		अगर (!queue) अणु
			काष्ठा nvmet_rdma_port *port = cm_id->context;

			schedule_delayed_work(&port->repair_work, 0);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		nvmet_rdma_queue_disconnect(queue);
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		ret = nvmet_rdma_device_removal(cm_id, queue);
		अवरोध;
	हाल RDMA_CM_EVENT_REJECTED:
		pr_debug("Connection rejected: %s\n",
			 rdma_reject_msg(cm_id, event->status));
		fallthrough;
	हाल RDMA_CM_EVENT_UNREACHABLE:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
		nvmet_rdma_queue_connect_fail(cm_id, queue);
		अवरोध;
	शेष:
		pr_err("received unrecognized RDMA CM event %d\n",
			event->event);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_delete_ctrl(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा nvmet_rdma_queue *queue;

restart:
	mutex_lock(&nvmet_rdma_queue_mutex);
	list_क्रम_each_entry(queue, &nvmet_rdma_queue_list, queue_list) अणु
		अगर (queue->nvme_sq.ctrl == ctrl) अणु
			list_del_init(&queue->queue_list);
			mutex_unlock(&nvmet_rdma_queue_mutex);

			__nvmet_rdma_queue_disconnect(queue);
			जाओ restart;
		पूर्ण
	पूर्ण
	mutex_unlock(&nvmet_rdma_queue_mutex);
पूर्ण

अटल व्योम nvmet_rdma_disable_port(काष्ठा nvmet_rdma_port *port)
अणु
	काष्ठा rdma_cm_id *cm_id = xchg(&port->cm_id, शून्य);

	अगर (cm_id)
		rdma_destroy_id(cm_id);
पूर्ण

अटल पूर्णांक nvmet_rdma_enable_port(काष्ठा nvmet_rdma_port *port)
अणु
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)&port->addr;
	काष्ठा rdma_cm_id *cm_id;
	पूर्णांक ret;

	cm_id = rdma_create_id(&init_net, nvmet_rdma_cm_handler, port,
			RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(cm_id)) अणु
		pr_err("CM ID creation failed\n");
		वापस PTR_ERR(cm_id);
	पूर्ण

	/*
	 * Allow both IPv4 and IPv6 sockets to bind a single port
	 * at the same समय.
	 */
	ret = rdma_set_afonly(cm_id, 1);
	अगर (ret) अणु
		pr_err("rdma_set_afonly failed (%d)\n", ret);
		जाओ out_destroy_id;
	पूर्ण

	ret = rdma_bind_addr(cm_id, addr);
	अगर (ret) अणु
		pr_err("binding CM ID to %pISpcs failed (%d)\n", addr, ret);
		जाओ out_destroy_id;
	पूर्ण

	ret = rdma_listen(cm_id, 128);
	अगर (ret) अणु
		pr_err("listening to %pISpcs failed (%d)\n", addr, ret);
		जाओ out_destroy_id;
	पूर्ण

	port->cm_id = cm_id;
	वापस 0;

out_destroy_id:
	rdma_destroy_id(cm_id);
	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_repair_port_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_rdma_port *port = container_of(to_delayed_work(w),
			काष्ठा nvmet_rdma_port, repair_work);
	पूर्णांक ret;

	nvmet_rdma_disable_port(port);
	ret = nvmet_rdma_enable_port(port);
	अगर (ret)
		schedule_delayed_work(&port->repair_work, 5 * HZ);
पूर्ण

अटल पूर्णांक nvmet_rdma_add_port(काष्ठा nvmet_port *nport)
अणु
	काष्ठा nvmet_rdma_port *port;
	__kernel_sa_family_t af;
	पूर्णांक ret;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	nport->priv = port;
	port->nport = nport;
	INIT_DELAYED_WORK(&port->repair_work, nvmet_rdma_repair_port_work);

	चयन (nport->disc_addr.adrfam) अणु
	हाल NVMF_ADDR_FAMILY_IP4:
		af = AF_INET;
		अवरोध;
	हाल NVMF_ADDR_FAMILY_IP6:
		af = AF_INET6;
		अवरोध;
	शेष:
		pr_err("address family %d not supported\n",
			nport->disc_addr.adrfam);
		ret = -EINVAL;
		जाओ out_मुक्त_port;
	पूर्ण

	अगर (nport->अंतरभूत_data_size < 0) अणु
		nport->अंतरभूत_data_size = NVMET_RDMA_DEFAULT_INLINE_DATA_SIZE;
	पूर्ण अन्यथा अगर (nport->अंतरभूत_data_size > NVMET_RDMA_MAX_INLINE_DATA_SIZE) अणु
		pr_warn("inline_data_size %u is too large, reducing to %u\n",
			nport->अंतरभूत_data_size,
			NVMET_RDMA_MAX_INLINE_DATA_SIZE);
		nport->अंतरभूत_data_size = NVMET_RDMA_MAX_INLINE_DATA_SIZE;
	पूर्ण

	ret = inet_pton_with_scope(&init_net, af, nport->disc_addr.traddr,
			nport->disc_addr.trsvcid, &port->addr);
	अगर (ret) अणु
		pr_err("malformed ip/port passed: %s:%s\n",
			nport->disc_addr.traddr, nport->disc_addr.trsvcid);
		जाओ out_मुक्त_port;
	पूर्ण

	ret = nvmet_rdma_enable_port(port);
	अगर (ret)
		जाओ out_मुक्त_port;

	pr_info("enabling port %d (%pISpcs)\n",
		le16_to_cpu(nport->disc_addr.portid),
		(काष्ठा sockaddr *)&port->addr);

	वापस 0;

out_मुक्त_port:
	kमुक्त(port);
	वापस ret;
पूर्ण

अटल व्योम nvmet_rdma_हटाओ_port(काष्ठा nvmet_port *nport)
अणु
	काष्ठा nvmet_rdma_port *port = nport->priv;

	cancel_delayed_work_sync(&port->repair_work);
	nvmet_rdma_disable_port(port);
	kमुक्त(port);
पूर्ण

अटल व्योम nvmet_rdma_disc_port_addr(काष्ठा nvmet_req *req,
		काष्ठा nvmet_port *nport, अक्षर *traddr)
अणु
	काष्ठा nvmet_rdma_port *port = nport->priv;
	काष्ठा rdma_cm_id *cm_id = port->cm_id;

	अगर (inet_addr_is_any((काष्ठा sockaddr *)&cm_id->route.addr.src_addr)) अणु
		काष्ठा nvmet_rdma_rsp *rsp =
			container_of(req, काष्ठा nvmet_rdma_rsp, req);
		काष्ठा rdma_cm_id *req_cm_id = rsp->queue->cm_id;
		काष्ठा sockaddr *addr = (व्योम *)&req_cm_id->route.addr.src_addr;

		प्र_लिखो(traddr, "%pISc", addr);
	पूर्ण अन्यथा अणु
		स_नकल(traddr, nport->disc_addr.traddr, NVMF_TRADDR_SIZE);
	पूर्ण
पूर्ण

अटल u8 nvmet_rdma_get_mdts(स्थिर काष्ठा nvmet_ctrl *ctrl)
अणु
	अगर (ctrl->pi_support)
		वापस NVMET_RDMA_MAX_METADATA_MDTS;
	वापस NVMET_RDMA_MAX_MDTS;
पूर्ण

अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_rdma_ops = अणु
	.owner			= THIS_MODULE,
	.type			= NVMF_TRTYPE_RDMA,
	.msdbd			= 1,
	.flags			= NVMF_KEYED_SGLS | NVMF_METADATA_SUPPORTED,
	.add_port		= nvmet_rdma_add_port,
	.हटाओ_port		= nvmet_rdma_हटाओ_port,
	.queue_response		= nvmet_rdma_queue_response,
	.delete_ctrl		= nvmet_rdma_delete_ctrl,
	.disc_traddr		= nvmet_rdma_disc_port_addr,
	.get_mdts		= nvmet_rdma_get_mdts,
पूर्ण;

अटल व्योम nvmet_rdma_हटाओ_one(काष्ठा ib_device *ib_device, व्योम *client_data)
अणु
	काष्ठा nvmet_rdma_queue *queue, *पंचांगp;
	काष्ठा nvmet_rdma_device *ndev;
	bool found = false;

	mutex_lock(&device_list_mutex);
	list_क्रम_each_entry(ndev, &device_list, entry) अणु
		अगर (ndev->device == ib_device) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&device_list_mutex);

	अगर (!found)
		वापस;

	/*
	 * IB Device that is used by nvmet controllers is being हटाओd,
	 * delete all queues using this device.
	 */
	mutex_lock(&nvmet_rdma_queue_mutex);
	list_क्रम_each_entry_safe(queue, पंचांगp, &nvmet_rdma_queue_list,
				 queue_list) अणु
		अगर (queue->dev->device != ib_device)
			जारी;

		pr_info("Removing queue %d\n", queue->idx);
		list_del_init(&queue->queue_list);
		__nvmet_rdma_queue_disconnect(queue);
	पूर्ण
	mutex_unlock(&nvmet_rdma_queue_mutex);

	flush_scheduled_work();
पूर्ण

अटल काष्ठा ib_client nvmet_rdma_ib_client = अणु
	.name   = "nvmet_rdma",
	.हटाओ = nvmet_rdma_हटाओ_one
पूर्ण;

अटल पूर्णांक __init nvmet_rdma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ib_रेजिस्टर_client(&nvmet_rdma_ib_client);
	अगर (ret)
		वापस ret;

	ret = nvmet_रेजिस्टर_transport(&nvmet_rdma_ops);
	अगर (ret)
		जाओ err_ib_client;

	वापस 0;

err_ib_client:
	ib_unरेजिस्टर_client(&nvmet_rdma_ib_client);
	वापस ret;
पूर्ण

अटल व्योम __निकास nvmet_rdma_निकास(व्योम)
अणु
	nvmet_unरेजिस्टर_transport(&nvmet_rdma_ops);
	ib_unरेजिस्टर_client(&nvmet_rdma_ib_client);
	WARN_ON_ONCE(!list_empty(&nvmet_rdma_queue_list));
	ida_destroy(&nvmet_rdma_queue_ida);
पूर्ण

module_init(nvmet_rdma_init);
module_निकास(nvmet_rdma_निकास);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("nvmet-transport-1"); /* 1 == NVMF_TRTYPE_RDMA */
