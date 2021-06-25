<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics TCP host.
 * Copyright (c) 2018 Lightbits Lअसल. All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/nvme-tcp.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <linux/blk-mq.h>
#समावेश <crypto/hash.h>
#समावेश <net/busy_poll.h>

#समावेश "nvme.h"
#समावेश "fabrics.h"

काष्ठा nvme_tcp_queue;

/* Define the socket priority to use क्रम connections were it is desirable
 * that the NIC consider perक्रमming optimized packet processing or filtering.
 * A non-zero value being sufficient to indicate general consideration of any
 * possible optimization.  Making it a module param allows क्रम alternative
 * values that may be unique क्रम some NIC implementations.
 */
अटल पूर्णांक so_priority;
module_param(so_priority, पूर्णांक, 0644);
MODULE_PARM_DESC(so_priority, "nvme tcp socket optimize priority");

क्रमागत nvme_tcp_send_state अणु
	NVME_TCP_SEND_CMD_PDU = 0,
	NVME_TCP_SEND_H2C_PDU,
	NVME_TCP_SEND_DATA,
	NVME_TCP_SEND_DDGST,
पूर्ण;

काष्ठा nvme_tcp_request अणु
	काष्ठा nvme_request	req;
	व्योम			*pdu;
	काष्ठा nvme_tcp_queue	*queue;
	u32			data_len;
	u32			pdu_len;
	u32			pdu_sent;
	u16			ttag;
	काष्ठा list_head	entry;
	काष्ठा llist_node	lentry;
	__le32			ddgst;

	काष्ठा bio		*curr_bio;
	काष्ठा iov_iter		iter;

	/* send state */
	माप_प्रकार			offset;
	माप_प्रकार			data_sent;
	क्रमागत nvme_tcp_send_state state;
पूर्ण;

क्रमागत nvme_tcp_queue_flags अणु
	NVME_TCP_Q_ALLOCATED	= 0,
	NVME_TCP_Q_LIVE		= 1,
	NVME_TCP_Q_POLLING	= 2,
पूर्ण;

क्रमागत nvme_tcp_recv_state अणु
	NVME_TCP_RECV_PDU = 0,
	NVME_TCP_RECV_DATA,
	NVME_TCP_RECV_DDGST,
पूर्ण;

काष्ठा nvme_tcp_ctrl;
काष्ठा nvme_tcp_queue अणु
	काष्ठा socket		*sock;
	काष्ठा work_काष्ठा	io_work;
	पूर्णांक			io_cpu;

	काष्ठा mutex		queue_lock;
	काष्ठा mutex		send_mutex;
	काष्ठा llist_head	req_list;
	काष्ठा list_head	send_list;
	bool			more_requests;

	/* recv state */
	व्योम			*pdu;
	पूर्णांक			pdu_reमुख्यing;
	पूर्णांक			pdu_offset;
	माप_प्रकार			data_reमुख्यing;
	माप_प्रकार			ddgst_reमुख्यing;
	अचिन्हित पूर्णांक		nr_cqe;

	/* send state */
	काष्ठा nvme_tcp_request *request;

	पूर्णांक			queue_size;
	माप_प्रकार			cmnd_capsule_len;
	काष्ठा nvme_tcp_ctrl	*ctrl;
	अचिन्हित दीर्घ		flags;
	bool			rd_enabled;

	bool			hdr_digest;
	bool			data_digest;
	काष्ठा ahash_request	*rcv_hash;
	काष्ठा ahash_request	*snd_hash;
	__le32			exp_ddgst;
	__le32			recv_ddgst;

	काष्ठा page_frag_cache	pf_cache;

	व्योम (*state_change)(काष्ठा sock *);
	व्योम (*data_पढ़ोy)(काष्ठा sock *);
	व्योम (*ग_लिखो_space)(काष्ठा sock *);
पूर्ण;

काष्ठा nvme_tcp_ctrl अणु
	/* पढ़ो only in the hot path */
	काष्ठा nvme_tcp_queue	*queues;
	काष्ठा blk_mq_tag_set	tag_set;

	/* other member variables */
	काष्ठा list_head	list;
	काष्ठा blk_mq_tag_set	admin_tag_set;
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_storage src_addr;
	काष्ठा nvme_ctrl	ctrl;

	काष्ठा work_काष्ठा	err_work;
	काष्ठा delayed_work	connect_work;
	काष्ठा nvme_tcp_request async_req;
	u32			io_queues[HCTX_MAX_TYPES];
पूर्ण;

अटल LIST_HEAD(nvme_tcp_ctrl_list);
अटल DEFINE_MUTEX(nvme_tcp_ctrl_mutex);
अटल काष्ठा workqueue_काष्ठा *nvme_tcp_wq;
अटल स्थिर काष्ठा blk_mq_ops nvme_tcp_mq_ops;
अटल स्थिर काष्ठा blk_mq_ops nvme_tcp_admin_mq_ops;
अटल पूर्णांक nvme_tcp_try_send(काष्ठा nvme_tcp_queue *queue);

अटल अंतरभूत काष्ठा nvme_tcp_ctrl *to_tcp_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा nvme_tcp_ctrl, ctrl);
पूर्ण

अटल अंतरभूत पूर्णांक nvme_tcp_queue_id(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस queue - queue->ctrl->queues;
पूर्ण

अटल अंतरभूत काष्ठा blk_mq_tags *nvme_tcp_tagset(काष्ठा nvme_tcp_queue *queue)
अणु
	u32 queue_idx = nvme_tcp_queue_id(queue);

	अगर (queue_idx == 0)
		वापस queue->ctrl->admin_tag_set.tags[queue_idx];
	वापस queue->ctrl->tag_set.tags[queue_idx - 1];
पूर्ण

अटल अंतरभूत u8 nvme_tcp_hdgst_len(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस queue->hdr_digest ? NVME_TCP_DIGEST_LENGTH : 0;
पूर्ण

अटल अंतरभूत u8 nvme_tcp_ddgst_len(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस queue->data_digest ? NVME_TCP_DIGEST_LENGTH : 0;
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_tcp_अंतरभूत_data_size(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस queue->cmnd_capsule_len - माप(काष्ठा nvme_command);
पूर्ण

अटल अंतरभूत bool nvme_tcp_async_req(काष्ठा nvme_tcp_request *req)
अणु
	वापस req == &req->queue->ctrl->async_req;
पूर्ण

अटल अंतरभूत bool nvme_tcp_has_अंतरभूत_data(काष्ठा nvme_tcp_request *req)
अणु
	काष्ठा request *rq;

	अगर (unlikely(nvme_tcp_async_req(req)))
		वापस false; /* async events करोn't have a request */

	rq = blk_mq_rq_from_pdu(req);

	वापस rq_data_dir(rq) == WRITE && req->data_len &&
		req->data_len <= nvme_tcp_अंतरभूत_data_size(req->queue);
पूर्ण

अटल अंतरभूत काष्ठा page *nvme_tcp_req_cur_page(काष्ठा nvme_tcp_request *req)
अणु
	वापस req->iter.bvec->bv_page;
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_tcp_req_cur_offset(काष्ठा nvme_tcp_request *req)
अणु
	वापस req->iter.bvec->bv_offset + req->iter.iov_offset;
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_tcp_req_cur_length(काष्ठा nvme_tcp_request *req)
अणु
	वापस min_t(माप_प्रकार, iov_iter_single_seg_count(&req->iter),
			req->pdu_len - req->pdu_sent);
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_tcp_pdu_data_left(काष्ठा nvme_tcp_request *req)
अणु
	वापस rq_data_dir(blk_mq_rq_from_pdu(req)) == WRITE ?
			req->pdu_len - req->pdu_sent : 0;
पूर्ण

अटल अंतरभूत माप_प्रकार nvme_tcp_pdu_last_send(काष्ठा nvme_tcp_request *req,
		पूर्णांक len)
अणु
	वापस nvme_tcp_pdu_data_left(req) <= len;
पूर्ण

अटल व्योम nvme_tcp_init_iter(काष्ठा nvme_tcp_request *req,
		अचिन्हित पूर्णांक dir)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(req);
	काष्ठा bio_vec *vec;
	अचिन्हित पूर्णांक size;
	पूर्णांक nr_bvec;
	माप_प्रकार offset;

	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD) अणु
		vec = &rq->special_vec;
		nr_bvec = 1;
		size = blk_rq_payload_bytes(rq);
		offset = 0;
	पूर्ण अन्यथा अणु
		काष्ठा bio *bio = req->curr_bio;
		काष्ठा bvec_iter bi;
		काष्ठा bio_vec bv;

		vec = __bvec_iter_bvec(bio->bi_io_vec, bio->bi_iter);
		nr_bvec = 0;
		bio_क्रम_each_bvec(bv, bio, bi) अणु
			nr_bvec++;
		पूर्ण
		size = bio->bi_iter.bi_size;
		offset = bio->bi_iter.bi_bvec_करोne;
	पूर्ण

	iov_iter_bvec(&req->iter, dir, vec, nr_bvec, size);
	req->iter.iov_offset = offset;
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_advance_req(काष्ठा nvme_tcp_request *req,
		पूर्णांक len)
अणु
	req->data_sent += len;
	req->pdu_sent += len;
	iov_iter_advance(&req->iter, len);
	अगर (!iov_iter_count(&req->iter) &&
	    req->data_sent < req->data_len) अणु
		req->curr_bio = req->curr_bio->bi_next;
		nvme_tcp_init_iter(req, WRITE);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_send_all(काष्ठा nvme_tcp_queue *queue)
अणु
	पूर्णांक ret;

	/* drain the send queue as much as we can... */
	करो अणु
		ret = nvme_tcp_try_send(queue);
	पूर्ण जबतक (ret > 0);
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_queue_request(काष्ठा nvme_tcp_request *req,
		bool sync, bool last)
अणु
	काष्ठा nvme_tcp_queue *queue = req->queue;
	bool empty;

	empty = llist_add(&req->lentry, &queue->req_list) &&
		list_empty(&queue->send_list) && !queue->request;

	/*
	 * अगर we're the first on the send_list and we can try to send
	 * directly, otherwise queue io_work. Also, only करो that अगर we
	 * are on the same cpu, so we करोn't पूर्णांकroduce contention.
	 */
	अगर (queue->io_cpu == raw_smp_processor_id() &&
	    sync && empty && mutex_trylock(&queue->send_mutex)) अणु
		queue->more_requests = !last;
		nvme_tcp_send_all(queue);
		queue->more_requests = false;
		mutex_unlock(&queue->send_mutex);
	पूर्ण अन्यथा अगर (last) अणु
		queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
	पूर्ण
पूर्ण

अटल व्योम nvme_tcp_process_req_list(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_request *req;
	काष्ठा llist_node *node;

	क्रम (node = llist_del_all(&queue->req_list); node; node = node->next) अणु
		req = llist_entry(node, काष्ठा nvme_tcp_request, lentry);
		list_add(&req->entry, &queue->send_list);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा nvme_tcp_request *
nvme_tcp_fetch_request(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_request *req;

	req = list_first_entry_or_null(&queue->send_list,
			काष्ठा nvme_tcp_request, entry);
	अगर (!req) अणु
		nvme_tcp_process_req_list(queue);
		req = list_first_entry_or_null(&queue->send_list,
				काष्ठा nvme_tcp_request, entry);
		अगर (unlikely(!req))
			वापस शून्य;
	पूर्ण

	list_del(&req->entry);
	वापस req;
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_ddgst_final(काष्ठा ahash_request *hash,
		__le32 *dgst)
अणु
	ahash_request_set_crypt(hash, शून्य, (u8 *)dgst, 0);
	crypto_ahash_final(hash);
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_ddgst_update(काष्ठा ahash_request *hash,
		काष्ठा page *page, off_t off, माप_प्रकार len)
अणु
	काष्ठा scatterlist sg;

	sg_init_marker(&sg, 1);
	sg_set_page(&sg, page, len, off);
	ahash_request_set_crypt(hash, &sg, शून्य, len);
	crypto_ahash_update(hash);
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_hdgst(काष्ठा ahash_request *hash,
		व्योम *pdu, माप_प्रकार len)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, pdu, len);
	ahash_request_set_crypt(hash, &sg, pdu + len, len);
	crypto_ahash_digest(hash);
पूर्ण

अटल पूर्णांक nvme_tcp_verअगरy_hdgst(काष्ठा nvme_tcp_queue *queue,
		व्योम *pdu, माप_प्रकार pdu_len)
अणु
	काष्ठा nvme_tcp_hdr *hdr = pdu;
	__le32 recv_digest;
	__le32 exp_digest;

	अगर (unlikely(!(hdr->flags & NVME_TCP_F_HDGST))) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d: header digest flag is cleared\n",
			nvme_tcp_queue_id(queue));
		वापस -EPROTO;
	पूर्ण

	recv_digest = *(__le32 *)(pdu + hdr->hlen);
	nvme_tcp_hdgst(queue->rcv_hash, pdu, pdu_len);
	exp_digest = *(__le32 *)(pdu + hdr->hlen);
	अगर (recv_digest != exp_digest) अणु
		dev_err(queue->ctrl->ctrl.device,
			"header digest error: recv %#x expected %#x\n",
			le32_to_cpu(recv_digest), le32_to_cpu(exp_digest));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_check_ddgst(काष्ठा nvme_tcp_queue *queue, व्योम *pdu)
अणु
	काष्ठा nvme_tcp_hdr *hdr = pdu;
	u8 digest_len = nvme_tcp_hdgst_len(queue);
	u32 len;

	len = le32_to_cpu(hdr->plen) - hdr->hlen -
		((hdr->flags & NVME_TCP_F_HDGST) ? digest_len : 0);

	अगर (unlikely(len && !(hdr->flags & NVME_TCP_F_DDGST))) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d: data digest flag is cleared\n",
		nvme_tcp_queue_id(queue));
		वापस -EPROTO;
	पूर्ण
	crypto_ahash_init(queue->rcv_hash);

	वापस 0;
पूर्ण

अटल व्योम nvme_tcp_निकास_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *rq, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);

	page_frag_मुक्त(req->pdu);
पूर्ण

अटल पूर्णांक nvme_tcp_init_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *rq, अचिन्हित पूर्णांक hctx_idx,
		अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = set->driver_data;
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_tcp_cmd_pdu *pdu;
	पूर्णांक queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[queue_idx];
	u8 hdgst = nvme_tcp_hdgst_len(queue);

	req->pdu = page_frag_alloc(&queue->pf_cache,
		माप(काष्ठा nvme_tcp_cmd_pdu) + hdgst,
		GFP_KERNEL | __GFP_ZERO);
	अगर (!req->pdu)
		वापस -ENOMEM;

	pdu = req->pdu;
	req->queue = queue;
	nvme_req(rq)->ctrl = &ctrl->ctrl;
	nvme_req(rq)->cmd = &pdu->cmd;

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = data;
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[hctx_idx + 1];

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_init_admin_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = data;
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[0];

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल क्रमागत nvme_tcp_recv_state
nvme_tcp_recv_state(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस  (queue->pdu_reमुख्यing) ? NVME_TCP_RECV_PDU :
		(queue->ddgst_reमुख्यing) ? NVME_TCP_RECV_DDGST :
		NVME_TCP_RECV_DATA;
पूर्ण

अटल व्योम nvme_tcp_init_recv_ctx(काष्ठा nvme_tcp_queue *queue)
अणु
	queue->pdu_reमुख्यing = माप(काष्ठा nvme_tcp_rsp_pdu) +
				nvme_tcp_hdgst_len(queue);
	queue->pdu_offset = 0;
	queue->data_reमुख्यing = -1;
	queue->ddgst_reमुख्यing = 0;
पूर्ण

अटल व्योम nvme_tcp_error_recovery(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_RESETTING))
		वापस;

	dev_warn(ctrl->device, "starting error recovery\n");
	queue_work(nvme_reset_wq, &to_tcp_ctrl(ctrl)->err_work);
पूर्ण

अटल पूर्णांक nvme_tcp_process_nvme_cqe(काष्ठा nvme_tcp_queue *queue,
		काष्ठा nvme_completion *cqe)
अणु
	काष्ठा request *rq;

	rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue), cqe->command_id);
	अगर (!rq) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag 0x%x not found\n",
			nvme_tcp_queue_id(queue), cqe->command_id);
		nvme_tcp_error_recovery(&queue->ctrl->ctrl);
		वापस -EINVAL;
	पूर्ण

	अगर (!nvme_try_complete_req(rq, cqe->status, cqe->result))
		nvme_complete_rq(rq);
	queue->nr_cqe++;

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_handle_c2h_data(काष्ठा nvme_tcp_queue *queue,
		काष्ठा nvme_tcp_data_pdu *pdu)
अणु
	काष्ठा request *rq;

	rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue), pdu->command_id);
	अगर (!rq) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag %#x not found\n",
			nvme_tcp_queue_id(queue), pdu->command_id);
		वापस -ENOENT;
	पूर्ण

	अगर (!blk_rq_payload_bytes(rq)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag %#x unexpected data\n",
			nvme_tcp_queue_id(queue), rq->tag);
		वापस -EIO;
	पूर्ण

	queue->data_reमुख्यing = le32_to_cpu(pdu->data_length);

	अगर (pdu->hdr.flags & NVME_TCP_F_DATA_SUCCESS &&
	    unlikely(!(pdu->hdr.flags & NVME_TCP_F_DATA_LAST))) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag %#x SUCCESS set but not last PDU\n",
			nvme_tcp_queue_id(queue), rq->tag);
		nvme_tcp_error_recovery(&queue->ctrl->ctrl);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_handle_comp(काष्ठा nvme_tcp_queue *queue,
		काष्ठा nvme_tcp_rsp_pdu *pdu)
अणु
	काष्ठा nvme_completion *cqe = &pdu->cqe;
	पूर्णांक ret = 0;

	/*
	 * AEN requests are special as they करोn't समय out and can
	 * survive any kind of queue मुक्तze and often करोn't respond to
	 * पातs.  We करोn't even bother to allocate a काष्ठा request
	 * क्रम them but rather special हाल them here.
	 */
	अगर (unlikely(nvme_is_aen_req(nvme_tcp_queue_id(queue),
				     cqe->command_id)))
		nvme_complete_async_event(&queue->ctrl->ctrl, cqe->status,
				&cqe->result);
	अन्यथा
		ret = nvme_tcp_process_nvme_cqe(queue, cqe);

	वापस ret;
पूर्ण

अटल पूर्णांक nvme_tcp_setup_h2c_data_pdu(काष्ठा nvme_tcp_request *req,
		काष्ठा nvme_tcp_r2t_pdu *pdu)
अणु
	काष्ठा nvme_tcp_data_pdu *data = req->pdu;
	काष्ठा nvme_tcp_queue *queue = req->queue;
	काष्ठा request *rq = blk_mq_rq_from_pdu(req);
	u8 hdgst = nvme_tcp_hdgst_len(queue);
	u8 ddgst = nvme_tcp_ddgst_len(queue);

	req->pdu_len = le32_to_cpu(pdu->r2t_length);
	req->pdu_sent = 0;

	अगर (unlikely(!req->pdu_len)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"req %d r2t len is %u, probably a bug...\n",
			rq->tag, req->pdu_len);
		वापस -EPROTO;
	पूर्ण

	अगर (unlikely(req->data_sent + req->pdu_len > req->data_len)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"req %d r2t len %u exceeded data len %u (%zu sent)\n",
			rq->tag, req->pdu_len, req->data_len,
			req->data_sent);
		वापस -EPROTO;
	पूर्ण

	अगर (unlikely(le32_to_cpu(pdu->r2t_offset) < req->data_sent)) अणु
		dev_err(queue->ctrl->ctrl.device,
			"req %d unexpected r2t offset %u (expected %zu)\n",
			rq->tag, le32_to_cpu(pdu->r2t_offset),
			req->data_sent);
		वापस -EPROTO;
	पूर्ण

	स_रखो(data, 0, माप(*data));
	data->hdr.type = nvme_tcp_h2c_data;
	data->hdr.flags = NVME_TCP_F_DATA_LAST;
	अगर (queue->hdr_digest)
		data->hdr.flags |= NVME_TCP_F_HDGST;
	अगर (queue->data_digest)
		data->hdr.flags |= NVME_TCP_F_DDGST;
	data->hdr.hlen = माप(*data);
	data->hdr.pकरो = data->hdr.hlen + hdgst;
	data->hdr.plen =
		cpu_to_le32(data->hdr.hlen + hdgst + req->pdu_len + ddgst);
	data->ttag = pdu->ttag;
	data->command_id = rq->tag;
	data->data_offset = cpu_to_le32(req->data_sent);
	data->data_length = cpu_to_le32(req->pdu_len);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_handle_r2t(काष्ठा nvme_tcp_queue *queue,
		काष्ठा nvme_tcp_r2t_pdu *pdu)
अणु
	काष्ठा nvme_tcp_request *req;
	काष्ठा request *rq;
	पूर्णांक ret;

	rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue), pdu->command_id);
	अगर (!rq) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag %#x not found\n",
			nvme_tcp_queue_id(queue), pdu->command_id);
		वापस -ENOENT;
	पूर्ण
	req = blk_mq_rq_to_pdu(rq);

	ret = nvme_tcp_setup_h2c_data_pdu(req, pdu);
	अगर (unlikely(ret))
		वापस ret;

	req->state = NVME_TCP_SEND_H2C_PDU;
	req->offset = 0;

	nvme_tcp_queue_request(req, false, true);

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_recv_pdu(काष्ठा nvme_tcp_queue *queue, काष्ठा sk_buff *skb,
		अचिन्हित पूर्णांक *offset, माप_प्रकार *len)
अणु
	काष्ठा nvme_tcp_hdr *hdr;
	अक्षर *pdu = queue->pdu;
	माप_प्रकार rcv_len = min_t(माप_प्रकार, *len, queue->pdu_reमुख्यing);
	पूर्णांक ret;

	ret = skb_copy_bits(skb, *offset,
		&pdu[queue->pdu_offset], rcv_len);
	अगर (unlikely(ret))
		वापस ret;

	queue->pdu_reमुख्यing -= rcv_len;
	queue->pdu_offset += rcv_len;
	*offset += rcv_len;
	*len -= rcv_len;
	अगर (queue->pdu_reमुख्यing)
		वापस 0;

	hdr = queue->pdu;
	अगर (queue->hdr_digest) अणु
		ret = nvme_tcp_verअगरy_hdgst(queue, queue->pdu, hdr->hlen);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण


	अगर (queue->data_digest) अणु
		ret = nvme_tcp_check_ddgst(queue, queue->pdu);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण

	चयन (hdr->type) अणु
	हाल nvme_tcp_c2h_data:
		वापस nvme_tcp_handle_c2h_data(queue, (व्योम *)queue->pdu);
	हाल nvme_tcp_rsp:
		nvme_tcp_init_recv_ctx(queue);
		वापस nvme_tcp_handle_comp(queue, (व्योम *)queue->pdu);
	हाल nvme_tcp_r2t:
		nvme_tcp_init_recv_ctx(queue);
		वापस nvme_tcp_handle_r2t(queue, (व्योम *)queue->pdu);
	शेष:
		dev_err(queue->ctrl->ctrl.device,
			"unsupported pdu type (%d)\n", hdr->type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_end_request(काष्ठा request *rq, u16 status)
अणु
	जोड़ nvme_result res = अणुपूर्ण;

	अगर (!nvme_try_complete_req(rq, cpu_to_le16(status << 1), res))
		nvme_complete_rq(rq);
पूर्ण

अटल पूर्णांक nvme_tcp_recv_data(काष्ठा nvme_tcp_queue *queue, काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक *offset, माप_प्रकार *len)
अणु
	काष्ठा nvme_tcp_data_pdu *pdu = (व्योम *)queue->pdu;
	काष्ठा nvme_tcp_request *req;
	काष्ठा request *rq;

	rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue), pdu->command_id);
	अगर (!rq) अणु
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag %#x not found\n",
			nvme_tcp_queue_id(queue), pdu->command_id);
		वापस -ENOENT;
	पूर्ण
	req = blk_mq_rq_to_pdu(rq);

	जबतक (true) अणु
		पूर्णांक recv_len, ret;

		recv_len = min_t(माप_प्रकार, *len, queue->data_reमुख्यing);
		अगर (!recv_len)
			अवरोध;

		अगर (!iov_iter_count(&req->iter)) अणु
			req->curr_bio = req->curr_bio->bi_next;

			/*
			 * If we करोn`t have any bios it means that controller
			 * sent more data than we requested, hence error
			 */
			अगर (!req->curr_bio) अणु
				dev_err(queue->ctrl->ctrl.device,
					"queue %d no space in request %#x",
					nvme_tcp_queue_id(queue), rq->tag);
				nvme_tcp_init_recv_ctx(queue);
				वापस -EIO;
			पूर्ण
			nvme_tcp_init_iter(req, READ);
		पूर्ण

		/* we can पढ़ो only from what is left in this bio */
		recv_len = min_t(माप_प्रकार, recv_len,
				iov_iter_count(&req->iter));

		अगर (queue->data_digest)
			ret = skb_copy_and_hash_datagram_iter(skb, *offset,
				&req->iter, recv_len, queue->rcv_hash);
		अन्यथा
			ret = skb_copy_datagram_iter(skb, *offset,
					&req->iter, recv_len);
		अगर (ret) अणु
			dev_err(queue->ctrl->ctrl.device,
				"queue %d failed to copy request %#x data",
				nvme_tcp_queue_id(queue), rq->tag);
			वापस ret;
		पूर्ण

		*len -= recv_len;
		*offset += recv_len;
		queue->data_reमुख्यing -= recv_len;
	पूर्ण

	अगर (!queue->data_reमुख्यing) अणु
		अगर (queue->data_digest) अणु
			nvme_tcp_ddgst_final(queue->rcv_hash, &queue->exp_ddgst);
			queue->ddgst_reमुख्यing = NVME_TCP_DIGEST_LENGTH;
		पूर्ण अन्यथा अणु
			अगर (pdu->hdr.flags & NVME_TCP_F_DATA_SUCCESS) अणु
				nvme_tcp_end_request(rq, NVME_SC_SUCCESS);
				queue->nr_cqe++;
			पूर्ण
			nvme_tcp_init_recv_ctx(queue);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_recv_ddgst(काष्ठा nvme_tcp_queue *queue,
		काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *offset, माप_प्रकार *len)
अणु
	काष्ठा nvme_tcp_data_pdu *pdu = (व्योम *)queue->pdu;
	अक्षर *ddgst = (अक्षर *)&queue->recv_ddgst;
	माप_प्रकार recv_len = min_t(माप_प्रकार, *len, queue->ddgst_reमुख्यing);
	off_t off = NVME_TCP_DIGEST_LENGTH - queue->ddgst_reमुख्यing;
	पूर्णांक ret;

	ret = skb_copy_bits(skb, *offset, &ddgst[off], recv_len);
	अगर (unlikely(ret))
		वापस ret;

	queue->ddgst_reमुख्यing -= recv_len;
	*offset += recv_len;
	*len -= recv_len;
	अगर (queue->ddgst_reमुख्यing)
		वापस 0;

	अगर (queue->recv_ddgst != queue->exp_ddgst) अणु
		dev_err(queue->ctrl->ctrl.device,
			"data digest error: recv %#x expected %#x\n",
			le32_to_cpu(queue->recv_ddgst),
			le32_to_cpu(queue->exp_ddgst));
		वापस -EIO;
	पूर्ण

	अगर (pdu->hdr.flags & NVME_TCP_F_DATA_SUCCESS) अणु
		काष्ठा request *rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue),
						pdu->command_id);

		nvme_tcp_end_request(rq, NVME_SC_SUCCESS);
		queue->nr_cqe++;
	पूर्ण

	nvme_tcp_init_recv_ctx(queue);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_tcp_recv_skb(पढ़ो_descriptor_t *desc, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	काष्ठा nvme_tcp_queue *queue = desc->arg.data;
	माप_प्रकार consumed = len;
	पूर्णांक result;

	जबतक (len) अणु
		चयन (nvme_tcp_recv_state(queue)) अणु
		हाल NVME_TCP_RECV_PDU:
			result = nvme_tcp_recv_pdu(queue, skb, &offset, &len);
			अवरोध;
		हाल NVME_TCP_RECV_DATA:
			result = nvme_tcp_recv_data(queue, skb, &offset, &len);
			अवरोध;
		हाल NVME_TCP_RECV_DDGST:
			result = nvme_tcp_recv_ddgst(queue, skb, &offset, &len);
			अवरोध;
		शेष:
			result = -EFAULT;
		पूर्ण
		अगर (result) अणु
			dev_err(queue->ctrl->ctrl.device,
				"receive failed:  %d\n", result);
			queue->rd_enabled = false;
			nvme_tcp_error_recovery(&queue->ctrl->ctrl);
			वापस result;
		पूर्ण
	पूर्ण

	वापस consumed;
पूर्ण

अटल व्योम nvme_tcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा nvme_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (likely(queue && queue->rd_enabled) &&
	    !test_bit(NVME_TCP_Q_POLLING, &queue->flags))
		queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम nvme_tcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा nvme_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (likely(queue && sk_stream_is_ग_लिखोable(sk))) अणु
		clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम nvme_tcp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा nvme_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (!queue)
		जाओ करोne;

	चयन (sk->sk_state) अणु
	हाल TCP_CLOSE:
	हाल TCP_CLOSE_WAIT:
	हाल TCP_LAST_ACK:
	हाल TCP_FIN_WAIT1:
	हाल TCP_FIN_WAIT2:
		nvme_tcp_error_recovery(&queue->ctrl->ctrl);
		अवरोध;
	शेष:
		dev_info(queue->ctrl->ctrl.device,
			"queue %d socket state %d\n",
			nvme_tcp_queue_id(queue), sk->sk_state);
	पूर्ण

	queue->state_change(sk);
करोne:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल अंतरभूत bool nvme_tcp_queue_more(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस !list_empty(&queue->send_list) ||
		!llist_empty(&queue->req_list) || queue->more_requests;
पूर्ण

अटल अंतरभूत व्योम nvme_tcp_करोne_send_req(काष्ठा nvme_tcp_queue *queue)
अणु
	queue->request = शून्य;
पूर्ण

अटल व्योम nvme_tcp_fail_request(काष्ठा nvme_tcp_request *req)
अणु
	nvme_tcp_end_request(blk_mq_rq_from_pdu(req), NVME_SC_HOST_PATH_ERROR);
पूर्ण

अटल पूर्णांक nvme_tcp_try_send_data(काष्ठा nvme_tcp_request *req)
अणु
	काष्ठा nvme_tcp_queue *queue = req->queue;

	जबतक (true) अणु
		काष्ठा page *page = nvme_tcp_req_cur_page(req);
		माप_प्रकार offset = nvme_tcp_req_cur_offset(req);
		माप_प्रकार len = nvme_tcp_req_cur_length(req);
		bool last = nvme_tcp_pdu_last_send(req, len);
		पूर्णांक ret, flags = MSG_DONTWAIT;

		अगर (last && !queue->data_digest && !nvme_tcp_queue_more(queue))
			flags |= MSG_EOR;
		अन्यथा
			flags |= MSG_MORE | MSG_SENDPAGE_NOTLAST;

		अगर (sendpage_ok(page)) अणु
			ret = kernel_sendpage(queue->sock, page, offset, len,
					flags);
		पूर्ण अन्यथा अणु
			ret = sock_no_sendpage(queue->sock, page, offset, len,
					flags);
		पूर्ण
		अगर (ret <= 0)
			वापस ret;

		अगर (queue->data_digest)
			nvme_tcp_ddgst_update(queue->snd_hash, page,
					offset, ret);

		/* fully successful last ग_लिखो*/
		अगर (last && ret == len) अणु
			अगर (queue->data_digest) अणु
				nvme_tcp_ddgst_final(queue->snd_hash,
					&req->ddgst);
				req->state = NVME_TCP_SEND_DDGST;
				req->offset = 0;
			पूर्ण अन्यथा अणु
				nvme_tcp_करोne_send_req(queue);
			पूर्ण
			वापस 1;
		पूर्ण
		nvme_tcp_advance_req(req, ret);
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक nvme_tcp_try_send_cmd_pdu(काष्ठा nvme_tcp_request *req)
अणु
	काष्ठा nvme_tcp_queue *queue = req->queue;
	काष्ठा nvme_tcp_cmd_pdu *pdu = req->pdu;
	bool अंतरभूत_data = nvme_tcp_has_अंतरभूत_data(req);
	u8 hdgst = nvme_tcp_hdgst_len(queue);
	पूर्णांक len = माप(*pdu) + hdgst - req->offset;
	पूर्णांक flags = MSG_DONTWAIT;
	पूर्णांक ret;

	अगर (अंतरभूत_data || nvme_tcp_queue_more(queue))
		flags |= MSG_MORE | MSG_SENDPAGE_NOTLAST;
	अन्यथा
		flags |= MSG_EOR;

	अगर (queue->hdr_digest && !req->offset)
		nvme_tcp_hdgst(queue->snd_hash, pdu, माप(*pdu));

	ret = kernel_sendpage(queue->sock, virt_to_page(pdu),
			offset_in_page(pdu) + req->offset, len,  flags);
	अगर (unlikely(ret <= 0))
		वापस ret;

	len -= ret;
	अगर (!len) अणु
		अगर (अंतरभूत_data) अणु
			req->state = NVME_TCP_SEND_DATA;
			अगर (queue->data_digest)
				crypto_ahash_init(queue->snd_hash);
		पूर्ण अन्यथा अणु
			nvme_tcp_करोne_send_req(queue);
		पूर्ण
		वापस 1;
	पूर्ण
	req->offset += ret;

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक nvme_tcp_try_send_data_pdu(काष्ठा nvme_tcp_request *req)
अणु
	काष्ठा nvme_tcp_queue *queue = req->queue;
	काष्ठा nvme_tcp_data_pdu *pdu = req->pdu;
	u8 hdgst = nvme_tcp_hdgst_len(queue);
	पूर्णांक len = माप(*pdu) - req->offset + hdgst;
	पूर्णांक ret;

	अगर (queue->hdr_digest && !req->offset)
		nvme_tcp_hdgst(queue->snd_hash, pdu, माप(*pdu));

	ret = kernel_sendpage(queue->sock, virt_to_page(pdu),
			offset_in_page(pdu) + req->offset, len,
			MSG_DONTWAIT | MSG_MORE | MSG_SENDPAGE_NOTLAST);
	अगर (unlikely(ret <= 0))
		वापस ret;

	len -= ret;
	अगर (!len) अणु
		req->state = NVME_TCP_SEND_DATA;
		अगर (queue->data_digest)
			crypto_ahash_init(queue->snd_hash);
		वापस 1;
	पूर्ण
	req->offset += ret;

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक nvme_tcp_try_send_ddgst(काष्ठा nvme_tcp_request *req)
अणु
	काष्ठा nvme_tcp_queue *queue = req->queue;
	पूर्णांक ret;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT पूर्ण;
	काष्ठा kvec iov = अणु
		.iov_base = &req->ddgst + req->offset,
		.iov_len = NVME_TCP_DIGEST_LENGTH - req->offset
	पूर्ण;

	अगर (nvme_tcp_queue_more(queue))
		msg.msg_flags |= MSG_MORE;
	अन्यथा
		msg.msg_flags |= MSG_EOR;

	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	अगर (unlikely(ret <= 0))
		वापस ret;

	अगर (req->offset + ret == NVME_TCP_DIGEST_LENGTH) अणु
		nvme_tcp_करोne_send_req(queue);
		वापस 1;
	पूर्ण

	req->offset += ret;
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक nvme_tcp_try_send(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_request *req;
	पूर्णांक ret = 1;

	अगर (!queue->request) अणु
		queue->request = nvme_tcp_fetch_request(queue);
		अगर (!queue->request)
			वापस 0;
	पूर्ण
	req = queue->request;

	अगर (req->state == NVME_TCP_SEND_CMD_PDU) अणु
		ret = nvme_tcp_try_send_cmd_pdu(req);
		अगर (ret <= 0)
			जाओ करोne;
		अगर (!nvme_tcp_has_अंतरभूत_data(req))
			वापस ret;
	पूर्ण

	अगर (req->state == NVME_TCP_SEND_H2C_PDU) अणु
		ret = nvme_tcp_try_send_data_pdu(req);
		अगर (ret <= 0)
			जाओ करोne;
	पूर्ण

	अगर (req->state == NVME_TCP_SEND_DATA) अणु
		ret = nvme_tcp_try_send_data(req);
		अगर (ret <= 0)
			जाओ करोne;
	पूर्ण

	अगर (req->state == NVME_TCP_SEND_DDGST)
		ret = nvme_tcp_try_send_ddgst(req);
करोne:
	अगर (ret == -EAGAIN) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(queue->ctrl->ctrl.device,
			"failed to send request %d\n", ret);
		अगर (ret != -EPIPE && ret != -ECONNRESET)
			nvme_tcp_fail_request(queue->request);
		nvme_tcp_करोne_send_req(queue);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_tcp_try_recv(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा socket *sock = queue->sock;
	काष्ठा sock *sk = sock->sk;
	पढ़ो_descriptor_t rd_desc;
	पूर्णांक consumed;

	rd_desc.arg.data = queue;
	rd_desc.count = 1;
	lock_sock(sk);
	queue->nr_cqe = 0;
	consumed = sock->ops->पढ़ो_sock(sk, &rd_desc, nvme_tcp_recv_skb);
	release_sock(sk);
	वापस consumed;
पूर्ण

अटल व्योम nvme_tcp_io_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvme_tcp_queue *queue =
		container_of(w, काष्ठा nvme_tcp_queue, io_work);
	अचिन्हित दीर्घ deadline = jअगरfies + msecs_to_jअगरfies(1);

	करो अणु
		bool pending = false;
		पूर्णांक result;

		अगर (mutex_trylock(&queue->send_mutex)) अणु
			result = nvme_tcp_try_send(queue);
			mutex_unlock(&queue->send_mutex);
			अगर (result > 0)
				pending = true;
			अन्यथा अगर (unlikely(result < 0))
				अवरोध;
		पूर्ण अन्यथा
			pending = !llist_empty(&queue->req_list);

		result = nvme_tcp_try_recv(queue);
		अगर (result > 0)
			pending = true;
		अन्यथा अगर (unlikely(result < 0))
			वापस;

		अगर (!pending)
			वापस;

	पूर्ण जबतक (!समय_after(jअगरfies, deadline)); /* quota is exhausted */

	queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
पूर्ण

अटल व्योम nvme_tcp_मुक्त_crypto(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(queue->rcv_hash);

	ahash_request_मुक्त(queue->rcv_hash);
	ahash_request_मुक्त(queue->snd_hash);
	crypto_मुक्त_ahash(tfm);
पूर्ण

अटल पूर्णांक nvme_tcp_alloc_crypto(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा crypto_ahash *tfm;

	tfm = crypto_alloc_ahash("crc32c", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	queue->snd_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!queue->snd_hash)
		जाओ मुक्त_tfm;
	ahash_request_set_callback(queue->snd_hash, 0, शून्य, शून्य);

	queue->rcv_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!queue->rcv_hash)
		जाओ मुक्त_snd_hash;
	ahash_request_set_callback(queue->rcv_hash, 0, शून्य, शून्य);

	वापस 0;
मुक्त_snd_hash:
	ahash_request_मुक्त(queue->snd_hash);
मुक्त_tfm:
	crypto_मुक्त_ahash(tfm);
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvme_tcp_मुक्त_async_req(काष्ठा nvme_tcp_ctrl *ctrl)
अणु
	काष्ठा nvme_tcp_request *async = &ctrl->async_req;

	page_frag_मुक्त(async->pdu);
पूर्ण

अटल पूर्णांक nvme_tcp_alloc_async_req(काष्ठा nvme_tcp_ctrl *ctrl)
अणु
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[0];
	काष्ठा nvme_tcp_request *async = &ctrl->async_req;
	u8 hdgst = nvme_tcp_hdgst_len(queue);

	async->pdu = page_frag_alloc(&queue->pf_cache,
		माप(काष्ठा nvme_tcp_cmd_pdu) + hdgst,
		GFP_KERNEL | __GFP_ZERO);
	अगर (!async->pdu)
		वापस -ENOMEM;

	async->queue = &ctrl->queues[0];
	वापस 0;
पूर्ण

अटल व्योम nvme_tcp_मुक्त_queue(काष्ठा nvme_ctrl *nctrl, पूर्णांक qid)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[qid];

	अगर (!test_and_clear_bit(NVME_TCP_Q_ALLOCATED, &queue->flags))
		वापस;

	अगर (queue->hdr_digest || queue->data_digest)
		nvme_tcp_मुक्त_crypto(queue);

	sock_release(queue->sock);
	kमुक्त(queue->pdu);
	mutex_destroy(&queue->queue_lock);
पूर्ण

अटल पूर्णांक nvme_tcp_init_connection(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_icreq_pdu *icreq;
	काष्ठा nvme_tcp_icresp_pdu *icresp;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा kvec iov;
	bool ctrl_hdgst, ctrl_ddgst;
	पूर्णांक ret;

	icreq = kzalloc(माप(*icreq), GFP_KERNEL);
	अगर (!icreq)
		वापस -ENOMEM;

	icresp = kzalloc(माप(*icresp), GFP_KERNEL);
	अगर (!icresp) अणु
		ret = -ENOMEM;
		जाओ मुक्त_icreq;
	पूर्ण

	icreq->hdr.type = nvme_tcp_icreq;
	icreq->hdr.hlen = माप(*icreq);
	icreq->hdr.pकरो = 0;
	icreq->hdr.plen = cpu_to_le32(icreq->hdr.hlen);
	icreq->pfv = cpu_to_le16(NVME_TCP_PFV_1_0);
	icreq->maxr2t = 0; /* single inflight r2t supported */
	icreq->hpda = 0; /* no alignment स्थिरraपूर्णांक */
	अगर (queue->hdr_digest)
		icreq->digest |= NVME_TCP_HDR_DIGEST_ENABLE;
	अगर (queue->data_digest)
		icreq->digest |= NVME_TCP_DATA_DIGEST_ENABLE;

	iov.iov_base = icreq;
	iov.iov_len = माप(*icreq);
	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	अगर (ret < 0)
		जाओ मुक्त_icresp;

	स_रखो(&msg, 0, माप(msg));
	iov.iov_base = icresp;
	iov.iov_len = माप(*icresp);
	ret = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	अगर (ret < 0)
		जाओ मुक्त_icresp;

	ret = -EINVAL;
	अगर (icresp->hdr.type != nvme_tcp_icresp) अणु
		pr_err("queue %d: bad type returned %d\n",
			nvme_tcp_queue_id(queue), icresp->hdr.type);
		जाओ मुक्त_icresp;
	पूर्ण

	अगर (le32_to_cpu(icresp->hdr.plen) != माप(*icresp)) अणु
		pr_err("queue %d: bad pdu length returned %d\n",
			nvme_tcp_queue_id(queue), icresp->hdr.plen);
		जाओ मुक्त_icresp;
	पूर्ण

	अगर (icresp->pfv != NVME_TCP_PFV_1_0) अणु
		pr_err("queue %d: bad pfv returned %d\n",
			nvme_tcp_queue_id(queue), icresp->pfv);
		जाओ मुक्त_icresp;
	पूर्ण

	ctrl_ddgst = !!(icresp->digest & NVME_TCP_DATA_DIGEST_ENABLE);
	अगर ((queue->data_digest && !ctrl_ddgst) ||
	    (!queue->data_digest && ctrl_ddgst)) अणु
		pr_err("queue %d: data digest mismatch host: %s ctrl: %s\n",
			nvme_tcp_queue_id(queue),
			queue->data_digest ? "enabled" : "disabled",
			ctrl_ddgst ? "enabled" : "disabled");
		जाओ मुक्त_icresp;
	पूर्ण

	ctrl_hdgst = !!(icresp->digest & NVME_TCP_HDR_DIGEST_ENABLE);
	अगर ((queue->hdr_digest && !ctrl_hdgst) ||
	    (!queue->hdr_digest && ctrl_hdgst)) अणु
		pr_err("queue %d: header digest mismatch host: %s ctrl: %s\n",
			nvme_tcp_queue_id(queue),
			queue->hdr_digest ? "enabled" : "disabled",
			ctrl_hdgst ? "enabled" : "disabled");
		जाओ मुक्त_icresp;
	पूर्ण

	अगर (icresp->cpda != 0) अणु
		pr_err("queue %d: unsupported cpda returned %d\n",
			nvme_tcp_queue_id(queue), icresp->cpda);
		जाओ मुक्त_icresp;
	पूर्ण

	ret = 0;
मुक्त_icresp:
	kमुक्त(icresp);
मुक्त_icreq:
	kमुक्त(icreq);
	वापस ret;
पूर्ण

अटल bool nvme_tcp_admin_queue(काष्ठा nvme_tcp_queue *queue)
अणु
	वापस nvme_tcp_queue_id(queue) == 0;
पूर्ण

अटल bool nvme_tcp_शेष_queue(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = queue->ctrl;
	पूर्णांक qid = nvme_tcp_queue_id(queue);

	वापस !nvme_tcp_admin_queue(queue) &&
		qid < 1 + ctrl->io_queues[HCTX_TYPE_DEFAULT];
पूर्ण

अटल bool nvme_tcp_पढ़ो_queue(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = queue->ctrl;
	पूर्णांक qid = nvme_tcp_queue_id(queue);

	वापस !nvme_tcp_admin_queue(queue) &&
		!nvme_tcp_शेष_queue(queue) &&
		qid < 1 + ctrl->io_queues[HCTX_TYPE_DEFAULT] +
			  ctrl->io_queues[HCTX_TYPE_READ];
पूर्ण

अटल bool nvme_tcp_poll_queue(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = queue->ctrl;
	पूर्णांक qid = nvme_tcp_queue_id(queue);

	वापस !nvme_tcp_admin_queue(queue) &&
		!nvme_tcp_शेष_queue(queue) &&
		!nvme_tcp_पढ़ो_queue(queue) &&
		qid < 1 + ctrl->io_queues[HCTX_TYPE_DEFAULT] +
			  ctrl->io_queues[HCTX_TYPE_READ] +
			  ctrl->io_queues[HCTX_TYPE_POLL];
पूर्ण

अटल व्योम nvme_tcp_set_queue_io_cpu(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = queue->ctrl;
	पूर्णांक qid = nvme_tcp_queue_id(queue);
	पूर्णांक n = 0;

	अगर (nvme_tcp_शेष_queue(queue))
		n = qid - 1;
	अन्यथा अगर (nvme_tcp_पढ़ो_queue(queue))
		n = qid - ctrl->io_queues[HCTX_TYPE_DEFAULT] - 1;
	अन्यथा अगर (nvme_tcp_poll_queue(queue))
		n = qid - ctrl->io_queues[HCTX_TYPE_DEFAULT] -
				ctrl->io_queues[HCTX_TYPE_READ] - 1;
	queue->io_cpu = cpumask_next_wrap(n - 1, cpu_online_mask, -1, false);
पूर्ण

अटल पूर्णांक nvme_tcp_alloc_queue(काष्ठा nvme_ctrl *nctrl,
		पूर्णांक qid, माप_प्रकार queue_size)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[qid];
	पूर्णांक ret, rcv_pdu_size;

	mutex_init(&queue->queue_lock);
	queue->ctrl = ctrl;
	init_llist_head(&queue->req_list);
	INIT_LIST_HEAD(&queue->send_list);
	mutex_init(&queue->send_mutex);
	INIT_WORK(&queue->io_work, nvme_tcp_io_work);
	queue->queue_size = queue_size;

	अगर (qid > 0)
		queue->cmnd_capsule_len = nctrl->ioccsz * 16;
	अन्यथा
		queue->cmnd_capsule_len = माप(काष्ठा nvme_command) +
						NVME_TCP_ADMIN_CCSZ;

	ret = sock_create(ctrl->addr.ss_family, SOCK_STREAM,
			IPPROTO_TCP, &queue->sock);
	अगर (ret) अणु
		dev_err(nctrl->device,
			"failed to create socket: %d\n", ret);
		जाओ err_destroy_mutex;
	पूर्ण

	/* Single syn retry */
	tcp_sock_set_syncnt(queue->sock->sk, 1);

	/* Set TCP no delay */
	tcp_sock_set_nodelay(queue->sock->sk);

	/*
	 * Cleanup whatever is sitting in the TCP transmit queue on socket
	 * बंद. This is करोne to prevent stale data from being sent should
	 * the network connection be restored beक्रमe TCP बार out.
	 */
	sock_no_linger(queue->sock->sk);

	अगर (so_priority > 0)
		sock_set_priority(queue->sock->sk, so_priority);

	/* Set socket type of service */
	अगर (nctrl->opts->tos >= 0)
		ip_sock_set_tos(queue->sock->sk, nctrl->opts->tos);

	/* Set 10 seconds समयout क्रम icresp recvmsg */
	queue->sock->sk->sk_rcvसमयo = 10 * HZ;

	queue->sock->sk->sk_allocation = GFP_ATOMIC;
	nvme_tcp_set_queue_io_cpu(queue);
	queue->request = शून्य;
	queue->data_reमुख्यing = 0;
	queue->ddgst_reमुख्यing = 0;
	queue->pdu_reमुख्यing = 0;
	queue->pdu_offset = 0;
	sk_set_meदो_स्मृति(queue->sock->sk);

	अगर (nctrl->opts->mask & NVMF_OPT_HOST_TRADDR) अणु
		ret = kernel_bind(queue->sock, (काष्ठा sockaddr *)&ctrl->src_addr,
			माप(ctrl->src_addr));
		अगर (ret) अणु
			dev_err(nctrl->device,
				"failed to bind queue %d socket %d\n",
				qid, ret);
			जाओ err_sock;
		पूर्ण
	पूर्ण

	queue->hdr_digest = nctrl->opts->hdr_digest;
	queue->data_digest = nctrl->opts->data_digest;
	अगर (queue->hdr_digest || queue->data_digest) अणु
		ret = nvme_tcp_alloc_crypto(queue);
		अगर (ret) अणु
			dev_err(nctrl->device,
				"failed to allocate queue %d crypto\n", qid);
			जाओ err_sock;
		पूर्ण
	पूर्ण

	rcv_pdu_size = माप(काष्ठा nvme_tcp_rsp_pdu) +
			nvme_tcp_hdgst_len(queue);
	queue->pdu = kदो_स्मृति(rcv_pdu_size, GFP_KERNEL);
	अगर (!queue->pdu) अणु
		ret = -ENOMEM;
		जाओ err_crypto;
	पूर्ण

	dev_dbg(nctrl->device, "connecting queue %d\n",
			nvme_tcp_queue_id(queue));

	ret = kernel_connect(queue->sock, (काष्ठा sockaddr *)&ctrl->addr,
		माप(ctrl->addr), 0);
	अगर (ret) अणु
		dev_err(nctrl->device,
			"failed to connect socket: %d\n", ret);
		जाओ err_rcv_pdu;
	पूर्ण

	ret = nvme_tcp_init_connection(queue);
	अगर (ret)
		जाओ err_init_connect;

	queue->rd_enabled = true;
	set_bit(NVME_TCP_Q_ALLOCATED, &queue->flags);
	nvme_tcp_init_recv_ctx(queue);

	ग_लिखो_lock_bh(&queue->sock->sk->sk_callback_lock);
	queue->sock->sk->sk_user_data = queue;
	queue->state_change = queue->sock->sk->sk_state_change;
	queue->data_पढ़ोy = queue->sock->sk->sk_data_पढ़ोy;
	queue->ग_लिखो_space = queue->sock->sk->sk_ग_लिखो_space;
	queue->sock->sk->sk_data_पढ़ोy = nvme_tcp_data_पढ़ोy;
	queue->sock->sk->sk_state_change = nvme_tcp_state_change;
	queue->sock->sk->sk_ग_लिखो_space = nvme_tcp_ग_लिखो_space;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	queue->sock->sk->sk_ll_usec = 1;
#पूर्ण_अगर
	ग_लिखो_unlock_bh(&queue->sock->sk->sk_callback_lock);

	वापस 0;

err_init_connect:
	kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
err_rcv_pdu:
	kमुक्त(queue->pdu);
err_crypto:
	अगर (queue->hdr_digest || queue->data_digest)
		nvme_tcp_मुक्त_crypto(queue);
err_sock:
	sock_release(queue->sock);
	queue->sock = शून्य;
err_destroy_mutex:
	mutex_destroy(&queue->queue_lock);
	वापस ret;
पूर्ण

अटल व्योम nvme_tcp_restore_sock_calls(काष्ठा nvme_tcp_queue *queue)
अणु
	काष्ठा socket *sock = queue->sock;

	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_user_data  = शून्य;
	sock->sk->sk_data_पढ़ोy = queue->data_पढ़ोy;
	sock->sk->sk_state_change = queue->state_change;
	sock->sk->sk_ग_लिखो_space  = queue->ग_लिखो_space;
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);
पूर्ण

अटल व्योम __nvme_tcp_stop_queue(काष्ठा nvme_tcp_queue *queue)
अणु
	kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
	nvme_tcp_restore_sock_calls(queue);
	cancel_work_sync(&queue->io_work);
पूर्ण

अटल व्योम nvme_tcp_stop_queue(काष्ठा nvme_ctrl *nctrl, पूर्णांक qid)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[qid];

	mutex_lock(&queue->queue_lock);
	अगर (test_and_clear_bit(NVME_TCP_Q_LIVE, &queue->flags))
		__nvme_tcp_stop_queue(queue);
	mutex_unlock(&queue->queue_lock);
पूर्ण

अटल पूर्णांक nvme_tcp_start_queue(काष्ठा nvme_ctrl *nctrl, पूर्णांक idx)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	पूर्णांक ret;

	अगर (idx)
		ret = nvmf_connect_io_queue(nctrl, idx, false);
	अन्यथा
		ret = nvmf_connect_admin_queue(nctrl);

	अगर (!ret) अणु
		set_bit(NVME_TCP_Q_LIVE, &ctrl->queues[idx].flags);
	पूर्ण अन्यथा अणु
		अगर (test_bit(NVME_TCP_Q_ALLOCATED, &ctrl->queues[idx].flags))
			__nvme_tcp_stop_queue(&ctrl->queues[idx]);
		dev_err(nctrl->device,
			"failed to connect queue: %d ret=%d\n", idx, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा blk_mq_tag_set *nvme_tcp_alloc_tagset(काष्ठा nvme_ctrl *nctrl,
		bool admin)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	काष्ठा blk_mq_tag_set *set;
	पूर्णांक ret;

	अगर (admin) अणु
		set = &ctrl->admin_tag_set;
		स_रखो(set, 0, माप(*set));
		set->ops = &nvme_tcp_admin_mq_ops;
		set->queue_depth = NVME_AQ_MQ_TAG_DEPTH;
		set->reserved_tags = NVMF_RESERVED_TAGS;
		set->numa_node = nctrl->numa_node;
		set->flags = BLK_MQ_F_BLOCKING;
		set->cmd_size = माप(काष्ठा nvme_tcp_request);
		set->driver_data = ctrl;
		set->nr_hw_queues = 1;
		set->समयout = NVME_ADMIN_TIMEOUT;
	पूर्ण अन्यथा अणु
		set = &ctrl->tag_set;
		स_रखो(set, 0, माप(*set));
		set->ops = &nvme_tcp_mq_ops;
		set->queue_depth = nctrl->sqsize + 1;
		set->reserved_tags = NVMF_RESERVED_TAGS;
		set->numa_node = nctrl->numa_node;
		set->flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;
		set->cmd_size = माप(काष्ठा nvme_tcp_request);
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

अटल व्योम nvme_tcp_मुक्त_admin_queue(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (to_tcp_ctrl(ctrl)->async_req.pdu) अणु
		cancel_work_sync(&ctrl->async_event_work);
		nvme_tcp_मुक्त_async_req(to_tcp_ctrl(ctrl));
		to_tcp_ctrl(ctrl)->async_req.pdu = शून्य;
	पूर्ण

	nvme_tcp_मुक्त_queue(ctrl, 0);
पूर्ण

अटल व्योम nvme_tcp_मुक्त_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->queue_count; i++)
		nvme_tcp_मुक्त_queue(ctrl, i);
पूर्ण

अटल व्योम nvme_tcp_stop_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->queue_count; i++)
		nvme_tcp_stop_queue(ctrl, i);
पूर्ण

अटल पूर्णांक nvme_tcp_start_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 1; i < ctrl->queue_count; i++) अणु
		ret = nvme_tcp_start_queue(ctrl, i);
		अगर (ret)
			जाओ out_stop_queues;
	पूर्ण

	वापस 0;

out_stop_queues:
	क्रम (i--; i >= 1; i--)
		nvme_tcp_stop_queue(ctrl, i);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_tcp_alloc_admin_queue(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = nvme_tcp_alloc_queue(ctrl, 0, NVME_AQ_DEPTH);
	अगर (ret)
		वापस ret;

	ret = nvme_tcp_alloc_async_req(to_tcp_ctrl(ctrl));
	अगर (ret)
		जाओ out_मुक्त_queue;

	वापस 0;

out_मुक्त_queue:
	nvme_tcp_मुक्त_queue(ctrl, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक __nvme_tcp_alloc_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक i, ret;

	क्रम (i = 1; i < ctrl->queue_count; i++) अणु
		ret = nvme_tcp_alloc_queue(ctrl, i,
				ctrl->sqsize + 1);
		अगर (ret)
			जाओ out_मुक्त_queues;
	पूर्ण

	वापस 0;

out_मुक्त_queues:
	क्रम (i--; i >= 1; i--)
		nvme_tcp_मुक्त_queue(ctrl, i);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक nvme_tcp_nr_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	अचिन्हित पूर्णांक nr_io_queues;

	nr_io_queues = min(ctrl->opts->nr_io_queues, num_online_cpus());
	nr_io_queues += min(ctrl->opts->nr_ग_लिखो_queues, num_online_cpus());
	nr_io_queues += min(ctrl->opts->nr_poll_queues, num_online_cpus());

	वापस nr_io_queues;
पूर्ण

अटल व्योम nvme_tcp_set_io_queues(काष्ठा nvme_ctrl *nctrl,
		अचिन्हित पूर्णांक nr_io_queues)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	काष्ठा nvmf_ctrl_options *opts = nctrl->opts;

	अगर (opts->nr_ग_लिखो_queues && opts->nr_io_queues < nr_io_queues) अणु
		/*
		 * separate पढ़ो/ग_लिखो queues
		 * hand out dedicated शेष queues only after we have
		 * sufficient पढ़ो queues.
		 */
		ctrl->io_queues[HCTX_TYPE_READ] = opts->nr_io_queues;
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_READ];
		ctrl->io_queues[HCTX_TYPE_DEFAULT] =
			min(opts->nr_ग_लिखो_queues, nr_io_queues);
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_DEFAULT];
	पूर्ण अन्यथा अणु
		/*
		 * shared पढ़ो/ग_लिखो queues
		 * either no ग_लिखो queues were requested, or we करोn't have
		 * sufficient queue count to have dedicated शेष queues.
		 */
		ctrl->io_queues[HCTX_TYPE_DEFAULT] =
			min(opts->nr_io_queues, nr_io_queues);
		nr_io_queues -= ctrl->io_queues[HCTX_TYPE_DEFAULT];
	पूर्ण

	अगर (opts->nr_poll_queues && nr_io_queues) अणु
		/* map dedicated poll queues only अगर we have queues left */
		ctrl->io_queues[HCTX_TYPE_POLL] =
			min(opts->nr_poll_queues, nr_io_queues);
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_tcp_alloc_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	अचिन्हित पूर्णांक nr_io_queues;
	पूर्णांक ret;

	nr_io_queues = nvme_tcp_nr_io_queues(ctrl);
	ret = nvme_set_queue_count(ctrl, &nr_io_queues);
	अगर (ret)
		वापस ret;

	ctrl->queue_count = nr_io_queues + 1;
	अगर (ctrl->queue_count < 2) अणु
		dev_err(ctrl->device,
			"unable to set any I/O queues\n");
		वापस -ENOMEM;
	पूर्ण

	dev_info(ctrl->device,
		"creating %d I/O queues.\n", nr_io_queues);

	nvme_tcp_set_io_queues(ctrl, nr_io_queues);

	वापस __nvme_tcp_alloc_io_queues(ctrl);
पूर्ण

अटल व्योम nvme_tcp_destroy_io_queues(काष्ठा nvme_ctrl *ctrl, bool हटाओ)
अणु
	nvme_tcp_stop_io_queues(ctrl);
	अगर (हटाओ) अणु
		blk_cleanup_queue(ctrl->connect_q);
		blk_mq_मुक्त_tag_set(ctrl->tagset);
	पूर्ण
	nvme_tcp_मुक्त_io_queues(ctrl);
पूर्ण

अटल पूर्णांक nvme_tcp_configure_io_queues(काष्ठा nvme_ctrl *ctrl, bool new)
अणु
	पूर्णांक ret;

	ret = nvme_tcp_alloc_io_queues(ctrl);
	अगर (ret)
		वापस ret;

	अगर (new) अणु
		ctrl->tagset = nvme_tcp_alloc_tagset(ctrl, false);
		अगर (IS_ERR(ctrl->tagset)) अणु
			ret = PTR_ERR(ctrl->tagset);
			जाओ out_मुक्त_io_queues;
		पूर्ण

		ctrl->connect_q = blk_mq_init_queue(ctrl->tagset);
		अगर (IS_ERR(ctrl->connect_q)) अणु
			ret = PTR_ERR(ctrl->connect_q);
			जाओ out_मुक्त_tag_set;
		पूर्ण
	पूर्ण

	ret = nvme_tcp_start_io_queues(ctrl);
	अगर (ret)
		जाओ out_cleanup_connect_q;

	अगर (!new) अणु
		nvme_start_queues(ctrl);
		अगर (!nvme_रुको_मुक्तze_समयout(ctrl, NVME_IO_TIMEOUT)) अणु
			/*
			 * If we समयd out रुकोing क्रम मुक्तze we are likely to
			 * be stuck.  Fail the controller initialization just
			 * to be safe.
			 */
			ret = -ENODEV;
			जाओ out_रुको_मुक्तze_समयd_out;
		पूर्ण
		blk_mq_update_nr_hw_queues(ctrl->tagset,
			ctrl->queue_count - 1);
		nvme_unमुक्तze(ctrl);
	पूर्ण

	वापस 0;

out_रुको_मुक्तze_समयd_out:
	nvme_stop_queues(ctrl);
	nvme_sync_io_queues(ctrl);
	nvme_tcp_stop_io_queues(ctrl);
out_cleanup_connect_q:
	nvme_cancel_tagset(ctrl);
	अगर (new)
		blk_cleanup_queue(ctrl->connect_q);
out_मुक्त_tag_set:
	अगर (new)
		blk_mq_मुक्त_tag_set(ctrl->tagset);
out_मुक्त_io_queues:
	nvme_tcp_मुक्त_io_queues(ctrl);
	वापस ret;
पूर्ण

अटल व्योम nvme_tcp_destroy_admin_queue(काष्ठा nvme_ctrl *ctrl, bool हटाओ)
अणु
	nvme_tcp_stop_queue(ctrl, 0);
	अगर (हटाओ) अणु
		blk_cleanup_queue(ctrl->admin_q);
		blk_cleanup_queue(ctrl->fabrics_q);
		blk_mq_मुक्त_tag_set(ctrl->admin_tagset);
	पूर्ण
	nvme_tcp_मुक्त_admin_queue(ctrl);
पूर्ण

अटल पूर्णांक nvme_tcp_configure_admin_queue(काष्ठा nvme_ctrl *ctrl, bool new)
अणु
	पूर्णांक error;

	error = nvme_tcp_alloc_admin_queue(ctrl);
	अगर (error)
		वापस error;

	अगर (new) अणु
		ctrl->admin_tagset = nvme_tcp_alloc_tagset(ctrl, true);
		अगर (IS_ERR(ctrl->admin_tagset)) अणु
			error = PTR_ERR(ctrl->admin_tagset);
			जाओ out_मुक्त_queue;
		पूर्ण

		ctrl->fabrics_q = blk_mq_init_queue(ctrl->admin_tagset);
		अगर (IS_ERR(ctrl->fabrics_q)) अणु
			error = PTR_ERR(ctrl->fabrics_q);
			जाओ out_मुक्त_tagset;
		पूर्ण

		ctrl->admin_q = blk_mq_init_queue(ctrl->admin_tagset);
		अगर (IS_ERR(ctrl->admin_q)) अणु
			error = PTR_ERR(ctrl->admin_q);
			जाओ out_cleanup_fabrics_q;
		पूर्ण
	पूर्ण

	error = nvme_tcp_start_queue(ctrl, 0);
	अगर (error)
		जाओ out_cleanup_queue;

	error = nvme_enable_ctrl(ctrl);
	अगर (error)
		जाओ out_stop_queue;

	blk_mq_unquiesce_queue(ctrl->admin_q);

	error = nvme_init_ctrl_finish(ctrl);
	अगर (error)
		जाओ out_quiesce_queue;

	वापस 0;

out_quiesce_queue:
	blk_mq_quiesce_queue(ctrl->admin_q);
	blk_sync_queue(ctrl->admin_q);
out_stop_queue:
	nvme_tcp_stop_queue(ctrl, 0);
	nvme_cancel_admin_tagset(ctrl);
out_cleanup_queue:
	अगर (new)
		blk_cleanup_queue(ctrl->admin_q);
out_cleanup_fabrics_q:
	अगर (new)
		blk_cleanup_queue(ctrl->fabrics_q);
out_मुक्त_tagset:
	अगर (new)
		blk_mq_मुक्त_tag_set(ctrl->admin_tagset);
out_मुक्त_queue:
	nvme_tcp_मुक्त_admin_queue(ctrl);
	वापस error;
पूर्ण

अटल व्योम nvme_tcp_tearकरोwn_admin_queue(काष्ठा nvme_ctrl *ctrl,
		bool हटाओ)
अणु
	blk_mq_quiesce_queue(ctrl->admin_q);
	blk_sync_queue(ctrl->admin_q);
	nvme_tcp_stop_queue(ctrl, 0);
	nvme_cancel_admin_tagset(ctrl);
	अगर (हटाओ)
		blk_mq_unquiesce_queue(ctrl->admin_q);
	nvme_tcp_destroy_admin_queue(ctrl, हटाओ);
पूर्ण

अटल व्योम nvme_tcp_tearकरोwn_io_queues(काष्ठा nvme_ctrl *ctrl,
		bool हटाओ)
अणु
	अगर (ctrl->queue_count <= 1)
		वापस;
	blk_mq_quiesce_queue(ctrl->admin_q);
	nvme_start_मुक्तze(ctrl);
	nvme_stop_queues(ctrl);
	nvme_sync_io_queues(ctrl);
	nvme_tcp_stop_io_queues(ctrl);
	nvme_cancel_tagset(ctrl);
	अगर (हटाओ)
		nvme_start_queues(ctrl);
	nvme_tcp_destroy_io_queues(ctrl, हटाओ);
पूर्ण

अटल व्योम nvme_tcp_reconnect_or_हटाओ(काष्ठा nvme_ctrl *ctrl)
अणु
	/* If we are resetting/deleting then करो nothing */
	अगर (ctrl->state != NVME_CTRL_CONNECTING) अणु
		WARN_ON_ONCE(ctrl->state == NVME_CTRL_NEW ||
			ctrl->state == NVME_CTRL_LIVE);
		वापस;
	पूर्ण

	अगर (nvmf_should_reconnect(ctrl)) अणु
		dev_info(ctrl->device, "Reconnecting in %d seconds...\n",
			ctrl->opts->reconnect_delay);
		queue_delayed_work(nvme_wq, &to_tcp_ctrl(ctrl)->connect_work,
				ctrl->opts->reconnect_delay * HZ);
	पूर्ण अन्यथा अणु
		dev_info(ctrl->device, "Removing controller...\n");
		nvme_delete_ctrl(ctrl);
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_tcp_setup_ctrl(काष्ठा nvme_ctrl *ctrl, bool new)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->opts;
	पूर्णांक ret;

	ret = nvme_tcp_configure_admin_queue(ctrl, new);
	अगर (ret)
		वापस ret;

	अगर (ctrl->icकरोff) अणु
		dev_err(ctrl->device, "icdoff is not supported!\n");
		जाओ destroy_admin;
	पूर्ण

	अगर (!(ctrl->sgls & ((1 << 0) | (1 << 1)))) अणु
		dev_err(ctrl->device, "Mandatory sgls are not supported!\n");
		जाओ destroy_admin;
	पूर्ण

	अगर (opts->queue_size > ctrl->sqsize + 1)
		dev_warn(ctrl->device,
			"queue_size %zu > ctrl sqsize %u, clamping down\n",
			opts->queue_size, ctrl->sqsize + 1);

	अगर (ctrl->sqsize + 1 > ctrl->maxcmd) अणु
		dev_warn(ctrl->device,
			"sqsize %u > ctrl maxcmd %u, clamping down\n",
			ctrl->sqsize + 1, ctrl->maxcmd);
		ctrl->sqsize = ctrl->maxcmd - 1;
	पूर्ण

	अगर (ctrl->queue_count > 1) अणु
		ret = nvme_tcp_configure_io_queues(ctrl, new);
		अगर (ret)
			जाओ destroy_admin;
	पूर्ण

	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_LIVE)) अणु
		/*
		 * state change failure is ok अगर we started ctrl delete,
		 * unless we're during creation of a new controller to
		 * aव्योम races with tearकरोwn flow.
		 */
		WARN_ON_ONCE(ctrl->state != NVME_CTRL_DELETING &&
			     ctrl->state != NVME_CTRL_DELETING_NOIO);
		WARN_ON_ONCE(new);
		ret = -EINVAL;
		जाओ destroy_io;
	पूर्ण

	nvme_start_ctrl(ctrl);
	वापस 0;

destroy_io:
	अगर (ctrl->queue_count > 1) अणु
		nvme_stop_queues(ctrl);
		nvme_sync_io_queues(ctrl);
		nvme_tcp_stop_io_queues(ctrl);
		nvme_cancel_tagset(ctrl);
		nvme_tcp_destroy_io_queues(ctrl, new);
	पूर्ण
destroy_admin:
	blk_mq_quiesce_queue(ctrl->admin_q);
	blk_sync_queue(ctrl->admin_q);
	nvme_tcp_stop_queue(ctrl, 0);
	nvme_cancel_admin_tagset(ctrl);
	nvme_tcp_destroy_admin_queue(ctrl, new);
	वापस ret;
पूर्ण

अटल व्योम nvme_tcp_reconnect_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_tcp_ctrl *tcp_ctrl = container_of(to_delayed_work(work),
			काष्ठा nvme_tcp_ctrl, connect_work);
	काष्ठा nvme_ctrl *ctrl = &tcp_ctrl->ctrl;

	++ctrl->nr_reconnects;

	अगर (nvme_tcp_setup_ctrl(ctrl, false))
		जाओ requeue;

	dev_info(ctrl->device, "Successfully reconnected (%d attempt)\n",
			ctrl->nr_reconnects);

	ctrl->nr_reconnects = 0;

	वापस;

requeue:
	dev_info(ctrl->device, "Failed reconnect attempt %d\n",
			ctrl->nr_reconnects);
	nvme_tcp_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल व्योम nvme_tcp_error_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_tcp_ctrl *tcp_ctrl = container_of(work,
				काष्ठा nvme_tcp_ctrl, err_work);
	काष्ठा nvme_ctrl *ctrl = &tcp_ctrl->ctrl;

	nvme_stop_keep_alive(ctrl);
	nvme_tcp_tearकरोwn_io_queues(ctrl, false);
	/* unquiesce to fail fast pending requests */
	nvme_start_queues(ctrl);
	nvme_tcp_tearकरोwn_admin_queue(ctrl, false);
	blk_mq_unquiesce_queue(ctrl->admin_q);

	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_CONNECTING)) अणु
		/* state change failure is ok अगर we started ctrl delete */
		WARN_ON_ONCE(ctrl->state != NVME_CTRL_DELETING &&
			     ctrl->state != NVME_CTRL_DELETING_NOIO);
		वापस;
	पूर्ण

	nvme_tcp_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल व्योम nvme_tcp_tearकरोwn_ctrl(काष्ठा nvme_ctrl *ctrl, bool shutकरोwn)
अणु
	cancel_work_sync(&to_tcp_ctrl(ctrl)->err_work);
	cancel_delayed_work_sync(&to_tcp_ctrl(ctrl)->connect_work);

	nvme_tcp_tearकरोwn_io_queues(ctrl, shutकरोwn);
	blk_mq_quiesce_queue(ctrl->admin_q);
	अगर (shutकरोwn)
		nvme_shutकरोwn_ctrl(ctrl);
	अन्यथा
		nvme_disable_ctrl(ctrl);
	nvme_tcp_tearकरोwn_admin_queue(ctrl, shutकरोwn);
पूर्ण

अटल व्योम nvme_tcp_delete_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_tcp_tearकरोwn_ctrl(ctrl, true);
पूर्ण

अटल व्योम nvme_reset_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(work, काष्ठा nvme_ctrl, reset_work);

	nvme_stop_ctrl(ctrl);
	nvme_tcp_tearकरोwn_ctrl(ctrl, false);

	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_CONNECTING)) अणु
		/* state change failure is ok अगर we started ctrl delete */
		WARN_ON_ONCE(ctrl->state != NVME_CTRL_DELETING &&
			     ctrl->state != NVME_CTRL_DELETING_NOIO);
		वापस;
	पूर्ण

	अगर (nvme_tcp_setup_ctrl(ctrl, false))
		जाओ out_fail;

	वापस;

out_fail:
	++ctrl->nr_reconnects;
	nvme_tcp_reconnect_or_हटाओ(ctrl);
पूर्ण

अटल व्योम nvme_tcp_मुक्त_ctrl(काष्ठा nvme_ctrl *nctrl)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);

	अगर (list_empty(&ctrl->list))
		जाओ मुक्त_ctrl;

	mutex_lock(&nvme_tcp_ctrl_mutex);
	list_del(&ctrl->list);
	mutex_unlock(&nvme_tcp_ctrl_mutex);

	nvmf_मुक्त_options(nctrl->opts);
मुक्त_ctrl:
	kमुक्त(ctrl->queues);
	kमुक्त(ctrl);
पूर्ण

अटल व्योम nvme_tcp_set_sg_null(काष्ठा nvme_command *c)
अणु
	काष्ठा nvme_sgl_desc *sg = &c->common.dptr.sgl;

	sg->addr = 0;
	sg->length = 0;
	sg->type = (NVME_TRANSPORT_SGL_DATA_DESC << 4) |
			NVME_SGL_FMT_TRANSPORT_A;
पूर्ण

अटल व्योम nvme_tcp_set_sg_अंतरभूत(काष्ठा nvme_tcp_queue *queue,
		काष्ठा nvme_command *c, u32 data_len)
अणु
	काष्ठा nvme_sgl_desc *sg = &c->common.dptr.sgl;

	sg->addr = cpu_to_le64(queue->ctrl->ctrl.icकरोff);
	sg->length = cpu_to_le32(data_len);
	sg->type = (NVME_SGL_FMT_DATA_DESC << 4) | NVME_SGL_FMT_OFFSET;
पूर्ण

अटल व्योम nvme_tcp_set_sg_host_data(काष्ठा nvme_command *c,
		u32 data_len)
अणु
	काष्ठा nvme_sgl_desc *sg = &c->common.dptr.sgl;

	sg->addr = 0;
	sg->length = cpu_to_le32(data_len);
	sg->type = (NVME_TRANSPORT_SGL_DATA_DESC << 4) |
			NVME_SGL_FMT_TRANSPORT_A;
पूर्ण

अटल व्योम nvme_tcp_submit_async_event(काष्ठा nvme_ctrl *arg)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = to_tcp_ctrl(arg);
	काष्ठा nvme_tcp_queue *queue = &ctrl->queues[0];
	काष्ठा nvme_tcp_cmd_pdu *pdu = ctrl->async_req.pdu;
	काष्ठा nvme_command *cmd = &pdu->cmd;
	u8 hdgst = nvme_tcp_hdgst_len(queue);

	स_रखो(pdu, 0, माप(*pdu));
	pdu->hdr.type = nvme_tcp_cmd;
	अगर (queue->hdr_digest)
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
	pdu->hdr.hlen = माप(*pdu);
	pdu->hdr.plen = cpu_to_le32(pdu->hdr.hlen + hdgst);

	cmd->common.opcode = nvme_admin_async_event;
	cmd->common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	cmd->common.flags |= NVME_CMD_SGL_METABUF;
	nvme_tcp_set_sg_null(cmd);

	ctrl->async_req.state = NVME_TCP_SEND_CMD_PDU;
	ctrl->async_req.offset = 0;
	ctrl->async_req.curr_bio = शून्य;
	ctrl->async_req.data_len = 0;

	nvme_tcp_queue_request(&ctrl->async_req, true, true);
पूर्ण

अटल व्योम nvme_tcp_complete_समयd_out(काष्ठा request *rq)
अणु
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_ctrl *ctrl = &req->queue->ctrl->ctrl;

	nvme_tcp_stop_queue(ctrl, nvme_tcp_queue_id(req->queue));
	अगर (blk_mq_request_started(rq) && !blk_mq_request_completed(rq)) अणु
		nvme_req(rq)->status = NVME_SC_HOST_ABORTED_CMD;
		blk_mq_complete_request(rq);
	पूर्ण
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस
nvme_tcp_समयout(काष्ठा request *rq, bool reserved)
अणु
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_ctrl *ctrl = &req->queue->ctrl->ctrl;
	काष्ठा nvme_tcp_cmd_pdu *pdu = req->pdu;

	dev_warn(ctrl->device,
		"queue %d: timeout request %#x type %d\n",
		nvme_tcp_queue_id(req->queue), rq->tag, pdu->hdr.type);

	अगर (ctrl->state != NVME_CTRL_LIVE) अणु
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
		nvme_tcp_complete_समयd_out(rq);
		वापस BLK_EH_DONE;
	पूर्ण

	/*
	 * LIVE state should trigger the normal error recovery which will
	 * handle completing this request.
	 */
	nvme_tcp_error_recovery(ctrl);
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल blk_status_t nvme_tcp_map_data(काष्ठा nvme_tcp_queue *queue,
			काष्ठा request *rq)
अणु
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_tcp_cmd_pdu *pdu = req->pdu;
	काष्ठा nvme_command *c = &pdu->cmd;

	c->common.flags |= NVME_CMD_SGL_METABUF;

	अगर (!blk_rq_nr_phys_segments(rq))
		nvme_tcp_set_sg_null(c);
	अन्यथा अगर (rq_data_dir(rq) == WRITE &&
	    req->data_len <= nvme_tcp_अंतरभूत_data_size(queue))
		nvme_tcp_set_sg_अंतरभूत(queue, c, req->data_len);
	अन्यथा
		nvme_tcp_set_sg_host_data(c, req->data_len);

	वापस 0;
पूर्ण

अटल blk_status_t nvme_tcp_setup_cmd_pdu(काष्ठा nvme_ns *ns,
		काष्ठा request *rq)
अणु
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	काष्ठा nvme_tcp_cmd_pdu *pdu = req->pdu;
	काष्ठा nvme_tcp_queue *queue = req->queue;
	u8 hdgst = nvme_tcp_hdgst_len(queue), ddgst = 0;
	blk_status_t ret;

	ret = nvme_setup_cmd(ns, rq);
	अगर (ret)
		वापस ret;

	req->state = NVME_TCP_SEND_CMD_PDU;
	req->offset = 0;
	req->data_sent = 0;
	req->pdu_len = 0;
	req->pdu_sent = 0;
	req->data_len = blk_rq_nr_phys_segments(rq) ?
				blk_rq_payload_bytes(rq) : 0;
	req->curr_bio = rq->bio;
	अगर (req->curr_bio && req->data_len)
		nvme_tcp_init_iter(req, rq_data_dir(rq));

	अगर (rq_data_dir(rq) == WRITE &&
	    req->data_len <= nvme_tcp_अंतरभूत_data_size(queue))
		req->pdu_len = req->data_len;

	pdu->hdr.type = nvme_tcp_cmd;
	pdu->hdr.flags = 0;
	अगर (queue->hdr_digest)
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
	अगर (queue->data_digest && req->pdu_len) अणु
		pdu->hdr.flags |= NVME_TCP_F_DDGST;
		ddgst = nvme_tcp_ddgst_len(queue);
	पूर्ण
	pdu->hdr.hlen = माप(*pdu);
	pdu->hdr.pकरो = req->pdu_len ? pdu->hdr.hlen + hdgst : 0;
	pdu->hdr.plen =
		cpu_to_le32(pdu->hdr.hlen + hdgst + req->pdu_len + ddgst);

	ret = nvme_tcp_map_data(queue, rq);
	अगर (unlikely(ret)) अणु
		nvme_cleanup_cmd(rq);
		dev_err(queue->ctrl->ctrl.device,
			"Failed to map data (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvme_tcp_commit_rqs(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा nvme_tcp_queue *queue = hctx->driver_data;

	अगर (!llist_empty(&queue->req_list))
		queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
पूर्ण

अटल blk_status_t nvme_tcp_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
		स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nvme_ns *ns = hctx->queue->queuedata;
	काष्ठा nvme_tcp_queue *queue = hctx->driver_data;
	काष्ठा request *rq = bd->rq;
	काष्ठा nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	bool queue_पढ़ोy = test_bit(NVME_TCP_Q_LIVE, &queue->flags);
	blk_status_t ret;

	अगर (!nvme_check_पढ़ोy(&queue->ctrl->ctrl, rq, queue_पढ़ोy))
		वापस nvme_fail_nonपढ़ोy_command(&queue->ctrl->ctrl, rq);

	ret = nvme_tcp_setup_cmd_pdu(ns, rq);
	अगर (unlikely(ret))
		वापस ret;

	blk_mq_start_request(rq);

	nvme_tcp_queue_request(req, true, bd->last);

	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक nvme_tcp_map_queues(काष्ठा blk_mq_tag_set *set)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl = set->driver_data;
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
	blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
	blk_mq_map_queues(&set->map[HCTX_TYPE_READ]);

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

अटल पूर्णांक nvme_tcp_poll(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा nvme_tcp_queue *queue = hctx->driver_data;
	काष्ठा sock *sk = queue->sock->sk;

	अगर (!test_bit(NVME_TCP_Q_LIVE, &queue->flags))
		वापस 0;

	set_bit(NVME_TCP_Q_POLLING, &queue->flags);
	अगर (sk_can_busy_loop(sk) && skb_queue_empty_lockless(&sk->sk_receive_queue))
		sk_busy_loop(sk, true);
	nvme_tcp_try_recv(queue);
	clear_bit(NVME_TCP_Q_POLLING, &queue->flags);
	वापस queue->nr_cqe;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops nvme_tcp_mq_ops = अणु
	.queue_rq	= nvme_tcp_queue_rq,
	.commit_rqs	= nvme_tcp_commit_rqs,
	.complete	= nvme_complete_rq,
	.init_request	= nvme_tcp_init_request,
	.निकास_request	= nvme_tcp_निकास_request,
	.init_hctx	= nvme_tcp_init_hctx,
	.समयout	= nvme_tcp_समयout,
	.map_queues	= nvme_tcp_map_queues,
	.poll		= nvme_tcp_poll,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops nvme_tcp_admin_mq_ops = अणु
	.queue_rq	= nvme_tcp_queue_rq,
	.complete	= nvme_complete_rq,
	.init_request	= nvme_tcp_init_request,
	.निकास_request	= nvme_tcp_निकास_request,
	.init_hctx	= nvme_tcp_init_admin_hctx,
	.समयout	= nvme_tcp_समयout,
पूर्ण;

अटल स्थिर काष्ठा nvme_ctrl_ops nvme_tcp_ctrl_ops = अणु
	.name			= "tcp",
	.module			= THIS_MODULE,
	.flags			= NVME_F_FABRICS,
	.reg_पढ़ो32		= nvmf_reg_पढ़ो32,
	.reg_पढ़ो64		= nvmf_reg_पढ़ो64,
	.reg_ग_लिखो32		= nvmf_reg_ग_लिखो32,
	.मुक्त_ctrl		= nvme_tcp_मुक्त_ctrl,
	.submit_async_event	= nvme_tcp_submit_async_event,
	.delete_ctrl		= nvme_tcp_delete_ctrl,
	.get_address		= nvmf_get_address,
पूर्ण;

अटल bool
nvme_tcp_existing_controller(काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl;
	bool found = false;

	mutex_lock(&nvme_tcp_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_tcp_ctrl_list, list) अणु
		found = nvmf_ip_options_match(&ctrl->ctrl, opts);
		अगर (found)
			अवरोध;
	पूर्ण
	mutex_unlock(&nvme_tcp_ctrl_mutex);

	वापस found;
पूर्ण

अटल काष्ठा nvme_ctrl *nvme_tcp_create_ctrl(काष्ठा device *dev,
		काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl;
	पूर्णांक ret;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ctrl->list);
	ctrl->ctrl.opts = opts;
	ctrl->ctrl.queue_count = opts->nr_io_queues + opts->nr_ग_लिखो_queues +
				opts->nr_poll_queues + 1;
	ctrl->ctrl.sqsize = opts->queue_size - 1;
	ctrl->ctrl.kato = opts->kato;

	INIT_DELAYED_WORK(&ctrl->connect_work,
			nvme_tcp_reconnect_ctrl_work);
	INIT_WORK(&ctrl->err_work, nvme_tcp_error_recovery_work);
	INIT_WORK(&ctrl->ctrl.reset_work, nvme_reset_ctrl_work);

	अगर (!(opts->mask & NVMF_OPT_TRSVCID)) अणु
		opts->trsvcid =
			kstrdup(__stringअगरy(NVME_TCP_DISC_PORT), GFP_KERNEL);
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

	अगर (!opts->duplicate_connect && nvme_tcp_existing_controller(opts)) अणु
		ret = -EALREADY;
		जाओ out_मुक्त_ctrl;
	पूर्ण

	ctrl->queues = kसुस्मृति(ctrl->ctrl.queue_count, माप(*ctrl->queues),
				GFP_KERNEL);
	अगर (!ctrl->queues) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_ctrl;
	पूर्ण

	ret = nvme_init_ctrl(&ctrl->ctrl, dev, &nvme_tcp_ctrl_ops, 0);
	अगर (ret)
		जाओ out_kमुक्त_queues;

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING)) अणु
		WARN_ON_ONCE(1);
		ret = -EINTR;
		जाओ out_uninit_ctrl;
	पूर्ण

	ret = nvme_tcp_setup_ctrl(&ctrl->ctrl, true);
	अगर (ret)
		जाओ out_uninit_ctrl;

	dev_info(ctrl->ctrl.device, "new ctrl: NQN \"%s\", addr %pISp\n",
		ctrl->ctrl.opts->subsysnqn, &ctrl->addr);

	mutex_lock(&nvme_tcp_ctrl_mutex);
	list_add_tail(&ctrl->list, &nvme_tcp_ctrl_list);
	mutex_unlock(&nvme_tcp_ctrl_mutex);

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

अटल काष्ठा nvmf_transport_ops nvme_tcp_transport = अणु
	.name		= "tcp",
	.module		= THIS_MODULE,
	.required_opts	= NVMF_OPT_TRADDR,
	.allowed_opts	= NVMF_OPT_TRSVCID | NVMF_OPT_RECONNECT_DELAY |
			  NVMF_OPT_HOST_TRADDR | NVMF_OPT_CTRL_LOSS_TMO |
			  NVMF_OPT_HDR_DIGEST | NVMF_OPT_DATA_DIGEST |
			  NVMF_OPT_NR_WRITE_QUEUES | NVMF_OPT_NR_POLL_QUEUES |
			  NVMF_OPT_TOS,
	.create_ctrl	= nvme_tcp_create_ctrl,
पूर्ण;

अटल पूर्णांक __init nvme_tcp_init_module(व्योम)
अणु
	nvme_tcp_wq = alloc_workqueue("nvme_tcp_wq",
			WQ_MEM_RECLAIM | WQ_HIGHPRI, 0);
	अगर (!nvme_tcp_wq)
		वापस -ENOMEM;

	nvmf_रेजिस्टर_transport(&nvme_tcp_transport);
	वापस 0;
पूर्ण

अटल व्योम __निकास nvme_tcp_cleanup_module(व्योम)
अणु
	काष्ठा nvme_tcp_ctrl *ctrl;

	nvmf_unरेजिस्टर_transport(&nvme_tcp_transport);

	mutex_lock(&nvme_tcp_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_tcp_ctrl_list, list)
		nvme_delete_ctrl(&ctrl->ctrl);
	mutex_unlock(&nvme_tcp_ctrl_mutex);
	flush_workqueue(nvme_delete_wq);

	destroy_workqueue(nvme_tcp_wq);
पूर्ण

module_init(nvme_tcp_init_module);
module_निकास(nvme_tcp_cleanup_module);

MODULE_LICENSE("GPL v2");
