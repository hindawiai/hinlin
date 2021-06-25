<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018 Chelsio Communications, Inc.
 *
 * Written by: Atul Gupta (atul.gupta@chelsio.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp.h>
#समावेश <net/dst.h>
#समावेश <net/tls.h>
#समावेश <net/addrconf.h>
#समावेश <net/secure_seq.h>

#समावेश "chtls.h"
#समावेश "chtls_cm.h"
#समावेश "clip_tbl.h"
#समावेश "t4_tcb.h"

/*
 * State transitions and actions क्रम बंद.  Note that अगर we are in SYN_SENT
 * we reमुख्य in that state as we cannot control a connection जबतक it's in
 * SYN_SENT; such connections are allowed to establish and are then पातed.
 */
अटल अचिन्हित अक्षर new_state[16] = अणु
	/* current state:     new state:      action: */
	/* (Invalid)       */ TCP_CLOSE,
	/* TCP_ESTABLISHED */ TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	/* TCP_SYN_SENT    */ TCP_SYN_SENT,
	/* TCP_SYN_RECV    */ TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	/* TCP_FIN_WAIT1   */ TCP_FIN_WAIT1,
	/* TCP_FIN_WAIT2   */ TCP_FIN_WAIT2,
	/* TCP_TIME_WAIT   */ TCP_CLOSE,
	/* TCP_CLOSE       */ TCP_CLOSE,
	/* TCP_CLOSE_WAIT  */ TCP_LAST_ACK | TCP_ACTION_FIN,
	/* TCP_LAST_ACK    */ TCP_LAST_ACK,
	/* TCP_LISTEN      */ TCP_CLOSE,
	/* TCP_CLOSING     */ TCP_CLOSING,
पूर्ण;

अटल काष्ठा chtls_sock *chtls_sock_create(काष्ठा chtls_dev *cdev)
अणु
	काष्ठा chtls_sock *csk = kzalloc(माप(*csk), GFP_ATOMIC);

	अगर (!csk)
		वापस शून्य;

	csk->txdata_skb_cache = alloc_skb(TXDATA_SKB_LEN, GFP_ATOMIC);
	अगर (!csk->txdata_skb_cache) अणु
		kमुक्त(csk);
		वापस शून्य;
	पूर्ण

	kref_init(&csk->kref);
	csk->cdev = cdev;
	skb_queue_head_init(&csk->txq);
	csk->wr_skb_head = शून्य;
	csk->wr_skb_tail = शून्य;
	csk->mss = MAX_MSS;
	csk->tlshws.ofld = 1;
	csk->tlshws.txkey = -1;
	csk->tlshws.rxkey = -1;
	csk->tlshws.mfs = TLS_MFS;
	skb_queue_head_init(&csk->tlshws.sk_recv_queue);
	वापस csk;
पूर्ण

अटल व्योम chtls_sock_release(काष्ठा kref *ref)
अणु
	काष्ठा chtls_sock *csk =
		container_of(ref, काष्ठा chtls_sock, kref);

	kमुक्त(csk);
पूर्ण

अटल काष्ठा net_device *chtls_find_netdev(काष्ठा chtls_dev *cdev,
					    काष्ठा sock *sk)
अणु
	काष्ठा adapter *adap = pci_get_drvdata(cdev->pdev);
	काष्ठा net_device *ndev = cdev->ports[0];
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा net_device *temp;
	पूर्णांक addr_type;
#पूर्ण_अगर
	पूर्णांक i;

	चयन (sk->sk_family) अणु
	हाल PF_INET:
		अगर (likely(!inet_sk(sk)->inet_rcv_saddr))
			वापस ndev;
		ndev = __ip_dev_find(&init_net, inet_sk(sk)->inet_rcv_saddr, false);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		addr_type = ipv6_addr_type(&sk->sk_v6_rcv_saddr);
		अगर (likely(addr_type == IPV6_ADDR_ANY))
			वापस ndev;

		क्रम_each_netdev_rcu(&init_net, temp) अणु
			अगर (ipv6_chk_addr(&init_net, (काष्ठा in6_addr *)
					  &sk->sk_v6_rcv_saddr, temp, 1)) अणु
				ndev = temp;
				अवरोध;
			पूर्ण
		पूर्ण
	अवरोध;
#पूर्ण_अगर
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (!ndev)
		वापस शून्य;

	अगर (is_vlan_dev(ndev))
		ndev = vlan_dev_real_dev(ndev);

	क्रम_each_port(adap, i)
		अगर (cdev->ports[i] == ndev)
			वापस ndev;
	वापस शून्य;
पूर्ण

अटल व्योम assign_rxopt(काष्ठा sock *sk, अचिन्हित पूर्णांक opt)
अणु
	स्थिर काष्ठा chtls_dev *cdev;
	काष्ठा chtls_sock *csk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);

	cdev = csk->cdev;
	tp->tcp_header_len           = माप(काष्ठा tcphdr);
	tp->rx_opt.mss_clamp         = cdev->mtus[TCPOPT_MSS_G(opt)] - 40;
	tp->mss_cache                = tp->rx_opt.mss_clamp;
	tp->rx_opt.tstamp_ok         = TCPOPT_TSTAMP_G(opt);
	tp->rx_opt.snd_wscale        = TCPOPT_SACK_G(opt);
	tp->rx_opt.wscale_ok         = TCPOPT_WSCALE_OK_G(opt);
	SND_WSCALE(tp)               = TCPOPT_SND_WSCALE_G(opt);
	अगर (!tp->rx_opt.wscale_ok)
		tp->rx_opt.rcv_wscale = 0;
	अगर (tp->rx_opt.tstamp_ok) अणु
		tp->tcp_header_len += TCPOLEN_TSTAMP_ALIGNED;
		tp->rx_opt.mss_clamp -= TCPOLEN_TSTAMP_ALIGNED;
	पूर्ण अन्यथा अगर (csk->opt2 & TSTAMPS_EN_F) अणु
		csk->opt2 &= ~TSTAMPS_EN_F;
		csk->mtu_idx = TCPOPT_MSS_G(opt);
	पूर्ण
पूर्ण

अटल व्योम chtls_purge_receive_queue(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		skb_dst_set(skb, (व्योम *)शून्य);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम chtls_purge_ग_लिखो_queue(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&csk->txq))) अणु
		sk->sk_wmem_queued -= skb->truesize;
		__kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम chtls_purge_recv_queue(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_hws *tlsk = &csk->tlshws;
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&tlsk->sk_recv_queue)) != शून्य) अणु
		skb_dst_set(skb, शून्य);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम पात_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req *req = cplhdr(skb);
	काष्ठा chtls_dev *cdev;

	cdev = (काष्ठा chtls_dev *)handle;
	req->cmd = CPL_ABORT_NO_RST;
	cxgb4_ofld_send(cdev->lldi->ports[0], skb);
पूर्ण

अटल काष्ठा sk_buff *alloc_ctrl_skb(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	अगर (likely(skb && !skb_shared(skb) && !skb_cloned(skb))) अणु
		__skb_trim(skb, 0);
		refcount_inc(&skb->users);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(len, GFP_KERNEL | __GFP_NOFAIL);
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम chtls_send_पात(काष्ठा sock *sk, पूर्णांक mode, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req *req;
	काष्ठा chtls_sock *csk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);

	अगर (!skb)
		skb = alloc_ctrl_skb(csk->txdata_skb_cache, माप(*req));

	req = (काष्ठा cpl_पात_req *)skb_put(skb, माप(*req));
	INIT_TP_WR_CPL(req, CPL_ABORT_REQ, csk->tid);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPL_PRIORITY_DATA);
	req->rsvd0 = htonl(tp->snd_nxt);
	req->rsvd1 = !csk_flag_nochk(csk, CSK_TX_DATA_SENT);
	req->cmd = mode;
	t4_set_arp_err_handler(skb, csk->cdev, पात_arp_failure);
	send_or_defer(sk, tp, skb, mode == CPL_ABORT_SEND_RST);
पूर्ण

अटल व्योम chtls_send_reset(काष्ठा sock *sk, पूर्णांक mode, काष्ठा sk_buff *skb)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	अगर (unlikely(csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN) ||
		     !csk->cdev)) अणु
		अगर (sk->sk_state == TCP_SYN_RECV)
			csk_set_flag(csk, CSK_RST_ABORTED);
		जाओ out;
	पूर्ण

	अगर (!csk_flag_nochk(csk, CSK_TX_DATA_SENT)) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);

		अगर (send_tx_flowc_wr(sk, 0, tp->snd_nxt, tp->rcv_nxt) < 0)
			WARN_ONCE(1, "send tx flowc error");
		csk_set_flag(csk, CSK_TX_DATA_SENT);
	पूर्ण

	csk_set_flag(csk, CSK_ABORT_RPL_PENDING);
	chtls_purge_ग_लिखो_queue(sk);

	csk_set_flag(csk, CSK_ABORT_SHUTDOWN);
	अगर (sk->sk_state != TCP_SYN_RECV)
		chtls_send_पात(sk, mode, skb);
	अन्यथा
		chtls_set_tcb_field_rpl_skb(sk, TCB_T_FLAGS_W,
					    TCB_T_FLAGS_V(TCB_T_FLAGS_M), 0,
					    TCB_FIELD_COOKIE_TFLAG, 1);

	वापस;
out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम release_tcp_port(काष्ठा sock *sk)
अणु
	अगर (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);
पूर्ण

अटल व्योम tcp_uncork(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tp->nonagle & TCP_NAGLE_CORK) अणु
		tp->nonagle &= ~TCP_NAGLE_CORK;
		chtls_tcp_push(sk, 0);
	पूर्ण
पूर्ण

अटल व्योम chtls_बंद_conn(काष्ठा sock *sk)
अणु
	काष्ठा cpl_बंद_con_req *req;
	काष्ठा chtls_sock *csk;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक tid;
	अचिन्हित पूर्णांक len;

	len = roundup(माप(काष्ठा cpl_बंद_con_req), 16);
	csk = rcu_dereference_sk_user_data(sk);
	tid = csk->tid;

	skb = alloc_skb(len, GFP_KERNEL | __GFP_NOFAIL);
	req = (काष्ठा cpl_बंद_con_req *)__skb_put(skb, len);
	स_रखो(req, 0, len);
	req->wr.wr_hi = htonl(FW_WR_OP_V(FW_TP_WR) |
			      FW_WR_IMMDLEN_V(माप(*req) -
					      माप(req->wr)));
	req->wr.wr_mid = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(माप(*req), 16)) |
			       FW_WR_FLOWID_V(tid));

	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, tid));

	tcp_uncork(sk);
	skb_entail(sk, skb, ULPCB_FLAG_NO_HDR | ULPCB_FLAG_NO_APPEND);
	अगर (sk->sk_state != TCP_SYN_SENT)
		chtls_push_frames(csk, 1);
पूर्ण

/*
 * Perक्रमm a state transition during बंद and वापस the actions indicated
 * क्रम the transition.  Do not make this function अंतरभूत, the मुख्य reason
 * it exists at all is to aव्योम multiple inlining of tcp_set_state.
 */
अटल पूर्णांक make_बंद_transition(काष्ठा sock *sk)
अणु
	पूर्णांक next = (पूर्णांक)new_state[sk->sk_state];

	tcp_set_state(sk, next & TCP_STATE_MASK);
	वापस next & TCP_ACTION_FIN;
पूर्ण

व्योम chtls_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	पूर्णांक data_lost, prev_state;
	काष्ठा chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(sk);

	lock_sock(sk);
	sk->sk_shutकरोwn |= SHUTDOWN_MASK;

	data_lost = skb_queue_len(&sk->sk_receive_queue);
	data_lost |= skb_queue_len(&csk->tlshws.sk_recv_queue);
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);

	अगर (sk->sk_state == TCP_CLOSE) अणु
		जाओ रुको;
	पूर्ण अन्यथा अगर (data_lost || sk->sk_state == TCP_SYN_SENT) अणु
		chtls_send_reset(sk, CPL_ABORT_SEND_RST, शून्य);
		release_tcp_port(sk);
		जाओ unlock;
	पूर्ण अन्यथा अगर (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingerसमय) अणु
		sk->sk_prot->disconnect(sk, 0);
	पूर्ण अन्यथा अगर (make_बंद_transition(sk)) अणु
		chtls_बंद_conn(sk);
	पूर्ण
रुको:
	अगर (समयout)
		sk_stream_रुको_बंद(sk, समयout);

unlock:
	prev_state = sk->sk_state;
	sock_hold(sk);
	sock_orphan(sk);

	release_sock(sk);

	local_bh_disable();
	bh_lock_sock(sk);

	अगर (prev_state != TCP_CLOSE && sk->sk_state == TCP_CLOSE)
		जाओ out;

	अगर (sk->sk_state == TCP_FIN_WAIT2 && tcp_sk(sk)->linger2 < 0 &&
	    !csk_flag(sk, CSK_ABORT_SHUTDOWN)) अणु
		काष्ठा sk_buff *skb;

		skb = alloc_skb(माप(काष्ठा cpl_पात_req), GFP_ATOMIC);
		अगर (skb)
			chtls_send_reset(sk, CPL_ABORT_SEND_RST, skb);
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE)
		inet_csk_destroy_sock(sk);

out:
	bh_unlock_sock(sk);
	local_bh_enable();
	sock_put(sk);
पूर्ण

/*
 * Wait until a socket enters on of the given states.
 */
अटल पूर्णांक रुको_क्रम_states(काष्ठा sock *sk, अचिन्हित पूर्णांक states)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा socket_wq _sk_wq;
	दीर्घ current_समयo;
	पूर्णांक err = 0;

	current_समयo = 200;

	/*
	 * We want this to work even when there's no associated काष्ठा socket.
	 * In that हाल we provide a temporary रुको_queue_head_t.
	 */
	अगर (!sk->sk_wq) अणु
		init_रुकोqueue_head(&_sk_wq.रुको);
		_sk_wq.fasync_list = शून्य;
		init_rcu_head_on_stack(&_sk_wq.rcu);
		RCU_INIT_POINTER(sk->sk_wq, &_sk_wq);
	पूर्ण

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (!sk_in_state(sk, states)) अणु
		अगर (!current_समयo) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(current_समयo);
			अवरोध;
		पूर्ण
		set_current_state(TASK_UNINTERRUPTIBLE);
		release_sock(sk);
		अगर (!sk_in_state(sk, states))
			current_समयo = schedule_समयout(current_समयo);
		__set_current_state(TASK_RUNNING);
		lock_sock(sk);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (rcu_dereference(sk->sk_wq) == &_sk_wq)
		sk->sk_wq = शून्य;
	वापस err;
पूर्ण

पूर्णांक chtls_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा tcp_sock *tp;
	पूर्णांक err;

	tp = tcp_sk(sk);
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);
	chtls_purge_ग_लिखो_queue(sk);

	अगर (sk->sk_state != TCP_CLOSE) अणु
		sk->sk_err = ECONNRESET;
		chtls_send_reset(sk, CPL_ABORT_SEND_RST, शून्य);
		err = रुको_क्रम_states(sk, TCPF_CLOSE);
		अगर (err)
			वापस err;
	पूर्ण
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);
	tp->max_winकरोw = 0xFFFF << (tp->rx_opt.snd_wscale);
	वापस tcp_disconnect(sk, flags);
पूर्ण

#घोषणा SHUTDOWN_ELIGIBLE_STATE (TCPF_ESTABLISHED | \
				 TCPF_SYN_RECV | TCPF_CLOSE_WAIT)
व्योम chtls_shutकरोwn(काष्ठा sock *sk, पूर्णांक how)
अणु
	अगर ((how & SEND_SHUTDOWN) &&
	    sk_in_state(sk, SHUTDOWN_ELIGIBLE_STATE) &&
	    make_बंद_transition(sk))
		chtls_बंद_conn(sk);
पूर्ण

व्योम chtls_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(sk);
	chtls_purge_recv_queue(sk);
	csk->ulp_mode = ULP_MODE_NONE;
	chtls_purge_ग_लिखो_queue(sk);
	मुक्त_tls_keyid(sk);
	kref_put(&csk->kref, chtls_sock_release);
	अगर (sk->sk_family == AF_INET)
		sk->sk_prot = &tcp_prot;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		sk->sk_prot = &tcpv6_prot;
#पूर्ण_अगर
	sk->sk_prot->destroy(sk);
पूर्ण

अटल व्योम reset_listen_child(काष्ठा sock *child)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(child);
	काष्ठा sk_buff *skb;

	skb = alloc_ctrl_skb(csk->txdata_skb_cache,
			     माप(काष्ठा cpl_पात_req));

	chtls_send_reset(child, CPL_ABORT_SEND_RST, skb);
	sock_orphan(child);
	INC_ORPHAN_COUNT(child);
	अगर (child->sk_state == TCP_CLOSE)
		inet_csk_destroy_sock(child);
पूर्ण

अटल व्योम chtls_disconnect_acceptq(काष्ठा sock *listen_sk)
अणु
	काष्ठा request_sock **pprev;

	pprev = ACCEPT_QUEUE(listen_sk);
	जबतक (*pprev) अणु
		काष्ठा request_sock *req = *pprev;

		अगर (req->rsk_ops == &chtls_rsk_ops ||
		    req->rsk_ops == &chtls_rsk_opsv6) अणु
			काष्ठा sock *child = req->sk;

			*pprev = req->dl_next;
			sk_acceptq_हटाओd(listen_sk);
			reqsk_put(req);
			sock_hold(child);
			local_bh_disable();
			bh_lock_sock(child);
			release_tcp_port(child);
			reset_listen_child(child);
			bh_unlock_sock(child);
			local_bh_enable();
			sock_put(child);
		पूर्ण अन्यथा अणु
			pprev = &req->dl_next;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक listen_hashfn(स्थिर काष्ठा sock *sk)
अणु
	वापस ((अचिन्हित दीर्घ)sk >> 10) & (LISTEN_INFO_HASH_SIZE - 1);
पूर्ण

अटल काष्ठा listen_info *listen_hash_add(काष्ठा chtls_dev *cdev,
					   काष्ठा sock *sk,
					   अचिन्हित पूर्णांक stid)
अणु
	काष्ठा listen_info *p = kदो_स्मृति(माप(*p), GFP_KERNEL);

	अगर (p) अणु
		पूर्णांक key = listen_hashfn(sk);

		p->sk = sk;
		p->stid = stid;
		spin_lock(&cdev->listen_lock);
		p->next = cdev->listen_hash_tab[key];
		cdev->listen_hash_tab[key] = p;
		spin_unlock(&cdev->listen_lock);
	पूर्ण
	वापस p;
पूर्ण

अटल पूर्णांक listen_hash_find(काष्ठा chtls_dev *cdev,
			    काष्ठा sock *sk)
अणु
	काष्ठा listen_info *p;
	पूर्णांक stid = -1;
	पूर्णांक key;

	key = listen_hashfn(sk);

	spin_lock(&cdev->listen_lock);
	क्रम (p = cdev->listen_hash_tab[key]; p; p = p->next)
		अगर (p->sk == sk) अणु
			stid = p->stid;
			अवरोध;
		पूर्ण
	spin_unlock(&cdev->listen_lock);
	वापस stid;
पूर्ण

अटल पूर्णांक listen_hash_del(काष्ठा chtls_dev *cdev,
			   काष्ठा sock *sk)
अणु
	काष्ठा listen_info *p, **prev;
	पूर्णांक stid = -1;
	पूर्णांक key;

	key = listen_hashfn(sk);
	prev = &cdev->listen_hash_tab[key];

	spin_lock(&cdev->listen_lock);
	क्रम (p = *prev; p; prev = &p->next, p = p->next)
		अगर (p->sk == sk) अणु
			stid = p->stid;
			*prev = p->next;
			kमुक्त(p);
			अवरोध;
		पूर्ण
	spin_unlock(&cdev->listen_lock);
	वापस stid;
पूर्ण

अटल व्योम cleanup_syn_rcv_conn(काष्ठा sock *child, काष्ठा sock *parent)
अणु
	काष्ठा request_sock *req;
	काष्ठा chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(child);
	req = csk->passive_reap_next;

	reqsk_queue_हटाओd(&inet_csk(parent)->icsk_accept_queue, req);
	__skb_unlink((काष्ठा sk_buff *)&csk->synq, &csk->listen_ctx->synq);
	chtls_reqsk_मुक्त(req);
	csk->passive_reap_next = शून्य;
पूर्ण

अटल व्योम chtls_reset_synq(काष्ठा listen_ctx *listen_ctx)
अणु
	काष्ठा sock *listen_sk = listen_ctx->lsk;

	जबतक (!skb_queue_empty(&listen_ctx->synq)) अणु
		काष्ठा chtls_sock *csk =
			container_of((काष्ठा synq *)skb_peek
				(&listen_ctx->synq), काष्ठा chtls_sock, synq);
		काष्ठा sock *child = csk->sk;

		cleanup_syn_rcv_conn(child, listen_sk);
		sock_hold(child);
		local_bh_disable();
		bh_lock_sock(child);
		release_tcp_port(child);
		reset_listen_child(child);
		bh_unlock_sock(child);
		local_bh_enable();
		sock_put(child);
	पूर्ण
पूर्ण

पूर्णांक chtls_listen_start(काष्ठा chtls_dev *cdev, काष्ठा sock *sk)
अणु
	काष्ठा net_device *ndev;
#अगर IS_ENABLED(CONFIG_IPV6)
	bool clip_valid = false;
#पूर्ण_अगर
	काष्ठा listen_ctx *ctx;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	पूर्णांक ret = 0;
	पूर्णांक stid;

	rcu_पढ़ो_lock();
	ndev = chtls_find_netdev(cdev, sk);
	rcu_पढ़ो_unlock();
	अगर (!ndev)
		वापस -EBADF;

	pi = netdev_priv(ndev);
	adap = pi->adapter;
	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE))
		वापस -EBADF;

	अगर (listen_hash_find(cdev, sk) >= 0)   /* alपढ़ोy have it */
		वापस -EADDRINUSE;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	__module_get(THIS_MODULE);
	ctx->lsk = sk;
	ctx->cdev = cdev;
	ctx->state = T4_LISTEN_START_PENDING;
	skb_queue_head_init(&ctx->synq);

	stid = cxgb4_alloc_stid(cdev->tids, sk->sk_family, ctx);
	अगर (stid < 0)
		जाओ मुक्त_ctx;

	sock_hold(sk);
	अगर (!listen_hash_add(cdev, sk, stid))
		जाओ मुक्त_stid;

	अगर (sk->sk_family == PF_INET) अणु
		ret = cxgb4_create_server(ndev, stid,
					  inet_sk(sk)->inet_rcv_saddr,
					  inet_sk(sk)->inet_sport, 0,
					  cdev->lldi->rxq_ids[0]);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		पूर्णांक addr_type;

		addr_type = ipv6_addr_type(&sk->sk_v6_rcv_saddr);
		अगर (addr_type != IPV6_ADDR_ANY) अणु
			ret = cxgb4_clip_get(ndev, (स्थिर u32 *)
					     &sk->sk_v6_rcv_saddr, 1);
			अगर (ret)
				जाओ del_hash;
			clip_valid = true;
		पूर्ण
		ret = cxgb4_create_server6(ndev, stid,
					   &sk->sk_v6_rcv_saddr,
					   inet_sk(sk)->inet_sport,
					   cdev->lldi->rxq_ids[0]);
#पूर्ण_अगर
	पूर्ण
	अगर (ret > 0)
		ret = net_xmit_त्रुटि_सं(ret);
	अगर (ret)
		जाओ del_hash;
	वापस 0;
del_hash:
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (clip_valid)
		cxgb4_clip_release(ndev, (स्थिर u32 *)&sk->sk_v6_rcv_saddr, 1);
#पूर्ण_अगर
	listen_hash_del(cdev, sk);
मुक्त_stid:
	cxgb4_मुक्त_stid(cdev->tids, stid, sk->sk_family);
	sock_put(sk);
मुक्त_ctx:
	kमुक्त(ctx);
	module_put(THIS_MODULE);
	वापस -EBADF;
पूर्ण

व्योम chtls_listen_stop(काष्ठा chtls_dev *cdev, काष्ठा sock *sk)
अणु
	काष्ठा listen_ctx *listen_ctx;
	पूर्णांक stid;

	stid = listen_hash_del(cdev, sk);
	अगर (stid < 0)
		वापस;

	listen_ctx = (काष्ठा listen_ctx *)lookup_stid(cdev->tids, stid);
	chtls_reset_synq(listen_ctx);

	cxgb4_हटाओ_server(cdev->lldi->ports[0], stid,
			    cdev->lldi->rxq_ids[0], sk->sk_family == PF_INET6);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == PF_INET6) अणु
		काष्ठा net_device *ndev = chtls_find_netdev(cdev, sk);
		पूर्णांक addr_type = 0;

		addr_type = ipv6_addr_type((स्थिर काष्ठा in6_addr *)
					  &sk->sk_v6_rcv_saddr);
		अगर (addr_type != IPV6_ADDR_ANY)
			cxgb4_clip_release(ndev, (स्थिर u32 *)
					   &sk->sk_v6_rcv_saddr, 1);
	पूर्ण
#पूर्ण_अगर
	chtls_disconnect_acceptq(sk);
पूर्ण

अटल पूर्णांक chtls_pass_खोलो_rpl(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_खोलो_rpl *rpl = cplhdr(skb) + RSS_HDR;
	अचिन्हित पूर्णांक stid = GET_TID(rpl);
	काष्ठा listen_ctx *listen_ctx;

	listen_ctx = (काष्ठा listen_ctx *)lookup_stid(cdev->tids, stid);
	अगर (!listen_ctx)
		वापस CPL_RET_BUF_DONE;

	अगर (listen_ctx->state == T4_LISTEN_START_PENDING) अणु
		listen_ctx->state = T4_LISTEN_STARTED;
		वापस CPL_RET_BUF_DONE;
	पूर्ण

	अगर (rpl->status != CPL_ERR_NONE) अणु
		pr_info("Unexpected PASS_OPEN_RPL status %u for STID %u\n",
			rpl->status, stid);
	पूर्ण अन्यथा अणु
		cxgb4_मुक्त_stid(cdev->tids, stid, listen_ctx->lsk->sk_family);
		sock_put(listen_ctx->lsk);
		kमुक्त(listen_ctx);
		module_put(THIS_MODULE);
	पूर्ण
	वापस CPL_RET_BUF_DONE;
पूर्ण

अटल पूर्णांक chtls_बंद_listsrv_rpl(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_बंद_listsvr_rpl *rpl = cplhdr(skb) + RSS_HDR;
	काष्ठा listen_ctx *listen_ctx;
	अचिन्हित पूर्णांक stid;
	व्योम *data;

	stid = GET_TID(rpl);
	data = lookup_stid(cdev->tids, stid);
	listen_ctx = (काष्ठा listen_ctx *)data;

	अगर (rpl->status != CPL_ERR_NONE) अणु
		pr_info("Unexpected CLOSE_LISTSRV_RPL status %u for STID %u\n",
			rpl->status, stid);
	पूर्ण अन्यथा अणु
		cxgb4_मुक्त_stid(cdev->tids, stid, listen_ctx->lsk->sk_family);
		sock_put(listen_ctx->lsk);
		kमुक्त(listen_ctx);
		module_put(THIS_MODULE);
	पूर्ण
	वापस CPL_RET_BUF_DONE;
पूर्ण

अटल व्योम chtls_purge_wr_queue(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = dequeue_wr(sk)) != शून्य)
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम chtls_release_resources(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	काष्ठा chtls_dev *cdev = csk->cdev;
	अचिन्हित पूर्णांक tid = csk->tid;
	काष्ठा tid_info *tids;

	अगर (!cdev)
		वापस;

	tids = cdev->tids;
	kमुक्त_skb(csk->txdata_skb_cache);
	csk->txdata_skb_cache = शून्य;

	अगर (csk->wr_credits != csk->wr_max_credits) अणु
		chtls_purge_wr_queue(sk);
		chtls_reset_wr_list(csk);
	पूर्ण

	अगर (csk->l2t_entry) अणु
		cxgb4_l2t_release(csk->l2t_entry);
		csk->l2t_entry = शून्य;
	पूर्ण

	अगर (sk->sk_state != TCP_SYN_SENT) अणु
		cxgb4_हटाओ_tid(tids, csk->port_id, tid, sk->sk_family);
		sock_put(sk);
	पूर्ण
पूर्ण

अटल व्योम chtls_conn_करोne(काष्ठा sock *sk)
अणु
	अगर (sock_flag(sk, SOCK_DEAD))
		chtls_purge_receive_queue(sk);
	sk_wakeup_sleepers(sk, 0);
	tcp_करोne(sk);
पूर्ण

अटल व्योम करो_पात_syn_rcv(काष्ठा sock *child, काष्ठा sock *parent)
अणु
	/*
	 * If the server is still खोलो we clean up the child connection,
	 * otherwise the server alपढ़ोy did the clean up as it was purging
	 * its SYN queue and the skb was just sitting in its backlog.
	 */
	अगर (likely(parent->sk_state == TCP_LISTEN)) अणु
		cleanup_syn_rcv_conn(child, parent);
		/* Without the below call to sock_orphan,
		 * we leak the socket resource with syn_flood test
		 * as inet_csk_destroy_sock will not be called
		 * in tcp_करोne since SOCK_DEAD flag is not set.
		 * Kernel handles this dअगरferently where new socket is
		 * created only after 3 way handshake is करोne.
		 */
		sock_orphan(child);
		percpu_counter_inc((child)->sk_prot->orphan_count);
		chtls_release_resources(child);
		chtls_conn_करोne(child);
	पूर्ण अन्यथा अणु
		अगर (csk_flag(child, CSK_RST_ABORTED)) अणु
			chtls_release_resources(child);
			chtls_conn_करोne(child);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pass_खोलो_पात(काष्ठा sock *child, काष्ठा sock *parent,
			    काष्ठा sk_buff *skb)
अणु
	करो_पात_syn_rcv(child, parent);
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम bl_pass_खोलो_पात(काष्ठा sock *lsk, काष्ठा sk_buff *skb)
अणु
	pass_खोलो_पात(skb->sk, lsk, skb);
पूर्ण

अटल व्योम chtls_pass_खोलो_arp_failure(काष्ठा sock *sk,
					काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा request_sock *oreq;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;
	काष्ठा sock *parent;
	व्योम *data;

	csk = rcu_dereference_sk_user_data(sk);
	cdev = csk->cdev;

	/*
	 * If the connection is being पातed due to the parent listening
	 * socket going away there's nothing to करो, the ABORT_REQ will बंद
	 * the connection.
	 */
	अगर (csk_flag(sk, CSK_ABORT_RPL_PENDING)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	oreq = csk->passive_reap_next;
	data = lookup_stid(cdev->tids, oreq->ts_recent);
	parent = ((काष्ठा listen_ctx *)data)->lsk;

	bh_lock_sock(parent);
	अगर (!sock_owned_by_user(parent)) अणु
		pass_खोलो_पात(sk, parent, skb);
	पूर्ण अन्यथा अणु
		BLOG_SKB_CB(skb)->backlog_rcv = bl_pass_खोलो_पात;
		__sk_add_backlog(parent, skb);
	पूर्ण
	bh_unlock_sock(parent);
पूर्ण

अटल व्योम chtls_accept_rpl_arp_failure(व्योम *handle,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)handle;

	sock_hold(sk);
	process_cpl_msg(chtls_pass_खोलो_arp_failure, sk, skb);
	sock_put(sk);
पूर्ण

अटल अचिन्हित पूर्णांक chtls_select_mss(स्थिर काष्ठा chtls_sock *csk,
				     अचिन्हित पूर्णांक pmtu,
				     काष्ठा cpl_pass_accept_req *req)
अणु
	काष्ठा chtls_dev *cdev;
	काष्ठा dst_entry *dst;
	अचिन्हित पूर्णांक tcpoptsz;
	अचिन्हित पूर्णांक iphdrsz;
	अचिन्हित पूर्णांक mtu_idx;
	काष्ठा tcp_sock *tp;
	अचिन्हित पूर्णांक mss;
	काष्ठा sock *sk;

	mss = ntohs(req->tcpopt.mss);
	sk = csk->sk;
	dst = __sk_dst_get(sk);
	cdev = csk->cdev;
	tp = tcp_sk(sk);
	tcpoptsz = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		iphdrsz = माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr);
	अन्यथा
#पूर्ण_अगर
		iphdrsz = माप(काष्ठा iphdr) + माप(काष्ठा tcphdr);
	अगर (req->tcpopt.tstamp)
		tcpoptsz += round_up(TCPOLEN_TIMESTAMP, 4);

	tp->advmss = dst_metric_advmss(dst);
	अगर (USER_MSS(tp) && tp->advmss > USER_MSS(tp))
		tp->advmss = USER_MSS(tp);
	अगर (tp->advmss > pmtu - iphdrsz)
		tp->advmss = pmtu - iphdrsz;
	अगर (mss && tp->advmss > mss)
		tp->advmss = mss;

	tp->advmss = cxgb4_best_aligned_mtu(cdev->lldi->mtus,
					    iphdrsz + tcpoptsz,
					    tp->advmss - tcpoptsz,
					    8, &mtu_idx);
	tp->advmss -= iphdrsz;

	inet_csk(sk)->icsk_pmtu_cookie = pmtu;
	वापस mtu_idx;
पूर्ण

अटल अचिन्हित पूर्णांक select_rcv_wscale(पूर्णांक space, पूर्णांक wscale_ok, पूर्णांक win_clamp)
अणु
	पूर्णांक wscale = 0;

	अगर (space > MAX_RCV_WND)
		space = MAX_RCV_WND;
	अगर (win_clamp && win_clamp < space)
		space = win_clamp;

	अगर (wscale_ok) अणु
		जबतक (wscale < 14 && (65535 << wscale) < space)
			wscale++;
	पूर्ण
	वापस wscale;
पूर्ण

अटल व्योम chtls_pass_accept_rpl(काष्ठा sk_buff *skb,
				  काष्ठा cpl_pass_accept_req *req,
				  अचिन्हित पूर्णांक tid)

अणु
	काष्ठा cpl_t5_pass_accept_rpl *rpl5;
	काष्ठा cxgb4_lld_info *lldi;
	स्थिर काष्ठा tcphdr *tcph;
	स्थिर काष्ठा tcp_sock *tp;
	काष्ठा chtls_sock *csk;
	अचिन्हित पूर्णांक len;
	काष्ठा sock *sk;
	u32 opt2, hlen;
	u64 opt0;

	sk = skb->sk;
	tp = tcp_sk(sk);
	csk = sk->sk_user_data;
	csk->tid = tid;
	lldi = csk->cdev->lldi;
	len = roundup(माप(*rpl5), 16);

	rpl5 = __skb_put_zero(skb, len);
	INIT_TP_WR(rpl5, tid);

	OPCODE_TID(rpl5) = cpu_to_be32(MK_OPCODE_TID(CPL_PASS_ACCEPT_RPL,
						     csk->tid));
	csk->mtu_idx = chtls_select_mss(csk, dst_mtu(__sk_dst_get(sk)),
					req);
	opt0 = TCAM_BYPASS_F |
	       WND_SCALE_V(RCV_WSCALE(tp)) |
	       MSS_IDX_V(csk->mtu_idx) |
	       L2T_IDX_V(csk->l2t_entry->idx) |
	       NAGLE_V(!(tp->nonagle & TCP_NAGLE_OFF)) |
	       TX_CHAN_V(csk->tx_chan) |
	       SMAC_SEL_V(csk->smac_idx) |
	       DSCP_V(csk->tos >> 2) |
	       ULP_MODE_V(ULP_MODE_TLS) |
	       RCV_बफ_मान_V(min(tp->rcv_wnd >> 10, RCV_बफ_मान_M));

	opt2 = RX_CHANNEL_V(0) |
		RSS_QUEUE_VALID_F | RSS_QUEUE_V(csk->rss_qid);

	अगर (!is_t5(lldi->adapter_type))
		opt2 |= RX_FC_DISABLE_F;
	अगर (req->tcpopt.tstamp)
		opt2 |= TSTAMPS_EN_F;
	अगर (req->tcpopt.sack)
		opt2 |= SACK_EN_F;
	hlen = ntohl(req->hdr_len);

	tcph = (काष्ठा tcphdr *)((u8 *)(req + 1) +
			T6_ETH_HDR_LEN_G(hlen) + T6_IP_HDR_LEN_G(hlen));
	अगर (tcph->ece && tcph->cwr)
		opt2 |= CCTRL_ECN_V(1);
	opt2 |= CONG_CNTRL_V(CONG_ALG_NEWRENO);
	opt2 |= T5_ISS_F;
	opt2 |= T5_OPT_2_VALID_F;
	opt2 |= WND_SCALE_EN_V(WSCALE_OK(tp));
	rpl5->opt0 = cpu_to_be64(opt0);
	rpl5->opt2 = cpu_to_be32(opt2);
	rpl5->iss = cpu_to_be32((pअक्रमom_u32() & ~7UL) - 1);
	set_wr_txq(skb, CPL_PRIORITY_SETUP, csk->port_id);
	t4_set_arp_err_handler(skb, sk, chtls_accept_rpl_arp_failure);
	cxgb4_l2t_send(csk->egress_dev, skb, csk->l2t_entry);
पूर्ण

अटल व्योम inet_inherit_port(काष्ठा inet_hashinfo *hash_info,
			      काष्ठा sock *lsk, काष्ठा sock *newsk)
अणु
	local_bh_disable();
	__inet_inherit_port(lsk, newsk);
	local_bh_enable();
पूर्ण

अटल पूर्णांक chtls_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	BLOG_SKB_CB(skb)->backlog_rcv(sk, skb);
	वापस 0;
पूर्ण

अटल व्योम chtls_set_tcp_winकरोw(काष्ठा chtls_sock *csk)
अणु
	काष्ठा net_device *ndev = csk->egress_dev;
	काष्ठा port_info *pi = netdev_priv(ndev);
	अचिन्हित पूर्णांक linkspeed;
	u8 scale;

	linkspeed = pi->link_cfg.speed;
	scale = linkspeed / SPEED_10000;
#घोषणा CHTLS_10G_RCVWIN (256 * 1024)
	csk->rcv_win = CHTLS_10G_RCVWIN;
	अगर (scale)
		csk->rcv_win *= scale;
#घोषणा CHTLS_10G_SNDWIN (256 * 1024)
	csk->snd_win = CHTLS_10G_SNDWIN;
	अगर (scale)
		csk->snd_win *= scale;
पूर्ण

अटल काष्ठा sock *chtls_recv_sock(काष्ठा sock *lsk,
				    काष्ठा request_sock *oreq,
				    व्योम *network_hdr,
				    स्थिर काष्ठा cpl_pass_accept_req *req,
				    काष्ठा chtls_dev *cdev)
अणु
	काष्ठा adapter *adap = pci_get_drvdata(cdev->pdev);
	काष्ठा neighbour *n = शून्य;
	काष्ठा inet_sock *newinet;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा tls_context *ctx;
	काष्ठा net_device *ndev;
	काष्ठा chtls_sock *csk;
	काष्ठा dst_entry *dst;
	काष्ठा tcp_sock *tp;
	काष्ठा sock *newsk;
	bool found = false;
	u16 port_id;
	पूर्णांक rxq_idx;
	पूर्णांक step, i;

	iph = (स्थिर काष्ठा iphdr *)network_hdr;
	newsk = tcp_create_खोलोreq_child(lsk, oreq, cdev->askb);
	अगर (!newsk)
		जाओ मुक्त_oreq;

	अगर (lsk->sk_family == AF_INET) अणु
		dst = inet_csk_route_child_sock(lsk, newsk, oreq);
		अगर (!dst)
			जाओ मुक्त_sk;

		n = dst_neigh_lookup(dst, &iph->saddr);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ipv6hdr *ip6h;
		काष्ठा flowi6 fl6;

		ip6h = (स्थिर काष्ठा ipv6hdr *)network_hdr;
		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_proto = IPPROTO_TCP;
		fl6.saddr = ip6h->daddr;
		fl6.daddr = ip6h->saddr;
		fl6.fl6_dport = inet_rsk(oreq)->ir_rmt_port;
		fl6.fl6_sport = htons(inet_rsk(oreq)->ir_num);
		security_req_classअगरy_flow(oreq, flowi6_to_flowi_common(&fl6));
		dst = ip6_dst_lookup_flow(sock_net(lsk), lsk, &fl6, शून्य);
		अगर (IS_ERR(dst))
			जाओ मुक्त_sk;
		n = dst_neigh_lookup(dst, &ip6h->saddr);
#पूर्ण_अगर
	पूर्ण
	अगर (!n || !n->dev)
		जाओ मुक्त_dst;

	ndev = n->dev;
	अगर (is_vlan_dev(ndev))
		ndev = vlan_dev_real_dev(ndev);

	क्रम_each_port(adap, i)
		अगर (cdev->ports[i] == ndev)
			found = true;

	अगर (!found)
		जाओ मुक्त_dst;

	port_id = cxgb4_port_idx(ndev);

	csk = chtls_sock_create(cdev);
	अगर (!csk)
		जाओ मुक्त_dst;

	csk->l2t_entry = cxgb4_l2t_get(cdev->lldi->l2t, n, ndev, 0);
	अगर (!csk->l2t_entry)
		जाओ मुक्त_csk;

	newsk->sk_user_data = csk;
	newsk->sk_backlog_rcv = chtls_backlog_rcv;

	tp = tcp_sk(newsk);
	newinet = inet_sk(newsk);

	अगर (iph->version == 0x4) अणु
		newinet->inet_daddr = iph->saddr;
		newinet->inet_rcv_saddr = iph->daddr;
		newinet->inet_saddr = iph->daddr;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा tcp6_sock *newtcp6sk = (काष्ठा tcp6_sock *)newsk;
		काष्ठा inet_request_sock *treq = inet_rsk(oreq);
		काष्ठा ipv6_pinfo *newnp = inet6_sk(newsk);
		काष्ठा ipv6_pinfo *np = inet6_sk(lsk);

		inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;
		स_नकल(newnp, np, माप(काष्ठा ipv6_pinfo));
		newsk->sk_v6_daddr = treq->ir_v6_rmt_addr;
		newsk->sk_v6_rcv_saddr = treq->ir_v6_loc_addr;
		inet6_sk(newsk)->saddr = treq->ir_v6_loc_addr;
		newnp->ipv6_fl_list = शून्य;
		newnp->pktoptions = शून्य;
		newsk->sk_bound_dev_अगर = treq->ir_iअगर;
		newinet->inet_opt = शून्य;
		newinet->inet_daddr = LOOPBACK4_IPV6;
		newinet->inet_saddr = LOOPBACK4_IPV6;
#पूर्ण_अगर
	पूर्ण

	oreq->ts_recent = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	sk_setup_caps(newsk, dst);
	ctx = tls_get_ctx(lsk);
	newsk->sk_deकाष्ठा = ctx->sk_deकाष्ठा;
	newsk->sk_prot_creator = lsk->sk_prot_creator;
	csk->sk = newsk;
	csk->passive_reap_next = oreq;
	csk->tx_chan = cxgb4_port_chan(ndev);
	csk->port_id = port_id;
	csk->egress_dev = ndev;
	csk->tos = PASS_OPEN_TOS_G(ntohl(req->tos_stid));
	chtls_set_tcp_winकरोw(csk);
	tp->rcv_wnd = csk->rcv_win;
	csk->sndbuf = csk->snd_win;
	csk->ulp_mode = ULP_MODE_TLS;
	step = cdev->lldi->nrxq / cdev->lldi->nchan;
	rxq_idx = port_id * step;
	rxq_idx += cdev->round_robin_cnt++ % step;
	csk->rss_qid = cdev->lldi->rxq_ids[rxq_idx];
	csk->txq_idx = (rxq_idx < cdev->lldi->ntxq) ? rxq_idx :
			port_id * step;
	csk->sndbuf = newsk->sk_sndbuf;
	csk->smac_idx = ((काष्ठा port_info *)netdev_priv(ndev))->smt_idx;
	RCV_WSCALE(tp) = select_rcv_wscale(tcp_full_space(newsk),
					   sock_net(newsk)->
						ipv4.sysctl_tcp_winकरोw_scaling,
					   tp->winकरोw_clamp);
	neigh_release(n);
	inet_inherit_port(&tcp_hashinfo, lsk, newsk);
	csk_set_flag(csk, CSK_CONN_INLINE);
	bh_unlock_sock(newsk); /* tcp_create_खोलोreq_child ->sk_clone_lock */

	वापस newsk;
मुक्त_csk:
	chtls_sock_release(&csk->kref);
मुक्त_dst:
	अगर (n)
		neigh_release(n);
	dst_release(dst);
मुक्त_sk:
	inet_csk_prepare_क्रमced_बंद(newsk);
	tcp_करोne(newsk);
मुक्त_oreq:
	chtls_reqsk_मुक्त(oreq);
	वापस शून्य;
पूर्ण

/*
 * Populate a TID_RELEASE WR.  The skb must be alपढ़ोy propely sized.
 */
अटल  व्योम mk_tid_release(काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा cpl_tid_release *req;
	अचिन्हित पूर्णांक len;

	len = roundup(माप(काष्ठा cpl_tid_release), 16);
	req = (काष्ठा cpl_tid_release *)__skb_put(skb, len);
	स_रखो(req, 0, len);
	set_wr_txq(skb, CPL_PRIORITY_SETUP, chan);
	INIT_TP_WR_CPL(req, CPL_TID_RELEASE, tid);
पूर्ण

अटल पूर्णांक chtls_get_module(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (!try_module_get(icsk->icsk_ulp_ops->owner))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम chtls_pass_accept_request(काष्ठा sock *sk,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_t5_pass_accept_rpl *rpl;
	काष्ठा cpl_pass_accept_req *req;
	काष्ठा listen_ctx *listen_ctx;
	काष्ठा vlan_ethhdr *vlan_eh;
	काष्ठा request_sock *oreq;
	काष्ठा sk_buff *reply_skb;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा tcphdr *tcph;
	काष्ठा sock *newsk;
	काष्ठा ethhdr *eh;
	काष्ठा iphdr *iph;
	व्योम *network_hdr;
	अचिन्हित पूर्णांक stid;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक tid;
	bool th_ecn, ect;
	__u8 ip_dsfield; /* IPv4 tos or IPv6 dsfield */
	u16 eth_hdr_len;
	bool ecn_ok;

	req = cplhdr(skb) + RSS_HDR;
	tid = GET_TID(req);
	cdev = BLOG_SKB_CB(skb)->cdev;
	newsk = lookup_tid(cdev->tids, tid);
	stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	अगर (newsk) अणु
		pr_info("tid (%d) already in use\n", tid);
		वापस;
	पूर्ण

	len = roundup(माप(*rpl), 16);
	reply_skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!reply_skb) अणु
		cxgb4_हटाओ_tid(cdev->tids, 0, tid, sk->sk_family);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (sk->sk_state != TCP_LISTEN)
		जाओ reject;

	अगर (inet_csk_reqsk_queue_is_full(sk))
		जाओ reject;

	अगर (sk_acceptq_is_full(sk))
		जाओ reject;


	eth_hdr_len = T6_ETH_HDR_LEN_G(ntohl(req->hdr_len));
	अगर (eth_hdr_len == ETH_HLEN) अणु
		eh = (काष्ठा ethhdr *)(req + 1);
		iph = (काष्ठा iphdr *)(eh + 1);
		ip6h = (काष्ठा ipv6hdr *)(eh + 1);
		network_hdr = (व्योम *)(eh + 1);
	पूर्ण अन्यथा अणु
		vlan_eh = (काष्ठा vlan_ethhdr *)(req + 1);
		iph = (काष्ठा iphdr *)(vlan_eh + 1);
		ip6h = (काष्ठा ipv6hdr *)(vlan_eh + 1);
		network_hdr = (व्योम *)(vlan_eh + 1);
	पूर्ण

	अगर (iph->version == 0x4) अणु
		tcph = (काष्ठा tcphdr *)(iph + 1);
		skb_set_network_header(skb, (व्योम *)iph - (व्योम *)req);
		oreq = inet_reqsk_alloc(&chtls_rsk_ops, sk, true);
	पूर्ण अन्यथा अणु
		tcph = (काष्ठा tcphdr *)(ip6h + 1);
		skb_set_network_header(skb, (व्योम *)ip6h - (व्योम *)req);
		oreq = inet_reqsk_alloc(&chtls_rsk_opsv6, sk, false);
	पूर्ण

	अगर (!oreq)
		जाओ reject;

	oreq->rsk_rcv_wnd = 0;
	oreq->rsk_winकरोw_clamp = 0;
	oreq->syncookie = 0;
	oreq->mss = 0;
	oreq->ts_recent = 0;

	tcp_rsk(oreq)->tfo_listener = false;
	tcp_rsk(oreq)->rcv_isn = ntohl(tcph->seq);
	chtls_set_req_port(oreq, tcph->source, tcph->dest);
	अगर (iph->version == 0x4) अणु
		chtls_set_req_addr(oreq, iph->daddr, iph->saddr);
		ip_dsfield = ipv4_get_dsfield(iph);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		inet_rsk(oreq)->ir_v6_rmt_addr = ipv6_hdr(skb)->saddr;
		inet_rsk(oreq)->ir_v6_loc_addr = ipv6_hdr(skb)->daddr;
		ip_dsfield = ipv6_get_dsfield(ipv6_hdr(skb));
#पूर्ण_अगर
	पूर्ण
	अगर (req->tcpopt.wsf <= 14 &&
	    sock_net(sk)->ipv4.sysctl_tcp_winकरोw_scaling) अणु
		inet_rsk(oreq)->wscale_ok = 1;
		inet_rsk(oreq)->snd_wscale = req->tcpopt.wsf;
	पूर्ण
	inet_rsk(oreq)->ir_iअगर = sk->sk_bound_dev_अगर;
	th_ecn = tcph->ece && tcph->cwr;
	अगर (th_ecn) अणु
		ect = !INET_ECN_is_not_ect(ip_dsfield);
		ecn_ok = sock_net(sk)->ipv4.sysctl_tcp_ecn;
		अगर ((!ect && ecn_ok) || tcp_ca_needs_ecn(sk))
			inet_rsk(oreq)->ecn_ok = 1;
	पूर्ण

	newsk = chtls_recv_sock(sk, oreq, network_hdr, req, cdev);
	अगर (!newsk)
		जाओ reject;

	अगर (chtls_get_module(newsk))
		जाओ reject;
	inet_csk_reqsk_queue_added(sk);
	reply_skb->sk = newsk;
	chtls_install_cpl_ops(newsk);
	cxgb4_insert_tid(cdev->tids, newsk, tid, newsk->sk_family);
	csk = rcu_dereference_sk_user_data(newsk);
	listen_ctx = (काष्ठा listen_ctx *)lookup_stid(cdev->tids, stid);
	csk->listen_ctx = listen_ctx;
	__skb_queue_tail(&listen_ctx->synq, (काष्ठा sk_buff *)&csk->synq);
	chtls_pass_accept_rpl(reply_skb, req, tid);
	kमुक्त_skb(skb);
	वापस;

reject:
	mk_tid_release(reply_skb, 0, tid);
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
	kमुक्त_skb(skb);
पूर्ण

/*
 * Handle a CPL_PASS_ACCEPT_REQ message.
 */
अटल पूर्णांक chtls_pass_accept_req(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_accept_req *req = cplhdr(skb) + RSS_HDR;
	काष्ठा listen_ctx *ctx;
	अचिन्हित पूर्णांक stid;
	अचिन्हित पूर्णांक tid;
	काष्ठा sock *lsk;
	व्योम *data;

	stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	tid = GET_TID(req);

	data = lookup_stid(cdev->tids, stid);
	अगर (!data)
		वापस 1;

	ctx = (काष्ठा listen_ctx *)data;
	lsk = ctx->lsk;

	अगर (unlikely(tid_out_of_range(cdev->tids, tid))) अणु
		pr_info("passive open TID %u too large\n", tid);
		वापस 1;
	पूर्ण

	BLOG_SKB_CB(skb)->cdev = cdev;
	process_cpl_msg(chtls_pass_accept_request, lsk, skb);
	वापस 0;
पूर्ण

/*
 * Completes some final bits of initialization क्रम just established connections
 * and changes their state to TCP_ESTABLISHED.
 *
 * snd_isn here is the ISN after the SYN, i.e., the true ISN + 1.
 */
अटल व्योम make_established(काष्ठा sock *sk, u32 snd_isn, अचिन्हित पूर्णांक opt)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->pushed_seq = snd_isn;
	tp->ग_लिखो_seq = snd_isn;
	tp->snd_nxt = snd_isn;
	tp->snd_una = snd_isn;
	inet_sk(sk)->inet_id = pअक्रमom_u32();
	assign_rxopt(sk, opt);

	अगर (tp->rcv_wnd > (RCV_बफ_मान_M << 10))
		tp->rcv_wup -= tp->rcv_wnd - (RCV_बफ_मान_M << 10);

	smp_mb();
	tcp_set_state(sk, TCP_ESTABLISHED);
पूर्ण

अटल व्योम chtls_पात_conn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *पात_skb;

	पात_skb = alloc_skb(माप(काष्ठा cpl_पात_req), GFP_ATOMIC);
	अगर (पात_skb)
		chtls_send_reset(sk, CPL_ABORT_SEND_RST, पात_skb);
पूर्ण

अटल काष्ठा sock *reap_list;
अटल DEFINE_SPINLOCK(reap_list_lock);

/*
 * Process the reap list.
 */
DECLARE_TASK_FUNC(process_reap_list, task_param)
अणु
	spin_lock_bh(&reap_list_lock);
	जबतक (reap_list) अणु
		काष्ठा sock *sk = reap_list;
		काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

		reap_list = csk->passive_reap_next;
		csk->passive_reap_next = शून्य;
		spin_unlock(&reap_list_lock);
		sock_hold(sk);

		bh_lock_sock(sk);
		chtls_पात_conn(sk, शून्य);
		sock_orphan(sk);
		अगर (sk->sk_state == TCP_CLOSE)
			inet_csk_destroy_sock(sk);
		bh_unlock_sock(sk);
		sock_put(sk);
		spin_lock(&reap_list_lock);
	पूर्ण
	spin_unlock_bh(&reap_list_lock);
पूर्ण

अटल DECLARE_WORK(reap_task, process_reap_list);

अटल व्योम add_to_reap_list(काष्ठा sock *sk)
अणु
	काष्ठा chtls_sock *csk = sk->sk_user_data;

	local_bh_disable();
	release_tcp_port(sk); /* release the port immediately */

	spin_lock(&reap_list_lock);
	csk->passive_reap_next = reap_list;
	reap_list = sk;
	अगर (!csk->passive_reap_next)
		schedule_work(&reap_task);
	spin_unlock(&reap_list_lock);
	local_bh_enable();
पूर्ण

अटल व्योम add_pass_खोलो_to_parent(काष्ठा sock *child, काष्ठा sock *lsk,
				    काष्ठा chtls_dev *cdev)
अणु
	काष्ठा request_sock *oreq;
	काष्ठा chtls_sock *csk;

	अगर (lsk->sk_state != TCP_LISTEN)
		वापस;

	csk = child->sk_user_data;
	oreq = csk->passive_reap_next;
	csk->passive_reap_next = शून्य;

	reqsk_queue_हटाओd(&inet_csk(lsk)->icsk_accept_queue, oreq);
	__skb_unlink((काष्ठा sk_buff *)&csk->synq, &csk->listen_ctx->synq);

	अगर (sk_acceptq_is_full(lsk)) अणु
		chtls_reqsk_मुक्त(oreq);
		add_to_reap_list(child);
	पूर्ण अन्यथा अणु
		refcount_set(&oreq->rsk_refcnt, 1);
		inet_csk_reqsk_queue_add(lsk, oreq, child);
		lsk->sk_data_पढ़ोy(lsk);
	पूर्ण
पूर्ण

अटल व्योम bl_add_pass_खोलो_to_parent(काष्ठा sock *lsk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *child = skb->sk;

	skb->sk = शून्य;
	add_pass_खोलो_to_parent(child, lsk, BLOG_SKB_CB(skb)->cdev);
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक chtls_pass_establish(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_establish *req = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk;
	काष्ठा sock *lsk, *sk;
	अचिन्हित पूर्णांक hwtid;

	hwtid = GET_TID(req);
	sk = lookup_tid(cdev->tids, hwtid);
	अगर (!sk)
		वापस (CPL_RET_UNKNOWN_TID | CPL_RET_BUF_DONE);

	bh_lock_sock(sk);
	अगर (unlikely(sock_owned_by_user(sk))) अणु
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक stid;
		व्योम *data;

		csk = sk->sk_user_data;
		csk->wr_max_credits = 64;
		csk->wr_credits = 64;
		csk->wr_unacked = 0;
		make_established(sk, ntohl(req->snd_isn), ntohs(req->tcp_opt));
		stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
		sk->sk_state_change(sk);
		अगर (unlikely(sk->sk_socket))
			sk_wake_async(sk, 0, POLL_OUT);

		data = lookup_stid(cdev->tids, stid);
		अगर (!data) अणु
			/* listening server बंद */
			kमुक्त_skb(skb);
			जाओ unlock;
		पूर्ण
		lsk = ((काष्ठा listen_ctx *)data)->lsk;

		bh_lock_sock(lsk);
		अगर (unlikely(skb_queue_empty(&csk->listen_ctx->synq))) अणु
			/* हटाओd from synq */
			bh_unlock_sock(lsk);
			kमुक्त_skb(skb);
			जाओ unlock;
		पूर्ण

		अगर (likely(!sock_owned_by_user(lsk))) अणु
			kमुक्त_skb(skb);
			add_pass_खोलो_to_parent(sk, lsk, cdev);
		पूर्ण अन्यथा अणु
			skb->sk = sk;
			BLOG_SKB_CB(skb)->cdev = cdev;
			BLOG_SKB_CB(skb)->backlog_rcv =
				bl_add_pass_खोलो_to_parent;
			__sk_add_backlog(lsk, skb);
		पूर्ण
		bh_unlock_sock(lsk);
	पूर्ण
unlock:
	bh_unlock_sock(sk);
	वापस 0;
पूर्ण

/*
 * Handle receipt of an urgent poपूर्णांकer.
 */
अटल व्योम handle_urg_ptr(काष्ठा sock *sk, u32 urg_seq)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	urg_seq--;
	अगर (tp->urg_data && !after(urg_seq, tp->urg_seq))
		वापस;	/* duplicate poपूर्णांकer */

	sk_send_sigurg(sk);
	अगर (tp->urg_seq == tp->copied_seq && tp->urg_data &&
	    !sock_flag(sk, SOCK_URGINLINE) &&
	    tp->copied_seq != tp->rcv_nxt) अणु
		काष्ठा sk_buff *skb = skb_peek(&sk->sk_receive_queue);

		tp->copied_seq++;
		अगर (skb && tp->copied_seq - ULP_SKB_CB(skb)->seq >= skb->len)
			chtls_मुक्त_skb(sk, skb);
	पूर्ण

	tp->urg_data = TCP_URG_NOTYET;
	tp->urg_seq = urg_seq;
पूर्ण

अटल व्योम check_sk_callbacks(काष्ठा chtls_sock *csk)
अणु
	काष्ठा sock *sk = csk->sk;

	अगर (unlikely(sk->sk_user_data &&
		     !csk_flag_nochk(csk, CSK_CALLBACKS_CHKD)))
		csk_set_flag(csk, CSK_CALLBACKS_CHKD);
पूर्ण

/*
 * Handles Rx data that arrives in a state where the socket isn't accepting
 * new data.
 */
अटल व्योम handle_excess_rx(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (!csk_flag(sk, CSK_ABORT_SHUTDOWN))
		chtls_पात_conn(sk, skb);

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम chtls_recv_data(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_rx_data *hdr = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);

	अगर (unlikely(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		handle_excess_rx(sk, skb);
		वापस;
	पूर्ण

	ULP_SKB_CB(skb)->seq = ntohl(hdr->seq);
	ULP_SKB_CB(skb)->psh = hdr->psh;
	skb_ulp_mode(skb) = ULP_MODE_NONE;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*hdr) + RSS_HDR);
	अगर (!skb->data_len)
		__skb_trim(skb, ntohs(hdr->len));

	अगर (unlikely(hdr->urg))
		handle_urg_ptr(sk, tp->rcv_nxt + ntohs(hdr->urg));
	अगर (unlikely(tp->urg_data == TCP_URG_NOTYET &&
		     tp->urg_seq - tp->rcv_nxt < skb->len))
		tp->urg_data = TCP_URG_VALID |
			       skb->data[tp->urg_seq - tp->rcv_nxt];

	अगर (unlikely(hdr->dack_mode != csk->delack_mode)) अणु
		csk->delack_mode = hdr->dack_mode;
		csk->delack_seq = tp->rcv_nxt;
	पूर्ण

	tcp_hdr(skb)->fin = 0;
	tp->rcv_nxt += skb->len;

	__skb_queue_tail(&sk->sk_receive_queue, skb);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		check_sk_callbacks(csk);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक chtls_rx_data(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_rx_data *req = cplhdr(skb) + RSS_HDR;
	अचिन्हित पूर्णांक hwtid = GET_TID(req);
	काष्ठा sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);
	अगर (unlikely(!sk)) अणु
		pr_err("can't find conn. for hwtid %u.\n", hwtid);
		वापस -EINVAL;
	पूर्ण
	skb_dst_set(skb, शून्य);
	process_cpl_msg(chtls_recv_data, sk, skb);
	वापस 0;
पूर्ण

अटल व्योम chtls_recv_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_tls_data *hdr = cplhdr(skb);
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_hws *tlsk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tlsk = &csk->tlshws;
	tp = tcp_sk(sk);

	अगर (unlikely(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		handle_excess_rx(sk, skb);
		वापस;
	पूर्ण

	ULP_SKB_CB(skb)->seq = ntohl(hdr->seq);
	ULP_SKB_CB(skb)->flags = 0;
	skb_ulp_mode(skb) = ULP_MODE_TLS;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*hdr));
	अगर (!skb->data_len)
		__skb_trim(skb,
			   CPL_TLS_DATA_LENGTH_G(ntohl(hdr->length_pkd)));

	अगर (unlikely(tp->urg_data == TCP_URG_NOTYET && tp->urg_seq -
		     tp->rcv_nxt < skb->len))
		tp->urg_data = TCP_URG_VALID |
			       skb->data[tp->urg_seq - tp->rcv_nxt];

	tcp_hdr(skb)->fin = 0;
	tlsk->pldlen = CPL_TLS_DATA_LENGTH_G(ntohl(hdr->length_pkd));
	__skb_queue_tail(&tlsk->sk_recv_queue, skb);
पूर्ण

अटल पूर्णांक chtls_rx_pdu(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_tls_data *req = cplhdr(skb);
	अचिन्हित पूर्णांक hwtid = GET_TID(req);
	काष्ठा sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);
	अगर (unlikely(!sk)) अणु
		pr_err("can't find conn. for hwtid %u.\n", hwtid);
		वापस -EINVAL;
	पूर्ण
	skb_dst_set(skb, शून्य);
	process_cpl_msg(chtls_recv_pdu, sk, skb);
	वापस 0;
पूर्ण

अटल व्योम chtls_set_hdrlen(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nlen)
अणु
	काष्ठा tlsrx_cmp_hdr *tls_cmp_hdr = cplhdr(skb);

	skb->hdr_len = ntohs((__क्रमce __be16)tls_cmp_hdr->length);
	tls_cmp_hdr->length = ntohs((__क्रमce __be16)nlen);
पूर्ण

अटल व्योम chtls_rx_hdr(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tlsrx_cmp_hdr *tls_hdr_pkt;
	काष्ठा cpl_rx_tls_cmp *cmp_cpl;
	काष्ठा sk_buff *skb_rec;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_hws *tlsk;
	काष्ठा tcp_sock *tp;

	cmp_cpl = cplhdr(skb);
	csk = rcu_dereference_sk_user_data(sk);
	tlsk = &csk->tlshws;
	tp = tcp_sk(sk);

	ULP_SKB_CB(skb)->seq = ntohl(cmp_cpl->seq);
	ULP_SKB_CB(skb)->flags = 0;

	skb_reset_transport_header(skb);
	__skb_pull(skb, माप(*cmp_cpl));
	tls_hdr_pkt = (काष्ठा tlsrx_cmp_hdr *)skb->data;
	अगर (tls_hdr_pkt->res_to_mac_error & TLSRX_HDR_PKT_ERROR_M)
		tls_hdr_pkt->type = CONTENT_TYPE_ERROR;
	अगर (!skb->data_len)
		__skb_trim(skb, TLS_HEADER_LENGTH);

	tp->rcv_nxt +=
		CPL_RX_TLS_CMP_PDULENGTH_G(ntohl(cmp_cpl->pdulength_length));

	ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_TLS_HDR;
	skb_rec = __skb_dequeue(&tlsk->sk_recv_queue);
	अगर (!skb_rec) अणु
		__skb_queue_tail(&sk->sk_receive_queue, skb);
	पूर्ण अन्यथा अणु
		chtls_set_hdrlen(skb, tlsk->pldlen);
		tlsk->pldlen = 0;
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		__skb_queue_tail(&sk->sk_receive_queue, skb_rec);
	पूर्ण

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		check_sk_callbacks(csk);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक chtls_rx_cmp(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_rx_tls_cmp *req = cplhdr(skb);
	अचिन्हित पूर्णांक hwtid = GET_TID(req);
	काष्ठा sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);
	अगर (unlikely(!sk)) अणु
		pr_err("can't find conn. for hwtid %u.\n", hwtid);
		वापस -EINVAL;
	पूर्ण
	skb_dst_set(skb, शून्य);
	process_cpl_msg(chtls_rx_hdr, sk, skb);

	वापस 0;
पूर्ण

अटल व्योम chtls_समयरुको(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->rcv_nxt++;
	tp->rx_opt.ts_recent_stamp = kसमय_get_seconds();
	tp->srtt_us = 0;
	tcp_समय_रुको(sk, TCP_TIME_WAIT, 0);
पूर्ण

अटल व्योम chtls_peer_बंद(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	अगर (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
		जाओ out;

	sk->sk_shutकरोwn |= RCV_SHUTDOWN;
	sock_set_flag(sk, SOCK_DONE);

	चयन (sk->sk_state) अणु
	हाल TCP_SYN_RECV:
	हाल TCP_ESTABLISHED:
		tcp_set_state(sk, TCP_CLOSE_WAIT);
		अवरोध;
	हाल TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_CLOSING);
		अवरोध;
	हाल TCP_FIN_WAIT2:
		chtls_release_resources(sk);
		अगर (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
			chtls_conn_करोne(sk);
		अन्यथा
			chtls_समयरुको(sk);
		अवरोध;
	शेष:
		pr_info("cpl_peer_close in bad state %d\n", sk->sk_state);
	पूर्ण

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		/* Do not send POLL_HUP क्रम half duplex बंद. */

		अगर ((sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
		    sk->sk_state == TCP_CLOSE)
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
		अन्यथा
			sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	पूर्ण
out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम chtls_बंद_con_rpl(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_बंद_con_rpl *rpl = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk;
	काष्ठा tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);

	अगर (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
		जाओ out;

	tp = tcp_sk(sk);

	tp->snd_una = ntohl(rpl->snd_nxt) - 1;  /* exclude FIN */

	चयन (sk->sk_state) अणु
	हाल TCP_CLOSING:
		chtls_release_resources(sk);
		अगर (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
			chtls_conn_करोne(sk);
		अन्यथा
			chtls_समयरुको(sk);
		अवरोध;
	हाल TCP_LAST_ACK:
		chtls_release_resources(sk);
		chtls_conn_करोne(sk);
		अवरोध;
	हाल TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_FIN_WAIT2);
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;

		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अन्यथा अगर (tcp_sk(sk)->linger2 < 0 &&
			 !csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN))
			chtls_पात_conn(sk, skb);
		अन्यथा अगर (csk_flag_nochk(csk, CSK_TX_DATA_SENT))
			chtls_set_quiesce_ctrl(sk, 0);
		अवरोध;
	शेष:
		pr_info("close_con_rpl in bad state %d\n", sk->sk_state);
	पूर्ण
out:
	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा sk_buff *get_cpl_skb(काष्ठा sk_buff *skb,
				   माप_प्रकार len, gfp_t gfp)
अणु
	अगर (likely(!skb_is_nonlinear(skb) && !skb_cloned(skb))) अणु
		WARN_ONCE(skb->len < len, "skb alloc error");
		__skb_trim(skb, len);
		skb_get(skb);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(len, gfp);
		अगर (skb)
			__skb_put(skb, len);
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम set_पात_rpl_wr(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक tid,
			     पूर्णांक cmd)
अणु
	काष्ठा cpl_पात_rpl *rpl = cplhdr(skb);

	INIT_TP_WR_CPL(rpl, CPL_ABORT_RPL, tid);
	rpl->cmd = cmd;
पूर्ण

अटल व्योम send_defer_पात_rpl(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req_rss *req = cplhdr(skb);
	काष्ठा sk_buff *reply_skb;

	reply_skb = alloc_skb(माप(काष्ठा cpl_पात_rpl),
			      GFP_KERNEL | __GFP_NOFAIL);
	__skb_put(reply_skb, माप(काष्ठा cpl_पात_rpl));
	set_पात_rpl_wr(reply_skb, GET_TID(req),
			 (req->status & CPL_ABORT_NO_RST));
	set_wr_txq(reply_skb, CPL_PRIORITY_DATA, req->status >> 1);
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
	kमुक्त_skb(skb);
पूर्ण

/*
 * Add an skb to the deferred skb queue क्रम processing from process context.
 */
अटल व्योम t4_defer_reply(काष्ठा sk_buff *skb, काष्ठा chtls_dev *cdev,
			   defer_handler_t handler)
अणु
	DEFERRED_SKB_CB(skb)->handler = handler;
	spin_lock_bh(&cdev->deferq.lock);
	__skb_queue_tail(&cdev->deferq, skb);
	अगर (skb_queue_len(&cdev->deferq) == 1)
		schedule_work(&cdev->deferq_task);
	spin_unlock_bh(&cdev->deferq.lock);
पूर्ण

अटल व्योम chtls_send_पात_rpl(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 काष्ठा chtls_dev *cdev,
				 पूर्णांक status, पूर्णांक queue)
अणु
	काष्ठा cpl_पात_req_rss *req = cplhdr(skb) + RSS_HDR;
	काष्ठा sk_buff *reply_skb;
	काष्ठा chtls_sock *csk;
	अचिन्हित पूर्णांक tid;

	csk = rcu_dereference_sk_user_data(sk);
	tid = GET_TID(req);

	reply_skb = get_cpl_skb(skb, माप(काष्ठा cpl_पात_rpl), gfp_any());
	अगर (!reply_skb) अणु
		req->status = (queue << 1) | status;
		t4_defer_reply(skb, cdev, send_defer_पात_rpl);
		वापस;
	पूर्ण

	set_पात_rpl_wr(reply_skb, tid, status);
	kमुक्त_skb(skb);
	set_wr_txq(reply_skb, CPL_PRIORITY_DATA, queue);
	अगर (csk_conn_अंतरभूत(csk)) अणु
		काष्ठा l2t_entry *e = csk->l2t_entry;

		अगर (e && sk->sk_state != TCP_SYN_RECV) अणु
			cxgb4_l2t_send(csk->egress_dev, reply_skb, e);
			वापस;
		पूर्ण
	पूर्ण
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
पूर्ण

/*
 * This is run from a listener's backlog to पात a child connection in
 * SYN_RCV state (i.e., one on the listener's SYN queue).
 */
अटल व्योम bl_पात_syn_rcv(काष्ठा sock *lsk, काष्ठा sk_buff *skb)
अणु
	काष्ठा chtls_sock *csk;
	काष्ठा sock *child;
	पूर्णांक queue;

	child = skb->sk;
	csk = rcu_dereference_sk_user_data(child);
	queue = csk->txq_idx;

	skb->sk	= शून्य;
	chtls_send_पात_rpl(child, skb, BLOG_SKB_CB(skb)->cdev,
			     CPL_ABORT_NO_RST, queue);
	करो_पात_syn_rcv(child, lsk);
पूर्ण

अटल पूर्णांक पात_syn_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा request_sock *oreq;
	काष्ठा listen_ctx *listen_ctx;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;
	काष्ठा sock *psk;
	व्योम *ctx;

	csk = sk->sk_user_data;
	oreq = csk->passive_reap_next;
	cdev = csk->cdev;

	अगर (!oreq)
		वापस -1;

	ctx = lookup_stid(cdev->tids, oreq->ts_recent);
	अगर (!ctx)
		वापस -1;

	listen_ctx = (काष्ठा listen_ctx *)ctx;
	psk = listen_ctx->lsk;

	bh_lock_sock(psk);
	अगर (!sock_owned_by_user(psk)) अणु
		पूर्णांक queue = csk->txq_idx;

		chtls_send_पात_rpl(sk, skb, cdev, CPL_ABORT_NO_RST, queue);
		करो_पात_syn_rcv(sk, psk);
	पूर्ण अन्यथा अणु
		skb->sk = sk;
		BLOG_SKB_CB(skb)->backlog_rcv = bl_पात_syn_rcv;
		__sk_add_backlog(psk, skb);
	पूर्ण
	bh_unlock_sock(psk);
	वापस 0;
पूर्ण

अटल व्योम chtls_पात_req_rss(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा cpl_पात_req_rss *req = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk = sk->sk_user_data;
	पूर्णांक rst_status = CPL_ABORT_NO_RST;
	पूर्णांक queue = csk->txq_idx;

	अगर (is_neg_adv(req->status)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	csk_reset_flag(csk, CSK_ABORT_REQ_RCVD);

	अगर (!csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN) &&
	    !csk_flag_nochk(csk, CSK_TX_DATA_SENT)) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);

		अगर (send_tx_flowc_wr(sk, 0, tp->snd_nxt, tp->rcv_nxt) < 0)
			WARN_ONCE(1, "send_tx_flowc error");
		csk_set_flag(csk, CSK_TX_DATA_SENT);
	पूर्ण

	csk_set_flag(csk, CSK_ABORT_SHUTDOWN);

	अगर (!csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING)) अणु
		sk->sk_err = ETIMEDOUT;

		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		अगर (sk->sk_state == TCP_SYN_RECV && !पात_syn_rcv(sk, skb))
			वापस;

	पूर्ण

	chtls_send_पात_rpl(sk, skb, BLOG_SKB_CB(skb)->cdev,
			     rst_status, queue);
	chtls_release_resources(sk);
	chtls_conn_करोne(sk);
पूर्ण

अटल व्योम chtls_पात_rpl_rss(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_rpl_rss *rpl = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk;
	काष्ठा chtls_dev *cdev;

	csk = rcu_dereference_sk_user_data(sk);
	cdev = csk->cdev;

	अगर (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING)) अणु
		csk_reset_flag(csk, CSK_ABORT_RPL_PENDING);
		अगर (!csk_flag_nochk(csk, CSK_ABORT_REQ_RCVD)) अणु
			अगर (sk->sk_state == TCP_SYN_SENT) अणु
				cxgb4_हटाओ_tid(cdev->tids,
						 csk->port_id,
						 GET_TID(rpl),
						 sk->sk_family);
				sock_put(sk);
			पूर्ण
			chtls_release_resources(sk);
			chtls_conn_करोne(sk);
		पूर्ण
	पूर्ण
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक chtls_conn_cpl(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_peer_बंद *req = cplhdr(skb) + RSS_HDR;
	व्योम (*fn)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	अचिन्हित पूर्णांक hwtid = GET_TID(req);
	काष्ठा chtls_sock *csk;
	काष्ठा sock *sk;
	u8 opcode;

	opcode = ((स्थिर काष्ठा rss_header *)cplhdr(skb))->opcode;

	sk = lookup_tid(cdev->tids, hwtid);
	अगर (!sk)
		जाओ rel_skb;

	csk = sk->sk_user_data;

	चयन (opcode) अणु
	हाल CPL_PEER_CLOSE:
		fn = chtls_peer_बंद;
		अवरोध;
	हाल CPL_CLOSE_CON_RPL:
		fn = chtls_बंद_con_rpl;
		अवरोध;
	हाल CPL_ABORT_REQ_RSS:
		/*
		 * Save the offload device in the skb, we may process this
		 * message after the socket has बंदd.
		 */
		BLOG_SKB_CB(skb)->cdev = csk->cdev;
		fn = chtls_पात_req_rss;
		अवरोध;
	हाल CPL_ABORT_RPL_RSS:
		fn = chtls_पात_rpl_rss;
		अवरोध;
	शेष:
		जाओ rel_skb;
	पूर्ण

	process_cpl_msg(fn, sk, skb);
	वापस 0;

rel_skb:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम chtls_rx_ack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_fw4_ack *hdr = cplhdr(skb) + RSS_HDR;
	काष्ठा chtls_sock *csk = sk->sk_user_data;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 credits = hdr->credits;
	u32 snd_una;

	snd_una = ntohl(hdr->snd_una);
	csk->wr_credits += credits;

	अगर (csk->wr_unacked > csk->wr_max_credits - csk->wr_credits)
		csk->wr_unacked = csk->wr_max_credits - csk->wr_credits;

	जबतक (credits) अणु
		काष्ठा sk_buff *pskb = csk->wr_skb_head;
		u32 csum;

		अगर (unlikely(!pskb)) अणु
			अगर (csk->wr_nondata)
				csk->wr_nondata -= credits;
			अवरोध;
		पूर्ण
		csum = (__क्रमce u32)pskb->csum;
		अगर (unlikely(credits < csum)) अणु
			pskb->csum = (__क्रमce __wsum)(csum - credits);
			अवरोध;
		पूर्ण
		dequeue_wr(sk);
		credits -= csum;
		kमुक्त_skb(pskb);
	पूर्ण
	अगर (hdr->seq_vld & CPL_FW4_ACK_FLAGS_SEQVAL) अणु
		अगर (unlikely(beक्रमe(snd_una, tp->snd_una))) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		अगर (tp->snd_una != snd_una) अणु
			tp->snd_una = snd_una;
			tp->rcv_tstamp = tcp_समय_stamp(tp);
			अगर (tp->snd_una == tp->snd_nxt &&
			    !csk_flag_nochk(csk, CSK_TX_FAILOVER))
				csk_reset_flag(csk, CSK_TX_WAIT_IDLE);
		पूर्ण
	पूर्ण

	अगर (hdr->seq_vld & CPL_FW4_ACK_FLAGS_CH) अणु
		अचिन्हित पूर्णांक fclen16 = roundup(failover_flowc_wr_len, 16);

		csk->wr_credits -= fclen16;
		csk_reset_flag(csk, CSK_TX_WAIT_IDLE);
		csk_reset_flag(csk, CSK_TX_FAILOVER);
	पूर्ण
	अगर (skb_queue_len(&csk->txq) && chtls_push_frames(csk, 0))
		sk->sk_ग_लिखो_space(sk);

	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक chtls_wr_ack(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_fw4_ack *rpl = cplhdr(skb) + RSS_HDR;
	अचिन्हित पूर्णांक hwtid = GET_TID(rpl);
	काष्ठा sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);
	अगर (unlikely(!sk)) अणु
		pr_err("can't find conn. for hwtid %u.\n", hwtid);
		वापस -EINVAL;
	पूर्ण
	process_cpl_msg(chtls_rx_ack, sk, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक chtls_set_tcb_rpl(काष्ठा chtls_dev *cdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_set_tcb_rpl *rpl = cplhdr(skb) + RSS_HDR;
	अचिन्हित पूर्णांक hwtid = GET_TID(rpl);
	काष्ठा sock *sk;

	sk = lookup_tid(cdev->tids, hwtid);

	/* वापस EINVAL अगर socket करोesn't exist */
	अगर (!sk)
		वापस -EINVAL;

	/* Reusing the skb as size of cpl_set_tcb_field काष्ठाure
	 * is greater than cpl_पात_req
	 */
	अगर (TCB_COOKIE_G(rpl->cookie) == TCB_FIELD_COOKIE_TFLAG)
		chtls_send_पात(sk, CPL_ABORT_SEND_RST, शून्य);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

chtls_handler_func chtls_handlers[NUM_CPL_CMDS] = अणु
	[CPL_PASS_OPEN_RPL]     = chtls_pass_खोलो_rpl,
	[CPL_CLOSE_LISTSRV_RPL] = chtls_बंद_listsrv_rpl,
	[CPL_PASS_ACCEPT_REQ]   = chtls_pass_accept_req,
	[CPL_PASS_ESTABLISH]    = chtls_pass_establish,
	[CPL_RX_DATA]           = chtls_rx_data,
	[CPL_TLS_DATA]          = chtls_rx_pdu,
	[CPL_RX_TLS_CMP]        = chtls_rx_cmp,
	[CPL_PEER_CLOSE]        = chtls_conn_cpl,
	[CPL_CLOSE_CON_RPL]     = chtls_conn_cpl,
	[CPL_ABORT_REQ_RSS]     = chtls_conn_cpl,
	[CPL_ABORT_RPL_RSS]     = chtls_conn_cpl,
	[CPL_FW4_ACK]		= chtls_wr_ack,
	[CPL_SET_TCB_RPL]	= chtls_set_tcb_rpl,
पूर्ण;
