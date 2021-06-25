<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2017 - 2019, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/sha2.h>
#समावेश <net/sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
#समावेश <net/ip6_route.h>
#समावेश <net/transp_v6.h>
#पूर्ण_अगर
#समावेश <net/mptcp.h>
#समावेश <uapi/linux/mptcp.h>
#समावेश "protocol.h"
#समावेश "mib.h"

#समावेश <trace/events/mptcp.h>

अटल व्योम mptcp_subflow_ops_unकरो_override(काष्ठा sock *ssk);

अटल व्योम SUBFLOW_REQ_INC_STATS(काष्ठा request_sock *req,
				  क्रमागत linux_mptcp_mib_field field)
अणु
	MPTCP_INC_STATS(sock_net(req_to_sk(req)), field);
पूर्ण

अटल व्योम subflow_req_deकाष्ठाor(काष्ठा request_sock *req)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);

	pr_debug("subflow_req=%p", subflow_req);

	अगर (subflow_req->msk)
		sock_put((काष्ठा sock *)subflow_req->msk);

	mptcp_token_destroy_request(req);
	tcp_request_sock_ops.deकाष्ठाor(req);
पूर्ण

अटल व्योम subflow_generate_hmac(u64 key1, u64 key2, u32 nonce1, u32 nonce2,
				  व्योम *hmac)
अणु
	u8 msg[8];

	put_unaligned_be32(nonce1, &msg[0]);
	put_unaligned_be32(nonce2, &msg[4]);

	mptcp_crypto_hmac_sha(key1, key2, msg, 8, hmac);
पूर्ण

अटल bool mptcp_can_accept_new_subflow(स्थिर काष्ठा mptcp_sock *msk)
अणु
	वापस mptcp_is_fully_established((व्योम *)msk) &&
	       READ_ONCE(msk->pm.accept_subflow);
पूर्ण

/* validate received token and create truncated hmac and nonce क्रम SYN-ACK */
अटल व्योम subflow_req_create_thmac(काष्ठा mptcp_subflow_request_sock *subflow_req)
अणु
	काष्ठा mptcp_sock *msk = subflow_req->msk;
	u8 hmac[SHA256_DIGEST_SIZE];

	get_अक्रमom_bytes(&subflow_req->local_nonce, माप(u32));

	subflow_generate_hmac(msk->local_key, msk->remote_key,
			      subflow_req->local_nonce,
			      subflow_req->remote_nonce, hmac);

	subflow_req->thmac = get_unaligned_be64(hmac);
पूर्ण

अटल काष्ठा mptcp_sock *subflow_token_join_request(काष्ठा request_sock *req)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा mptcp_sock *msk;
	पूर्णांक local_id;

	msk = mptcp_token_get_sock(subflow_req->token);
	अगर (!msk) अणु
		SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINNOTOKEN);
		वापस शून्य;
	पूर्ण

	local_id = mptcp_pm_get_local_id(msk, (काष्ठा sock_common *)req);
	अगर (local_id < 0) अणु
		sock_put((काष्ठा sock *)msk);
		वापस शून्य;
	पूर्ण
	subflow_req->local_id = local_id;

	वापस msk;
पूर्ण

अटल व्योम subflow_init_req(काष्ठा request_sock *req, स्थिर काष्ठा sock *sk_listener)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);

	subflow_req->mp_capable = 0;
	subflow_req->mp_join = 0;
	subflow_req->msk = शून्य;
	mptcp_token_init_request(req);
पूर्ण

अटल bool subflow_use_dअगरferent_sport(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->inet_sport != inet_sk((काष्ठा sock *)msk)->inet_sport;
पूर्ण

अटल व्योम subflow_add_reset_reason(काष्ठा sk_buff *skb, u8 reason)
अणु
	काष्ठा mptcp_ext *mpext = skb_ext_add(skb, SKB_EXT_MPTCP);

	अगर (mpext) अणु
		स_रखो(mpext, 0, माप(*mpext));
		mpext->reset_reason = reason;
	पूर्ण
पूर्ण

/* Init mptcp request socket.
 *
 * Returns an error code अगर a JOIN has failed and a TCP reset
 * should be sent.
 */
अटल पूर्णांक subflow_check_req(काष्ठा request_sock *req,
			     स्थिर काष्ठा sock *sk_listener,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *listener = mptcp_subflow_ctx(sk_listener);
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा mptcp_options_received mp_opt;

	pr_debug("subflow_req=%p, listener=%p", subflow_req, listener);

#अगर_घोषित CONFIG_TCP_MD5SIG
	/* no MPTCP अगर MD5SIG is enabled on this socket or we may run out of
	 * TCP option space.
	 */
	अगर (rcu_access_poपूर्णांकer(tcp_sk(sk_listener)->md5sig_info))
		वापस -EINVAL;
#पूर्ण_अगर

	mptcp_get_options(skb, &mp_opt);

	अगर (mp_opt.mp_capable) अणु
		SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_MPCAPABLEPASSIVE);

		अगर (mp_opt.mp_join)
			वापस 0;
	पूर्ण अन्यथा अगर (mp_opt.mp_join) अणु
		SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINSYNRX);
	पूर्ण

	अगर (mp_opt.mp_capable && listener->request_mptcp) अणु
		पूर्णांक err, retries = 4;

		subflow_req->ssn_offset = TCP_SKB_CB(skb)->seq;
again:
		करो अणु
			get_अक्रमom_bytes(&subflow_req->local_key, माप(subflow_req->local_key));
		पूर्ण जबतक (subflow_req->local_key == 0);

		अगर (unlikely(req->syncookie)) अणु
			mptcp_crypto_key_sha(subflow_req->local_key,
					     &subflow_req->token,
					     &subflow_req->idsn);
			अगर (mptcp_token_exists(subflow_req->token)) अणु
				अगर (retries-- > 0)
					जाओ again;
				SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_TOKENFALLBACKINIT);
			पूर्ण अन्यथा अणु
				subflow_req->mp_capable = 1;
			पूर्ण
			वापस 0;
		पूर्ण

		err = mptcp_token_new_request(req);
		अगर (err == 0)
			subflow_req->mp_capable = 1;
		अन्यथा अगर (retries-- > 0)
			जाओ again;
		अन्यथा
			SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_TOKENFALLBACKINIT);

	पूर्ण अन्यथा अगर (mp_opt.mp_join && listener->request_mptcp) अणु
		subflow_req->ssn_offset = TCP_SKB_CB(skb)->seq;
		subflow_req->mp_join = 1;
		subflow_req->backup = mp_opt.backup;
		subflow_req->remote_id = mp_opt.join_id;
		subflow_req->token = mp_opt.token;
		subflow_req->remote_nonce = mp_opt.nonce;
		subflow_req->msk = subflow_token_join_request(req);

		/* Can't fall back to TCP in this हाल. */
		अगर (!subflow_req->msk) अणु
			subflow_add_reset_reason(skb, MPTCP_RST_EMPTCP);
			वापस -EPERM;
		पूर्ण

		अगर (subflow_use_dअगरferent_sport(subflow_req->msk, sk_listener)) अणु
			pr_debug("syn inet_sport=%d %d",
				 ntohs(inet_sk(sk_listener)->inet_sport),
				 ntohs(inet_sk((काष्ठा sock *)subflow_req->msk)->inet_sport));
			अगर (!mptcp_pm_sport_in_anno_list(subflow_req->msk, sk_listener)) अणु
				sock_put((काष्ठा sock *)subflow_req->msk);
				mptcp_token_destroy_request(req);
				tcp_request_sock_ops.deकाष्ठाor(req);
				subflow_req->msk = शून्य;
				subflow_req->mp_join = 0;
				SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_MISMATCHPORTSYNRX);
				वापस -EPERM;
			पूर्ण
			SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINPORTSYNRX);
		पूर्ण

		subflow_req_create_thmac(subflow_req);

		अगर (unlikely(req->syncookie)) अणु
			अगर (mptcp_can_accept_new_subflow(subflow_req->msk))
				subflow_init_req_cookie_join_save(subflow_req, skb);
		पूर्ण

		pr_debug("token=%u, remote_nonce=%u msk=%p", subflow_req->token,
			 subflow_req->remote_nonce, subflow_req->msk);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mptcp_subflow_init_cookie_req(काष्ठा request_sock *req,
				  स्थिर काष्ठा sock *sk_listener,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *listener = mptcp_subflow_ctx(sk_listener);
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा mptcp_options_received mp_opt;
	पूर्णांक err;

	subflow_init_req(req, sk_listener);
	mptcp_get_options(skb, &mp_opt);

	अगर (mp_opt.mp_capable && mp_opt.mp_join)
		वापस -EINVAL;

	अगर (mp_opt.mp_capable && listener->request_mptcp) अणु
		अगर (mp_opt.sndr_key == 0)
			वापस -EINVAL;

		subflow_req->local_key = mp_opt.rcvr_key;
		err = mptcp_token_new_request(req);
		अगर (err)
			वापस err;

		subflow_req->mp_capable = 1;
		subflow_req->ssn_offset = TCP_SKB_CB(skb)->seq - 1;
	पूर्ण अन्यथा अगर (mp_opt.mp_join && listener->request_mptcp) अणु
		अगर (!mptcp_token_join_cookie_init_state(subflow_req, skb))
			वापस -EINVAL;

		अगर (mptcp_can_accept_new_subflow(subflow_req->msk))
			subflow_req->mp_join = 1;

		subflow_req->ssn_offset = TCP_SKB_CB(skb)->seq - 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_subflow_init_cookie_req);

अटल काष्ठा dst_entry *subflow_v4_route_req(स्थिर काष्ठा sock *sk,
					      काष्ठा sk_buff *skb,
					      काष्ठा flowi *fl,
					      काष्ठा request_sock *req)
अणु
	काष्ठा dst_entry *dst;
	पूर्णांक err;

	tcp_rsk(req)->is_mptcp = 1;
	subflow_init_req(req, sk);

	dst = tcp_request_sock_ipv4_ops.route_req(sk, skb, fl, req);
	अगर (!dst)
		वापस शून्य;

	err = subflow_check_req(req, sk, skb);
	अगर (err == 0)
		वापस dst;

	dst_release(dst);
	अगर (!req->syncookie)
		tcp_request_sock_ops.send_reset(sk, skb);
	वापस शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
अटल काष्ठा dst_entry *subflow_v6_route_req(स्थिर काष्ठा sock *sk,
					      काष्ठा sk_buff *skb,
					      काष्ठा flowi *fl,
					      काष्ठा request_sock *req)
अणु
	काष्ठा dst_entry *dst;
	पूर्णांक err;

	tcp_rsk(req)->is_mptcp = 1;
	subflow_init_req(req, sk);

	dst = tcp_request_sock_ipv6_ops.route_req(sk, skb, fl, req);
	अगर (!dst)
		वापस शून्य;

	err = subflow_check_req(req, sk, skb);
	अगर (err == 0)
		वापस dst;

	dst_release(dst);
	अगर (!req->syncookie)
		tcp6_request_sock_ops.send_reset(sk, skb);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* validate received truncated hmac and create hmac क्रम third ACK */
अटल bool subflow_thmac_valid(काष्ठा mptcp_subflow_context *subflow)
अणु
	u8 hmac[SHA256_DIGEST_SIZE];
	u64 thmac;

	subflow_generate_hmac(subflow->remote_key, subflow->local_key,
			      subflow->remote_nonce, subflow->local_nonce,
			      hmac);

	thmac = get_unaligned_be64(hmac);
	pr_debug("subflow=%p, token=%u, thmac=%llu, subflow->thmac=%llu\n",
		 subflow, subflow->token,
		 (अचिन्हित दीर्घ दीर्घ)thmac,
		 (अचिन्हित दीर्घ दीर्घ)subflow->thmac);

	वापस thmac == subflow->thmac;
पूर्ण

व्योम mptcp_subflow_reset(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा sock *sk = subflow->conn;

	/* must hold: tcp_करोne() could drop last reference on parent */
	sock_hold(sk);

	tcp_set_state(ssk, TCP_CLOSE);
	tcp_send_active_reset(ssk, GFP_ATOMIC);
	tcp_करोne(ssk);
	अगर (!test_and_set_bit(MPTCP_WORK_CLOSE_SUBFLOW, &mptcp_sk(sk)->flags) &&
	    schedule_work(&mptcp_sk(sk)->work))
		वापस; /* worker will put sk क्रम us */

	sock_put(sk);
पूर्ण

अटल bool subflow_use_dअगरferent_dport(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->inet_dport != inet_sk((काष्ठा sock *)msk)->inet_dport;
पूर्ण

अटल व्योम subflow_finish_connect(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_options_received mp_opt;
	काष्ठा sock *parent = subflow->conn;

	subflow->icsk_af_ops->sk_rx_dst_set(sk, skb);

	अगर (inet_sk_state_load(parent) == TCP_SYN_SENT) अणु
		inet_sk_state_store(parent, TCP_ESTABLISHED);
		parent->sk_state_change(parent);
	पूर्ण

	/* be sure no special action on any packet other than syn-ack */
	अगर (subflow->conn_finished)
		वापस;

	mptcp_propagate_sndbuf(parent, sk);
	subflow->rel_ग_लिखो_seq = 1;
	subflow->conn_finished = 1;
	subflow->ssn_offset = TCP_SKB_CB(skb)->seq;
	pr_debug("subflow=%p synack seq=%x", subflow, subflow->ssn_offset);

	mptcp_get_options(skb, &mp_opt);
	अगर (subflow->request_mptcp) अणु
		अगर (!mp_opt.mp_capable) अणु
			MPTCP_INC_STATS(sock_net(sk),
					MPTCP_MIB_MPCAPABLEACTIVEFALLBACK);
			mptcp_करो_fallback(sk);
			pr_fallback(mptcp_sk(subflow->conn));
			जाओ fallback;
		पूर्ण

		subflow->mp_capable = 1;
		subflow->can_ack = 1;
		subflow->remote_key = mp_opt.sndr_key;
		pr_debug("subflow=%p, remote_key=%llu", subflow,
			 subflow->remote_key);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPCAPABLEACTIVEACK);
		mptcp_finish_connect(sk);
	पूर्ण अन्यथा अगर (subflow->request_join) अणु
		u8 hmac[SHA256_DIGEST_SIZE];

		अगर (!mp_opt.mp_join) अणु
			subflow->reset_reason = MPTCP_RST_EMPTCP;
			जाओ करो_reset;
		पूर्ण

		subflow->thmac = mp_opt.thmac;
		subflow->remote_nonce = mp_opt.nonce;
		pr_debug("subflow=%p, thmac=%llu, remote_nonce=%u", subflow,
			 subflow->thmac, subflow->remote_nonce);

		अगर (!subflow_thmac_valid(subflow)) अणु
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINACKMAC);
			subflow->reset_reason = MPTCP_RST_EMPTCP;
			जाओ करो_reset;
		पूर्ण

		subflow_generate_hmac(subflow->local_key, subflow->remote_key,
				      subflow->local_nonce,
				      subflow->remote_nonce,
				      hmac);
		स_नकल(subflow->hmac, hmac, MPTCPOPT_HMAC_LEN);

		अगर (!mptcp_finish_join(sk))
			जाओ करो_reset;

		subflow->mp_join = 1;
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINSYNACKRX);

		अगर (subflow_use_dअगरferent_dport(mptcp_sk(parent), sk)) अणु
			pr_debug("synack inet_dport=%d %d",
				 ntohs(inet_sk(sk)->inet_dport),
				 ntohs(inet_sk(parent)->inet_dport));
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINPORTSYNACKRX);
		पूर्ण
	पूर्ण अन्यथा अगर (mptcp_check_fallback(sk)) अणु
fallback:
		mptcp_rcv_space_init(mptcp_sk(parent), sk);
	पूर्ण
	वापस;

करो_reset:
	subflow->reset_transient = 0;
	mptcp_subflow_reset(sk);
पूर्ण

काष्ठा request_sock_ops mptcp_subflow_request_sock_ops;
EXPORT_SYMBOL_GPL(mptcp_subflow_request_sock_ops);
अटल काष्ठा tcp_request_sock_ops subflow_request_sock_ipv4_ops;

अटल पूर्णांक subflow_v4_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	pr_debug("subflow=%p", subflow);

	/* Never answer to SYNs sent to broadcast or multicast */
	अगर (skb_rtable(skb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		जाओ drop;

	वापस tcp_conn_request(&mptcp_subflow_request_sock_ops,
				&subflow_request_sock_ipv4_ops,
				sk, skb);
drop:
	tcp_listendrop(sk);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
अटल काष्ठा tcp_request_sock_ops subflow_request_sock_ipv6_ops;
अटल काष्ठा inet_connection_sock_af_ops subflow_v6_specअगरic;
अटल काष्ठा inet_connection_sock_af_ops subflow_v6m_specअगरic;
अटल काष्ठा proto tcpv6_prot_override;

अटल पूर्णांक subflow_v6_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	pr_debug("subflow=%p", subflow);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस subflow_v4_conn_request(sk, skb);

	अगर (!ipv6_unicast_destination(skb))
		जाओ drop;

	अगर (ipv6_addr_v4mapped(&ipv6_hdr(skb)->saddr)) अणु
		__IP6_INC_STATS(sock_net(sk), शून्य, IPSTATS_MIB_INHDRERRORS);
		वापस 0;
	पूर्ण

	वापस tcp_conn_request(&mptcp_subflow_request_sock_ops,
				&subflow_request_sock_ipv6_ops, sk, skb);

drop:
	tcp_listendrop(sk);
	वापस 0; /* करोn't send reset */
पूर्ण
#पूर्ण_अगर

/* validate hmac received in third ACK */
अटल bool subflow_hmac_valid(स्थिर काष्ठा request_sock *req,
			       स्थिर काष्ठा mptcp_options_received *mp_opt)
अणु
	स्थिर काष्ठा mptcp_subflow_request_sock *subflow_req;
	u8 hmac[SHA256_DIGEST_SIZE];
	काष्ठा mptcp_sock *msk;

	subflow_req = mptcp_subflow_rsk(req);
	msk = subflow_req->msk;
	अगर (!msk)
		वापस false;

	subflow_generate_hmac(msk->remote_key, msk->local_key,
			      subflow_req->remote_nonce,
			      subflow_req->local_nonce, hmac);

	वापस !crypto_memneq(hmac, mp_opt->hmac, MPTCPOPT_HMAC_LEN);
पूर्ण

अटल व्योम mptcp_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	/* अगर new mptcp socket isn't accepted, it is free'd
	 * from the tcp listener sockets request queue, linked
	 * from req->sk.  The tcp socket is released.
	 * This calls the ULP release function which will
	 * also हटाओ the mptcp socket, via
	 * sock_put(ctx->conn).
	 *
	 * Problem is that the mptcp socket will be in
	 * ESTABLISHED state and will not have the SOCK_DEAD flag.
	 * Both result in warnings from inet_sock_deकाष्ठा.
	 */
	अगर ((1 << sk->sk_state) & (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) अणु
		sk->sk_state = TCP_CLOSE;
		WARN_ON_ONCE(sk->sk_socket);
		sock_orphan(sk);
	पूर्ण

	mptcp_destroy_common(mptcp_sk(sk));
	inet_sock_deकाष्ठा(sk);
पूर्ण

अटल व्योम mptcp_क्रमce_बंद(काष्ठा sock *sk)
अणु
	inet_sk_state_store(sk, TCP_CLOSE);
	sk_common_release(sk);
पूर्ण

अटल व्योम subflow_ulp_fallback(काष्ठा sock *sk,
				 काष्ठा mptcp_subflow_context *old_ctx)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	mptcp_subflow_tcp_fallback(sk, old_ctx);
	icsk->icsk_ulp_ops = शून्य;
	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, शून्य);
	tcp_sk(sk)->is_mptcp = 0;

	mptcp_subflow_ops_unकरो_override(sk);
पूर्ण

अटल व्योम subflow_drop_ctx(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *ctx = mptcp_subflow_ctx(ssk);

	अगर (!ctx)
		वापस;

	subflow_ulp_fallback(ssk, ctx);
	अगर (ctx->conn)
		sock_put(ctx->conn);

	kमुक्त_rcu(ctx, rcu);
पूर्ण

व्योम mptcp_subflow_fully_established(काष्ठा mptcp_subflow_context *subflow,
				     काष्ठा mptcp_options_received *mp_opt)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);

	subflow->remote_key = mp_opt->sndr_key;
	subflow->fully_established = 1;
	subflow->can_ack = 1;
	WRITE_ONCE(msk->fully_established, true);
पूर्ण

अटल काष्ठा sock *subflow_syn_recv_sock(स्थिर काष्ठा sock *sk,
					  काष्ठा sk_buff *skb,
					  काष्ठा request_sock *req,
					  काष्ठा dst_entry *dst,
					  काष्ठा request_sock *req_unhash,
					  bool *own_req)
अणु
	काष्ठा mptcp_subflow_context *listener = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_subflow_request_sock *subflow_req;
	काष्ठा mptcp_options_received mp_opt;
	bool fallback, fallback_is_fatal;
	काष्ठा sock *new_msk = शून्य;
	काष्ठा sock *child;

	pr_debug("listener=%p, req=%p, conn=%p", listener, req, listener->conn);

	/* After child creation we must look क्रम 'mp_capable' even when options
	 * are not parsed
	 */
	mp_opt.mp_capable = 0;

	/* hopefully temporary handling क्रम MP_JOIN+syncookie */
	subflow_req = mptcp_subflow_rsk(req);
	fallback_is_fatal = tcp_rsk(req)->is_mptcp && subflow_req->mp_join;
	fallback = !tcp_rsk(req)->is_mptcp;
	अगर (fallback)
		जाओ create_child;

	/* अगर the sk is MP_CAPABLE, we try to fetch the client key */
	अगर (subflow_req->mp_capable) अणु
		/* we can receive and accept an in-winकरोw, out-of-order pkt,
		 * which may not carry the MP_CAPABLE opt even on mptcp enabled
		 * paths: always try to extract the peer key, and fallback
		 * क्रम packets missing it.
		 * Even OoO DSS packets coming legitly after dropped or
		 * reordered MPC will cause fallback, but we करोn't have other
		 * options.
		 */
		mptcp_get_options(skb, &mp_opt);
		अगर (!mp_opt.mp_capable) अणु
			fallback = true;
			जाओ create_child;
		पूर्ण

		new_msk = mptcp_sk_clone(listener->conn, &mp_opt, req);
		अगर (!new_msk)
			fallback = true;
	पूर्ण अन्यथा अगर (subflow_req->mp_join) अणु
		mptcp_get_options(skb, &mp_opt);
		अगर (!mp_opt.mp_join || !subflow_hmac_valid(req, &mp_opt) ||
		    !mptcp_can_accept_new_subflow(subflow_req->msk)) अणु
			SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINACKMAC);
			fallback = true;
		पूर्ण
	पूर्ण

create_child:
	child = listener->icsk_af_ops->syn_recv_sock(sk, skb, req, dst,
						     req_unhash, own_req);

	अगर (child && *own_req) अणु
		काष्ठा mptcp_subflow_context *ctx = mptcp_subflow_ctx(child);

		tcp_rsk(req)->drop_req = false;

		/* we need to fallback on ctx allocation failure and on pre-reqs
		 * checking above. In the latter scenario we additionally need
		 * to reset the context to non MPTCP status.
		 */
		अगर (!ctx || fallback) अणु
			अगर (fallback_is_fatal) अणु
				subflow_add_reset_reason(skb, MPTCP_RST_EMPTCP);
				जाओ dispose_child;
			पूर्ण

			subflow_drop_ctx(child);
			जाओ out;
		पूर्ण

		/* ssk inherits options of listener sk */
		ctx->setsockopt_seq = listener->setsockopt_seq;

		अगर (ctx->mp_capable) अणु
			/* this can't race with mptcp_बंद(), as the msk is
			 * not yet exposted to user-space
			 */
			inet_sk_state_store((व्योम *)new_msk, TCP_ESTABLISHED);

			/* record the newly created socket as the first msk
			 * subflow, but करोn't link it yet पूर्णांकo conn_list
			 */
			WRITE_ONCE(mptcp_sk(new_msk)->first, child);

			/* new mpc subflow takes ownership of the newly
			 * created mptcp socket
			 */
			new_msk->sk_deकाष्ठा = mptcp_sock_deकाष्ठा;
			mptcp_sk(new_msk)->setsockopt_seq = ctx->setsockopt_seq;
			mptcp_pm_new_connection(mptcp_sk(new_msk), child, 1);
			mptcp_token_accept(subflow_req, mptcp_sk(new_msk));
			ctx->conn = new_msk;
			new_msk = शून्य;

			/* with OoO packets we can reach here without ingress
			 * mpc option
			 */
			अगर (mp_opt.mp_capable)
				mptcp_subflow_fully_established(ctx, &mp_opt);
		पूर्ण अन्यथा अगर (ctx->mp_join) अणु
			काष्ठा mptcp_sock *owner;

			owner = subflow_req->msk;
			अगर (!owner) अणु
				subflow_add_reset_reason(skb, MPTCP_RST_EPROHIBIT);
				जाओ dispose_child;
			पूर्ण

			/* move the msk reference ownership to the subflow */
			subflow_req->msk = शून्य;
			ctx->conn = (काष्ठा sock *)owner;

			अगर (subflow_use_dअगरferent_sport(owner, sk)) अणु
				pr_debug("ack inet_sport=%d %d",
					 ntohs(inet_sk(sk)->inet_sport),
					 ntohs(inet_sk((काष्ठा sock *)owner)->inet_sport));
				अगर (!mptcp_pm_sport_in_anno_list(owner, sk)) अणु
					SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_MISMATCHPORTACKRX);
					जाओ dispose_child;
				पूर्ण
				SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINPORTACKRX);
			पूर्ण

			अगर (!mptcp_finish_join(child))
				जाओ dispose_child;

			SUBFLOW_REQ_INC_STATS(req, MPTCP_MIB_JOINACKRX);
			tcp_rsk(req)->drop_req = true;
		पूर्ण
	पूर्ण

out:
	/* dispose of the left over mptcp master, अगर any */
	अगर (unlikely(new_msk))
		mptcp_क्रमce_बंद(new_msk);

	/* check क्रम expected invariant - should never trigger, just help
	 * catching eariler subtle bugs
	 */
	WARN_ON_ONCE(child && *own_req && tcp_sk(child)->is_mptcp &&
		     (!mptcp_subflow_ctx(child) ||
		      !mptcp_subflow_ctx(child)->conn));
	वापस child;

dispose_child:
	subflow_drop_ctx(child);
	tcp_rsk(req)->drop_req = true;
	inet_csk_prepare_क्रम_destroy_sock(child);
	tcp_करोne(child);
	req->rsk_ops->send_reset(sk, skb);

	/* The last child reference will be released by the caller */
	वापस child;
पूर्ण

अटल काष्ठा inet_connection_sock_af_ops subflow_specअगरic;
अटल काष्ठा proto tcp_prot_override;

क्रमागत mapping_status अणु
	MAPPING_OK,
	MAPPING_INVALID,
	MAPPING_EMPTY,
	MAPPING_DATA_FIN,
	MAPPING_DUMMY
पूर्ण;

अटल u64 expand_seq(u64 old_seq, u16 old_data_len, u64 seq)
अणु
	अगर ((u32)seq == (u32)old_seq)
		वापस old_seq;

	/* Assume map covers data not mapped yet. */
	वापस seq | ((old_seq + old_data_len + 1) & GENMASK_ULL(63, 32));
पूर्ण

अटल व्योम dbg_bad_map(काष्ठा mptcp_subflow_context *subflow, u32 ssn)
अणु
	pr_debug("Bad mapping: ssn=%d map_seq=%d map_data_len=%d",
		 ssn, subflow->map_subflow_seq, subflow->map_data_len);
पूर्ण

अटल bool skb_is_fully_mapped(काष्ठा sock *ssk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	अचिन्हित पूर्णांक skb_consumed;

	skb_consumed = tcp_sk(ssk)->copied_seq - TCP_SKB_CB(skb)->seq;
	अगर (WARN_ON_ONCE(skb_consumed >= skb->len))
		वापस true;

	वापस skb->len - skb_consumed <= subflow->map_data_len -
					  mptcp_subflow_get_map_offset(subflow);
पूर्ण

अटल bool validate_mapping(काष्ठा sock *ssk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	u32 ssn = tcp_sk(ssk)->copied_seq - subflow->ssn_offset;

	अगर (unlikely(beक्रमe(ssn, subflow->map_subflow_seq))) अणु
		/* Mapping covers data later in the subflow stream,
		 * currently unsupported.
		 */
		dbg_bad_map(subflow, ssn);
		वापस false;
	पूर्ण
	अगर (unlikely(!beक्रमe(ssn, subflow->map_subflow_seq +
				  subflow->map_data_len))) अणु
		/* Mapping करोes covers past subflow data, invalid */
		dbg_bad_map(subflow, ssn);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल क्रमागत mapping_status get_mapping_status(काष्ठा sock *ssk,
					      काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा mptcp_ext *mpext;
	काष्ठा sk_buff *skb;
	u16 data_len;
	u64 map_seq;

	skb = skb_peek(&ssk->sk_receive_queue);
	अगर (!skb)
		वापस MAPPING_EMPTY;

	अगर (mptcp_check_fallback(ssk))
		वापस MAPPING_DUMMY;

	mpext = mptcp_get_ext(skb);
	अगर (!mpext || !mpext->use_map) अणु
		अगर (!subflow->map_valid && !skb->len) अणु
			/* the TCP stack deliver 0 len FIN pkt to the receive
			 * queue, that is the only 0len pkts ever expected here,
			 * and we can admit no mapping only क्रम 0 len pkts
			 */
			अगर (!(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN))
				WARN_ONCE(1, "0len seq %d:%d flags %x",
					  TCP_SKB_CB(skb)->seq,
					  TCP_SKB_CB(skb)->end_seq,
					  TCP_SKB_CB(skb)->tcp_flags);
			sk_eat_skb(ssk, skb);
			वापस MAPPING_EMPTY;
		पूर्ण

		अगर (!subflow->map_valid)
			वापस MAPPING_INVALID;

		जाओ validate_seq;
	पूर्ण

	trace_get_mapping_status(mpext);

	data_len = mpext->data_len;
	अगर (data_len == 0) अणु
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_INFINITEMAPRX);
		वापस MAPPING_INVALID;
	पूर्ण

	अगर (mpext->data_fin == 1) अणु
		अगर (data_len == 1) अणु
			bool updated = mptcp_update_rcv_data_fin(msk, mpext->data_seq,
								 mpext->dsn64);
			pr_debug("DATA_FIN with no payload seq=%llu", mpext->data_seq);
			अगर (subflow->map_valid) अणु
				/* A DATA_FIN might arrive in a DSS
				 * option beक्रमe the previous mapping
				 * has been fully consumed. Continue
				 * handling the existing mapping.
				 */
				skb_ext_del(skb, SKB_EXT_MPTCP);
				वापस MAPPING_OK;
			पूर्ण अन्यथा अणु
				अगर (updated && schedule_work(&msk->work))
					sock_hold((काष्ठा sock *)msk);

				वापस MAPPING_DATA_FIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			u64 data_fin_seq = mpext->data_seq + data_len - 1;

			/* If mpext->data_seq is a 32-bit value, data_fin_seq
			 * must also be limited to 32 bits.
			 */
			अगर (!mpext->dsn64)
				data_fin_seq &= GENMASK_ULL(31, 0);

			mptcp_update_rcv_data_fin(msk, data_fin_seq, mpext->dsn64);
			pr_debug("DATA_FIN with mapping seq=%llu dsn64=%d",
				 data_fin_seq, mpext->dsn64);
		पूर्ण

		/* Adjust क्रम DATA_FIN using 1 byte of sequence space */
		data_len--;
	पूर्ण

	अगर (!mpext->dsn64) अणु
		map_seq = expand_seq(subflow->map_seq, subflow->map_data_len,
				     mpext->data_seq);
		pr_debug("expanded seq=%llu", subflow->map_seq);
	पूर्ण अन्यथा अणु
		map_seq = mpext->data_seq;
	पूर्ण
	WRITE_ONCE(mptcp_sk(subflow->conn)->use_64bit_ack, !!mpext->dsn64);

	अगर (subflow->map_valid) अणु
		/* Allow replacing only with an identical map */
		अगर (subflow->map_seq == map_seq &&
		    subflow->map_subflow_seq == mpext->subflow_seq &&
		    subflow->map_data_len == data_len) अणु
			skb_ext_del(skb, SKB_EXT_MPTCP);
			वापस MAPPING_OK;
		पूर्ण

		/* If this skb data are fully covered by the current mapping,
		 * the new map would need caching, which is not supported
		 */
		अगर (skb_is_fully_mapped(ssk, skb)) अणु
			MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DSSNOMATCH);
			वापस MAPPING_INVALID;
		पूर्ण

		/* will validate the next map after consuming the current one */
		वापस MAPPING_OK;
	पूर्ण

	subflow->map_seq = map_seq;
	subflow->map_subflow_seq = mpext->subflow_seq;
	subflow->map_data_len = data_len;
	subflow->map_valid = 1;
	subflow->mpc_map = mpext->mpc_map;
	pr_debug("new map seq=%llu subflow_seq=%u data_len=%u",
		 subflow->map_seq, subflow->map_subflow_seq,
		 subflow->map_data_len);

validate_seq:
	/* we revalidate valid mapping on new skb, because we must ensure
	 * the current skb is completely covered by the available mapping
	 */
	अगर (!validate_mapping(ssk, skb))
		वापस MAPPING_INVALID;

	skb_ext_del(skb, SKB_EXT_MPTCP);
	वापस MAPPING_OK;
पूर्ण

अटल व्योम mptcp_subflow_discard_data(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
				       u64 limit)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	bool fin = TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN;
	u32 incr;

	incr = limit >= skb->len ? skb->len + fin : limit;

	pr_debug("discarding=%d len=%d seq=%d", incr, skb->len,
		 subflow->map_subflow_seq);
	MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DUPDATA);
	tcp_sk(ssk)->copied_seq += incr;
	अगर (!beक्रमe(tcp_sk(ssk)->copied_seq, TCP_SKB_CB(skb)->end_seq))
		sk_eat_skb(ssk, skb);
	अगर (mptcp_subflow_get_map_offset(subflow) >= subflow->map_data_len)
		subflow->map_valid = 0;
पूर्ण

/* sched mptcp worker to हटाओ the subflow अगर no more data is pending */
अटल व्योम subflow_sched_work_अगर_बंदd(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	अगर (likely(ssk->sk_state != TCP_CLOSE))
		वापस;

	अगर (skb_queue_empty(&ssk->sk_receive_queue) &&
	    !test_and_set_bit(MPTCP_WORK_CLOSE_SUBFLOW, &msk->flags)) अणु
		sock_hold(sk);
		अगर (!schedule_work(&msk->work))
			sock_put(sk);
	पूर्ण
पूर्ण

अटल bool subflow_check_data_avail(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	क्रमागत mapping_status status;
	काष्ठा mptcp_sock *msk;
	काष्ठा sk_buff *skb;

	अगर (!skb_peek(&ssk->sk_receive_queue))
		WRITE_ONCE(subflow->data_avail, 0);
	अगर (subflow->data_avail)
		वापस true;

	msk = mptcp_sk(subflow->conn);
	क्रम (;;) अणु
		u64 ack_seq;
		u64 old_ack;

		status = get_mapping_status(ssk, msk);
		trace_subflow_check_data_avail(status, skb_peek(&ssk->sk_receive_queue));
		अगर (unlikely(status == MAPPING_INVALID))
			जाओ fallback;

		अगर (unlikely(status == MAPPING_DUMMY))
			जाओ fallback;

		अगर (status != MAPPING_OK)
			जाओ no_data;

		skb = skb_peek(&ssk->sk_receive_queue);
		अगर (WARN_ON_ONCE(!skb))
			जाओ no_data;

		/* अगर msk lacks the remote key, this subflow must provide an
		 * MP_CAPABLE-based mapping
		 */
		अगर (unlikely(!READ_ONCE(msk->can_ack))) अणु
			अगर (!subflow->mpc_map)
				जाओ fallback;
			WRITE_ONCE(msk->remote_key, subflow->remote_key);
			WRITE_ONCE(msk->ack_seq, subflow->map_seq);
			WRITE_ONCE(msk->can_ack, true);
		पूर्ण

		old_ack = READ_ONCE(msk->ack_seq);
		ack_seq = mptcp_subflow_get_mapped_dsn(subflow);
		pr_debug("msk ack_seq=%llx subflow ack_seq=%llx", old_ack,
			 ack_seq);
		अगर (unlikely(beक्रमe64(ack_seq, old_ack))) अणु
			mptcp_subflow_discard_data(ssk, skb, old_ack - ack_seq);
			जारी;
		पूर्ण

		WRITE_ONCE(subflow->data_avail, MPTCP_SUBFLOW_DATA_AVAIL);
		अवरोध;
	पूर्ण
	वापस true;

no_data:
	subflow_sched_work_अगर_बंदd(msk, ssk);
	वापस false;

fallback:
	/* RFC 8684 section 3.7. */
	अगर (subflow->mp_join || subflow->fully_established) अणु
		/* fatal protocol error, बंद the socket.
		 * subflow_error_report() will पूर्णांकroduce the appropriate barriers
		 */
		ssk->sk_err = EBADMSG;
		tcp_set_state(ssk, TCP_CLOSE);
		subflow->reset_transient = 0;
		subflow->reset_reason = MPTCP_RST_EMPTCP;
		tcp_send_active_reset(ssk, GFP_ATOMIC);
		WRITE_ONCE(subflow->data_avail, 0);
		वापस false;
	पूर्ण

	__mptcp_करो_fallback(msk);
	skb = skb_peek(&ssk->sk_receive_queue);
	subflow->map_valid = 1;
	subflow->map_seq = READ_ONCE(msk->ack_seq);
	subflow->map_data_len = skb->len;
	subflow->map_subflow_seq = tcp_sk(ssk)->copied_seq - subflow->ssn_offset;
	WRITE_ONCE(subflow->data_avail, MPTCP_SUBFLOW_DATA_AVAIL);
	वापस true;
पूर्ण

bool mptcp_subflow_data_available(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);

	/* check अगर current mapping is still valid */
	अगर (subflow->map_valid &&
	    mptcp_subflow_get_map_offset(subflow) >= subflow->map_data_len) अणु
		subflow->map_valid = 0;
		WRITE_ONCE(subflow->data_avail, 0);

		pr_debug("Done with mapping: seq=%u data_len=%u",
			 subflow->map_subflow_seq,
			 subflow->map_data_len);
	पूर्ण

	वापस subflow_check_data_avail(sk);
पूर्ण

/* If ssk has an mptcp parent socket, use the mptcp rcvbuf occupancy,
 * not the ssk one.
 *
 * In mptcp, rwin is about the mptcp-level connection data.
 *
 * Data that is still on the ssk rx queue can thus be ignored,
 * as far as mptcp peer is concerned that data is still inflight.
 * DSS ACK is updated when skb is moved to the mptcp rx queue.
 */
व्योम mptcp_space(स्थिर काष्ठा sock *ssk, पूर्णांक *space, पूर्णांक *full_space)
अणु
	स्थिर काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	स्थिर काष्ठा sock *sk = subflow->conn;

	*space = __mptcp_space(sk);
	*full_space = tcp_full_space(sk);
पूर्ण

व्योम __mptcp_error_report(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		पूर्णांक err = sock_error(ssk);

		अगर (!err)
			जारी;

		/* only propagate errors on fallen-back sockets or
		 * on MPC connect
		 */
		अगर (sk->sk_state != TCP_SYN_SENT && !__mptcp_check_fallback(msk))
			जारी;

		inet_sk_state_store(sk, inet_sk_state_load(ssk));
		sk->sk_err = -err;

		/* This barrier is coupled with smp_rmb() in mptcp_poll() */
		smp_wmb();
		sk->sk_error_report(sk);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम subflow_error_report(काष्ठा sock *ssk)
अणु
	काष्ठा sock *sk = mptcp_subflow_ctx(ssk)->conn;

	mptcp_data_lock(sk);
	अगर (!sock_owned_by_user(sk))
		__mptcp_error_report(sk);
	अन्यथा
		set_bit(MPTCP_ERROR_REPORT,  &mptcp_sk(sk)->flags);
	mptcp_data_unlock(sk);
पूर्ण

अटल व्योम subflow_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	u16 state = 1 << inet_sk_state_load(sk);
	काष्ठा sock *parent = subflow->conn;
	काष्ठा mptcp_sock *msk;

	msk = mptcp_sk(parent);
	अगर (state & TCPF_LISTEN) अणु
		/* MPJ subflow are हटाओd from accept queue beक्रमe reaching here,
		 * aव्योम stray wakeups
		 */
		अगर (reqsk_queue_empty(&inet_csk(sk)->icsk_accept_queue))
			वापस;

		set_bit(MPTCP_DATA_READY, &msk->flags);
		parent->sk_data_पढ़ोy(parent);
		वापस;
	पूर्ण

	WARN_ON_ONCE(!__mptcp_check_fallback(msk) && !subflow->mp_capable &&
		     !subflow->mp_join && !(state & TCPF_CLOSE));

	अगर (mptcp_subflow_data_available(sk))
		mptcp_data_पढ़ोy(parent, sk);
	अन्यथा अगर (unlikely(sk->sk_err))
		subflow_error_report(sk);
पूर्ण

अटल व्योम subflow_ग_लिखो_space(काष्ठा sock *ssk)
अणु
	काष्ठा sock *sk = mptcp_subflow_ctx(ssk)->conn;

	mptcp_propagate_sndbuf(sk, ssk);
	mptcp_ग_लिखो_space(sk);
पूर्ण

अटल काष्ठा inet_connection_sock_af_ops *
subflow_शेष_af_ops(काष्ठा sock *sk)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस &subflow_v6_specअगरic;
#पूर्ण_अगर
	वापस &subflow_specअगरic;
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
व्योम mptcpv6_handle_mapped(काष्ठा sock *sk, bool mapped)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_connection_sock_af_ops *target;

	target = mapped ? &subflow_v6m_specअगरic : subflow_शेष_af_ops(sk);

	pr_debug("subflow=%p family=%d ops=%p target=%p mapped=%d",
		 subflow, sk->sk_family, icsk->icsk_af_ops, target, mapped);

	अगर (likely(icsk->icsk_af_ops == target))
		वापस;

	subflow->icsk_af_ops = icsk->icsk_af_ops;
	icsk->icsk_af_ops = target;
पूर्ण
#पूर्ण_अगर

व्योम mptcp_info2sockaddr(स्थिर काष्ठा mptcp_addr_info *info,
			 काष्ठा sockaddr_storage *addr,
			 अचिन्हित लघु family)
अणु
	स_रखो(addr, 0, माप(*addr));
	addr->ss_family = family;
	अगर (addr->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *in_addr = (काष्ठा sockaddr_in *)addr;

		अगर (info->family == AF_INET)
			in_addr->sin_addr = info->addr;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		अन्यथा अगर (ipv6_addr_v4mapped(&info->addr6))
			in_addr->sin_addr.s_addr = info->addr6.s6_addr32[3];
#पूर्ण_अगर
		in_addr->sin_port = info->port;
	पूर्ण
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अन्यथा अगर (addr->ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *in6_addr = (काष्ठा sockaddr_in6 *)addr;

		अगर (info->family == AF_INET)
			ipv6_addr_set_v4mapped(info->addr.s_addr,
					       &in6_addr->sin6_addr);
		अन्यथा
			in6_addr->sin6_addr = info->addr6;
		in6_addr->sin6_port = info->port;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक __mptcp_subflow_connect(काष्ठा sock *sk, स्थिर काष्ठा mptcp_addr_info *loc,
			    स्थिर काष्ठा mptcp_addr_info *remote,
			    u8 flags, पूर्णांक अगरindex)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sockaddr_storage addr;
	पूर्णांक remote_id = remote->id;
	पूर्णांक local_id = loc->id;
	काष्ठा socket *sf;
	काष्ठा sock *ssk;
	u32 remote_token;
	पूर्णांक addrlen;
	पूर्णांक err;

	अगर (!mptcp_is_fully_established(sk))
		वापस -ENOTCONN;

	err = mptcp_subflow_create_socket(sk, &sf);
	अगर (err)
		वापस err;

	ssk = sf->sk;
	subflow = mptcp_subflow_ctx(ssk);
	करो अणु
		get_अक्रमom_bytes(&subflow->local_nonce, माप(u32));
	पूर्ण जबतक (!subflow->local_nonce);

	अगर (!local_id) अणु
		err = mptcp_pm_get_local_id(msk, (काष्ठा sock_common *)ssk);
		अगर (err < 0)
			जाओ failed;

		local_id = err;
	पूर्ण

	subflow->remote_key = msk->remote_key;
	subflow->local_key = msk->local_key;
	subflow->token = msk->token;
	mptcp_info2sockaddr(loc, &addr, ssk->sk_family);

	addrlen = माप(काष्ठा sockaddr_in);
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (addr.ss_family == AF_INET6)
		addrlen = माप(काष्ठा sockaddr_in6);
#पूर्ण_अगर
	ssk->sk_bound_dev_अगर = अगरindex;
	err = kernel_bind(sf, (काष्ठा sockaddr *)&addr, addrlen);
	अगर (err)
		जाओ failed;

	mptcp_crypto_key_sha(subflow->remote_key, &remote_token, शून्य);
	pr_debug("msk=%p remote_token=%u local_id=%d remote_id=%d", msk,
		 remote_token, local_id, remote_id);
	subflow->remote_token = remote_token;
	subflow->local_id = local_id;
	subflow->remote_id = remote_id;
	subflow->request_join = 1;
	subflow->request_bkup = !!(flags & MPTCP_PM_ADDR_FLAG_BACKUP);
	mptcp_info2sockaddr(remote, &addr, ssk->sk_family);

	mptcp_add_pending_subflow(msk, subflow);
	mptcp_sockopt_sync(msk, ssk);
	err = kernel_connect(sf, (काष्ठा sockaddr *)&addr, addrlen, O_NONBLOCK);
	अगर (err && err != -EINPROGRESS)
		जाओ failed_unlink;

	/* discard the subflow socket */
	mptcp_sock_graft(ssk, sk->sk_socket);
	iput(SOCK_INODE(sf));
	वापस err;

failed_unlink:
	spin_lock_bh(&msk->join_list_lock);
	list_del(&subflow->node);
	spin_unlock_bh(&msk->join_list_lock);
	sock_put(mptcp_subflow_tcp_sock(subflow));

failed:
	subflow->disposable = 1;
	sock_release(sf);
	वापस err;
पूर्ण

अटल व्योम mptcp_attach_cgroup(काष्ठा sock *parent, काष्ठा sock *child)
अणु
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	काष्ठा sock_cgroup_data *parent_skcd = &parent->sk_cgrp_data,
				*child_skcd = &child->sk_cgrp_data;

	/* only the additional subflows created by kworkers have to be modअगरied */
	अगर (cgroup_id(sock_cgroup_ptr(parent_skcd)) !=
	    cgroup_id(sock_cgroup_ptr(child_skcd))) अणु
#अगर_घोषित CONFIG_MEMCG
		काष्ठा mem_cgroup *memcg = parent->sk_memcg;

		mem_cgroup_sk_मुक्त(child);
		अगर (memcg && css_tryget(&memcg->css))
			child->sk_memcg = memcg;
#पूर्ण_अगर /* CONFIG_MEMCG */

		cgroup_sk_मुक्त(child_skcd);
		*child_skcd = *parent_skcd;
		cgroup_sk_clone(child_skcd);
	पूर्ण
#पूर्ण_अगर /* CONFIG_SOCK_CGROUP_DATA */
पूर्ण

अटल व्योम mptcp_subflow_ops_override(काष्ठा sock *ssk)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (ssk->sk_prot == &tcpv6_prot)
		ssk->sk_prot = &tcpv6_prot_override;
	अन्यथा
#पूर्ण_अगर
		ssk->sk_prot = &tcp_prot_override;
पूर्ण

अटल व्योम mptcp_subflow_ops_unकरो_override(काष्ठा sock *ssk)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (ssk->sk_prot == &tcpv6_prot_override)
		ssk->sk_prot = &tcpv6_prot;
	अन्यथा
#पूर्ण_अगर
		ssk->sk_prot = &tcp_prot;
पूर्ण
पूर्णांक mptcp_subflow_create_socket(काष्ठा sock *sk, काष्ठा socket **new_sock)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा net *net = sock_net(sk);
	काष्ठा socket *sf;
	पूर्णांक err;

	/* un-accepted server sockets can reach here - on bad configuration
	 * bail early to aव्योम greater trouble later
	 */
	अगर (unlikely(!sk->sk_socket))
		वापस -EINVAL;

	err = sock_create_kern(net, sk->sk_family, SOCK_STREAM, IPPROTO_TCP,
			       &sf);
	अगर (err)
		वापस err;

	lock_sock(sf->sk);

	/* the newly created socket has to be in the same cgroup as its parent */
	mptcp_attach_cgroup(sk, sf->sk);

	/* kernel sockets करो not by शेष acquire net ref, but TCP समयr
	 * needs it.
	 */
	sf->sk->sk_net_refcnt = 1;
	get_net(net);
#अगर_घोषित CONFIG_PROC_FS
	this_cpu_add(*net->core.sock_inuse, 1);
#पूर्ण_अगर
	err = tcp_set_ulp(sf->sk, "mptcp");
	release_sock(sf->sk);

	अगर (err) अणु
		sock_release(sf);
		वापस err;
	पूर्ण

	/* the newly created socket really beदीर्घs to the owning MPTCP master
	 * socket, even अगर क्रम additional subflows the allocation is perक्रमmed
	 * by a kernel workqueue. Adjust inode references, so that the
	 * procfs/diag पूर्णांकeraces really show this one beदीर्घing to the correct
	 * user.
	 */
	SOCK_INODE(sf)->i_ino = SOCK_INODE(sk->sk_socket)->i_ino;
	SOCK_INODE(sf)->i_uid = SOCK_INODE(sk->sk_socket)->i_uid;
	SOCK_INODE(sf)->i_gid = SOCK_INODE(sk->sk_socket)->i_gid;

	subflow = mptcp_subflow_ctx(sf->sk);
	pr_debug("subflow=%p", subflow);

	*new_sock = sf;
	sock_hold(sk);
	subflow->conn = sk;
	mptcp_subflow_ops_override(sf->sk);

	वापस 0;
पूर्ण

अटल काष्ठा mptcp_subflow_context *subflow_create_ctx(काष्ठा sock *sk,
							gfp_t priority)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा mptcp_subflow_context *ctx;

	ctx = kzalloc(माप(*ctx), priority);
	अगर (!ctx)
		वापस शून्य;

	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, ctx);
	INIT_LIST_HEAD(&ctx->node);
	INIT_LIST_HEAD(&ctx->delegated_node);

	pr_debug("subflow=%p", ctx);

	ctx->tcp_sock = sk;

	वापस ctx;
पूर्ण

अटल व्योम __subflow_state_change(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_all(&wq->रुको);
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool subflow_is_करोne(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_shutकरोwn & RCV_SHUTDOWN || sk->sk_state == TCP_CLOSE;
पूर्ण

अटल व्योम subflow_state_change(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा sock *parent = subflow->conn;

	__subflow_state_change(sk);

	अगर (subflow_simultaneous_connect(sk)) अणु
		mptcp_propagate_sndbuf(parent, sk);
		mptcp_करो_fallback(sk);
		mptcp_rcv_space_init(mptcp_sk(parent), sk);
		pr_fallback(mptcp_sk(parent));
		subflow->conn_finished = 1;
		अगर (inet_sk_state_load(parent) == TCP_SYN_SENT) अणु
			inet_sk_state_store(parent, TCP_ESTABLISHED);
			parent->sk_state_change(parent);
		पूर्ण
	पूर्ण

	/* as recvmsg() करोes not acquire the subflow socket क्रम ssk selection
	 * a fin packet carrying a DSS can be unnoticed अगर we करोn't trigger
	 * the data available machinery here.
	 */
	अगर (mptcp_subflow_data_available(sk))
		mptcp_data_पढ़ोy(parent, sk);
	अन्यथा अगर (unlikely(sk->sk_err))
		subflow_error_report(sk);

	subflow_sched_work_अगर_बंदd(mptcp_sk(parent), sk);

	अगर (__mptcp_check_fallback(mptcp_sk(parent)) &&
	    !subflow->rx_eof && subflow_is_करोne(sk)) अणु
		subflow->rx_eof = 1;
		mptcp_subflow_eof(parent);
	पूर्ण
पूर्ण

अटल पूर्णांक subflow_ulp_init(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा mptcp_subflow_context *ctx;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक err = 0;

	/* disallow attaching ULP to a socket unless it has been
	 * created with sock_create_kern()
	 */
	अगर (!sk->sk_kern_sock) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ctx = subflow_create_ctx(sk, GFP_KERNEL);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	pr_debug("subflow=%p, family=%d", ctx, sk->sk_family);

	tp->is_mptcp = 1;
	ctx->icsk_af_ops = icsk->icsk_af_ops;
	icsk->icsk_af_ops = subflow_शेष_af_ops(sk);
	ctx->tcp_data_पढ़ोy = sk->sk_data_पढ़ोy;
	ctx->tcp_state_change = sk->sk_state_change;
	ctx->tcp_ग_लिखो_space = sk->sk_ग_लिखो_space;
	ctx->tcp_error_report = sk->sk_error_report;
	sk->sk_data_पढ़ोy = subflow_data_पढ़ोy;
	sk->sk_ग_लिखो_space = subflow_ग_लिखो_space;
	sk->sk_state_change = subflow_state_change;
	sk->sk_error_report = subflow_error_report;
out:
	वापस err;
पूर्ण

अटल व्योम subflow_ulp_release(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *ctx = mptcp_subflow_ctx(ssk);
	bool release = true;
	काष्ठा sock *sk;

	अगर (!ctx)
		वापस;

	sk = ctx->conn;
	अगर (sk) अणु
		/* अगर the msk has been orphaned, keep the ctx
		 * alive, will be मुक्तd by __mptcp_बंद_ssk(),
		 * when the subflow is still unaccepted
		 */
		release = ctx->disposable || list_empty(&ctx->node);
		sock_put(sk);
	पूर्ण

	mptcp_subflow_ops_unकरो_override(ssk);
	अगर (release)
		kमुक्त_rcu(ctx, rcu);
पूर्ण

अटल व्योम subflow_ulp_clone(स्थिर काष्ठा request_sock *req,
			      काष्ठा sock *newsk,
			      स्थिर gfp_t priority)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा mptcp_subflow_context *old_ctx = mptcp_subflow_ctx(newsk);
	काष्ठा mptcp_subflow_context *new_ctx;

	अगर (!tcp_rsk(req)->is_mptcp ||
	    (!subflow_req->mp_capable && !subflow_req->mp_join)) अणु
		subflow_ulp_fallback(newsk, old_ctx);
		वापस;
	पूर्ण

	new_ctx = subflow_create_ctx(newsk, priority);
	अगर (!new_ctx) अणु
		subflow_ulp_fallback(newsk, old_ctx);
		वापस;
	पूर्ण

	new_ctx->conn_finished = 1;
	new_ctx->icsk_af_ops = old_ctx->icsk_af_ops;
	new_ctx->tcp_data_पढ़ोy = old_ctx->tcp_data_पढ़ोy;
	new_ctx->tcp_state_change = old_ctx->tcp_state_change;
	new_ctx->tcp_ग_लिखो_space = old_ctx->tcp_ग_लिखो_space;
	new_ctx->tcp_error_report = old_ctx->tcp_error_report;
	new_ctx->rel_ग_लिखो_seq = 1;
	new_ctx->tcp_sock = newsk;

	अगर (subflow_req->mp_capable) अणु
		/* see comments in subflow_syn_recv_sock(), MPTCP connection
		 * is fully established only after we receive the remote key
		 */
		new_ctx->mp_capable = 1;
		new_ctx->local_key = subflow_req->local_key;
		new_ctx->token = subflow_req->token;
		new_ctx->ssn_offset = subflow_req->ssn_offset;
		new_ctx->idsn = subflow_req->idsn;
	पूर्ण अन्यथा अगर (subflow_req->mp_join) अणु
		new_ctx->ssn_offset = subflow_req->ssn_offset;
		new_ctx->mp_join = 1;
		new_ctx->fully_established = 1;
		new_ctx->backup = subflow_req->backup;
		new_ctx->local_id = subflow_req->local_id;
		new_ctx->remote_id = subflow_req->remote_id;
		new_ctx->token = subflow_req->token;
		new_ctx->thmac = subflow_req->thmac;
	पूर्ण
पूर्ण

अटल व्योम tcp_release_cb_override(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);

	अगर (mptcp_subflow_has_delegated_action(subflow))
		mptcp_subflow_process_delegated(ssk);

	tcp_release_cb(ssk);
पूर्ण

अटल काष्ठा tcp_ulp_ops subflow_ulp_ops __पढ़ो_mostly = अणु
	.name		= "mptcp",
	.owner		= THIS_MODULE,
	.init		= subflow_ulp_init,
	.release	= subflow_ulp_release,
	.clone		= subflow_ulp_clone,
पूर्ण;

अटल पूर्णांक subflow_ops_init(काष्ठा request_sock_ops *subflow_ops)
अणु
	subflow_ops->obj_size = माप(काष्ठा mptcp_subflow_request_sock);
	subflow_ops->slab_name = "request_sock_subflow";

	subflow_ops->slab = kmem_cache_create(subflow_ops->slab_name,
					      subflow_ops->obj_size, 0,
					      SLAB_ACCOUNT |
					      SLAB_TYPESAFE_BY_RCU,
					      शून्य);
	अगर (!subflow_ops->slab)
		वापस -ENOMEM;

	subflow_ops->deकाष्ठाor = subflow_req_deकाष्ठाor;

	वापस 0;
पूर्ण

व्योम __init mptcp_subflow_init(व्योम)
अणु
	mptcp_subflow_request_sock_ops = tcp_request_sock_ops;
	अगर (subflow_ops_init(&mptcp_subflow_request_sock_ops) != 0)
		panic("MPTCP: failed to init subflow request sock ops\n");

	subflow_request_sock_ipv4_ops = tcp_request_sock_ipv4_ops;
	subflow_request_sock_ipv4_ops.route_req = subflow_v4_route_req;

	subflow_specअगरic = ipv4_specअगरic;
	subflow_specअगरic.conn_request = subflow_v4_conn_request;
	subflow_specअगरic.syn_recv_sock = subflow_syn_recv_sock;
	subflow_specअगरic.sk_rx_dst_set = subflow_finish_connect;

	tcp_prot_override = tcp_prot;
	tcp_prot_override.release_cb = tcp_release_cb_override;

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	subflow_request_sock_ipv6_ops = tcp_request_sock_ipv6_ops;
	subflow_request_sock_ipv6_ops.route_req = subflow_v6_route_req;

	subflow_v6_specअगरic = ipv6_specअगरic;
	subflow_v6_specअगरic.conn_request = subflow_v6_conn_request;
	subflow_v6_specअगरic.syn_recv_sock = subflow_syn_recv_sock;
	subflow_v6_specअगरic.sk_rx_dst_set = subflow_finish_connect;

	subflow_v6m_specअगरic = subflow_v6_specअगरic;
	subflow_v6m_specअगरic.queue_xmit = ipv4_specअगरic.queue_xmit;
	subflow_v6m_specअगरic.send_check = ipv4_specअगरic.send_check;
	subflow_v6m_specअगरic.net_header_len = ipv4_specअगरic.net_header_len;
	subflow_v6m_specअगरic.mtu_reduced = ipv4_specअगरic.mtu_reduced;
	subflow_v6m_specअगरic.net_frag_header_len = 0;

	tcpv6_prot_override = tcpv6_prot;
	tcpv6_prot_override.release_cb = tcp_release_cb_override;
#पूर्ण_अगर

	mptcp_diag_subflow_init(&subflow_ulp_ops);

	अगर (tcp_रेजिस्टर_ulp(&subflow_ulp_ops) != 0)
		panic("MPTCP: failed to register subflows to ULP\n");
पूर्ण
