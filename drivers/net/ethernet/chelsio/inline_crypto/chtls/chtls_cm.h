<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2018 Chelsio Communications, Inc.
 */

#अगर_अघोषित __CHTLS_CM_H__
#घोषणा __CHTLS_CM_H__

/*
 * TCB settings
 */
/* 3:0 */
#घोषणा TCB_ULP_TYPE_W    0
#घोषणा TCB_ULP_TYPE_S    0
#घोषणा TCB_ULP_TYPE_M    0xfULL
#घोषणा TCB_ULP_TYPE_V(x) ((x) << TCB_ULP_TYPE_S)

/* 11:4 */
#घोषणा TCB_ULP_RAW_W    0
#घोषणा TCB_ULP_RAW_S    4
#घोषणा TCB_ULP_RAW_M    0xffULL
#घोषणा TCB_ULP_RAW_V(x) ((x) << TCB_ULP_RAW_S)

#घोषणा TF_TLS_KEY_SIZE_S    7
#घोषणा TF_TLS_KEY_SIZE_V(x) ((x) << TF_TLS_KEY_SIZE_S)

#घोषणा TF_TLS_CONTROL_S     2
#घोषणा TF_TLS_CONTROL_V(x) ((x) << TF_TLS_CONTROL_S)

#घोषणा TF_TLS_ACTIVE_S      1
#घोषणा TF_TLS_ACTIVE_V(x) ((x) << TF_TLS_ACTIVE_S)

#घोषणा TF_TLS_ENABLE_S      0
#घोषणा TF_TLS_ENABLE_V(x) ((x) << TF_TLS_ENABLE_S)

#घोषणा TF_RX_QUIESCE_S    15
#घोषणा TF_RX_QUIESCE_V(x) ((x) << TF_RX_QUIESCE_S)

/*
 * Max receive winकरोw supported by HW in bytes.  Only a small part of it can
 * be set through option0, the rest needs to be set through RX_DATA_ACK.
 */
#घोषणा MAX_RCV_WND ((1U << 27) - 1)
#घोषणा MAX_MSS     65536

/*
 * Min receive winकरोw.  We want it to be large enough to accommodate receive
 * coalescing, handle jumbo frames, and not trigger sender SWS aव्योमance.
 */
#घोषणा MIN_RCV_WND (24 * 1024U)
#घोषणा LOOPBACK(x)     (((x) & htonl(0xff000000)) == htonl(0x7f000000))

/* क्रम TX: a skb must have a headroom of at least TX_HEADER_LEN bytes */
#घोषणा TX_HEADER_LEN \
	(माप(काष्ठा fw_ofld_tx_data_wr) + माप(काष्ठा sge_opaque_hdr))
#घोषणा TX_TLSHDR_LEN \
	(माप(काष्ठा fw_tlstx_data_wr) + माप(काष्ठा cpl_tx_tls_sfo) + \
	 माप(काष्ठा sge_opaque_hdr))
#घोषणा TXDATA_SKB_LEN 128

क्रमागत अणु
	CPL_TX_TLS_SFO_TYPE_CCS,
	CPL_TX_TLS_SFO_TYPE_ALERT,
	CPL_TX_TLS_SFO_TYPE_HANDSHAKE,
	CPL_TX_TLS_SFO_TYPE_DATA,
	CPL_TX_TLS_SFO_TYPE_HEARTBEAT,
पूर्ण;

क्रमागत अणु
	TLS_HDR_TYPE_CCS = 20,
	TLS_HDR_TYPE_ALERT,
	TLS_HDR_TYPE_HANDSHAKE,
	TLS_HDR_TYPE_RECORD,
	TLS_HDR_TYPE_HEARTBEAT,
पूर्ण;

प्रकार व्योम (*defer_handler_t)(काष्ठा chtls_dev *dev, काष्ठा sk_buff *skb);
बाह्य काष्ठा request_sock_ops chtls_rsk_ops;
बाह्य काष्ठा request_sock_ops chtls_rsk_opsv6;

काष्ठा deferred_skb_cb अणु
	defer_handler_t handler;
	काष्ठा chtls_dev *dev;
पूर्ण;

#घोषणा DEFERRED_SKB_CB(skb) ((काष्ठा deferred_skb_cb *)(skb)->cb)
#घोषणा failover_flowc_wr_len दुरत्व(काष्ठा fw_flowc_wr, mnemval[3])
#घोषणा WR_SKB_CB(skb) ((काष्ठा wr_skb_cb *)(skb)->cb)
#घोषणा ACCEPT_QUEUE(sk) (&inet_csk(sk)->icsk_accept_queue.rskq_accept_head)

#घोषणा SND_WSCALE(tp) ((tp)->rx_opt.snd_wscale)
#घोषणा RCV_WSCALE(tp) ((tp)->rx_opt.rcv_wscale)
#घोषणा USER_MSS(tp) ((tp)->rx_opt.user_mss)
#घोषणा TS_RECENT_STAMP(tp) ((tp)->rx_opt.ts_recent_stamp)
#घोषणा WSCALE_OK(tp) ((tp)->rx_opt.wscale_ok)
#घोषणा TSTAMP_OK(tp) ((tp)->rx_opt.tstamp_ok)
#घोषणा SACK_OK(tp) ((tp)->rx_opt.sack_ok)
#घोषणा INC_ORPHAN_COUNT(sk) percpu_counter_inc((sk)->sk_prot->orphan_count)

/* TLS SKB */
#घोषणा skb_ulp_tls_अंतरभूत(skb)      (ULP_SKB_CB(skb)->ulp.tls.ofld)
#घोषणा skb_ulp_tls_iv_imm(skb)      (ULP_SKB_CB(skb)->ulp.tls.iv)

व्योम chtls_defer_reply(काष्ठा sk_buff *skb, काष्ठा chtls_dev *dev,
		       defer_handler_t handler);

/*
 * Returns true अगर the socket is in one of the supplied states.
 */
अटल अंतरभूत अचिन्हित पूर्णांक sk_in_state(स्थिर काष्ठा sock *sk,
				       अचिन्हित पूर्णांक states)
अणु
	वापस states & (1 << sk->sk_state);
पूर्ण

अटल व्योम chtls_rsk_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	/* करो nothing */
पूर्ण

अटल अंतरभूत व्योम chtls_init_rsk_ops(काष्ठा proto *chtls_tcp_prot,
				      काष्ठा request_sock_ops *chtls_tcp_ops,
				      काष्ठा proto *tcp_prot, पूर्णांक family)
अणु
	स_रखो(chtls_tcp_ops, 0, माप(*chtls_tcp_ops));
	chtls_tcp_ops->family = family;
	chtls_tcp_ops->obj_size = माप(काष्ठा tcp_request_sock);
	chtls_tcp_ops->deकाष्ठाor = chtls_rsk_deकाष्ठाor;
	chtls_tcp_ops->slab = tcp_prot->rsk_prot->slab;
	chtls_tcp_prot->rsk_prot = chtls_tcp_ops;
पूर्ण

अटल अंतरभूत व्योम chtls_reqsk_मुक्त(काष्ठा request_sock *req)
अणु
	अगर (req->rsk_listener)
		sock_put(req->rsk_listener);
	kmem_cache_मुक्त(req->rsk_ops->slab, req);
पूर्ण

#घोषणा DECLARE_TASK_FUNC(task, task_param) \
		अटल व्योम task(काष्ठा work_काष्ठा *task_param)

अटल अंतरभूत व्योम sk_wakeup_sleepers(काष्ठा sock *sk, bool पूर्णांकerruptable)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq)) अणु
		अगर (पूर्णांकerruptable)
			wake_up_पूर्णांकerruptible(sk_sleep(sk));
		अन्यथा
			wake_up_all(sk_sleep(sk));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम chtls_set_req_port(काष्ठा request_sock *oreq,
				      __be16 source, __be16 dest)
अणु
	inet_rsk(oreq)->ir_rmt_port = source;
	inet_rsk(oreq)->ir_num = ntohs(dest);
पूर्ण

अटल अंतरभूत व्योम chtls_set_req_addr(काष्ठा request_sock *oreq,
				      __be32 local_ip, __be32 peer_ip)
अणु
	inet_rsk(oreq)->ir_loc_addr = local_ip;
	inet_rsk(oreq)->ir_rmt_addr = peer_ip;
पूर्ण

अटल अंतरभूत व्योम chtls_मुक्त_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_dst_set(skb, शून्य);
	__skb_unlink(skb, &sk->sk_receive_queue);
	__kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत व्योम chtls_kमुक्त_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_dst_set(skb, शून्य);
	__skb_unlink(skb, &sk->sk_receive_queue);
	kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत व्योम chtls_reset_wr_list(काष्ठा chtls_sock *csk)
अणु
	csk->wr_skb_head = शून्य;
	csk->wr_skb_tail = शून्य;
पूर्ण

अटल अंतरभूत व्योम enqueue_wr(काष्ठा chtls_sock *csk, काष्ठा sk_buff *skb)
अणु
	WR_SKB_CB(skb)->next_wr = शून्य;

	skb_get(skb);

	अगर (!csk->wr_skb_head)
		csk->wr_skb_head = skb;
	अन्यथा
		WR_SKB_CB(csk->wr_skb_tail)->next_wr = skb;
	csk->wr_skb_tail = skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *dequeue_wr(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा sk_buff *skb = शून्य;

	skb = csk->wr_skb_head;

	अगर (likely(skb)) अणु
	 /* Don't bother clearing the tail */
		csk->wr_skb_head = WR_SKB_CB(skb)->next_wr;
		WR_SKB_CB(skb)->next_wr = शून्य;
	पूर्ण
	वापस skb;
पूर्ण
#पूर्ण_अगर
