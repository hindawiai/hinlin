<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics TCP target.
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
#समावेश <linux/inet.h>
#समावेश <linux/llist.h>
#समावेश <crypto/hash.h>

#समावेश "nvmet.h"

#घोषणा NVMET_TCP_DEF_INLINE_DATA_SIZE	(4 * PAGE_SIZE)

/* Define the socket priority to use क्रम connections were it is desirable
 * that the NIC consider perक्रमming optimized packet processing or filtering.
 * A non-zero value being sufficient to indicate general consideration of any
 * possible optimization.  Making it a module param allows क्रम alternative
 * values that may be unique क्रम some NIC implementations.
 */
अटल पूर्णांक so_priority;
module_param(so_priority, पूर्णांक, 0644);
MODULE_PARM_DESC(so_priority, "nvmet tcp socket optimize priority");

/* Define a समय period (in usecs) that io_work() shall sample an activated
 * queue beक्रमe determining it to be idle.  This optional module behavior
 * can enable NIC solutions that support socket optimized packet processing
 * using advanced पूर्णांकerrupt moderation techniques.
 */
अटल पूर्णांक idle_poll_period_usecs;
module_param(idle_poll_period_usecs, पूर्णांक, 0644);
MODULE_PARM_DESC(idle_poll_period_usecs,
		"nvmet tcp io_work poll till idle time period in usecs");

#घोषणा NVMET_TCP_RECV_BUDGET		8
#घोषणा NVMET_TCP_SEND_BUDGET		8
#घोषणा NVMET_TCP_IO_WORK_BUDGET	64

क्रमागत nvmet_tcp_send_state अणु
	NVMET_TCP_SEND_DATA_PDU,
	NVMET_TCP_SEND_DATA,
	NVMET_TCP_SEND_R2T,
	NVMET_TCP_SEND_DDGST,
	NVMET_TCP_SEND_RESPONSE
पूर्ण;

क्रमागत nvmet_tcp_recv_state अणु
	NVMET_TCP_RECV_PDU,
	NVMET_TCP_RECV_DATA,
	NVMET_TCP_RECV_DDGST,
	NVMET_TCP_RECV_ERR,
पूर्ण;

क्रमागत अणु
	NVMET_TCP_F_INIT_FAILED = (1 << 0),
पूर्ण;

काष्ठा nvmet_tcp_cmd अणु
	काष्ठा nvmet_tcp_queue		*queue;
	काष्ठा nvmet_req		req;

	काष्ठा nvme_tcp_cmd_pdu		*cmd_pdu;
	काष्ठा nvme_tcp_rsp_pdu		*rsp_pdu;
	काष्ठा nvme_tcp_data_pdu	*data_pdu;
	काष्ठा nvme_tcp_r2t_pdu		*r2t_pdu;

	u32				rbytes_करोne;
	u32				wbytes_करोne;

	u32				pdu_len;
	u32				pdu_recv;
	पूर्णांक				sg_idx;
	पूर्णांक				nr_mapped;
	काष्ठा msghdr			recv_msg;
	काष्ठा kvec			*iov;
	u32				flags;

	काष्ठा list_head		entry;
	काष्ठा llist_node		lentry;

	/* send state */
	u32				offset;
	काष्ठा scatterlist		*cur_sg;
	क्रमागत nvmet_tcp_send_state	state;

	__le32				exp_ddgst;
	__le32				recv_ddgst;
पूर्ण;

क्रमागत nvmet_tcp_queue_state अणु
	NVMET_TCP_Q_CONNECTING,
	NVMET_TCP_Q_LIVE,
	NVMET_TCP_Q_DISCONNECTING,
पूर्ण;

काष्ठा nvmet_tcp_queue अणु
	काष्ठा socket		*sock;
	काष्ठा nvmet_tcp_port	*port;
	काष्ठा work_काष्ठा	io_work;
	काष्ठा nvmet_cq		nvme_cq;
	काष्ठा nvmet_sq		nvme_sq;

	/* send state */
	काष्ठा nvmet_tcp_cmd	*cmds;
	अचिन्हित पूर्णांक		nr_cmds;
	काष्ठा list_head	मुक्त_list;
	काष्ठा llist_head	resp_list;
	काष्ठा list_head	resp_send_list;
	पूर्णांक			send_list_len;
	काष्ठा nvmet_tcp_cmd	*snd_cmd;

	/* recv state */
	पूर्णांक			offset;
	पूर्णांक			left;
	क्रमागत nvmet_tcp_recv_state rcv_state;
	काष्ठा nvmet_tcp_cmd	*cmd;
	जोड़ nvme_tcp_pdu	pdu;

	/* digest state */
	bool			hdr_digest;
	bool			data_digest;
	काष्ठा ahash_request	*snd_hash;
	काष्ठा ahash_request	*rcv_hash;

	अचिन्हित दीर्घ           poll_end;

	spinlock_t		state_lock;
	क्रमागत nvmet_tcp_queue_state state;

	काष्ठा sockaddr_storage	sockaddr;
	काष्ठा sockaddr_storage	sockaddr_peer;
	काष्ठा work_काष्ठा	release_work;

	पूर्णांक			idx;
	काष्ठा list_head	queue_list;

	काष्ठा nvmet_tcp_cmd	connect;

	काष्ठा page_frag_cache	pf_cache;

	व्योम (*data_पढ़ोy)(काष्ठा sock *);
	व्योम (*state_change)(काष्ठा sock *);
	व्योम (*ग_लिखो_space)(काष्ठा sock *);
पूर्ण;

काष्ठा nvmet_tcp_port अणु
	काष्ठा socket		*sock;
	काष्ठा work_काष्ठा	accept_work;
	काष्ठा nvmet_port	*nport;
	काष्ठा sockaddr_storage addr;
	व्योम (*data_पढ़ोy)(काष्ठा sock *);
पूर्ण;

अटल DEFINE_IDA(nvmet_tcp_queue_ida);
अटल LIST_HEAD(nvmet_tcp_queue_list);
अटल DEFINE_MUTEX(nvmet_tcp_queue_mutex);

अटल काष्ठा workqueue_काष्ठा *nvmet_tcp_wq;
अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_tcp_ops;
अटल व्योम nvmet_tcp_मुक्त_cmd(काष्ठा nvmet_tcp_cmd *c);
अटल व्योम nvmet_tcp_finish_cmd(काष्ठा nvmet_tcp_cmd *cmd);

अटल अंतरभूत u16 nvmet_tcp_cmd_tag(काष्ठा nvmet_tcp_queue *queue,
		काष्ठा nvmet_tcp_cmd *cmd)
अणु
	अगर (unlikely(!queue->nr_cmds)) अणु
		/* We didn't allocate cmds yet, send 0xffff */
		वापस अच_लघु_उच्च;
	पूर्ण

	वापस cmd - queue->cmds;
पूर्ण

अटल अंतरभूत bool nvmet_tcp_has_data_in(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	वापस nvme_is_ग_लिखो(cmd->req.cmd) &&
		cmd->rbytes_करोne < cmd->req.transfer_len;
पूर्ण

अटल अंतरभूत bool nvmet_tcp_need_data_in(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	वापस nvmet_tcp_has_data_in(cmd) && !cmd->req.cqe->status;
पूर्ण

अटल अंतरभूत bool nvmet_tcp_need_data_out(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	वापस !nvme_is_ग_लिखो(cmd->req.cmd) &&
		cmd->req.transfer_len > 0 &&
		!cmd->req.cqe->status;
पूर्ण

अटल अंतरभूत bool nvmet_tcp_has_अंतरभूत_data(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	वापस nvme_is_ग_लिखो(cmd->req.cmd) && cmd->pdu_len &&
		!cmd->rbytes_करोne;
पूर्ण

अटल अंतरभूत काष्ठा nvmet_tcp_cmd *
nvmet_tcp_get_cmd(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd *cmd;

	cmd = list_first_entry_or_null(&queue->मुक्त_list,
				काष्ठा nvmet_tcp_cmd, entry);
	अगर (!cmd)
		वापस शून्य;
	list_del_init(&cmd->entry);

	cmd->rbytes_करोne = cmd->wbytes_करोne = 0;
	cmd->pdu_len = 0;
	cmd->pdu_recv = 0;
	cmd->iov = शून्य;
	cmd->flags = 0;
	वापस cmd;
पूर्ण

अटल अंतरभूत व्योम nvmet_tcp_put_cmd(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	अगर (unlikely(cmd == &cmd->queue->connect))
		वापस;

	list_add_tail(&cmd->entry, &cmd->queue->मुक्त_list);
पूर्ण

अटल अंतरभूत पूर्णांक queue_cpu(काष्ठा nvmet_tcp_queue *queue)
अणु
	वापस queue->sock->sk->sk_incoming_cpu;
पूर्ण

अटल अंतरभूत u8 nvmet_tcp_hdgst_len(काष्ठा nvmet_tcp_queue *queue)
अणु
	वापस queue->hdr_digest ? NVME_TCP_DIGEST_LENGTH : 0;
पूर्ण

अटल अंतरभूत u8 nvmet_tcp_ddgst_len(काष्ठा nvmet_tcp_queue *queue)
अणु
	वापस queue->data_digest ? NVME_TCP_DIGEST_LENGTH : 0;
पूर्ण

अटल अंतरभूत व्योम nvmet_tcp_hdgst(काष्ठा ahash_request *hash,
		व्योम *pdu, माप_प्रकार len)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, pdu, len);
	ahash_request_set_crypt(hash, &sg, pdu + len, len);
	crypto_ahash_digest(hash);
पूर्ण

अटल पूर्णांक nvmet_tcp_verअगरy_hdgst(काष्ठा nvmet_tcp_queue *queue,
	व्योम *pdu, माप_प्रकार len)
अणु
	काष्ठा nvme_tcp_hdr *hdr = pdu;
	__le32 recv_digest;
	__le32 exp_digest;

	अगर (unlikely(!(hdr->flags & NVME_TCP_F_HDGST))) अणु
		pr_err("queue %d: header digest enabled but no header digest\n",
			queue->idx);
		वापस -EPROTO;
	पूर्ण

	recv_digest = *(__le32 *)(pdu + hdr->hlen);
	nvmet_tcp_hdgst(queue->rcv_hash, pdu, len);
	exp_digest = *(__le32 *)(pdu + hdr->hlen);
	अगर (recv_digest != exp_digest) अणु
		pr_err("queue %d: header digest error: recv %#x expected %#x\n",
			queue->idx, le32_to_cpu(recv_digest),
			le32_to_cpu(exp_digest));
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvmet_tcp_check_ddgst(काष्ठा nvmet_tcp_queue *queue, व्योम *pdu)
अणु
	काष्ठा nvme_tcp_hdr *hdr = pdu;
	u8 digest_len = nvmet_tcp_hdgst_len(queue);
	u32 len;

	len = le32_to_cpu(hdr->plen) - hdr->hlen -
		(hdr->flags & NVME_TCP_F_HDGST ? digest_len : 0);

	अगर (unlikely(len && !(hdr->flags & NVME_TCP_F_DDGST))) अणु
		pr_err("queue %d: data digest flag is cleared\n", queue->idx);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvmet_tcp_unmap_pdu_iovec(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	sg = &cmd->req.sg[cmd->sg_idx];

	क्रम (i = 0; i < cmd->nr_mapped; i++)
		kunmap(sg_page(&sg[i]));
पूर्ण

अटल व्योम nvmet_tcp_map_pdu_iovec(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा kvec *iov = cmd->iov;
	काष्ठा scatterlist *sg;
	u32 length, offset, sg_offset;

	length = cmd->pdu_len;
	cmd->nr_mapped = DIV_ROUND_UP(length, PAGE_SIZE);
	offset = cmd->rbytes_करोne;
	cmd->sg_idx = offset / PAGE_SIZE;
	sg_offset = offset % PAGE_SIZE;
	sg = &cmd->req.sg[cmd->sg_idx];

	जबतक (length) अणु
		u32 iov_len = min_t(u32, length, sg->length - sg_offset);

		iov->iov_base = kmap(sg_page(sg)) + sg->offset + sg_offset;
		iov->iov_len = iov_len;

		length -= iov_len;
		sg = sg_next(sg);
		iov++;
		sg_offset = 0;
	पूर्ण

	iov_iter_kvec(&cmd->recv_msg.msg_iter, READ, cmd->iov,
		cmd->nr_mapped, cmd->pdu_len);
पूर्ण

अटल व्योम nvmet_tcp_fatal_error(काष्ठा nvmet_tcp_queue *queue)
अणु
	queue->rcv_state = NVMET_TCP_RECV_ERR;
	अगर (queue->nvme_sq.ctrl)
		nvmet_ctrl_fatal_error(queue->nvme_sq.ctrl);
	अन्यथा
		kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
पूर्ण

अटल व्योम nvmet_tcp_socket_error(काष्ठा nvmet_tcp_queue *queue, पूर्णांक status)
अणु
	अगर (status == -EPIPE || status == -ECONNRESET)
		kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
	अन्यथा
		nvmet_tcp_fatal_error(queue);
पूर्ण

अटल पूर्णांक nvmet_tcp_map_data(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा nvme_sgl_desc *sgl = &cmd->req.cmd->common.dptr.sgl;
	u32 len = le32_to_cpu(sgl->length);

	अगर (!len)
		वापस 0;

	अगर (sgl->type == ((NVME_SGL_FMT_DATA_DESC << 4) |
			  NVME_SGL_FMT_OFFSET)) अणु
		अगर (!nvme_is_ग_लिखो(cmd->req.cmd))
			वापस NVME_SC_INVALID_FIELD | NVME_SC_DNR;

		अगर (len > cmd->req.port->अंतरभूत_data_size)
			वापस NVME_SC_SGL_INVALID_OFFSET | NVME_SC_DNR;
		cmd->pdu_len = len;
	पूर्ण
	cmd->req.transfer_len += len;

	cmd->req.sg = sgl_alloc(len, GFP_KERNEL, &cmd->req.sg_cnt);
	अगर (!cmd->req.sg)
		वापस NVME_SC_INTERNAL;
	cmd->cur_sg = cmd->req.sg;

	अगर (nvmet_tcp_has_data_in(cmd)) अणु
		cmd->iov = kदो_स्मृति_array(cmd->req.sg_cnt,
				माप(*cmd->iov), GFP_KERNEL);
		अगर (!cmd->iov)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	sgl_मुक्त(cmd->req.sg);
	वापस NVME_SC_INTERNAL;
पूर्ण

अटल व्योम nvmet_tcp_send_ddgst(काष्ठा ahash_request *hash,
		काष्ठा nvmet_tcp_cmd *cmd)
अणु
	ahash_request_set_crypt(hash, cmd->req.sg,
		(व्योम *)&cmd->exp_ddgst, cmd->req.transfer_len);
	crypto_ahash_digest(hash);
पूर्ण

अटल व्योम nvmet_tcp_recv_ddgst(काष्ठा ahash_request *hash,
		काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा scatterlist sg;
	काष्ठा kvec *iov;
	पूर्णांक i;

	crypto_ahash_init(hash);
	क्रम (i = 0, iov = cmd->iov; i < cmd->nr_mapped; i++, iov++) अणु
		sg_init_one(&sg, iov->iov_base, iov->iov_len);
		ahash_request_set_crypt(hash, &sg, शून्य, iov->iov_len);
		crypto_ahash_update(hash);
	पूर्ण
	ahash_request_set_crypt(hash, शून्य, (व्योम *)&cmd->exp_ddgst, 0);
	crypto_ahash_final(hash);
पूर्ण

अटल व्योम nvmet_setup_c2h_data_pdu(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा nvme_tcp_data_pdu *pdu = cmd->data_pdu;
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);
	u8 ddgst = nvmet_tcp_ddgst_len(cmd->queue);

	cmd->offset = 0;
	cmd->state = NVMET_TCP_SEND_DATA_PDU;

	pdu->hdr.type = nvme_tcp_c2h_data;
	pdu->hdr.flags = NVME_TCP_F_DATA_LAST | (queue->nvme_sq.sqhd_disabled ?
						NVME_TCP_F_DATA_SUCCESS : 0);
	pdu->hdr.hlen = माप(*pdu);
	pdu->hdr.pकरो = pdu->hdr.hlen + hdgst;
	pdu->hdr.plen =
		cpu_to_le32(pdu->hdr.hlen + hdgst +
				cmd->req.transfer_len + ddgst);
	pdu->command_id = cmd->req.cqe->command_id;
	pdu->data_length = cpu_to_le32(cmd->req.transfer_len);
	pdu->data_offset = cpu_to_le32(cmd->wbytes_करोne);

	अगर (queue->data_digest) अणु
		pdu->hdr.flags |= NVME_TCP_F_DDGST;
		nvmet_tcp_send_ddgst(queue->snd_hash, cmd);
	पूर्ण

	अगर (cmd->queue->hdr_digest) अणु
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
		nvmet_tcp_hdgst(queue->snd_hash, pdu, माप(*pdu));
	पूर्ण
पूर्ण

अटल व्योम nvmet_setup_r2t_pdu(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा nvme_tcp_r2t_pdu *pdu = cmd->r2t_pdu;
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);

	cmd->offset = 0;
	cmd->state = NVMET_TCP_SEND_R2T;

	pdu->hdr.type = nvme_tcp_r2t;
	pdu->hdr.flags = 0;
	pdu->hdr.hlen = माप(*pdu);
	pdu->hdr.pकरो = 0;
	pdu->hdr.plen = cpu_to_le32(pdu->hdr.hlen + hdgst);

	pdu->command_id = cmd->req.cmd->common.command_id;
	pdu->ttag = nvmet_tcp_cmd_tag(cmd->queue, cmd);
	pdu->r2t_length = cpu_to_le32(cmd->req.transfer_len - cmd->rbytes_करोne);
	pdu->r2t_offset = cpu_to_le32(cmd->rbytes_करोne);
	अगर (cmd->queue->hdr_digest) अणु
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
		nvmet_tcp_hdgst(queue->snd_hash, pdu, माप(*pdu));
	पूर्ण
पूर्ण

अटल व्योम nvmet_setup_response_pdu(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा nvme_tcp_rsp_pdu *pdu = cmd->rsp_pdu;
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);

	cmd->offset = 0;
	cmd->state = NVMET_TCP_SEND_RESPONSE;

	pdu->hdr.type = nvme_tcp_rsp;
	pdu->hdr.flags = 0;
	pdu->hdr.hlen = माप(*pdu);
	pdu->hdr.pकरो = 0;
	pdu->hdr.plen = cpu_to_le32(pdu->hdr.hlen + hdgst);
	अगर (cmd->queue->hdr_digest) अणु
		pdu->hdr.flags |= NVME_TCP_F_HDGST;
		nvmet_tcp_hdgst(queue->snd_hash, pdu, माप(*pdu));
	पूर्ण
पूर्ण

अटल व्योम nvmet_tcp_process_resp_list(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा llist_node *node;
	काष्ठा nvmet_tcp_cmd *cmd;

	क्रम (node = llist_del_all(&queue->resp_list); node; node = node->next) अणु
		cmd = llist_entry(node, काष्ठा nvmet_tcp_cmd, lentry);
		list_add(&cmd->entry, &queue->resp_send_list);
		queue->send_list_len++;
	पूर्ण
पूर्ण

अटल काष्ठा nvmet_tcp_cmd *nvmet_tcp_fetch_cmd(काष्ठा nvmet_tcp_queue *queue)
अणु
	queue->snd_cmd = list_first_entry_or_null(&queue->resp_send_list,
				काष्ठा nvmet_tcp_cmd, entry);
	अगर (!queue->snd_cmd) अणु
		nvmet_tcp_process_resp_list(queue);
		queue->snd_cmd =
			list_first_entry_or_null(&queue->resp_send_list,
					काष्ठा nvmet_tcp_cmd, entry);
		अगर (unlikely(!queue->snd_cmd))
			वापस शून्य;
	पूर्ण

	list_del_init(&queue->snd_cmd->entry);
	queue->send_list_len--;

	अगर (nvmet_tcp_need_data_out(queue->snd_cmd))
		nvmet_setup_c2h_data_pdu(queue->snd_cmd);
	अन्यथा अगर (nvmet_tcp_need_data_in(queue->snd_cmd))
		nvmet_setup_r2t_pdu(queue->snd_cmd);
	अन्यथा
		nvmet_setup_response_pdu(queue->snd_cmd);

	वापस queue->snd_cmd;
पूर्ण

अटल व्योम nvmet_tcp_queue_response(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_tcp_cmd *cmd =
		container_of(req, काष्ठा nvmet_tcp_cmd, req);
	काष्ठा nvmet_tcp_queue	*queue = cmd->queue;
	काष्ठा nvme_sgl_desc *sgl;
	u32 len;

	अगर (unlikely(cmd == queue->cmd)) अणु
		sgl = &cmd->req.cmd->common.dptr.sgl;
		len = le32_to_cpu(sgl->length);

		/*
		 * Wait क्रम अंतरभूत data beक्रमe processing the response.
		 * Aव्योम using helpers, this might happen beक्रमe
		 * nvmet_req_init is completed.
		 */
		अगर (queue->rcv_state == NVMET_TCP_RECV_PDU &&
		    len && len <= cmd->req.port->अंतरभूत_data_size &&
		    nvme_is_ग_लिखो(cmd->req.cmd))
			वापस;
	पूर्ण

	llist_add(&cmd->lentry, &queue->resp_list);
	queue_work_on(queue_cpu(queue), nvmet_tcp_wq, &cmd->queue->io_work);
पूर्ण

अटल व्योम nvmet_tcp_execute_request(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	अगर (unlikely(cmd->flags & NVMET_TCP_F_INIT_FAILED))
		nvmet_tcp_queue_response(&cmd->req);
	अन्यथा
		cmd->req.execute(&cmd->req);
पूर्ण

अटल पूर्णांक nvmet_try_send_data_pdu(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);
	पूर्णांक left = माप(*cmd->data_pdu) - cmd->offset + hdgst;
	पूर्णांक ret;

	ret = kernel_sendpage(cmd->queue->sock, virt_to_page(cmd->data_pdu),
			offset_in_page(cmd->data_pdu) + cmd->offset,
			left, MSG_DONTWAIT | MSG_MORE | MSG_SENDPAGE_NOTLAST);
	अगर (ret <= 0)
		वापस ret;

	cmd->offset += ret;
	left -= ret;

	अगर (left)
		वापस -EAGAIN;

	cmd->state = NVMET_TCP_SEND_DATA;
	cmd->offset  = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_try_send_data(काष्ठा nvmet_tcp_cmd *cmd, bool last_in_batch)
अणु
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;
	पूर्णांक ret;

	जबतक (cmd->cur_sg) अणु
		काष्ठा page *page = sg_page(cmd->cur_sg);
		u32 left = cmd->cur_sg->length - cmd->offset;
		पूर्णांक flags = MSG_DONTWAIT;

		अगर ((!last_in_batch && cmd->queue->send_list_len) ||
		    cmd->wbytes_करोne + left < cmd->req.transfer_len ||
		    queue->data_digest || !queue->nvme_sq.sqhd_disabled)
			flags |= MSG_MORE | MSG_SENDPAGE_NOTLAST;

		ret = kernel_sendpage(cmd->queue->sock, page, cmd->offset,
					left, flags);
		अगर (ret <= 0)
			वापस ret;

		cmd->offset += ret;
		cmd->wbytes_करोne += ret;

		/* Done with sg?*/
		अगर (cmd->offset == cmd->cur_sg->length) अणु
			cmd->cur_sg = sg_next(cmd->cur_sg);
			cmd->offset = 0;
		पूर्ण
	पूर्ण

	अगर (queue->data_digest) अणु
		cmd->state = NVMET_TCP_SEND_DDGST;
		cmd->offset = 0;
	पूर्ण अन्यथा अणु
		अगर (queue->nvme_sq.sqhd_disabled) अणु
			cmd->queue->snd_cmd = शून्य;
			nvmet_tcp_put_cmd(cmd);
		पूर्ण अन्यथा अणु
			nvmet_setup_response_pdu(cmd);
		पूर्ण
	पूर्ण

	अगर (queue->nvme_sq.sqhd_disabled) अणु
		kमुक्त(cmd->iov);
		sgl_मुक्त(cmd->req.sg);
	पूर्ण

	वापस 1;

पूर्ण

अटल पूर्णांक nvmet_try_send_response(काष्ठा nvmet_tcp_cmd *cmd,
		bool last_in_batch)
अणु
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);
	पूर्णांक left = माप(*cmd->rsp_pdu) - cmd->offset + hdgst;
	पूर्णांक flags = MSG_DONTWAIT;
	पूर्णांक ret;

	अगर (!last_in_batch && cmd->queue->send_list_len)
		flags |= MSG_MORE | MSG_SENDPAGE_NOTLAST;
	अन्यथा
		flags |= MSG_EOR;

	ret = kernel_sendpage(cmd->queue->sock, virt_to_page(cmd->rsp_pdu),
		offset_in_page(cmd->rsp_pdu) + cmd->offset, left, flags);
	अगर (ret <= 0)
		वापस ret;
	cmd->offset += ret;
	left -= ret;

	अगर (left)
		वापस -EAGAIN;

	kमुक्त(cmd->iov);
	sgl_मुक्त(cmd->req.sg);
	cmd->queue->snd_cmd = शून्य;
	nvmet_tcp_put_cmd(cmd);
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_try_send_r2t(काष्ठा nvmet_tcp_cmd *cmd, bool last_in_batch)
अणु
	u8 hdgst = nvmet_tcp_hdgst_len(cmd->queue);
	पूर्णांक left = माप(*cmd->r2t_pdu) - cmd->offset + hdgst;
	पूर्णांक flags = MSG_DONTWAIT;
	पूर्णांक ret;

	अगर (!last_in_batch && cmd->queue->send_list_len)
		flags |= MSG_MORE | MSG_SENDPAGE_NOTLAST;
	अन्यथा
		flags |= MSG_EOR;

	ret = kernel_sendpage(cmd->queue->sock, virt_to_page(cmd->r2t_pdu),
		offset_in_page(cmd->r2t_pdu) + cmd->offset, left, flags);
	अगर (ret <= 0)
		वापस ret;
	cmd->offset += ret;
	left -= ret;

	अगर (left)
		वापस -EAGAIN;

	cmd->queue->snd_cmd = शून्य;
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_try_send_ddgst(काष्ठा nvmet_tcp_cmd *cmd, bool last_in_batch)
अणु
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT पूर्ण;
	काष्ठा kvec iov = अणु
		.iov_base = &cmd->exp_ddgst + cmd->offset,
		.iov_len = NVME_TCP_DIGEST_LENGTH - cmd->offset
	पूर्ण;
	पूर्णांक ret;

	अगर (!last_in_batch && cmd->queue->send_list_len)
		msg.msg_flags |= MSG_MORE;
	अन्यथा
		msg.msg_flags |= MSG_EOR;

	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	अगर (unlikely(ret <= 0))
		वापस ret;

	cmd->offset += ret;

	अगर (queue->nvme_sq.sqhd_disabled) अणु
		cmd->queue->snd_cmd = शून्य;
		nvmet_tcp_put_cmd(cmd);
	पूर्ण अन्यथा अणु
		nvmet_setup_response_pdu(cmd);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_send_one(काष्ठा nvmet_tcp_queue *queue,
		bool last_in_batch)
अणु
	काष्ठा nvmet_tcp_cmd *cmd = queue->snd_cmd;
	पूर्णांक ret = 0;

	अगर (!cmd || queue->state == NVMET_TCP_Q_DISCONNECTING) अणु
		cmd = nvmet_tcp_fetch_cmd(queue);
		अगर (unlikely(!cmd))
			वापस 0;
	पूर्ण

	अगर (cmd->state == NVMET_TCP_SEND_DATA_PDU) अणु
		ret = nvmet_try_send_data_pdu(cmd);
		अगर (ret <= 0)
			जाओ करोne_send;
	पूर्ण

	अगर (cmd->state == NVMET_TCP_SEND_DATA) अणु
		ret = nvmet_try_send_data(cmd, last_in_batch);
		अगर (ret <= 0)
			जाओ करोne_send;
	पूर्ण

	अगर (cmd->state == NVMET_TCP_SEND_DDGST) अणु
		ret = nvmet_try_send_ddgst(cmd, last_in_batch);
		अगर (ret <= 0)
			जाओ करोne_send;
	पूर्ण

	अगर (cmd->state == NVMET_TCP_SEND_R2T) अणु
		ret = nvmet_try_send_r2t(cmd, last_in_batch);
		अगर (ret <= 0)
			जाओ करोne_send;
	पूर्ण

	अगर (cmd->state == NVMET_TCP_SEND_RESPONSE)
		ret = nvmet_try_send_response(cmd, last_in_batch);

करोne_send:
	अगर (ret < 0) अणु
		अगर (ret == -EAGAIN)
			वापस 0;
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_send(काष्ठा nvmet_tcp_queue *queue,
		पूर्णांक budget, पूर्णांक *sends)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < budget; i++) अणु
		ret = nvmet_tcp_try_send_one(queue, i == budget - 1);
		अगर (unlikely(ret < 0)) अणु
			nvmet_tcp_socket_error(queue, ret);
			जाओ करोne;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			अवरोध;
		पूर्ण
		(*sends)++;
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल व्योम nvmet_prepare_receive_pdu(काष्ठा nvmet_tcp_queue *queue)
अणु
	queue->offset = 0;
	queue->left = माप(काष्ठा nvme_tcp_hdr);
	queue->cmd = शून्य;
	queue->rcv_state = NVMET_TCP_RECV_PDU;
पूर्ण

अटल व्योम nvmet_tcp_मुक्त_crypto(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(queue->rcv_hash);

	ahash_request_मुक्त(queue->rcv_hash);
	ahash_request_मुक्त(queue->snd_hash);
	crypto_मुक्त_ahash(tfm);
पूर्ण

अटल पूर्णांक nvmet_tcp_alloc_crypto(काष्ठा nvmet_tcp_queue *queue)
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


अटल पूर्णांक nvmet_tcp_handle_icreq(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_icreq_pdu *icreq = &queue->pdu.icreq;
	काष्ठा nvme_tcp_icresp_pdu *icresp = &queue->pdu.icresp;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा kvec iov;
	पूर्णांक ret;

	अगर (le32_to_cpu(icreq->hdr.plen) != माप(काष्ठा nvme_tcp_icreq_pdu)) अणु
		pr_err("bad nvme-tcp pdu length (%d)\n",
			le32_to_cpu(icreq->hdr.plen));
		nvmet_tcp_fatal_error(queue);
	पूर्ण

	अगर (icreq->pfv != NVME_TCP_PFV_1_0) अणु
		pr_err("queue %d: bad pfv %d\n", queue->idx, icreq->pfv);
		वापस -EPROTO;
	पूर्ण

	अगर (icreq->hpda != 0) अणु
		pr_err("queue %d: unsupported hpda %d\n", queue->idx,
			icreq->hpda);
		वापस -EPROTO;
	पूर्ण

	queue->hdr_digest = !!(icreq->digest & NVME_TCP_HDR_DIGEST_ENABLE);
	queue->data_digest = !!(icreq->digest & NVME_TCP_DATA_DIGEST_ENABLE);
	अगर (queue->hdr_digest || queue->data_digest) अणु
		ret = nvmet_tcp_alloc_crypto(queue);
		अगर (ret)
			वापस ret;
	पूर्ण

	स_रखो(icresp, 0, माप(*icresp));
	icresp->hdr.type = nvme_tcp_icresp;
	icresp->hdr.hlen = माप(*icresp);
	icresp->hdr.pकरो = 0;
	icresp->hdr.plen = cpu_to_le32(icresp->hdr.hlen);
	icresp->pfv = cpu_to_le16(NVME_TCP_PFV_1_0);
	icresp->maxdata = cpu_to_le32(0x400000); /* 16M arbitrary limit */
	icresp->cpda = 0;
	अगर (queue->hdr_digest)
		icresp->digest |= NVME_TCP_HDR_DIGEST_ENABLE;
	अगर (queue->data_digest)
		icresp->digest |= NVME_TCP_DATA_DIGEST_ENABLE;

	iov.iov_base = icresp;
	iov.iov_len = माप(*icresp);
	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	अगर (ret < 0)
		जाओ मुक्त_crypto;

	queue->state = NVMET_TCP_Q_LIVE;
	nvmet_prepare_receive_pdu(queue);
	वापस 0;
मुक्त_crypto:
	अगर (queue->hdr_digest || queue->data_digest)
		nvmet_tcp_मुक्त_crypto(queue);
	वापस ret;
पूर्ण

अटल व्योम nvmet_tcp_handle_req_failure(काष्ठा nvmet_tcp_queue *queue,
		काष्ठा nvmet_tcp_cmd *cmd, काष्ठा nvmet_req *req)
अणु
	माप_प्रकार data_len = le32_to_cpu(req->cmd->common.dptr.sgl.length);
	पूर्णांक ret;

	अगर (!nvme_is_ग_लिखो(cmd->req.cmd) ||
	    data_len > cmd->req.port->अंतरभूत_data_size) अणु
		nvmet_prepare_receive_pdu(queue);
		वापस;
	पूर्ण

	ret = nvmet_tcp_map_data(cmd);
	अगर (unlikely(ret)) अणु
		pr_err("queue %d: failed to map data\n", queue->idx);
		nvmet_tcp_fatal_error(queue);
		वापस;
	पूर्ण

	queue->rcv_state = NVMET_TCP_RECV_DATA;
	nvmet_tcp_map_pdu_iovec(cmd);
	cmd->flags |= NVMET_TCP_F_INIT_FAILED;
पूर्ण

अटल पूर्णांक nvmet_tcp_handle_h2c_data_pdu(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_data_pdu *data = &queue->pdu.data;
	काष्ठा nvmet_tcp_cmd *cmd;

	अगर (likely(queue->nr_cmds))
		cmd = &queue->cmds[data->ttag];
	अन्यथा
		cmd = &queue->connect;

	अगर (le32_to_cpu(data->data_offset) != cmd->rbytes_करोne) अणु
		pr_err("ttag %u unexpected data offset %u (expected %u)\n",
			data->ttag, le32_to_cpu(data->data_offset),
			cmd->rbytes_करोne);
		/* FIXME: use path and transport errors */
		nvmet_req_complete(&cmd->req,
			NVME_SC_INVALID_FIELD | NVME_SC_DNR);
		वापस -EPROTO;
	पूर्ण

	cmd->pdu_len = le32_to_cpu(data->data_length);
	cmd->pdu_recv = 0;
	nvmet_tcp_map_pdu_iovec(cmd);
	queue->cmd = cmd;
	queue->rcv_state = NVMET_TCP_RECV_DATA;

	वापस 0;
पूर्ण

अटल पूर्णांक nvmet_tcp_करोne_recv_pdu(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_hdr *hdr = &queue->pdu.cmd.hdr;
	काष्ठा nvme_command *nvme_cmd = &queue->pdu.cmd.cmd;
	काष्ठा nvmet_req *req;
	पूर्णांक ret;

	अगर (unlikely(queue->state == NVMET_TCP_Q_CONNECTING)) अणु
		अगर (hdr->type != nvme_tcp_icreq) अणु
			pr_err("unexpected pdu type (%d) before icreq\n",
				hdr->type);
			nvmet_tcp_fatal_error(queue);
			वापस -EPROTO;
		पूर्ण
		वापस nvmet_tcp_handle_icreq(queue);
	पूर्ण

	अगर (hdr->type == nvme_tcp_h2c_data) अणु
		ret = nvmet_tcp_handle_h2c_data_pdu(queue);
		अगर (unlikely(ret))
			वापस ret;
		वापस 0;
	पूर्ण

	queue->cmd = nvmet_tcp_get_cmd(queue);
	अगर (unlikely(!queue->cmd)) अणु
		/* This should never happen */
		pr_err("queue %d: out of commands (%d) send_list_len: %d, opcode: %d",
			queue->idx, queue->nr_cmds, queue->send_list_len,
			nvme_cmd->common.opcode);
		nvmet_tcp_fatal_error(queue);
		वापस -ENOMEM;
	पूर्ण

	req = &queue->cmd->req;
	स_नकल(req->cmd, nvme_cmd, माप(*nvme_cmd));

	अगर (unlikely(!nvmet_req_init(req, &queue->nvme_cq,
			&queue->nvme_sq, &nvmet_tcp_ops))) अणु
		pr_err("failed cmd %p id %d opcode %d, data_len: %d\n",
			req->cmd, req->cmd->common.command_id,
			req->cmd->common.opcode,
			le32_to_cpu(req->cmd->common.dptr.sgl.length));

		nvmet_tcp_handle_req_failure(queue, queue->cmd, req);
		वापस 0;
	पूर्ण

	ret = nvmet_tcp_map_data(queue->cmd);
	अगर (unlikely(ret)) अणु
		pr_err("queue %d: failed to map data\n", queue->idx);
		अगर (nvmet_tcp_has_अंतरभूत_data(queue->cmd))
			nvmet_tcp_fatal_error(queue);
		अन्यथा
			nvmet_req_complete(req, ret);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (nvmet_tcp_need_data_in(queue->cmd)) अणु
		अगर (nvmet_tcp_has_अंतरभूत_data(queue->cmd)) अणु
			queue->rcv_state = NVMET_TCP_RECV_DATA;
			nvmet_tcp_map_pdu_iovec(queue->cmd);
			वापस 0;
		पूर्ण
		/* send back R2T */
		nvmet_tcp_queue_response(&queue->cmd->req);
		जाओ out;
	पूर्ण

	queue->cmd->req.execute(&queue->cmd->req);
out:
	nvmet_prepare_receive_pdu(queue);
	वापस ret;
पूर्ण

अटल स्थिर u8 nvme_tcp_pdu_sizes[] = अणु
	[nvme_tcp_icreq]	= माप(काष्ठा nvme_tcp_icreq_pdu),
	[nvme_tcp_cmd]		= माप(काष्ठा nvme_tcp_cmd_pdu),
	[nvme_tcp_h2c_data]	= माप(काष्ठा nvme_tcp_data_pdu),
पूर्ण;

अटल अंतरभूत u8 nvmet_tcp_pdu_size(u8 type)
अणु
	माप_प्रकार idx = type;

	वापस (idx < ARRAY_SIZE(nvme_tcp_pdu_sizes) &&
		nvme_tcp_pdu_sizes[idx]) ?
			nvme_tcp_pdu_sizes[idx] : 0;
पूर्ण

अटल अंतरभूत bool nvmet_tcp_pdu_valid(u8 type)
अणु
	चयन (type) अणु
	हाल nvme_tcp_icreq:
	हाल nvme_tcp_cmd:
	हाल nvme_tcp_h2c_data:
		/* fallthru */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_recv_pdu(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvme_tcp_hdr *hdr = &queue->pdu.cmd.hdr;
	पूर्णांक len;
	काष्ठा kvec iov;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT पूर्ण;

recv:
	iov.iov_base = (व्योम *)&queue->pdu + queue->offset;
	iov.iov_len = queue->left;
	len = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	अगर (unlikely(len < 0))
		वापस len;

	queue->offset += len;
	queue->left -= len;
	अगर (queue->left)
		वापस -EAGAIN;

	अगर (queue->offset == माप(काष्ठा nvme_tcp_hdr)) अणु
		u8 hdgst = nvmet_tcp_hdgst_len(queue);

		अगर (unlikely(!nvmet_tcp_pdu_valid(hdr->type))) अणु
			pr_err("unexpected pdu type %d\n", hdr->type);
			nvmet_tcp_fatal_error(queue);
			वापस -EIO;
		पूर्ण

		अगर (unlikely(hdr->hlen != nvmet_tcp_pdu_size(hdr->type))) अणु
			pr_err("pdu %d bad hlen %d\n", hdr->type, hdr->hlen);
			वापस -EIO;
		पूर्ण

		queue->left = hdr->hlen - queue->offset + hdgst;
		जाओ recv;
	पूर्ण

	अगर (queue->hdr_digest &&
	    nvmet_tcp_verअगरy_hdgst(queue, &queue->pdu, queue->offset)) अणु
		nvmet_tcp_fatal_error(queue); /* fatal */
		वापस -EPROTO;
	पूर्ण

	अगर (queue->data_digest &&
	    nvmet_tcp_check_ddgst(queue, &queue->pdu)) अणु
		nvmet_tcp_fatal_error(queue); /* fatal */
		वापस -EPROTO;
	पूर्ण

	वापस nvmet_tcp_करोne_recv_pdu(queue);
पूर्ण

अटल व्योम nvmet_tcp_prep_recv_ddgst(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	काष्ठा nvmet_tcp_queue *queue = cmd->queue;

	nvmet_tcp_recv_ddgst(queue->rcv_hash, cmd);
	queue->offset = 0;
	queue->left = NVME_TCP_DIGEST_LENGTH;
	queue->rcv_state = NVMET_TCP_RECV_DDGST;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_recv_data(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd  *cmd = queue->cmd;
	पूर्णांक ret;

	जबतक (msg_data_left(&cmd->recv_msg)) अणु
		ret = sock_recvmsg(cmd->queue->sock, &cmd->recv_msg,
			cmd->recv_msg.msg_flags);
		अगर (ret <= 0)
			वापस ret;

		cmd->pdu_recv += ret;
		cmd->rbytes_करोne += ret;
	पूर्ण

	nvmet_tcp_unmap_pdu_iovec(cmd);
	अगर (queue->data_digest) अणु
		nvmet_tcp_prep_recv_ddgst(cmd);
		वापस 0;
	पूर्ण

	अगर (cmd->rbytes_करोne == cmd->req.transfer_len)
		nvmet_tcp_execute_request(cmd);

	nvmet_prepare_receive_pdu(queue);
	वापस 0;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_recv_ddgst(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd *cmd = queue->cmd;
	पूर्णांक ret;
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT पूर्ण;
	काष्ठा kvec iov = अणु
		.iov_base = (व्योम *)&cmd->recv_ddgst + queue->offset,
		.iov_len = queue->left
	पूर्ण;

	ret = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	अगर (unlikely(ret < 0))
		वापस ret;

	queue->offset += ret;
	queue->left -= ret;
	अगर (queue->left)
		वापस -EAGAIN;

	अगर (queue->data_digest && cmd->exp_ddgst != cmd->recv_ddgst) अणु
		pr_err("queue %d: cmd %d pdu (%d) data digest error: recv %#x expected %#x\n",
			queue->idx, cmd->req.cmd->common.command_id,
			queue->pdu.cmd.hdr.type, le32_to_cpu(cmd->recv_ddgst),
			le32_to_cpu(cmd->exp_ddgst));
		nvmet_tcp_finish_cmd(cmd);
		nvmet_tcp_fatal_error(queue);
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	अगर (cmd->rbytes_करोne == cmd->req.transfer_len)
		nvmet_tcp_execute_request(cmd);

	ret = 0;
out:
	nvmet_prepare_receive_pdu(queue);
	वापस ret;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_recv_one(काष्ठा nvmet_tcp_queue *queue)
अणु
	पूर्णांक result = 0;

	अगर (unlikely(queue->rcv_state == NVMET_TCP_RECV_ERR))
		वापस 0;

	अगर (queue->rcv_state == NVMET_TCP_RECV_PDU) अणु
		result = nvmet_tcp_try_recv_pdu(queue);
		अगर (result != 0)
			जाओ करोne_recv;
	पूर्ण

	अगर (queue->rcv_state == NVMET_TCP_RECV_DATA) अणु
		result = nvmet_tcp_try_recv_data(queue);
		अगर (result != 0)
			जाओ करोne_recv;
	पूर्ण

	अगर (queue->rcv_state == NVMET_TCP_RECV_DDGST) अणु
		result = nvmet_tcp_try_recv_ddgst(queue);
		अगर (result != 0)
			जाओ करोne_recv;
	पूर्ण

करोne_recv:
	अगर (result < 0) अणु
		अगर (result == -EAGAIN)
			वापस 0;
		वापस result;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक nvmet_tcp_try_recv(काष्ठा nvmet_tcp_queue *queue,
		पूर्णांक budget, पूर्णांक *recvs)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < budget; i++) अणु
		ret = nvmet_tcp_try_recv_one(queue);
		अगर (unlikely(ret < 0)) अणु
			nvmet_tcp_socket_error(queue, ret);
			जाओ करोne;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			अवरोध;
		पूर्ण
		(*recvs)++;
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल व्योम nvmet_tcp_schedule_release_queue(काष्ठा nvmet_tcp_queue *queue)
अणु
	spin_lock(&queue->state_lock);
	अगर (queue->state != NVMET_TCP_Q_DISCONNECTING) अणु
		queue->state = NVMET_TCP_Q_DISCONNECTING;
		schedule_work(&queue->release_work);
	पूर्ण
	spin_unlock(&queue->state_lock);
पूर्ण

अटल अंतरभूत व्योम nvmet_tcp_arm_queue_deadline(काष्ठा nvmet_tcp_queue *queue)
अणु
	queue->poll_end = jअगरfies + usecs_to_jअगरfies(idle_poll_period_usecs);
पूर्ण

अटल bool nvmet_tcp_check_queue_deadline(काष्ठा nvmet_tcp_queue *queue,
		पूर्णांक ops)
अणु
	अगर (!idle_poll_period_usecs)
		वापस false;

	अगर (ops)
		nvmet_tcp_arm_queue_deadline(queue);

	वापस !समय_after(jअगरfies, queue->poll_end);
पूर्ण

अटल व्योम nvmet_tcp_io_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_tcp_queue *queue =
		container_of(w, काष्ठा nvmet_tcp_queue, io_work);
	bool pending;
	पूर्णांक ret, ops = 0;

	करो अणु
		pending = false;

		ret = nvmet_tcp_try_recv(queue, NVMET_TCP_RECV_BUDGET, &ops);
		अगर (ret > 0)
			pending = true;
		अन्यथा अगर (ret < 0)
			वापस;

		ret = nvmet_tcp_try_send(queue, NVMET_TCP_SEND_BUDGET, &ops);
		अगर (ret > 0)
			pending = true;
		अन्यथा अगर (ret < 0)
			वापस;

	पूर्ण जबतक (pending && ops < NVMET_TCP_IO_WORK_BUDGET);

	/*
	 * Requeue the worker अगर idle deadline period is in progress or any
	 * ops activity was recorded during the करो-जबतक loop above.
	 */
	अगर (nvmet_tcp_check_queue_deadline(queue, ops) || pending)
		queue_work_on(queue_cpu(queue), nvmet_tcp_wq, &queue->io_work);
पूर्ण

अटल पूर्णांक nvmet_tcp_alloc_cmd(काष्ठा nvmet_tcp_queue *queue,
		काष्ठा nvmet_tcp_cmd *c)
अणु
	u8 hdgst = nvmet_tcp_hdgst_len(queue);

	c->queue = queue;
	c->req.port = queue->port->nport;

	c->cmd_pdu = page_frag_alloc(&queue->pf_cache,
			माप(*c->cmd_pdu) + hdgst, GFP_KERNEL | __GFP_ZERO);
	अगर (!c->cmd_pdu)
		वापस -ENOMEM;
	c->req.cmd = &c->cmd_pdu->cmd;

	c->rsp_pdu = page_frag_alloc(&queue->pf_cache,
			माप(*c->rsp_pdu) + hdgst, GFP_KERNEL | __GFP_ZERO);
	अगर (!c->rsp_pdu)
		जाओ out_मुक्त_cmd;
	c->req.cqe = &c->rsp_pdu->cqe;

	c->data_pdu = page_frag_alloc(&queue->pf_cache,
			माप(*c->data_pdu) + hdgst, GFP_KERNEL | __GFP_ZERO);
	अगर (!c->data_pdu)
		जाओ out_मुक्त_rsp;

	c->r2t_pdu = page_frag_alloc(&queue->pf_cache,
			माप(*c->r2t_pdu) + hdgst, GFP_KERNEL | __GFP_ZERO);
	अगर (!c->r2t_pdu)
		जाओ out_मुक्त_data;

	c->recv_msg.msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL;

	list_add_tail(&c->entry, &queue->मुक्त_list);

	वापस 0;
out_मुक्त_data:
	page_frag_मुक्त(c->data_pdu);
out_मुक्त_rsp:
	page_frag_मुक्त(c->rsp_pdu);
out_मुक्त_cmd:
	page_frag_मुक्त(c->cmd_pdu);
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvmet_tcp_मुक्त_cmd(काष्ठा nvmet_tcp_cmd *c)
अणु
	page_frag_मुक्त(c->r2t_pdu);
	page_frag_मुक्त(c->data_pdu);
	page_frag_मुक्त(c->rsp_pdu);
	page_frag_मुक्त(c->cmd_pdu);
पूर्ण

अटल पूर्णांक nvmet_tcp_alloc_cmds(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd *cmds;
	पूर्णांक i, ret = -EINVAL, nr_cmds = queue->nr_cmds;

	cmds = kसुस्मृति(nr_cmds, माप(काष्ठा nvmet_tcp_cmd), GFP_KERNEL);
	अगर (!cmds)
		जाओ out;

	क्रम (i = 0; i < nr_cmds; i++) अणु
		ret = nvmet_tcp_alloc_cmd(queue, cmds + i);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	queue->cmds = cmds;

	वापस 0;
out_मुक्त:
	जबतक (--i >= 0)
		nvmet_tcp_मुक्त_cmd(cmds + i);
	kमुक्त(cmds);
out:
	वापस ret;
पूर्ण

अटल व्योम nvmet_tcp_मुक्त_cmds(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd *cmds = queue->cmds;
	पूर्णांक i;

	क्रम (i = 0; i < queue->nr_cmds; i++)
		nvmet_tcp_मुक्त_cmd(cmds + i);

	nvmet_tcp_मुक्त_cmd(&queue->connect);
	kमुक्त(cmds);
पूर्ण

अटल व्योम nvmet_tcp_restore_socket_callbacks(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा socket *sock = queue->sock;

	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_data_पढ़ोy =  queue->data_पढ़ोy;
	sock->sk->sk_state_change = queue->state_change;
	sock->sk->sk_ग_लिखो_space = queue->ग_लिखो_space;
	sock->sk->sk_user_data = शून्य;
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);
पूर्ण

अटल व्योम nvmet_tcp_finish_cmd(काष्ठा nvmet_tcp_cmd *cmd)
अणु
	nvmet_req_uninit(&cmd->req);
	nvmet_tcp_unmap_pdu_iovec(cmd);
	kमुक्त(cmd->iov);
	sgl_मुक्त(cmd->req.sg);
पूर्ण

अटल व्योम nvmet_tcp_uninit_data_in_cmds(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा nvmet_tcp_cmd *cmd = queue->cmds;
	पूर्णांक i;

	क्रम (i = 0; i < queue->nr_cmds; i++, cmd++) अणु
		अगर (nvmet_tcp_need_data_in(cmd))
			nvmet_tcp_finish_cmd(cmd);
	पूर्ण

	अगर (!queue->nr_cmds && nvmet_tcp_need_data_in(&queue->connect)) अणु
		/* failed in connect */
		nvmet_tcp_finish_cmd(&queue->connect);
	पूर्ण
पूर्ण

अटल व्योम nvmet_tcp_release_queue_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_tcp_queue *queue =
		container_of(w, काष्ठा nvmet_tcp_queue, release_work);

	mutex_lock(&nvmet_tcp_queue_mutex);
	list_del_init(&queue->queue_list);
	mutex_unlock(&nvmet_tcp_queue_mutex);

	nvmet_tcp_restore_socket_callbacks(queue);
	flush_work(&queue->io_work);

	nvmet_tcp_uninit_data_in_cmds(queue);
	nvmet_sq_destroy(&queue->nvme_sq);
	cancel_work_sync(&queue->io_work);
	sock_release(queue->sock);
	nvmet_tcp_मुक्त_cmds(queue);
	अगर (queue->hdr_digest || queue->data_digest)
		nvmet_tcp_मुक्त_crypto(queue);
	ida_simple_हटाओ(&nvmet_tcp_queue_ida, queue->idx);

	kमुक्त(queue);
पूर्ण

अटल व्योम nvmet_tcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा nvmet_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (likely(queue))
		queue_work_on(queue_cpu(queue), nvmet_tcp_wq, &queue->io_work);
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम nvmet_tcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा nvmet_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (unlikely(!queue))
		जाओ out;

	अगर (unlikely(queue->state == NVMET_TCP_Q_CONNECTING)) अणु
		queue->ग_लिखो_space(sk);
		जाओ out;
	पूर्ण

	अगर (sk_stream_is_ग_लिखोable(sk)) अणु
		clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		queue_work_on(queue_cpu(queue), nvmet_tcp_wq, &queue->io_work);
	पूर्ण
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम nvmet_tcp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा nvmet_tcp_queue *queue;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	अगर (!queue)
		जाओ करोne;

	चयन (sk->sk_state) अणु
	हाल TCP_FIN_WAIT1:
	हाल TCP_CLOSE_WAIT:
	हाल TCP_CLOSE:
		/* FALLTHRU */
		sk->sk_user_data = शून्य;
		nvmet_tcp_schedule_release_queue(queue);
		अवरोध;
	शेष:
		pr_warn("queue %d unhandled state %d\n",
			queue->idx, sk->sk_state);
	पूर्ण
करोne:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक nvmet_tcp_set_queue_sock(काष्ठा nvmet_tcp_queue *queue)
अणु
	काष्ठा socket *sock = queue->sock;
	काष्ठा inet_sock *inet = inet_sk(sock->sk);
	पूर्णांक ret;

	ret = kernel_माला_लोockname(sock,
		(काष्ठा sockaddr *)&queue->sockaddr);
	अगर (ret < 0)
		वापस ret;

	ret = kernel_getpeername(sock,
		(काष्ठा sockaddr *)&queue->sockaddr_peer);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Cleanup whatever is sitting in the TCP transmit queue on socket
	 * बंद. This is करोne to prevent stale data from being sent should
	 * the network connection be restored beक्रमe TCP बार out.
	 */
	sock_no_linger(sock->sk);

	अगर (so_priority > 0)
		sock_set_priority(sock->sk, so_priority);

	/* Set socket type of service */
	अगर (inet->rcv_tos > 0)
		ip_sock_set_tos(sock->sk, inet->rcv_tos);

	ret = 0;
	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);
	अगर (sock->sk->sk_state != TCP_ESTABLISHED) अणु
		/*
		 * If the socket is alपढ़ोy closing, करोn't even start
		 * consuming it
		 */
		ret = -ENOTCONN;
	पूर्ण अन्यथा अणु
		sock->sk->sk_user_data = queue;
		queue->data_पढ़ोy = sock->sk->sk_data_पढ़ोy;
		sock->sk->sk_data_पढ़ोy = nvmet_tcp_data_पढ़ोy;
		queue->state_change = sock->sk->sk_state_change;
		sock->sk->sk_state_change = nvmet_tcp_state_change;
		queue->ग_लिखो_space = sock->sk->sk_ग_लिखो_space;
		sock->sk->sk_ग_लिखो_space = nvmet_tcp_ग_लिखो_space;
		अगर (idle_poll_period_usecs)
			nvmet_tcp_arm_queue_deadline(queue);
		queue_work_on(queue_cpu(queue), nvmet_tcp_wq, &queue->io_work);
	पूर्ण
	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक nvmet_tcp_alloc_queue(काष्ठा nvmet_tcp_port *port,
		काष्ठा socket *newsock)
अणु
	काष्ठा nvmet_tcp_queue *queue;
	पूर्णांक ret;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस -ENOMEM;

	INIT_WORK(&queue->release_work, nvmet_tcp_release_queue_work);
	INIT_WORK(&queue->io_work, nvmet_tcp_io_work);
	queue->sock = newsock;
	queue->port = port;
	queue->nr_cmds = 0;
	spin_lock_init(&queue->state_lock);
	queue->state = NVMET_TCP_Q_CONNECTING;
	INIT_LIST_HEAD(&queue->मुक्त_list);
	init_llist_head(&queue->resp_list);
	INIT_LIST_HEAD(&queue->resp_send_list);

	queue->idx = ida_simple_get(&nvmet_tcp_queue_ida, 0, 0, GFP_KERNEL);
	अगर (queue->idx < 0) अणु
		ret = queue->idx;
		जाओ out_मुक्त_queue;
	पूर्ण

	ret = nvmet_tcp_alloc_cmd(queue, &queue->connect);
	अगर (ret)
		जाओ out_ida_हटाओ;

	ret = nvmet_sq_init(&queue->nvme_sq);
	अगर (ret)
		जाओ out_मुक्त_connect;

	nvmet_prepare_receive_pdu(queue);

	mutex_lock(&nvmet_tcp_queue_mutex);
	list_add_tail(&queue->queue_list, &nvmet_tcp_queue_list);
	mutex_unlock(&nvmet_tcp_queue_mutex);

	ret = nvmet_tcp_set_queue_sock(queue);
	अगर (ret)
		जाओ out_destroy_sq;

	वापस 0;
out_destroy_sq:
	mutex_lock(&nvmet_tcp_queue_mutex);
	list_del_init(&queue->queue_list);
	mutex_unlock(&nvmet_tcp_queue_mutex);
	nvmet_sq_destroy(&queue->nvme_sq);
out_मुक्त_connect:
	nvmet_tcp_मुक्त_cmd(&queue->connect);
out_ida_हटाओ:
	ida_simple_हटाओ(&nvmet_tcp_queue_ida, queue->idx);
out_मुक्त_queue:
	kमुक्त(queue);
	वापस ret;
पूर्ण

अटल व्योम nvmet_tcp_accept_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_tcp_port *port =
		container_of(w, काष्ठा nvmet_tcp_port, accept_work);
	काष्ठा socket *newsock;
	पूर्णांक ret;

	जबतक (true) अणु
		ret = kernel_accept(port->sock, &newsock, O_NONBLOCK);
		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				pr_warn("failed to accept err=%d\n", ret);
			वापस;
		पूर्ण
		ret = nvmet_tcp_alloc_queue(port, newsock);
		अगर (ret) अणु
			pr_err("failed to allocate queue\n");
			sock_release(newsock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nvmet_tcp_listen_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा nvmet_tcp_port *port;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	port = sk->sk_user_data;
	अगर (!port)
		जाओ out;

	अगर (sk->sk_state == TCP_LISTEN)
		schedule_work(&port->accept_work);
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक nvmet_tcp_add_port(काष्ठा nvmet_port *nport)
अणु
	काष्ठा nvmet_tcp_port *port;
	__kernel_sa_family_t af;
	पूर्णांक ret;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

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
		जाओ err_port;
	पूर्ण

	ret = inet_pton_with_scope(&init_net, af, nport->disc_addr.traddr,
			nport->disc_addr.trsvcid, &port->addr);
	अगर (ret) अणु
		pr_err("malformed ip/port passed: %s:%s\n",
			nport->disc_addr.traddr, nport->disc_addr.trsvcid);
		जाओ err_port;
	पूर्ण

	port->nport = nport;
	INIT_WORK(&port->accept_work, nvmet_tcp_accept_work);
	अगर (port->nport->अंतरभूत_data_size < 0)
		port->nport->अंतरभूत_data_size = NVMET_TCP_DEF_INLINE_DATA_SIZE;

	ret = sock_create(port->addr.ss_family, SOCK_STREAM,
				IPPROTO_TCP, &port->sock);
	अगर (ret) अणु
		pr_err("failed to create a socket\n");
		जाओ err_port;
	पूर्ण

	port->sock->sk->sk_user_data = port;
	port->data_पढ़ोy = port->sock->sk->sk_data_पढ़ोy;
	port->sock->sk->sk_data_पढ़ोy = nvmet_tcp_listen_data_पढ़ोy;
	sock_set_reuseaddr(port->sock->sk);
	tcp_sock_set_nodelay(port->sock->sk);
	अगर (so_priority > 0)
		sock_set_priority(port->sock->sk, so_priority);

	ret = kernel_bind(port->sock, (काष्ठा sockaddr *)&port->addr,
			माप(port->addr));
	अगर (ret) अणु
		pr_err("failed to bind port socket %d\n", ret);
		जाओ err_sock;
	पूर्ण

	ret = kernel_listen(port->sock, 128);
	अगर (ret) अणु
		pr_err("failed to listen %d on port sock\n", ret);
		जाओ err_sock;
	पूर्ण

	nport->priv = port;
	pr_info("enabling port %d (%pISpc)\n",
		le16_to_cpu(nport->disc_addr.portid), &port->addr);

	वापस 0;

err_sock:
	sock_release(port->sock);
err_port:
	kमुक्त(port);
	वापस ret;
पूर्ण

अटल व्योम nvmet_tcp_हटाओ_port(काष्ठा nvmet_port *nport)
अणु
	काष्ठा nvmet_tcp_port *port = nport->priv;

	ग_लिखो_lock_bh(&port->sock->sk->sk_callback_lock);
	port->sock->sk->sk_data_पढ़ोy = port->data_पढ़ोy;
	port->sock->sk->sk_user_data = शून्य;
	ग_लिखो_unlock_bh(&port->sock->sk->sk_callback_lock);
	cancel_work_sync(&port->accept_work);

	sock_release(port->sock);
	kमुक्त(port);
पूर्ण

अटल व्योम nvmet_tcp_delete_ctrl(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा nvmet_tcp_queue *queue;

	mutex_lock(&nvmet_tcp_queue_mutex);
	list_क्रम_each_entry(queue, &nvmet_tcp_queue_list, queue_list)
		अगर (queue->nvme_sq.ctrl == ctrl)
			kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
	mutex_unlock(&nvmet_tcp_queue_mutex);
पूर्ण

अटल u16 nvmet_tcp_install_queue(काष्ठा nvmet_sq *sq)
अणु
	काष्ठा nvmet_tcp_queue *queue =
		container_of(sq, काष्ठा nvmet_tcp_queue, nvme_sq);

	अगर (sq->qid == 0) अणु
		/* Let inflight controller tearकरोwn complete */
		flush_scheduled_work();
	पूर्ण

	queue->nr_cmds = sq->size * 2;
	अगर (nvmet_tcp_alloc_cmds(queue))
		वापस NVME_SC_INTERNAL;
	वापस 0;
पूर्ण

अटल व्योम nvmet_tcp_disc_port_addr(काष्ठा nvmet_req *req,
		काष्ठा nvmet_port *nport, अक्षर *traddr)
अणु
	काष्ठा nvmet_tcp_port *port = nport->priv;

	अगर (inet_addr_is_any((काष्ठा sockaddr *)&port->addr)) अणु
		काष्ठा nvmet_tcp_cmd *cmd =
			container_of(req, काष्ठा nvmet_tcp_cmd, req);
		काष्ठा nvmet_tcp_queue *queue = cmd->queue;

		प्र_लिखो(traddr, "%pISc", (काष्ठा sockaddr *)&queue->sockaddr);
	पूर्ण अन्यथा अणु
		स_नकल(traddr, nport->disc_addr.traddr, NVMF_TRADDR_SIZE);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvmet_fabrics_ops nvmet_tcp_ops = अणु
	.owner			= THIS_MODULE,
	.type			= NVMF_TRTYPE_TCP,
	.msdbd			= 1,
	.add_port		= nvmet_tcp_add_port,
	.हटाओ_port		= nvmet_tcp_हटाओ_port,
	.queue_response		= nvmet_tcp_queue_response,
	.delete_ctrl		= nvmet_tcp_delete_ctrl,
	.install_queue		= nvmet_tcp_install_queue,
	.disc_traddr		= nvmet_tcp_disc_port_addr,
पूर्ण;

अटल पूर्णांक __init nvmet_tcp_init(व्योम)
अणु
	पूर्णांक ret;

	nvmet_tcp_wq = alloc_workqueue("nvmet_tcp_wq", WQ_HIGHPRI, 0);
	अगर (!nvmet_tcp_wq)
		वापस -ENOMEM;

	ret = nvmet_रेजिस्टर_transport(&nvmet_tcp_ops);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	destroy_workqueue(nvmet_tcp_wq);
	वापस ret;
पूर्ण

अटल व्योम __निकास nvmet_tcp_निकास(व्योम)
अणु
	काष्ठा nvmet_tcp_queue *queue;

	nvmet_unरेजिस्टर_transport(&nvmet_tcp_ops);

	flush_scheduled_work();
	mutex_lock(&nvmet_tcp_queue_mutex);
	list_क्रम_each_entry(queue, &nvmet_tcp_queue_list, queue_list)
		kernel_sock_shutकरोwn(queue->sock, SHUT_RDWR);
	mutex_unlock(&nvmet_tcp_queue_mutex);
	flush_scheduled_work();

	destroy_workqueue(nvmet_tcp_wq);
पूर्ण

module_init(nvmet_tcp_init);
module_निकास(nvmet_tcp_निकास);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("nvmet-transport-3"); /* 3 == NVMF_TRTYPE_TCP */
