<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  AF_SMC protocol family socket handler keeping the AF_INET sock address type
 *  applies to SOCK_STREAM sockets only
 *  offers an alternative communication option क्रम TCP-protocol sockets
 *  applicable with RoCE-cards only
 *
 *  Initial restrictions:
 *    - support क्रम alternate links postponed
 *
 *  Copyright IBM Corp. 2016, 2018
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 *              based on prototype from Frank Blaschka
 */

#घोषणा KMSG_COMPONENT "smc"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/in.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/प्रकार.स>

#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <net/smc.h>
#समावेश <यंत्र/ioctls.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश "smc_netns.h"

#समावेश "smc.h"
#समावेश "smc_clc.h"
#समावेश "smc_llc.h"
#समावेश "smc_cdc.h"
#समावेश "smc_core.h"
#समावेश "smc_ib.h"
#समावेश "smc_ism.h"
#समावेश "smc_pnet.h"
#समावेश "smc_netlink.h"
#समावेश "smc_tx.h"
#समावेश "smc_rx.h"
#समावेश "smc_close.h"

अटल DEFINE_MUTEX(smc_server_lgr_pending);	/* serialize link group
						 * creation on server
						 */
अटल DEFINE_MUTEX(smc_client_lgr_pending);	/* serialize link group
						 * creation on client
						 */

काष्ठा workqueue_काष्ठा	*smc_hs_wq;	/* wq क्रम handshake work */
काष्ठा workqueue_काष्ठा	*smc_बंद_wq;	/* wq क्रम बंद work */

अटल व्योम smc_tcp_listen_work(काष्ठा work_काष्ठा *);
अटल व्योम smc_connect_work(काष्ठा work_काष्ठा *);

अटल व्योम smc_set_keepalive(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा smc_sock *smc = smc_sk(sk);

	smc->clcsock->sk->sk_prot->keepalive(smc->clcsock->sk, val);
पूर्ण

अटल काष्ठा smc_hashinfo smc_v4_hashinfo = अणु
	.lock = __RW_LOCK_UNLOCKED(smc_v4_hashinfo.lock),
पूर्ण;

अटल काष्ठा smc_hashinfo smc_v6_hashinfo = अणु
	.lock = __RW_LOCK_UNLOCKED(smc_v6_hashinfo.lock),
पूर्ण;

पूर्णांक smc_hash_sk(काष्ठा sock *sk)
अणु
	काष्ठा smc_hashinfo *h = sk->sk_prot->h.smc_hash;
	काष्ठा hlist_head *head;

	head = &h->ht;

	ग_लिखो_lock_bh(&h->lock);
	sk_add_node(sk, head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	ग_लिखो_unlock_bh(&h->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(smc_hash_sk);

व्योम smc_unhash_sk(काष्ठा sock *sk)
अणु
	काष्ठा smc_hashinfo *h = sk->sk_prot->h.smc_hash;

	ग_लिखो_lock_bh(&h->lock);
	अगर (sk_del_node_init(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	ग_लिखो_unlock_bh(&h->lock);
पूर्ण
EXPORT_SYMBOL_GPL(smc_unhash_sk);

काष्ठा proto smc_proto = अणु
	.name		= "SMC",
	.owner		= THIS_MODULE,
	.keepalive	= smc_set_keepalive,
	.hash		= smc_hash_sk,
	.unhash		= smc_unhash_sk,
	.obj_size	= माप(काष्ठा smc_sock),
	.h.smc_hash	= &smc_v4_hashinfo,
	.slab_flags	= SLAB_TYPESAFE_BY_RCU,
पूर्ण;
EXPORT_SYMBOL_GPL(smc_proto);

काष्ठा proto smc_proto6 = अणु
	.name		= "SMC6",
	.owner		= THIS_MODULE,
	.keepalive	= smc_set_keepalive,
	.hash		= smc_hash_sk,
	.unhash		= smc_unhash_sk,
	.obj_size	= माप(काष्ठा smc_sock),
	.h.smc_hash	= &smc_v6_hashinfo,
	.slab_flags	= SLAB_TYPESAFE_BY_RCU,
पूर्ण;
EXPORT_SYMBOL_GPL(smc_proto6);

अटल व्योम smc_restore_fallback_changes(काष्ठा smc_sock *smc)
अणु
	अगर (smc->clcsock->file) अणु /* non-accepted sockets have no file yet */
		smc->clcsock->file->निजी_data = smc->sk.sk_socket;
		smc->clcsock->file = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __smc_release(काष्ठा smc_sock *smc)
अणु
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक rc = 0;

	अगर (!smc->use_fallback) अणु
		rc = smc_बंद_active(smc);
		sock_set_flag(sk, SOCK_DEAD);
		sk->sk_shutकरोwn |= SHUTDOWN_MASK;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != SMC_LISTEN && sk->sk_state != SMC_INIT)
			sock_put(sk); /* passive closing */
		अगर (sk->sk_state == SMC_LISTEN) अणु
			/* wake up clcsock accept */
			rc = kernel_sock_shutकरोwn(smc->clcsock, SHUT_RDWR);
		पूर्ण
		sk->sk_state = SMC_CLOSED;
		sk->sk_state_change(sk);
		smc_restore_fallback_changes(smc);
	पूर्ण

	sk->sk_prot->unhash(sk);

	अगर (sk->sk_state == SMC_CLOSED) अणु
		अगर (smc->clcsock) अणु
			release_sock(sk);
			smc_clcsock_release(smc);
			lock_sock(sk);
		पूर्ण
		अगर (!smc->use_fallback)
			smc_conn_मुक्त(&smc->conn);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smc_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = 0;

	अगर (!sk)
		जाओ out;

	sock_hold(sk); /* sock_put below */
	smc = smc_sk(sk);

	/* cleanup क्रम a dangling non-blocking connect */
	अगर (smc->connect_nonblock && sk->sk_state == SMC_INIT)
		tcp_पात(smc->clcsock->sk, ECONNABORTED);
	flush_work(&smc->connect_work);

	अगर (sk->sk_state == SMC_LISTEN)
		/* smc_बंद_non_accepted() is called and acquires
		 * sock lock क्रम child sockets again
		 */
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	अन्यथा
		lock_sock(sk);

	rc = __smc_release(smc);

	/* detach socket */
	sock_orphan(sk);
	sock->sk = शून्य;
	release_sock(sk);

	sock_put(sk); /* sock_hold above */
	sock_put(sk); /* final sock_put */
out:
	वापस rc;
पूर्ण

अटल व्योम smc_deकाष्ठा(काष्ठा sock *sk)
अणु
	अगर (sk->sk_state != SMC_CLOSED)
		वापस;
	अगर (!sock_flag(sk, SOCK_DEAD))
		वापस;

	sk_refcnt_debug_dec(sk);
पूर्ण

अटल काष्ठा sock *smc_sock_alloc(काष्ठा net *net, काष्ठा socket *sock,
				   पूर्णांक protocol)
अणु
	काष्ठा smc_sock *smc;
	काष्ठा proto *prot;
	काष्ठा sock *sk;

	prot = (protocol == SMCPROTO_SMC6) ? &smc_proto6 : &smc_proto;
	sk = sk_alloc(net, PF_SMC, GFP_KERNEL, prot, 0);
	अगर (!sk)
		वापस शून्य;

	sock_init_data(sock, sk); /* sets sk_refcnt to 1 */
	sk->sk_state = SMC_INIT;
	sk->sk_deकाष्ठा = smc_deकाष्ठा;
	sk->sk_protocol = protocol;
	smc = smc_sk(sk);
	INIT_WORK(&smc->tcp_listen_work, smc_tcp_listen_work);
	INIT_WORK(&smc->connect_work, smc_connect_work);
	INIT_DELAYED_WORK(&smc->conn.tx_work, smc_tx_work);
	INIT_LIST_HEAD(&smc->accept_q);
	spin_lock_init(&smc->accept_q_lock);
	spin_lock_init(&smc->conn.send_lock);
	sk->sk_prot->hash(sk);
	sk_refcnt_debug_inc(sk);
	mutex_init(&smc->clcsock_release_lock);

	वापस sk;
पूर्ण

अटल पूर्णांक smc_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		    पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc;

	smc = smc_sk(sk);

	/* replicate tests from inet_bind(), to be safe wrt. future changes */
	rc = -EINVAL;
	अगर (addr_len < माप(काष्ठा sockaddr_in))
		जाओ out;

	rc = -EAFNOSUPPORT;
	अगर (addr->sin_family != AF_INET &&
	    addr->sin_family != AF_INET6 &&
	    addr->sin_family != AF_UNSPEC)
		जाओ out;
	/* accept AF_UNSPEC (mapped to AF_INET) only अगर s_addr is INADDR_ANY */
	अगर (addr->sin_family == AF_UNSPEC &&
	    addr->sin_addr.s_addr != htonl(INADDR_ANY))
		जाओ out;

	lock_sock(sk);

	/* Check अगर socket is alपढ़ोy active */
	rc = -EINVAL;
	अगर (sk->sk_state != SMC_INIT || smc->connect_nonblock)
		जाओ out_rel;

	smc->clcsock->sk->sk_reuse = sk->sk_reuse;
	rc = kernel_bind(smc->clcsock, uaddr, addr_len);

out_rel:
	release_sock(sk);
out:
	वापस rc;
पूर्ण

अटल व्योम smc_copy_sock_settings(काष्ठा sock *nsk, काष्ठा sock *osk,
				   अचिन्हित दीर्घ mask)
अणु
	/* options we करोn't get control via setsockopt क्रम */
	nsk->sk_type = osk->sk_type;
	nsk->sk_sndbuf = osk->sk_sndbuf;
	nsk->sk_rcvbuf = osk->sk_rcvbuf;
	nsk->sk_sndसमयo = osk->sk_sndसमयo;
	nsk->sk_rcvसमयo = osk->sk_rcvसमयo;
	nsk->sk_mark = osk->sk_mark;
	nsk->sk_priority = osk->sk_priority;
	nsk->sk_rcvlowat = osk->sk_rcvlowat;
	nsk->sk_bound_dev_अगर = osk->sk_bound_dev_अगर;
	nsk->sk_err = osk->sk_err;

	nsk->sk_flags &= ~mask;
	nsk->sk_flags |= osk->sk_flags & mask;
पूर्ण

#घोषणा SK_FLAGS_SMC_TO_CLC ((1UL << SOCK_URGINLINE) | \
			     (1UL << SOCK_KEEPOPEN) | \
			     (1UL << SOCK_LINGER) | \
			     (1UL << SOCK_BROADCAST) | \
			     (1UL << SOCK_TIMESTAMP) | \
			     (1UL << SOCK_DBG) | \
			     (1UL << SOCK_RCVTSTAMP) | \
			     (1UL << SOCK_RCVTSTAMPNS) | \
			     (1UL << SOCK_LOCALROUTE) | \
			     (1UL << SOCK_TIMESTAMPING_RX_SOFTWARE) | \
			     (1UL << SOCK_RXQ_OVFL) | \
			     (1UL << SOCK_WIFI_STATUS) | \
			     (1UL << SOCK_NOFCS) | \
			     (1UL << SOCK_FILTER_LOCKED) | \
			     (1UL << SOCK_TSTAMP_NEW))
/* copy only relevant settings and flags of SOL_SOCKET level from smc to
 * clc socket (since smc is not called क्रम these options from net/core)
 */
अटल व्योम smc_copy_sock_settings_to_clc(काष्ठा smc_sock *smc)
अणु
	smc_copy_sock_settings(smc->clcsock->sk, &smc->sk, SK_FLAGS_SMC_TO_CLC);
पूर्ण

#घोषणा SK_FLAGS_CLC_TO_SMC ((1UL << SOCK_URGINLINE) | \
			     (1UL << SOCK_KEEPOPEN) | \
			     (1UL << SOCK_LINGER) | \
			     (1UL << SOCK_DBG))
/* copy only settings and flags relevant क्रम smc from clc to smc socket */
अटल व्योम smc_copy_sock_settings_to_smc(काष्ठा smc_sock *smc)
अणु
	smc_copy_sock_settings(&smc->sk, smc->clcsock->sk, SK_FLAGS_CLC_TO_SMC);
पूर्ण

/* रेजिस्टर the new rmb on all links */
अटल पूर्णांक smcr_lgr_reg_rmbs(काष्ठा smc_link *link,
			     काष्ठा smc_buf_desc *rmb_desc)
अणु
	काष्ठा smc_link_group *lgr = link->lgr;
	पूर्णांक i, rc = 0;

	rc = smc_llc_flow_initiate(lgr, SMC_LLC_FLOW_RKEY);
	अगर (rc)
		वापस rc;
	/* protect against parallel smc_llc_cli_rkey_exchange() and
	 * parallel smcr_link_reg_rmb()
	 */
	mutex_lock(&lgr->llc_conf_mutex);
	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
		अगर (!smc_link_active(&lgr->lnk[i]))
			जारी;
		rc = smcr_link_reg_rmb(&lgr->lnk[i], rmb_desc);
		अगर (rc)
			जाओ out;
	पूर्ण

	/* exchange confirm_rkey msg with peer */
	rc = smc_llc_करो_confirm_rkey(link, rmb_desc);
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	rmb_desc->is_conf_rkey = true;
out:
	mutex_unlock(&lgr->llc_conf_mutex);
	smc_llc_flow_stop(lgr, &lgr->llc_flow_lcl);
	वापस rc;
पूर्ण

अटल पूर्णांक smcr_clnt_conf_first_link(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_link *link = smc->conn.lnk;
	काष्ठा smc_llc_qentry *qentry;
	पूर्णांक rc;

	/* receive CONFIRM LINK request from server over RoCE fabric */
	qentry = smc_llc_रुको(link->lgr, शून्य, SMC_LLC_WAIT_TIME,
			      SMC_LLC_CONFIRM_LINK);
	अगर (!qentry) अणु
		काष्ठा smc_clc_msg_decline dclc;

		rc = smc_clc_रुको_msg(smc, &dclc, माप(dclc),
				      SMC_CLC_DECLINE, CLC_WAIT_TIME_SHORT);
		वापस rc == -EAGAIN ? SMC_CLC_DECL_TIMEOUT_CL : rc;
	पूर्ण
	smc_llc_save_peer_uid(qentry);
	rc = smc_llc_eval_conf_link(qentry, SMC_LLC_REQ);
	smc_llc_flow_qentry_del(&link->lgr->llc_flow_lcl);
	अगर (rc)
		वापस SMC_CLC_DECL_RMBE_EC;

	rc = smc_ib_modअगरy_qp_rts(link);
	अगर (rc)
		वापस SMC_CLC_DECL_ERR_RDYLNK;

	smc_wr_remember_qp_attr(link);

	अगर (smcr_link_reg_rmb(link, smc->conn.rmb_desc))
		वापस SMC_CLC_DECL_ERR_REGRMB;

	/* confirm_rkey is implicit on 1st contact */
	smc->conn.rmb_desc->is_conf_rkey = true;

	/* send CONFIRM LINK response over RoCE fabric */
	rc = smc_llc_send_confirm_link(link, SMC_LLC_RESP);
	अगर (rc < 0)
		वापस SMC_CLC_DECL_TIMEOUT_CL;

	smc_llc_link_active(link);
	smcr_lgr_set_type(link->lgr, SMC_LGR_SINGLE);

	/* optional 2nd link, receive ADD LINK request from server */
	qentry = smc_llc_रुको(link->lgr, शून्य, SMC_LLC_WAIT_TIME,
			      SMC_LLC_ADD_LINK);
	अगर (!qentry) अणु
		काष्ठा smc_clc_msg_decline dclc;

		rc = smc_clc_रुको_msg(smc, &dclc, माप(dclc),
				      SMC_CLC_DECLINE, CLC_WAIT_TIME_SHORT);
		अगर (rc == -EAGAIN)
			rc = 0; /* no DECLINE received, go with one link */
		वापस rc;
	पूर्ण
	smc_llc_flow_qentry_clr(&link->lgr->llc_flow_lcl);
	smc_llc_cli_add_link(link, qentry);
	वापस 0;
पूर्ण

अटल व्योम smcr_conn_save_peer_info(काष्ठा smc_sock *smc,
				     काष्ठा smc_clc_msg_accept_confirm *clc)
अणु
	पूर्णांक bufsize = smc_uncompress_bufsize(clc->r0.rmbe_size);

	smc->conn.peer_rmbe_idx = clc->r0.rmbe_idx;
	smc->conn.local_tx_ctrl.token = ntohl(clc->r0.rmbe_alert_token);
	smc->conn.peer_rmbe_size = bufsize;
	atomic_set(&smc->conn.peer_rmbe_space, smc->conn.peer_rmbe_size);
	smc->conn.tx_off = bufsize * (smc->conn.peer_rmbe_idx - 1);
पूर्ण

अटल bool smc_isascii(अक्षर *hostname)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_MAX_HOSTNAME_LEN; i++)
		अगर (!isascii(hostname[i]))
			वापस false;
	वापस true;
पूर्ण

अटल व्योम smcd_conn_save_peer_info(काष्ठा smc_sock *smc,
				     काष्ठा smc_clc_msg_accept_confirm *clc)
अणु
	पूर्णांक bufsize = smc_uncompress_bufsize(clc->d0.dmbe_size);

	smc->conn.peer_rmbe_idx = clc->d0.dmbe_idx;
	smc->conn.peer_token = clc->d0.token;
	/* msg header takes up space in the buffer */
	smc->conn.peer_rmbe_size = bufsize - माप(काष्ठा smcd_cdc_msg);
	atomic_set(&smc->conn.peer_rmbe_space, smc->conn.peer_rmbe_size);
	smc->conn.tx_off = bufsize * smc->conn.peer_rmbe_idx;
	अगर (clc->hdr.version > SMC_V1 &&
	    (clc->hdr.typev2 & SMC_FIRST_CONTACT_MASK)) अणु
		काष्ठा smc_clc_msg_accept_confirm_v2 *clc_v2 =
			(काष्ठा smc_clc_msg_accept_confirm_v2 *)clc;
		काष्ठा smc_clc_first_contact_ext *fce =
			(काष्ठा smc_clc_first_contact_ext *)
				(((u8 *)clc_v2) + माप(*clc_v2));

		स_नकल(smc->conn.lgr->negotiated_eid, clc_v2->eid,
		       SMC_MAX_EID_LEN);
		smc->conn.lgr->peer_os = fce->os_type;
		smc->conn.lgr->peer_smc_release = fce->release;
		अगर (smc_isascii(fce->hostname))
			स_नकल(smc->conn.lgr->peer_hostname, fce->hostname,
			       SMC_MAX_HOSTNAME_LEN);
	पूर्ण
पूर्ण

अटल व्योम smc_conn_save_peer_info(काष्ठा smc_sock *smc,
				    काष्ठा smc_clc_msg_accept_confirm *clc)
अणु
	अगर (smc->conn.lgr->is_smcd)
		smcd_conn_save_peer_info(smc, clc);
	अन्यथा
		smcr_conn_save_peer_info(smc, clc);
पूर्ण

अटल व्योम smc_link_save_peer_info(काष्ठा smc_link *link,
				    काष्ठा smc_clc_msg_accept_confirm *clc)
अणु
	link->peer_qpn = ntoh24(clc->r0.qpn);
	स_नकल(link->peer_gid, clc->r0.lcl.gid, SMC_GID_SIZE);
	स_नकल(link->peer_mac, clc->r0.lcl.mac, माप(link->peer_mac));
	link->peer_psn = ntoh24(clc->r0.psn);
	link->peer_mtu = clc->r0.qp_mtu;
पूर्ण

अटल व्योम smc_चयन_to_fallback(काष्ठा smc_sock *smc)
अणु
	smc->use_fallback = true;
	अगर (smc->sk.sk_socket && smc->sk.sk_socket->file) अणु
		smc->clcsock->file = smc->sk.sk_socket->file;
		smc->clcsock->file->निजी_data = smc->clcsock;
		smc->clcsock->wq.fasync_list =
			smc->sk.sk_socket->wq.fasync_list;
	पूर्ण
पूर्ण

/* fall back during connect */
अटल पूर्णांक smc_connect_fallback(काष्ठा smc_sock *smc, पूर्णांक reason_code)
अणु
	smc_चयन_to_fallback(smc);
	smc->fallback_rsn = reason_code;
	smc_copy_sock_settings_to_clc(smc);
	smc->connect_nonblock = 0;
	अगर (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;
	वापस 0;
पूर्ण

/* decline and fall back during connect */
अटल पूर्णांक smc_connect_decline_fallback(काष्ठा smc_sock *smc, पूर्णांक reason_code,
					u8 version)
अणु
	पूर्णांक rc;

	अगर (reason_code < 0) अणु /* error, fallback is not possible */
		अगर (smc->sk.sk_state == SMC_INIT)
			sock_put(&smc->sk); /* passive closing */
		वापस reason_code;
	पूर्ण
	अगर (reason_code != SMC_CLC_DECL_PEERDECL) अणु
		rc = smc_clc_send_decline(smc, reason_code, version);
		अगर (rc < 0) अणु
			अगर (smc->sk.sk_state == SMC_INIT)
				sock_put(&smc->sk); /* passive closing */
			वापस rc;
		पूर्ण
	पूर्ण
	वापस smc_connect_fallback(smc, reason_code);
पूर्ण

अटल व्योम smc_conn_पात(काष्ठा smc_sock *smc, पूर्णांक local_first)
अणु
	अगर (local_first)
		smc_lgr_cleanup_early(&smc->conn);
	अन्यथा
		smc_conn_मुक्त(&smc->conn);
पूर्ण

/* check अगर there is a rdma device available क्रम this connection. */
/* called क्रम connect and listen */
अटल पूर्णांक smc_find_rdma_device(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini)
अणु
	/* PNET table look up: search active ib_device and port
	 * within same PNETID that also contains the ethernet device
	 * used क्रम the पूर्णांकernal TCP socket
	 */
	smc_pnet_find_roce_resource(smc->clcsock->sk, ini);
	अगर (!ini->ib_dev)
		वापस SMC_CLC_DECL_NOSMCRDEV;
	वापस 0;
पूर्ण

/* check अगर there is an ISM device available क्रम this connection. */
/* called क्रम connect and listen */
अटल पूर्णांक smc_find_ism_device(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini)
अणु
	/* Find ISM device with same PNETID as connecting पूर्णांकerface  */
	smc_pnet_find_ism_resource(smc->clcsock->sk, ini);
	अगर (!ini->ism_dev[0])
		वापस SMC_CLC_DECL_NOSMCDDEV;
	अन्यथा
		ini->ism_chid[0] = smc_ism_get_chid(ini->ism_dev[0]);
	वापस 0;
पूर्ण

/* is chid unique क्रम the ism devices that are alपढ़ोy determined? */
अटल bool smc_find_ism_v2_is_unique_chid(u16 chid, काष्ठा smc_init_info *ini,
					   पूर्णांक cnt)
अणु
	पूर्णांक i = (!ini->ism_dev[0]) ? 1 : 0;

	क्रम (; i < cnt; i++)
		अगर (ini->ism_chid[i] == chid)
			वापस false;
	वापस true;
पूर्ण

/* determine possible V2 ISM devices (either without PNETID or with PNETID plus
 * PNETID matching net_device)
 */
अटल पूर्णांक smc_find_ism_v2_device_clnt(काष्ठा smc_sock *smc,
				       काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc = SMC_CLC_DECL_NOSMCDDEV;
	काष्ठा smcd_dev *smcd;
	पूर्णांक i = 1;
	u16 chid;

	अगर (smcd_indicated(ini->smc_type_v1))
		rc = 0;		/* alपढ़ोy initialized क्रम V1 */
	mutex_lock(&smcd_dev_list.mutex);
	list_क्रम_each_entry(smcd, &smcd_dev_list.list, list) अणु
		अगर (smcd->going_away || smcd == ini->ism_dev[0])
			जारी;
		chid = smc_ism_get_chid(smcd);
		अगर (!smc_find_ism_v2_is_unique_chid(chid, ini, i))
			जारी;
		अगर (!smc_pnet_is_pnetid_set(smcd->pnetid) ||
		    smc_pnet_is_ndev_pnetid(sock_net(&smc->sk), smcd->pnetid)) अणु
			ini->ism_dev[i] = smcd;
			ini->ism_chid[i] = chid;
			ini->is_smcd = true;
			rc = 0;
			i++;
			अगर (i > SMC_MAX_ISM_DEVS)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);
	ini->ism_offered_cnt = i - 1;
	अगर (!ini->ism_dev[0] && !ini->ism_dev[1])
		ini->smcd_version = 0;

	वापस rc;
पूर्ण

/* Check क्रम VLAN ID and रेजिस्टर it on ISM device just क्रम CLC handshake */
अटल पूर्णांक smc_connect_ism_vlan_setup(काष्ठा smc_sock *smc,
				      काष्ठा smc_init_info *ini)
अणु
	अगर (ini->vlan_id && smc_ism_get_vlan(ini->ism_dev[0], ini->vlan_id))
		वापस SMC_CLC_DECL_ISMVLANERR;
	वापस 0;
पूर्ण

अटल पूर्णांक smc_find_proposal_devices(काष्ठा smc_sock *smc,
				     काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc = 0;

	/* check अगर there is an ism device available */
	अगर (ini->smcd_version & SMC_V1) अणु
		अगर (smc_find_ism_device(smc, ini) ||
		    smc_connect_ism_vlan_setup(smc, ini)) अणु
			अगर (ini->smc_type_v1 == SMC_TYPE_B)
				ini->smc_type_v1 = SMC_TYPE_R;
			अन्यथा
				ini->smc_type_v1 = SMC_TYPE_N;
		पूर्ण /* अन्यथा ISM V1 is supported क्रम this connection */
		अगर (smc_find_rdma_device(smc, ini)) अणु
			अगर (ini->smc_type_v1 == SMC_TYPE_B)
				ini->smc_type_v1 = SMC_TYPE_D;
			अन्यथा
				ini->smc_type_v1 = SMC_TYPE_N;
		पूर्ण /* अन्यथा RDMA is supported क्रम this connection */
	पूर्ण
	अगर (smc_ism_is_v2_capable() && smc_find_ism_v2_device_clnt(smc, ini))
		ini->smc_type_v2 = SMC_TYPE_N;

	/* अगर neither ISM nor RDMA are supported, fallback */
	अगर (!smcr_indicated(ini->smc_type_v1) &&
	    ini->smc_type_v1 == SMC_TYPE_N && ini->smc_type_v2 == SMC_TYPE_N)
		rc = SMC_CLC_DECL_NOSMCDEV;

	वापस rc;
पूर्ण

/* cleanup temporary VLAN ID registration used क्रम CLC handshake. If ISM is
 * used, the VLAN ID will be रेजिस्टरed again during the connection setup.
 */
अटल पूर्णांक smc_connect_ism_vlan_cleanup(काष्ठा smc_sock *smc,
					काष्ठा smc_init_info *ini)
अणु
	अगर (!smcd_indicated(ini->smc_type_v1))
		वापस 0;
	अगर (ini->vlan_id && smc_ism_put_vlan(ini->ism_dev[0], ini->vlan_id))
		वापस SMC_CLC_DECL_CNFERR;
	वापस 0;
पूर्ण

#घोषणा SMC_CLC_MAX_ACCEPT_LEN \
	(माप(काष्ठा smc_clc_msg_accept_confirm_v2) + \
	 माप(काष्ठा smc_clc_first_contact_ext) + \
	 माप(काष्ठा smc_clc_msg_trail))

/* CLC handshake during connect */
अटल पूर्णांक smc_connect_clc(काष्ठा smc_sock *smc,
			   काष्ठा smc_clc_msg_accept_confirm_v2 *aclc2,
			   काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc = 0;

	/* करो inband token exchange */
	rc = smc_clc_send_proposal(smc, ini);
	अगर (rc)
		वापस rc;
	/* receive SMC Accept CLC message */
	वापस smc_clc_रुको_msg(smc, aclc2, SMC_CLC_MAX_ACCEPT_LEN,
				SMC_CLC_ACCEPT, CLC_WAIT_TIME);
पूर्ण

/* setup क्रम RDMA connection of client */
अटल पूर्णांक smc_connect_rdma(काष्ठा smc_sock *smc,
			    काष्ठा smc_clc_msg_accept_confirm *aclc,
			    काष्ठा smc_init_info *ini)
अणु
	पूर्णांक i, reason_code = 0;
	काष्ठा smc_link *link;

	ini->is_smcd = false;
	ini->ib_lcl = &aclc->r0.lcl;
	ini->ib_clcqpn = ntoh24(aclc->r0.qpn);
	ini->first_contact_peer = aclc->hdr.typev2 & SMC_FIRST_CONTACT_MASK;

	mutex_lock(&smc_client_lgr_pending);
	reason_code = smc_conn_create(smc, ini);
	अगर (reason_code) अणु
		mutex_unlock(&smc_client_lgr_pending);
		वापस reason_code;
	पूर्ण

	smc_conn_save_peer_info(smc, aclc);

	अगर (ini->first_contact_local) अणु
		link = smc->conn.lnk;
	पूर्ण अन्यथा अणु
		/* set link that was asचिन्हित by server */
		link = शून्य;
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
			काष्ठा smc_link *l = &smc->conn.lgr->lnk[i];

			अगर (l->peer_qpn == ntoh24(aclc->r0.qpn) &&
			    !स_भेद(l->peer_gid, &aclc->r0.lcl.gid,
				    SMC_GID_SIZE) &&
			    !स_भेद(l->peer_mac, &aclc->r0.lcl.mac,
				    माप(l->peer_mac))) अणु
				link = l;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!link) अणु
			reason_code = SMC_CLC_DECL_NOSRVLINK;
			जाओ connect_पात;
		पूर्ण
		smc->conn.lnk = link;
	पूर्ण

	/* create send buffer and rmb */
	अगर (smc_buf_create(smc, false)) अणु
		reason_code = SMC_CLC_DECL_MEM;
		जाओ connect_पात;
	पूर्ण

	अगर (ini->first_contact_local)
		smc_link_save_peer_info(link, aclc);

	अगर (smc_rmb_rtoken_handling(&smc->conn, link, aclc)) अणु
		reason_code = SMC_CLC_DECL_ERR_RTOK;
		जाओ connect_पात;
	पूर्ण

	smc_बंद_init(smc);
	smc_rx_init(smc);

	अगर (ini->first_contact_local) अणु
		अगर (smc_ib_पढ़ोy_link(link)) अणु
			reason_code = SMC_CLC_DECL_ERR_RDYLNK;
			जाओ connect_पात;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smcr_lgr_reg_rmbs(link, smc->conn.rmb_desc)) अणु
			reason_code = SMC_CLC_DECL_ERR_REGRMB;
			जाओ connect_पात;
		पूर्ण
	पूर्ण
	smc_rmb_sync_sg_क्रम_device(&smc->conn);

	reason_code = smc_clc_send_confirm(smc, ini->first_contact_local,
					   SMC_V1);
	अगर (reason_code)
		जाओ connect_पात;

	smc_tx_init(smc);

	अगर (ini->first_contact_local) अणु
		/* QP confirmation over RoCE fabric */
		smc_llc_flow_initiate(link->lgr, SMC_LLC_FLOW_ADD_LINK);
		reason_code = smcr_clnt_conf_first_link(smc);
		smc_llc_flow_stop(link->lgr, &link->lgr->llc_flow_lcl);
		अगर (reason_code)
			जाओ connect_पात;
	पूर्ण
	mutex_unlock(&smc_client_lgr_pending);

	smc_copy_sock_settings_to_clc(smc);
	smc->connect_nonblock = 0;
	अगर (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;

	वापस 0;
connect_पात:
	smc_conn_पात(smc, ini->first_contact_local);
	mutex_unlock(&smc_client_lgr_pending);
	smc->connect_nonblock = 0;

	वापस reason_code;
पूर्ण

/* The server has chosen one of the proposed ISM devices क्रम the communication.
 * Determine from the CHID of the received CLC ACCEPT the ISM device chosen.
 */
अटल पूर्णांक
smc_v2_determine_accepted_chid(काष्ठा smc_clc_msg_accept_confirm_v2 *aclc,
			       काष्ठा smc_init_info *ini)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ini->ism_offered_cnt + 1; i++) अणु
		अगर (ini->ism_chid[i] == ntohs(aclc->chid)) अणु
			ini->ism_selected = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EPROTO;
पूर्ण

/* setup क्रम ISM connection of client */
अटल पूर्णांक smc_connect_ism(काष्ठा smc_sock *smc,
			   काष्ठा smc_clc_msg_accept_confirm *aclc,
			   काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc = 0;

	ini->is_smcd = true;
	ini->first_contact_peer = aclc->hdr.typev2 & SMC_FIRST_CONTACT_MASK;

	अगर (aclc->hdr.version == SMC_V2) अणु
		काष्ठा smc_clc_msg_accept_confirm_v2 *aclc_v2 =
			(काष्ठा smc_clc_msg_accept_confirm_v2 *)aclc;

		rc = smc_v2_determine_accepted_chid(aclc_v2, ini);
		अगर (rc)
			वापस rc;
	पूर्ण
	ini->ism_peer_gid[ini->ism_selected] = aclc->d0.gid;

	/* there is only one lgr role क्रम SMC-D; use server lock */
	mutex_lock(&smc_server_lgr_pending);
	rc = smc_conn_create(smc, ini);
	अगर (rc) अणु
		mutex_unlock(&smc_server_lgr_pending);
		वापस rc;
	पूर्ण

	/* Create send and receive buffers */
	rc = smc_buf_create(smc, true);
	अगर (rc) अणु
		rc = (rc == -ENOSPC) ? SMC_CLC_DECL_MAX_DMB : SMC_CLC_DECL_MEM;
		जाओ connect_पात;
	पूर्ण

	smc_conn_save_peer_info(smc, aclc);
	smc_बंद_init(smc);
	smc_rx_init(smc);
	smc_tx_init(smc);

	rc = smc_clc_send_confirm(smc, ini->first_contact_local,
				  aclc->hdr.version);
	अगर (rc)
		जाओ connect_पात;
	mutex_unlock(&smc_server_lgr_pending);

	smc_copy_sock_settings_to_clc(smc);
	smc->connect_nonblock = 0;
	अगर (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;

	वापस 0;
connect_पात:
	smc_conn_पात(smc, ini->first_contact_local);
	mutex_unlock(&smc_server_lgr_pending);
	smc->connect_nonblock = 0;

	वापस rc;
पूर्ण

/* check अगर received accept type and version matches a proposed one */
अटल पूर्णांक smc_connect_check_aclc(काष्ठा smc_init_info *ini,
				  काष्ठा smc_clc_msg_accept_confirm *aclc)
अणु
	अगर ((aclc->hdr.typev1 == SMC_TYPE_R &&
	     !smcr_indicated(ini->smc_type_v1)) ||
	    (aclc->hdr.typev1 == SMC_TYPE_D &&
	     ((!smcd_indicated(ini->smc_type_v1) &&
	       !smcd_indicated(ini->smc_type_v2)) ||
	      (aclc->hdr.version == SMC_V1 &&
	       !smcd_indicated(ini->smc_type_v1)) ||
	      (aclc->hdr.version == SMC_V2 &&
	       !smcd_indicated(ini->smc_type_v2)))))
		वापस SMC_CLC_DECL_MODEUNSUPP;

	वापस 0;
पूर्ण

/* perक्रमm steps beक्रमe actually connecting */
अटल पूर्णांक __smc_connect(काष्ठा smc_sock *smc)
अणु
	u8 version = smc_ism_is_v2_capable() ? SMC_V2 : SMC_V1;
	काष्ठा smc_clc_msg_accept_confirm_v2 *aclc2;
	काष्ठा smc_clc_msg_accept_confirm *aclc;
	काष्ठा smc_init_info *ini = शून्य;
	u8 *buf = शून्य;
	पूर्णांक rc = 0;

	अगर (smc->use_fallback)
		वापस smc_connect_fallback(smc, smc->fallback_rsn);

	/* अगर peer has not संकेतled SMC-capability, fall back */
	अगर (!tcp_sk(smc->clcsock->sk)->syn_smc)
		वापस smc_connect_fallback(smc, SMC_CLC_DECL_PEERNOSMC);

	/* IPSec connections opt out of SMC optimizations */
	अगर (using_ipsec(smc))
		वापस smc_connect_decline_fallback(smc, SMC_CLC_DECL_IPSEC,
						    version);

	ini = kzalloc(माप(*ini), GFP_KERNEL);
	अगर (!ini)
		वापस smc_connect_decline_fallback(smc, SMC_CLC_DECL_MEM,
						    version);

	ini->smcd_version = SMC_V1;
	ini->smcd_version |= smc_ism_is_v2_capable() ? SMC_V2 : 0;
	ini->smc_type_v1 = SMC_TYPE_B;
	ini->smc_type_v2 = smc_ism_is_v2_capable() ? SMC_TYPE_D : SMC_TYPE_N;

	/* get vlan id from IP device */
	अगर (smc_vlan_by_tcpsk(smc->clcsock, ini)) अणु
		ini->smcd_version &= ~SMC_V1;
		ini->smc_type_v1 = SMC_TYPE_N;
		अगर (!ini->smcd_version) अणु
			rc = SMC_CLC_DECL_GETVLANERR;
			जाओ fallback;
		पूर्ण
	पूर्ण

	rc = smc_find_proposal_devices(smc, ini);
	अगर (rc)
		जाओ fallback;

	buf = kzalloc(SMC_CLC_MAX_ACCEPT_LEN, GFP_KERNEL);
	अगर (!buf) अणु
		rc = SMC_CLC_DECL_MEM;
		जाओ fallback;
	पूर्ण
	aclc2 = (काष्ठा smc_clc_msg_accept_confirm_v2 *)buf;
	aclc = (काष्ठा smc_clc_msg_accept_confirm *)aclc2;

	/* perक्रमm CLC handshake */
	rc = smc_connect_clc(smc, aclc2, ini);
	अगर (rc)
		जाओ vlan_cleanup;

	/* check अगर smc modes and versions of CLC proposal and accept match */
	rc = smc_connect_check_aclc(ini, aclc);
	version = aclc->hdr.version == SMC_V1 ? SMC_V1 : SMC_V2;
	ini->smcd_version = version;
	अगर (rc)
		जाओ vlan_cleanup;

	/* depending on previous steps, connect using rdma or ism */
	अगर (aclc->hdr.typev1 == SMC_TYPE_R)
		rc = smc_connect_rdma(smc, aclc, ini);
	अन्यथा अगर (aclc->hdr.typev1 == SMC_TYPE_D)
		rc = smc_connect_ism(smc, aclc, ini);
	अगर (rc)
		जाओ vlan_cleanup;

	smc_connect_ism_vlan_cleanup(smc, ini);
	kमुक्त(buf);
	kमुक्त(ini);
	वापस 0;

vlan_cleanup:
	smc_connect_ism_vlan_cleanup(smc, ini);
	kमुक्त(buf);
fallback:
	kमुक्त(ini);
	वापस smc_connect_decline_fallback(smc, rc, version);
पूर्ण

अटल व्योम smc_connect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_sock *smc = container_of(work, काष्ठा smc_sock,
					    connect_work);
	दीर्घ समयo = smc->sk.sk_sndसमयo;
	पूर्णांक rc = 0;

	अगर (!समयo)
		समयo = MAX_SCHEDULE_TIMEOUT;
	lock_sock(smc->clcsock->sk);
	अगर (smc->clcsock->sk->sk_err) अणु
		smc->sk.sk_err = smc->clcsock->sk->sk_err;
	पूर्ण अन्यथा अगर ((1 << smc->clcsock->sk->sk_state) &
					(TCPF_SYN_SENT | TCP_SYN_RECV)) अणु
		rc = sk_stream_रुको_connect(smc->clcsock->sk, &समयo);
		अगर ((rc == -EPIPE) &&
		    ((1 << smc->clcsock->sk->sk_state) &
					(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)))
			rc = 0;
	पूर्ण
	release_sock(smc->clcsock->sk);
	lock_sock(&smc->sk);
	अगर (rc != 0 || smc->sk.sk_err) अणु
		smc->sk.sk_state = SMC_CLOSED;
		अगर (rc == -EPIPE || rc == -EAGAIN)
			smc->sk.sk_err = EPIPE;
		अन्यथा अगर (संकेत_pending(current))
			smc->sk.sk_err = -sock_पूर्णांकr_त्रुटि_सं(समयo);
		sock_put(&smc->sk); /* passive closing */
		जाओ out;
	पूर्ण

	rc = __smc_connect(smc);
	अगर (rc < 0)
		smc->sk.sk_err = -rc;

out:
	अगर (!sock_flag(&smc->sk, SOCK_DEAD)) अणु
		अगर (smc->sk.sk_err) अणु
			smc->sk.sk_state_change(&smc->sk);
		पूर्ण अन्यथा अणु /* allow polling beक्रमe and after fallback decision */
			smc->clcsock->sk->sk_ग_लिखो_space(smc->clcsock->sk);
			smc->sk.sk_ग_लिखो_space(&smc->sk);
		पूर्ण
	पूर्ण
	release_sock(&smc->sk);
पूर्ण

अटल पूर्णांक smc_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
		       पूर्णांक alen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -EINVAL;

	smc = smc_sk(sk);

	/* separate smc parameter checking to be safe */
	अगर (alen < माप(addr->sa_family))
		जाओ out_err;
	अगर (addr->sa_family != AF_INET && addr->sa_family != AF_INET6)
		जाओ out_err;

	lock_sock(sk);
	चयन (sk->sk_state) अणु
	शेष:
		जाओ out;
	हाल SMC_ACTIVE:
		rc = -EISCONN;
		जाओ out;
	हाल SMC_INIT:
		अवरोध;
	पूर्ण

	smc_copy_sock_settings_to_clc(smc);
	tcp_sk(smc->clcsock->sk)->syn_smc = 1;
	अगर (smc->connect_nonblock) अणु
		rc = -EALREADY;
		जाओ out;
	पूर्ण
	rc = kernel_connect(smc->clcsock, addr, alen, flags);
	अगर (rc && rc != -EINPROGRESS)
		जाओ out;

	sock_hold(&smc->sk); /* sock put in passive closing */
	अगर (smc->use_fallback)
		जाओ out;
	अगर (flags & O_NONBLOCK) अणु
		अगर (queue_work(smc_hs_wq, &smc->connect_work))
			smc->connect_nonblock = 1;
		rc = -EINPROGRESS;
	पूर्ण अन्यथा अणु
		rc = __smc_connect(smc);
		अगर (rc < 0)
			जाओ out;
		अन्यथा
			rc = 0; /* success हालs including fallback */
	पूर्ण

out:
	release_sock(sk);
out_err:
	वापस rc;
पूर्ण

अटल पूर्णांक smc_clcsock_accept(काष्ठा smc_sock *lsmc, काष्ठा smc_sock **new_smc)
अणु
	काष्ठा socket *new_clcsock = शून्य;
	काष्ठा sock *lsk = &lsmc->sk;
	काष्ठा sock *new_sk;
	पूर्णांक rc = -EINVAL;

	release_sock(lsk);
	new_sk = smc_sock_alloc(sock_net(lsk), शून्य, lsk->sk_protocol);
	अगर (!new_sk) अणु
		rc = -ENOMEM;
		lsk->sk_err = ENOMEM;
		*new_smc = शून्य;
		lock_sock(lsk);
		जाओ out;
	पूर्ण
	*new_smc = smc_sk(new_sk);

	mutex_lock(&lsmc->clcsock_release_lock);
	अगर (lsmc->clcsock)
		rc = kernel_accept(lsmc->clcsock, &new_clcsock, SOCK_NONBLOCK);
	mutex_unlock(&lsmc->clcsock_release_lock);
	lock_sock(lsk);
	अगर  (rc < 0 && rc != -EAGAIN)
		lsk->sk_err = -rc;
	अगर (rc < 0 || lsk->sk_state == SMC_CLOSED) अणु
		new_sk->sk_prot->unhash(new_sk);
		अगर (new_clcsock)
			sock_release(new_clcsock);
		new_sk->sk_state = SMC_CLOSED;
		sock_set_flag(new_sk, SOCK_DEAD);
		sock_put(new_sk); /* final */
		*new_smc = शून्य;
		जाओ out;
	पूर्ण

	/* new clcsock has inherited the smc listen-specअगरic sk_data_पढ़ोy
	 * function; चयन it back to the original sk_data_पढ़ोy function
	 */
	new_clcsock->sk->sk_data_पढ़ोy = lsmc->clcsk_data_पढ़ोy;
	(*new_smc)->clcsock = new_clcsock;
out:
	वापस rc;
पूर्ण

/* add a just created sock to the accept queue of the listen sock as
 * candidate क्रम a following socket accept call from user space
 */
अटल व्योम smc_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk)
अणु
	काष्ठा smc_sock *par = smc_sk(parent);

	sock_hold(sk); /* sock_put in smc_accept_unlink () */
	spin_lock(&par->accept_q_lock);
	list_add_tail(&smc_sk(sk)->accept_q, &par->accept_q);
	spin_unlock(&par->accept_q_lock);
	sk_acceptq_added(parent);
पूर्ण

/* हटाओ a socket from the accept queue of its parental listening socket */
अटल व्योम smc_accept_unlink(काष्ठा sock *sk)
अणु
	काष्ठा smc_sock *par = smc_sk(sk)->listen_smc;

	spin_lock(&par->accept_q_lock);
	list_del_init(&smc_sk(sk)->accept_q);
	spin_unlock(&par->accept_q_lock);
	sk_acceptq_हटाओd(&smc_sk(sk)->listen_smc->sk);
	sock_put(sk); /* sock_hold in smc_accept_enqueue */
पूर्ण

/* हटाओ a sock from the accept queue to bind it to a new socket created
 * क्रम a socket accept call from user space
 */
काष्ठा sock *smc_accept_dequeue(काष्ठा sock *parent,
				काष्ठा socket *new_sock)
अणु
	काष्ठा smc_sock *isk, *n;
	काष्ठा sock *new_sk;

	list_क्रम_each_entry_safe(isk, n, &smc_sk(parent)->accept_q, accept_q) अणु
		new_sk = (काष्ठा sock *)isk;

		smc_accept_unlink(new_sk);
		अगर (new_sk->sk_state == SMC_CLOSED) अणु
			new_sk->sk_prot->unhash(new_sk);
			अगर (isk->clcsock) अणु
				sock_release(isk->clcsock);
				isk->clcsock = शून्य;
			पूर्ण
			sock_put(new_sk); /* final */
			जारी;
		पूर्ण
		अगर (new_sock) अणु
			sock_graft(new_sk, new_sock);
			अगर (isk->use_fallback) अणु
				smc_sk(new_sk)->clcsock->file = new_sock->file;
				isk->clcsock->file->निजी_data = isk->clcsock;
			पूर्ण
		पूर्ण
		वापस new_sk;
	पूर्ण
	वापस शून्य;
पूर्ण

/* clean up क्रम a created but never accepted sock */
व्योम smc_बंद_non_accepted(काष्ठा sock *sk)
अणु
	काष्ठा smc_sock *smc = smc_sk(sk);

	sock_hold(sk); /* sock_put below */
	lock_sock(sk);
	अगर (!sk->sk_lingerसमय)
		/* रुको क्रम peer closing */
		sk->sk_lingerसमय = SMC_MAX_STREAM_WAIT_TIMEOUT;
	__smc_release(smc);
	release_sock(sk);
	sock_put(sk); /* sock_hold above */
	sock_put(sk); /* final sock_put */
पूर्ण

अटल पूर्णांक smcr_serv_conf_first_link(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_link *link = smc->conn.lnk;
	काष्ठा smc_llc_qentry *qentry;
	पूर्णांक rc;

	अगर (smcr_link_reg_rmb(link, smc->conn.rmb_desc))
		वापस SMC_CLC_DECL_ERR_REGRMB;

	/* send CONFIRM LINK request to client over the RoCE fabric */
	rc = smc_llc_send_confirm_link(link, SMC_LLC_REQ);
	अगर (rc < 0)
		वापस SMC_CLC_DECL_TIMEOUT_CL;

	/* receive CONFIRM LINK response from client over the RoCE fabric */
	qentry = smc_llc_रुको(link->lgr, link, SMC_LLC_WAIT_TIME,
			      SMC_LLC_CONFIRM_LINK);
	अगर (!qentry) अणु
		काष्ठा smc_clc_msg_decline dclc;

		rc = smc_clc_रुको_msg(smc, &dclc, माप(dclc),
				      SMC_CLC_DECLINE, CLC_WAIT_TIME_SHORT);
		वापस rc == -EAGAIN ? SMC_CLC_DECL_TIMEOUT_CL : rc;
	पूर्ण
	smc_llc_save_peer_uid(qentry);
	rc = smc_llc_eval_conf_link(qentry, SMC_LLC_RESP);
	smc_llc_flow_qentry_del(&link->lgr->llc_flow_lcl);
	अगर (rc)
		वापस SMC_CLC_DECL_RMBE_EC;

	/* confirm_rkey is implicit on 1st contact */
	smc->conn.rmb_desc->is_conf_rkey = true;

	smc_llc_link_active(link);
	smcr_lgr_set_type(link->lgr, SMC_LGR_SINGLE);

	/* initial contact - try to establish second link */
	smc_llc_srv_add_link(link);
	वापस 0;
पूर्ण

/* listen worker: finish */
अटल व्योम smc_listen_out(काष्ठा smc_sock *new_smc)
अणु
	काष्ठा smc_sock *lsmc = new_smc->listen_smc;
	काष्ठा sock *newsmcsk = &new_smc->sk;

	अगर (lsmc->sk.sk_state == SMC_LISTEN) अणु
		lock_sock_nested(&lsmc->sk, SINGLE_DEPTH_NESTING);
		smc_accept_enqueue(&lsmc->sk, newsmcsk);
		release_sock(&lsmc->sk);
	पूर्ण अन्यथा अणु /* no दीर्घer listening */
		smc_बंद_non_accepted(newsmcsk);
	पूर्ण

	/* Wake up accept */
	lsmc->sk.sk_data_पढ़ोy(&lsmc->sk);
	sock_put(&lsmc->sk); /* sock_hold in smc_tcp_listen_work */
पूर्ण

/* listen worker: finish in state connected */
अटल व्योम smc_listen_out_connected(काष्ठा smc_sock *new_smc)
अणु
	काष्ठा sock *newsmcsk = &new_smc->sk;

	sk_refcnt_debug_inc(newsmcsk);
	अगर (newsmcsk->sk_state == SMC_INIT)
		newsmcsk->sk_state = SMC_ACTIVE;

	smc_listen_out(new_smc);
पूर्ण

/* listen worker: finish in error state */
अटल व्योम smc_listen_out_err(काष्ठा smc_sock *new_smc)
अणु
	काष्ठा sock *newsmcsk = &new_smc->sk;

	अगर (newsmcsk->sk_state == SMC_INIT)
		sock_put(&new_smc->sk); /* passive closing */
	newsmcsk->sk_state = SMC_CLOSED;

	smc_listen_out(new_smc);
पूर्ण

/* listen worker: decline and fall back अगर possible */
अटल व्योम smc_listen_decline(काष्ठा smc_sock *new_smc, पूर्णांक reason_code,
			       पूर्णांक local_first, u8 version)
अणु
	/* RDMA setup failed, चयन back to TCP */
	smc_conn_पात(new_smc, local_first);
	अगर (reason_code < 0) अणु /* error, no fallback possible */
		smc_listen_out_err(new_smc);
		वापस;
	पूर्ण
	smc_चयन_to_fallback(new_smc);
	new_smc->fallback_rsn = reason_code;
	अगर (reason_code && reason_code != SMC_CLC_DECL_PEERDECL) अणु
		अगर (smc_clc_send_decline(new_smc, reason_code, version) < 0) अणु
			smc_listen_out_err(new_smc);
			वापस;
		पूर्ण
	पूर्ण
	smc_listen_out_connected(new_smc);
पूर्ण

/* listen worker: version checking */
अटल पूर्णांक smc_listen_v2_check(काष्ठा smc_sock *new_smc,
			       काष्ठा smc_clc_msg_proposal *pclc,
			       काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_clc_smcd_v2_extension *pclc_smcd_v2_ext;
	काष्ठा smc_clc_v2_extension *pclc_v2_ext;
	पूर्णांक rc = SMC_CLC_DECL_PEERNOSMC;

	ini->smc_type_v1 = pclc->hdr.typev1;
	ini->smc_type_v2 = pclc->hdr.typev2;
	ini->smcd_version = ini->smc_type_v1 != SMC_TYPE_N ? SMC_V1 : 0;
	अगर (pclc->hdr.version > SMC_V1)
		ini->smcd_version |=
				ini->smc_type_v2 != SMC_TYPE_N ? SMC_V2 : 0;
	अगर (!(ini->smcd_version & SMC_V2)) अणु
		rc = SMC_CLC_DECL_PEERNOSMC;
		जाओ out;
	पूर्ण
	अगर (!smc_ism_is_v2_capable()) अणु
		ini->smcd_version &= ~SMC_V2;
		rc = SMC_CLC_DECL_NOISM2SUPP;
		जाओ out;
	पूर्ण
	pclc_v2_ext = smc_get_clc_v2_ext(pclc);
	अगर (!pclc_v2_ext) अणु
		ini->smcd_version &= ~SMC_V2;
		rc = SMC_CLC_DECL_NOV2EXT;
		जाओ out;
	पूर्ण
	pclc_smcd_v2_ext = smc_get_clc_smcd_v2_ext(pclc_v2_ext);
	अगर (!pclc_smcd_v2_ext) अणु
		ini->smcd_version &= ~SMC_V2;
		rc = SMC_CLC_DECL_NOV2DEXT;
	पूर्ण

out:
	अगर (!ini->smcd_version)
		वापस rc;

	वापस 0;
पूर्ण

/* listen worker: check prefixes */
अटल पूर्णांक smc_listen_prfx_check(काष्ठा smc_sock *new_smc,
				 काष्ठा smc_clc_msg_proposal *pclc)
अणु
	काष्ठा smc_clc_msg_proposal_prefix *pclc_prfx;
	काष्ठा socket *newclcsock = new_smc->clcsock;

	अगर (pclc->hdr.typev1 == SMC_TYPE_N)
		वापस 0;
	pclc_prfx = smc_clc_proposal_get_prefix(pclc);
	अगर (smc_clc_prfx_match(newclcsock, pclc_prfx))
		वापस SMC_CLC_DECL_DIFFPREFIX;

	वापस 0;
पूर्ण

/* listen worker: initialize connection and buffers */
अटल पूर्णांक smc_listen_rdma_init(काष्ठा smc_sock *new_smc,
				काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc;

	/* allocate connection / link group */
	rc = smc_conn_create(new_smc, ini);
	अगर (rc)
		वापस rc;

	/* create send buffer and rmb */
	अगर (smc_buf_create(new_smc, false))
		वापस SMC_CLC_DECL_MEM;

	वापस 0;
पूर्ण

/* listen worker: initialize connection and buffers क्रम SMC-D */
अटल पूर्णांक smc_listen_ism_init(काष्ठा smc_sock *new_smc,
			       काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc;

	rc = smc_conn_create(new_smc, ini);
	अगर (rc)
		वापस rc;

	/* Create send and receive buffers */
	rc = smc_buf_create(new_smc, true);
	अगर (rc) अणु
		smc_conn_पात(new_smc, ini->first_contact_local);
		वापस (rc == -ENOSPC) ? SMC_CLC_DECL_MAX_DMB :
					 SMC_CLC_DECL_MEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool smc_is_alपढ़ोy_selected(काष्ठा smcd_dev *smcd,
				    काष्ठा smc_init_info *ini,
				    पूर्णांक matches)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < matches; i++)
		अगर (smcd == ini->ism_dev[i])
			वापस true;

	वापस false;
पूर्ण

/* check क्रम ISM devices matching proposed ISM devices */
अटल व्योम smc_check_ism_v2_match(काष्ठा smc_init_info *ini,
				   u16 proposed_chid, u64 proposed_gid,
				   अचिन्हित पूर्णांक *matches)
अणु
	काष्ठा smcd_dev *smcd;

	list_क्रम_each_entry(smcd, &smcd_dev_list.list, list) अणु
		अगर (smcd->going_away)
			जारी;
		अगर (smc_is_alपढ़ोy_selected(smcd, ini, *matches))
			जारी;
		अगर (smc_ism_get_chid(smcd) == proposed_chid &&
		    !smc_ism_cantalk(proposed_gid, ISM_RESERVED_VLANID, smcd)) अणु
			ini->ism_peer_gid[*matches] = proposed_gid;
			ini->ism_dev[*matches] = smcd;
			(*matches)++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smc_find_ism_store_rc(u32 rc, काष्ठा smc_init_info *ini)
अणु
	अगर (!ini->rc)
		ini->rc = rc;
पूर्ण

अटल व्योम smc_find_ism_v2_device_serv(काष्ठा smc_sock *new_smc,
					काष्ठा smc_clc_msg_proposal *pclc,
					काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_clc_smcd_v2_extension *smcd_v2_ext;
	काष्ठा smc_clc_v2_extension *smc_v2_ext;
	काष्ठा smc_clc_msg_smcd *pclc_smcd;
	अचिन्हित पूर्णांक matches = 0;
	u8 smcd_version;
	u8 *eid = शून्य;
	पूर्णांक i, rc;

	अगर (!(ini->smcd_version & SMC_V2) || !smcd_indicated(ini->smc_type_v2))
		जाओ not_found;

	pclc_smcd = smc_get_clc_msg_smcd(pclc);
	smc_v2_ext = smc_get_clc_v2_ext(pclc);
	smcd_v2_ext = smc_get_clc_smcd_v2_ext(smc_v2_ext);
	अगर (!smcd_v2_ext ||
	    !smc_v2_ext->hdr.flag.seid) अणु /* no प्रणाली EID support क्रम SMCD */
		smc_find_ism_store_rc(SMC_CLC_DECL_NOSEID, ini);
		जाओ not_found;
	पूर्ण

	mutex_lock(&smcd_dev_list.mutex);
	अगर (pclc_smcd->ism.chid)
		/* check क्रम ISM device matching proposed native ISM device */
		smc_check_ism_v2_match(ini, ntohs(pclc_smcd->ism.chid),
				       ntohll(pclc_smcd->ism.gid), &matches);
	क्रम (i = 1; i <= smc_v2_ext->hdr.ism_gid_cnt; i++) अणु
		/* check क्रम ISM devices matching proposed non-native ISM
		 * devices
		 */
		smc_check_ism_v2_match(ini,
				       ntohs(smcd_v2_ext->gidchid[i - 1].chid),
				       ntohll(smcd_v2_ext->gidchid[i - 1].gid),
				       &matches);
	पूर्ण
	mutex_unlock(&smcd_dev_list.mutex);

	अगर (ini->ism_dev[0]) अणु
		smc_ism_get_प्रणाली_eid(ini->ism_dev[0], &eid);
		अगर (स_भेद(eid, smcd_v2_ext->प्रणाली_eid, SMC_MAX_EID_LEN))
			जाओ not_found;
	पूर्ण अन्यथा अणु
		जाओ not_found;
	पूर्ण

	/* separate - outside the smcd_dev_list.lock */
	smcd_version = ini->smcd_version;
	क्रम (i = 0; i < matches; i++) अणु
		ini->smcd_version = SMC_V2;
		ini->is_smcd = true;
		ini->ism_selected = i;
		rc = smc_listen_ism_init(new_smc, ini);
		अगर (rc) अणु
			smc_find_ism_store_rc(rc, ini);
			/* try next active ISM device */
			जारी;
		पूर्ण
		वापस; /* matching and usable V2 ISM device found */
	पूर्ण
	/* no V2 ISM device could be initialized */
	ini->smcd_version = smcd_version;	/* restore original value */

not_found:
	ini->smcd_version &= ~SMC_V2;
	ini->ism_dev[0] = शून्य;
	ini->is_smcd = false;
पूर्ण

अटल व्योम smc_find_ism_v1_device_serv(काष्ठा smc_sock *new_smc,
					काष्ठा smc_clc_msg_proposal *pclc,
					काष्ठा smc_init_info *ini)
अणु
	काष्ठा smc_clc_msg_smcd *pclc_smcd = smc_get_clc_msg_smcd(pclc);
	पूर्णांक rc = 0;

	/* check अगर ISM V1 is available */
	अगर (!(ini->smcd_version & SMC_V1) || !smcd_indicated(ini->smc_type_v1))
		जाओ not_found;
	ini->is_smcd = true; /* prepare ISM check */
	ini->ism_peer_gid[0] = ntohll(pclc_smcd->ism.gid);
	rc = smc_find_ism_device(new_smc, ini);
	अगर (rc)
		जाओ not_found;
	ini->ism_selected = 0;
	rc = smc_listen_ism_init(new_smc, ini);
	अगर (!rc)
		वापस;		/* V1 ISM device found */

not_found:
	smc_find_ism_store_rc(rc, ini);
	ini->ism_dev[0] = शून्य;
	ini->is_smcd = false;
पूर्ण

/* listen worker: रेजिस्टर buffers */
अटल पूर्णांक smc_listen_rdma_reg(काष्ठा smc_sock *new_smc, bool local_first)
अणु
	काष्ठा smc_connection *conn = &new_smc->conn;

	अगर (!local_first) अणु
		अगर (smcr_lgr_reg_rmbs(conn->lnk, conn->rmb_desc))
			वापस SMC_CLC_DECL_ERR_REGRMB;
	पूर्ण
	smc_rmb_sync_sg_क्रम_device(&new_smc->conn);

	वापस 0;
पूर्ण

अटल पूर्णांक smc_find_rdma_v1_device_serv(काष्ठा smc_sock *new_smc,
					काष्ठा smc_clc_msg_proposal *pclc,
					काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc;

	अगर (!smcr_indicated(ini->smc_type_v1))
		वापस SMC_CLC_DECL_NOSMCDEV;

	/* prepare RDMA check */
	ini->ib_lcl = &pclc->lcl;
	rc = smc_find_rdma_device(new_smc, ini);
	अगर (rc) अणु
		/* no RDMA device found */
		अगर (ini->smc_type_v1 == SMC_TYPE_B)
			/* neither ISM nor RDMA device found */
			rc = SMC_CLC_DECL_NOSMCDEV;
		वापस rc;
	पूर्ण
	rc = smc_listen_rdma_init(new_smc, ini);
	अगर (rc)
		वापस rc;
	वापस smc_listen_rdma_reg(new_smc, ini->first_contact_local);
पूर्ण

/* determine the local device matching to proposal */
अटल पूर्णांक smc_listen_find_device(काष्ठा smc_sock *new_smc,
				  काष्ठा smc_clc_msg_proposal *pclc,
				  काष्ठा smc_init_info *ini)
अणु
	पूर्णांक rc;

	/* check क्रम ISM device matching V2 proposed device */
	smc_find_ism_v2_device_serv(new_smc, pclc, ini);
	अगर (ini->ism_dev[0])
		वापस 0;

	अगर (!(ini->smcd_version & SMC_V1))
		वापस ini->rc ?: SMC_CLC_DECL_NOSMCD2DEV;

	/* check क्रम matching IP prefix and subnet length */
	rc = smc_listen_prfx_check(new_smc, pclc);
	अगर (rc)
		वापस ini->rc ?: rc;

	/* get vlan id from IP device */
	अगर (smc_vlan_by_tcpsk(new_smc->clcsock, ini))
		वापस ini->rc ?: SMC_CLC_DECL_GETVLANERR;

	/* check क्रम ISM device matching V1 proposed device */
	smc_find_ism_v1_device_serv(new_smc, pclc, ini);
	अगर (ini->ism_dev[0])
		वापस 0;

	अगर (pclc->hdr.typev1 == SMC_TYPE_D)
		/* skip RDMA and decline */
		वापस ini->rc ?: SMC_CLC_DECL_NOSMCDDEV;

	/* check अगर RDMA is available */
	rc = smc_find_rdma_v1_device_serv(new_smc, pclc, ini);
	smc_find_ism_store_rc(rc, ini);

	वापस (!rc) ? 0 : ini->rc;
पूर्ण

/* listen worker: finish RDMA setup */
अटल पूर्णांक smc_listen_rdma_finish(काष्ठा smc_sock *new_smc,
				  काष्ठा smc_clc_msg_accept_confirm *cclc,
				  bool local_first)
अणु
	काष्ठा smc_link *link = new_smc->conn.lnk;
	पूर्णांक reason_code = 0;

	अगर (local_first)
		smc_link_save_peer_info(link, cclc);

	अगर (smc_rmb_rtoken_handling(&new_smc->conn, link, cclc))
		वापस SMC_CLC_DECL_ERR_RTOK;

	अगर (local_first) अणु
		अगर (smc_ib_पढ़ोy_link(link))
			वापस SMC_CLC_DECL_ERR_RDYLNK;
		/* QP confirmation over RoCE fabric */
		smc_llc_flow_initiate(link->lgr, SMC_LLC_FLOW_ADD_LINK);
		reason_code = smcr_serv_conf_first_link(new_smc);
		smc_llc_flow_stop(link->lgr, &link->lgr->llc_flow_lcl);
	पूर्ण
	वापस reason_code;
पूर्ण

/* setup क्रम connection of server */
अटल व्योम smc_listen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_sock *new_smc = container_of(work, काष्ठा smc_sock,
						smc_listen_work);
	u8 version = smc_ism_is_v2_capable() ? SMC_V2 : SMC_V1;
	काष्ठा socket *newclcsock = new_smc->clcsock;
	काष्ठा smc_clc_msg_accept_confirm *cclc;
	काष्ठा smc_clc_msg_proposal_area *buf;
	काष्ठा smc_clc_msg_proposal *pclc;
	काष्ठा smc_init_info *ini = शून्य;
	पूर्णांक rc = 0;

	अगर (new_smc->listen_smc->sk.sk_state != SMC_LISTEN)
		वापस smc_listen_out_err(new_smc);

	अगर (new_smc->use_fallback) अणु
		smc_listen_out_connected(new_smc);
		वापस;
	पूर्ण

	/* check अगर peer is smc capable */
	अगर (!tcp_sk(newclcsock->sk)->syn_smc) अणु
		smc_चयन_to_fallback(new_smc);
		new_smc->fallback_rsn = SMC_CLC_DECL_PEERNOSMC;
		smc_listen_out_connected(new_smc);
		वापस;
	पूर्ण

	/* करो inband token exchange -
	 * रुको क्रम and receive SMC Proposal CLC message
	 */
	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf) अणु
		rc = SMC_CLC_DECL_MEM;
		जाओ out_decl;
	पूर्ण
	pclc = (काष्ठा smc_clc_msg_proposal *)buf;
	rc = smc_clc_रुको_msg(new_smc, pclc, माप(*buf),
			      SMC_CLC_PROPOSAL, CLC_WAIT_TIME);
	अगर (rc)
		जाओ out_decl;
	version = pclc->hdr.version == SMC_V1 ? SMC_V1 : version;

	/* IPSec connections opt out of SMC optimizations */
	अगर (using_ipsec(new_smc)) अणु
		rc = SMC_CLC_DECL_IPSEC;
		जाओ out_decl;
	पूर्ण

	ini = kzalloc(माप(*ini), GFP_KERNEL);
	अगर (!ini) अणु
		rc = SMC_CLC_DECL_MEM;
		जाओ out_decl;
	पूर्ण

	/* initial version checking */
	rc = smc_listen_v2_check(new_smc, pclc, ini);
	अगर (rc)
		जाओ out_decl;

	mutex_lock(&smc_server_lgr_pending);
	smc_बंद_init(new_smc);
	smc_rx_init(new_smc);
	smc_tx_init(new_smc);

	/* determine ISM or RoCE device used क्रम connection */
	rc = smc_listen_find_device(new_smc, pclc, ini);
	अगर (rc)
		जाओ out_unlock;

	/* send SMC Accept CLC message */
	rc = smc_clc_send_accept(new_smc, ini->first_contact_local,
				 ini->smcd_version == SMC_V2 ? SMC_V2 : SMC_V1);
	अगर (rc)
		जाओ out_unlock;

	/* SMC-D करोes not need this lock any more */
	अगर (ini->is_smcd)
		mutex_unlock(&smc_server_lgr_pending);

	/* receive SMC Confirm CLC message */
	स_रखो(buf, 0, माप(*buf));
	cclc = (काष्ठा smc_clc_msg_accept_confirm *)buf;
	rc = smc_clc_रुको_msg(new_smc, cclc, माप(*buf),
			      SMC_CLC_CONFIRM, CLC_WAIT_TIME);
	अगर (rc) अणु
		अगर (!ini->is_smcd)
			जाओ out_unlock;
		जाओ out_decl;
	पूर्ण

	/* finish worker */
	अगर (!ini->is_smcd) अणु
		rc = smc_listen_rdma_finish(new_smc, cclc,
					    ini->first_contact_local);
		अगर (rc)
			जाओ out_unlock;
		mutex_unlock(&smc_server_lgr_pending);
	पूर्ण
	smc_conn_save_peer_info(new_smc, cclc);
	smc_listen_out_connected(new_smc);
	जाओ out_मुक्त;

out_unlock:
	mutex_unlock(&smc_server_lgr_pending);
out_decl:
	smc_listen_decline(new_smc, rc, ini ? ini->first_contact_local : 0,
			   version);
out_मुक्त:
	kमुक्त(ini);
	kमुक्त(buf);
पूर्ण

अटल व्योम smc_tcp_listen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_sock *lsmc = container_of(work, काष्ठा smc_sock,
					     tcp_listen_work);
	काष्ठा sock *lsk = &lsmc->sk;
	काष्ठा smc_sock *new_smc;
	पूर्णांक rc = 0;

	lock_sock(lsk);
	जबतक (lsk->sk_state == SMC_LISTEN) अणु
		rc = smc_clcsock_accept(lsmc, &new_smc);
		अगर (rc) /* clcsock accept queue empty or error */
			जाओ out;
		अगर (!new_smc)
			जारी;

		new_smc->listen_smc = lsmc;
		new_smc->use_fallback = lsmc->use_fallback;
		new_smc->fallback_rsn = lsmc->fallback_rsn;
		sock_hold(lsk); /* sock_put in smc_listen_work */
		INIT_WORK(&new_smc->smc_listen_work, smc_listen_work);
		smc_copy_sock_settings_to_smc(new_smc);
		new_smc->sk.sk_sndbuf = lsmc->sk.sk_sndbuf;
		new_smc->sk.sk_rcvbuf = lsmc->sk.sk_rcvbuf;
		sock_hold(&new_smc->sk); /* sock_put in passive closing */
		अगर (!queue_work(smc_hs_wq, &new_smc->smc_listen_work))
			sock_put(&new_smc->sk);
	पूर्ण

out:
	release_sock(lsk);
	sock_put(&lsmc->sk); /* sock_hold in smc_clcsock_data_पढ़ोy() */
पूर्ण

अटल व्योम smc_clcsock_data_पढ़ोy(काष्ठा sock *listen_clcsock)
अणु
	काष्ठा smc_sock *lsmc;

	lsmc = (काष्ठा smc_sock *)
	       ((uपूर्णांकptr_t)listen_clcsock->sk_user_data & ~SK_USER_DATA_NOCOPY);
	अगर (!lsmc)
		वापस;
	lsmc->clcsk_data_पढ़ोy(listen_clcsock);
	अगर (lsmc->sk.sk_state == SMC_LISTEN) अणु
		sock_hold(&lsmc->sk); /* sock_put in smc_tcp_listen_work() */
		अगर (!queue_work(smc_hs_wq, &lsmc->tcp_listen_work))
			sock_put(&lsmc->sk);
	पूर्ण
पूर्ण

अटल पूर्णांक smc_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc;

	smc = smc_sk(sk);
	lock_sock(sk);

	rc = -EINVAL;
	अगर ((sk->sk_state != SMC_INIT && sk->sk_state != SMC_LISTEN) ||
	    smc->connect_nonblock)
		जाओ out;

	rc = 0;
	अगर (sk->sk_state == SMC_LISTEN) अणु
		sk->sk_max_ack_backlog = backlog;
		जाओ out;
	पूर्ण
	/* some socket options are handled in core, so we could not apply
	 * them to the clc socket -- copy smc socket options to clc socket
	 */
	smc_copy_sock_settings_to_clc(smc);
	अगर (!smc->use_fallback)
		tcp_sk(smc->clcsock->sk)->syn_smc = 1;

	/* save original sk_data_पढ़ोy function and establish
	 * smc-specअगरic sk_data_पढ़ोy function
	 */
	smc->clcsk_data_पढ़ोy = smc->clcsock->sk->sk_data_पढ़ोy;
	smc->clcsock->sk->sk_data_पढ़ोy = smc_clcsock_data_पढ़ोy;
	smc->clcsock->sk->sk_user_data =
		(व्योम *)((uपूर्णांकptr_t)smc | SK_USER_DATA_NOCOPY);
	rc = kernel_listen(smc->clcsock, backlog);
	अगर (rc)
		जाओ out;
	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
	sk->sk_state = SMC_LISTEN;

out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_accept(काष्ठा socket *sock, काष्ठा socket *new_sock,
		      पूर्णांक flags, bool kern)
अणु
	काष्ठा sock *sk = sock->sk, *nsk;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा smc_sock *lsmc;
	दीर्घ समयo;
	पूर्णांक rc = 0;

	lsmc = smc_sk(sk);
	sock_hold(sk); /* sock_put below */
	lock_sock(sk);

	अगर (lsmc->sk.sk_state != SMC_LISTEN) अणु
		rc = -EINVAL;
		release_sock(sk);
		जाओ out;
	पूर्ण

	/* Wait क्रम an incoming connection */
	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);
	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	जबतक (!(nsk = smc_accept_dequeue(sk, new_sock))) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!समयo) अणु
			rc = -EAGAIN;
			अवरोध;
		पूर्ण
		release_sock(sk);
		समयo = schedule_समयout(समयo);
		/* wakeup by sk_data_पढ़ोy in smc_listen_work() */
		sched_annotate_sleep();
		lock_sock(sk);
		अगर (संकेत_pending(current)) अणु
			rc = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (!rc)
		rc = sock_error(nsk);
	release_sock(sk);
	अगर (rc)
		जाओ out;

	अगर (lsmc->sockopt_defer_accept && !(flags & O_NONBLOCK)) अणु
		/* रुको till data arrives on the socket */
		समयo = msecs_to_jअगरfies(lsmc->sockopt_defer_accept *
								MSEC_PER_SEC);
		अगर (smc_sk(nsk)->use_fallback) अणु
			काष्ठा sock *clcsk = smc_sk(nsk)->clcsock->sk;

			lock_sock(clcsk);
			अगर (skb_queue_empty(&clcsk->sk_receive_queue))
				sk_रुको_data(clcsk, &समयo, शून्य);
			release_sock(clcsk);
		पूर्ण अन्यथा अगर (!atomic_पढ़ो(&smc_sk(nsk)->conn.bytes_to_rcv)) अणु
			lock_sock(nsk);
			smc_rx_रुको(smc_sk(nsk), &समयo, smc_rx_data_available);
			release_sock(nsk);
		पूर्ण
	पूर्ण

out:
	sock_put(sk); /* sock_hold above */
	वापस rc;
पूर्ण

अटल पूर्णांक smc_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
		       पूर्णांक peer)
अणु
	काष्ठा smc_sock *smc;

	अगर (peer && (sock->sk->sk_state != SMC_ACTIVE) &&
	    (sock->sk->sk_state != SMC_APPCLOSEWAIT1))
		वापस -ENOTCONN;

	smc = smc_sk(sock->sk);

	वापस smc->clcsock->ops->getname(smc->clcsock, addr, peer);
पूर्ण

अटल पूर्णांक smc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -EPIPE;

	smc = smc_sk(sk);
	lock_sock(sk);
	अगर ((sk->sk_state != SMC_ACTIVE) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT1) &&
	    (sk->sk_state != SMC_INIT))
		जाओ out;

	अगर (msg->msg_flags & MSG_FASTOPEN) अणु
		अगर (sk->sk_state == SMC_INIT && !smc->connect_nonblock) अणु
			smc_चयन_to_fallback(smc);
			smc->fallback_rsn = SMC_CLC_DECL_OPTUNSUPP;
		पूर्ण अन्यथा अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (smc->use_fallback)
		rc = smc->clcsock->ops->sendmsg(smc->clcsock, msg, len);
	अन्यथा
		rc = smc_tx_sendmsg(smc, msg, len);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		       पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -ENOTCONN;

	smc = smc_sk(sk);
	lock_sock(sk);
	अगर (sk->sk_state == SMC_CLOSED && (sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		/* socket was connected beक्रमe, no more data to पढ़ो */
		rc = 0;
		जाओ out;
	पूर्ण
	अगर ((sk->sk_state == SMC_INIT) ||
	    (sk->sk_state == SMC_LISTEN) ||
	    (sk->sk_state == SMC_CLOSED))
		जाओ out;

	अगर (sk->sk_state == SMC_PEERFINCLOSEWAIT) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (smc->use_fallback) अणु
		rc = smc->clcsock->ops->recvmsg(smc->clcsock, msg, len, flags);
	पूर्ण अन्यथा अणु
		msg->msg_namelen = 0;
		rc = smc_rx_recvmsg(smc, msg, शून्य, len, flags);
	पूर्ण

out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल __poll_t smc_accept_poll(काष्ठा sock *parent)
अणु
	काष्ठा smc_sock *isk = smc_sk(parent);
	__poll_t mask = 0;

	spin_lock(&isk->accept_q_lock);
	अगर (!list_empty(&isk->accept_q))
		mask = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&isk->accept_q_lock);

	वापस mask;
पूर्ण

अटल __poll_t smc_poll(काष्ठा file *file, काष्ठा socket *sock,
			     poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	__poll_t mask = 0;

	अगर (!sk)
		वापस EPOLLNVAL;

	smc = smc_sk(sock->sk);
	अगर (smc->use_fallback) अणु
		/* delegate to CLC child sock */
		mask = smc->clcsock->ops->poll(file, smc->clcsock, रुको);
		sk->sk_err = smc->clcsock->sk->sk_err;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != SMC_CLOSED)
			sock_poll_रुको(file, sock, रुको);
		अगर (sk->sk_err)
			mask |= EPOLLERR;
		अगर ((sk->sk_shutकरोwn == SHUTDOWN_MASK) ||
		    (sk->sk_state == SMC_CLOSED))
			mask |= EPOLLHUP;
		अगर (sk->sk_state == SMC_LISTEN) अणु
			/* woken up by sk_data_पढ़ोy in smc_listen_work() */
			mask |= smc_accept_poll(sk);
		पूर्ण अन्यथा अगर (smc->use_fallback) अणु /* as result of connect_work()*/
			mask |= smc->clcsock->ops->poll(file, smc->clcsock,
							   रुको);
			sk->sk_err = smc->clcsock->sk->sk_err;
		पूर्ण अन्यथा अणु
			अगर ((sk->sk_state != SMC_INIT &&
			     atomic_पढ़ो(&smc->conn.sndbuf_space)) ||
			    sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
				mask |= EPOLLOUT | EPOLLWRNORM;
			पूर्ण अन्यथा अणु
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			पूर्ण
			अगर (atomic_पढ़ो(&smc->conn.bytes_to_rcv))
				mask |= EPOLLIN | EPOLLRDNORM;
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;
			अगर (sk->sk_state == SMC_APPCLOSEWAIT1)
				mask |= EPOLLIN;
			अगर (smc->conn.urg_state == SMC_URG_VALID)
				mask |= EPOLLPRI;
		पूर्ण
	पूर्ण

	वापस mask;
पूर्ण

अटल पूर्णांक smc_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -EINVAL;
	पूर्णांक rc1 = 0;

	smc = smc_sk(sk);

	अगर ((how < SHUT_RD) || (how > SHUT_RDWR))
		वापस rc;

	lock_sock(sk);

	rc = -ENOTCONN;
	अगर ((sk->sk_state != SMC_ACTIVE) &&
	    (sk->sk_state != SMC_PEERCLOSEWAIT1) &&
	    (sk->sk_state != SMC_PEERCLOSEWAIT2) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT1) &&
	    (sk->sk_state != SMC_APPCLOSEWAIT2) &&
	    (sk->sk_state != SMC_APPFINCLOSEWAIT))
		जाओ out;
	अगर (smc->use_fallback) अणु
		rc = kernel_sock_shutकरोwn(smc->clcsock, how);
		sk->sk_shutकरोwn = smc->clcsock->sk->sk_shutकरोwn;
		अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
			sk->sk_state = SMC_CLOSED;
		जाओ out;
	पूर्ण
	चयन (how) अणु
	हाल SHUT_RDWR:		/* shutकरोwn in both directions */
		rc = smc_बंद_active(smc);
		अवरोध;
	हाल SHUT_WR:
		rc = smc_बंद_shutकरोwn_ग_लिखो(smc);
		अवरोध;
	हाल SHUT_RD:
		rc = 0;
		/* nothing more to करो because peer is not involved */
		अवरोध;
	पूर्ण
	अगर (smc->clcsock)
		rc1 = kernel_sock_shutकरोwn(smc->clcsock, how);
	/* map sock_shutकरोwn_cmd स्थिरants to sk_shutकरोwn value range */
	sk->sk_shutकरोwn |= how + 1;

out:
	release_sock(sk);
	वापस rc ? rc : rc1;
पूर्ण

अटल पूर्णांक smc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक val, rc;

	अगर (level == SOL_TCP && optname == TCP_ULP)
		वापस -EOPNOTSUPP;

	smc = smc_sk(sk);

	/* generic setsockopts reaching us here always apply to the
	 * CLC socket
	 */
	अगर (unlikely(!smc->clcsock->ops->setsockopt))
		rc = -EOPNOTSUPP;
	अन्यथा
		rc = smc->clcsock->ops->setsockopt(smc->clcsock, level, optname,
						   optval, optlen);
	अगर (smc->clcsock->sk->sk_err) अणु
		sk->sk_err = smc->clcsock->sk->sk_err;
		sk->sk_error_report(sk);
	पूर्ण

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	lock_sock(sk);
	अगर (rc || smc->use_fallback)
		जाओ out;
	चयन (optname) अणु
	हाल TCP_FASTOPEN:
	हाल TCP_FASTOPEN_CONNECT:
	हाल TCP_FASTOPEN_KEY:
	हाल TCP_FASTOPEN_NO_COOKIE:
		/* option not supported by SMC */
		अगर (sk->sk_state == SMC_INIT && !smc->connect_nonblock) अणु
			smc_चयन_to_fallback(smc);
			smc->fallback_rsn = SMC_CLC_DECL_OPTUNSUPP;
		पूर्ण अन्यथा अणु
			rc = -EINVAL;
		पूर्ण
		अवरोध;
	हाल TCP_NODELAY:
		अगर (sk->sk_state != SMC_INIT &&
		    sk->sk_state != SMC_LISTEN &&
		    sk->sk_state != SMC_CLOSED) अणु
			अगर (val)
				mod_delayed_work(smc->conn.lgr->tx_wq,
						 &smc->conn.tx_work, 0);
		पूर्ण
		अवरोध;
	हाल TCP_CORK:
		अगर (sk->sk_state != SMC_INIT &&
		    sk->sk_state != SMC_LISTEN &&
		    sk->sk_state != SMC_CLOSED) अणु
			अगर (!val)
				mod_delayed_work(smc->conn.lgr->tx_wq,
						 &smc->conn.tx_work, 0);
		पूर्ण
		अवरोध;
	हाल TCP_DEFER_ACCEPT:
		smc->sockopt_defer_accept = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक smc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा smc_sock *smc;

	smc = smc_sk(sock->sk);
	/* socket options apply to the CLC socket */
	अगर (unlikely(!smc->clcsock->ops->माला_लोockopt))
		वापस -EOPNOTSUPP;
	वापस smc->clcsock->ops->माला_लोockopt(smc->clcsock, level, optname,
					     optval, optlen);
पूर्ण

अटल पूर्णांक smc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
		     अचिन्हित दीर्घ arg)
अणु
	जोड़ smc_host_cursor cons, urg;
	काष्ठा smc_connection *conn;
	काष्ठा smc_sock *smc;
	पूर्णांक answ;

	smc = smc_sk(sock->sk);
	conn = &smc->conn;
	lock_sock(&smc->sk);
	अगर (smc->use_fallback) अणु
		अगर (!smc->clcsock) अणु
			release_sock(&smc->sk);
			वापस -EBADF;
		पूर्ण
		answ = smc->clcsock->ops->ioctl(smc->clcsock, cmd, arg);
		release_sock(&smc->sk);
		वापस answ;
	पूर्ण
	चयन (cmd) अणु
	हाल SIOCINQ: /* same as FIONREAD */
		अगर (smc->sk.sk_state == SMC_LISTEN) अणु
			release_sock(&smc->sk);
			वापस -EINVAL;
		पूर्ण
		अगर (smc->sk.sk_state == SMC_INIT ||
		    smc->sk.sk_state == SMC_CLOSED)
			answ = 0;
		अन्यथा
			answ = atomic_पढ़ो(&smc->conn.bytes_to_rcv);
		अवरोध;
	हाल SIOCOUTQ:
		/* output queue size (not send + not acked) */
		अगर (smc->sk.sk_state == SMC_LISTEN) अणु
			release_sock(&smc->sk);
			वापस -EINVAL;
		पूर्ण
		अगर (smc->sk.sk_state == SMC_INIT ||
		    smc->sk.sk_state == SMC_CLOSED)
			answ = 0;
		अन्यथा
			answ = smc->conn.sndbuf_desc->len -
					atomic_पढ़ो(&smc->conn.sndbuf_space);
		अवरोध;
	हाल SIOCOUTQNSD:
		/* output queue size (not send only) */
		अगर (smc->sk.sk_state == SMC_LISTEN) अणु
			release_sock(&smc->sk);
			वापस -EINVAL;
		पूर्ण
		अगर (smc->sk.sk_state == SMC_INIT ||
		    smc->sk.sk_state == SMC_CLOSED)
			answ = 0;
		अन्यथा
			answ = smc_tx_prepared_sends(&smc->conn);
		अवरोध;
	हाल SIOCATMARK:
		अगर (smc->sk.sk_state == SMC_LISTEN) अणु
			release_sock(&smc->sk);
			वापस -EINVAL;
		पूर्ण
		अगर (smc->sk.sk_state == SMC_INIT ||
		    smc->sk.sk_state == SMC_CLOSED) अणु
			answ = 0;
		पूर्ण अन्यथा अणु
			smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
			smc_curs_copy(&urg, &conn->urg_curs, conn);
			answ = smc_curs_dअगरf(conn->rmb_desc->len,
					     &cons, &urg) == 1;
		पूर्ण
		अवरोध;
	शेष:
		release_sock(&smc->sk);
		वापस -ENOIOCTLCMD;
	पूर्ण
	release_sock(&smc->sk);

	वापस put_user(answ, (पूर्णांक __user *)arg);
पूर्ण

अटल sमाप_प्रकार smc_sendpage(काष्ठा socket *sock, काष्ठा page *page,
			    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -EPIPE;

	smc = smc_sk(sk);
	lock_sock(sk);
	अगर (sk->sk_state != SMC_ACTIVE) अणु
		release_sock(sk);
		जाओ out;
	पूर्ण
	release_sock(sk);
	अगर (smc->use_fallback)
		rc = kernel_sendpage(smc->clcsock, page, offset,
				     size, flags);
	अन्यथा
		rc = sock_no_sendpage(sock, page, offset, size, flags);

out:
	वापस rc;
पूर्ण

/* Map the affected portions of the rmbe पूर्णांकo an spd, note the number of bytes
 * to splice in conn->splice_pending, and press 'go'. Delays consumer cursor
 * updates till whenever a respective page has been fully processed.
 * Note that subsequent recv() calls have to रुको till all splice() processing
 * completed.
 */
अटल sमाप_प्रकार smc_splice_पढ़ो(काष्ठा socket *sock, loff_t *ppos,
			       काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा smc_sock *smc;
	पूर्णांक rc = -ENOTCONN;

	smc = smc_sk(sk);
	lock_sock(sk);
	अगर (sk->sk_state == SMC_CLOSED && (sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		/* socket was connected beक्रमe, no more data to पढ़ो */
		rc = 0;
		जाओ out;
	पूर्ण
	अगर (sk->sk_state == SMC_INIT ||
	    sk->sk_state == SMC_LISTEN ||
	    sk->sk_state == SMC_CLOSED)
		जाओ out;

	अगर (sk->sk_state == SMC_PEERFINCLOSEWAIT) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (smc->use_fallback) अणु
		rc = smc->clcsock->ops->splice_पढ़ो(smc->clcsock, ppos,
						    pipe, len, flags);
	पूर्ण अन्यथा अणु
		अगर (*ppos) अणु
			rc = -ESPIPE;
			जाओ out;
		पूर्ण
		अगर (flags & SPLICE_F_NONBLOCK)
			flags = MSG_DONTWAIT;
		अन्यथा
			flags = 0;
		rc = smc_rx_recvmsg(smc, शून्य, pipe, len, flags);
	पूर्ण
out:
	release_sock(sk);

	वापस rc;
पूर्ण

/* must look like tcp */
अटल स्थिर काष्ठा proto_ops smc_sock_ops = अणु
	.family		= PF_SMC,
	.owner		= THIS_MODULE,
	.release	= smc_release,
	.bind		= smc_bind,
	.connect	= smc_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= smc_accept,
	.getname	= smc_getname,
	.poll		= smc_poll,
	.ioctl		= smc_ioctl,
	.listen		= smc_listen,
	.shutकरोwn	= smc_shutकरोwn,
	.setsockopt	= smc_setsockopt,
	.माला_लोockopt	= smc_माला_लोockopt,
	.sendmsg	= smc_sendmsg,
	.recvmsg	= smc_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= smc_sendpage,
	.splice_पढ़ो	= smc_splice_पढ़ो,
पूर्ण;

अटल पूर्णांक smc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	पूर्णांक family = (protocol == SMCPROTO_SMC6) ? PF_INET6 : PF_INET;
	काष्ठा smc_sock *smc;
	काष्ठा sock *sk;
	पूर्णांक rc;

	rc = -ESOCKTNOSUPPORT;
	अगर (sock->type != SOCK_STREAM)
		जाओ out;

	rc = -EPROTONOSUPPORT;
	अगर (protocol != SMCPROTO_SMC && protocol != SMCPROTO_SMC6)
		जाओ out;

	rc = -ENOBUFS;
	sock->ops = &smc_sock_ops;
	sk = smc_sock_alloc(net, sock, protocol);
	अगर (!sk)
		जाओ out;

	/* create पूर्णांकernal TCP socket क्रम CLC handshake and fallback */
	smc = smc_sk(sk);
	smc->use_fallback = false; /* assume rdma capability first */
	smc->fallback_rsn = 0;
	rc = sock_create_kern(net, family, SOCK_STREAM, IPPROTO_TCP,
			      &smc->clcsock);
	अगर (rc) अणु
		sk_common_release(sk);
		जाओ out;
	पूर्ण
	smc->sk.sk_sndbuf = max(smc->clcsock->sk->sk_sndbuf, SMC_BUF_MIN_SIZE);
	smc->sk.sk_rcvbuf = max(smc->clcsock->sk->sk_rcvbuf, SMC_BUF_MIN_SIZE);

out:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family smc_sock_family_ops = अणु
	.family	= PF_SMC,
	.owner	= THIS_MODULE,
	.create	= smc_create,
पूर्ण;

अचिन्हित पूर्णांक smc_net_id;

अटल __net_init पूर्णांक smc_net_init(काष्ठा net *net)
अणु
	वापस smc_pnet_net_init(net);
पूर्ण

अटल व्योम __net_निकास smc_net_निकास(काष्ठा net *net)
अणु
	smc_pnet_net_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations smc_net_ops = अणु
	.init = smc_net_init,
	.निकास = smc_net_निकास,
	.id   = &smc_net_id,
	.size = माप(काष्ठा smc_net),
पूर्ण;

अटल पूर्णांक __init smc_init(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_pernet_subsys(&smc_net_ops);
	अगर (rc)
		वापस rc;

	smc_ism_init();
	smc_clc_init();

	rc = smc_nl_init();
	अगर (rc)
		जाओ out_pernet_subsys;

	rc = smc_pnet_init();
	अगर (rc)
		जाओ out_nl;

	rc = -ENOMEM;
	smc_hs_wq = alloc_workqueue("smc_hs_wq", 0, 0);
	अगर (!smc_hs_wq)
		जाओ out_pnet;

	smc_बंद_wq = alloc_workqueue("smc_close_wq", 0, 0);
	अगर (!smc_बंद_wq)
		जाओ out_alloc_hs_wq;

	rc = smc_core_init();
	अगर (rc) अणु
		pr_err("%s: smc_core_init fails with %d\n", __func__, rc);
		जाओ out_alloc_wqs;
	पूर्ण

	rc = smc_llc_init();
	अगर (rc) अणु
		pr_err("%s: smc_llc_init fails with %d\n", __func__, rc);
		जाओ out_core;
	पूर्ण

	rc = smc_cdc_init();
	अगर (rc) अणु
		pr_err("%s: smc_cdc_init fails with %d\n", __func__, rc);
		जाओ out_core;
	पूर्ण

	rc = proto_रेजिस्टर(&smc_proto, 1);
	अगर (rc) अणु
		pr_err("%s: proto_register(v4) fails with %d\n", __func__, rc);
		जाओ out_core;
	पूर्ण

	rc = proto_रेजिस्टर(&smc_proto6, 1);
	अगर (rc) अणु
		pr_err("%s: proto_register(v6) fails with %d\n", __func__, rc);
		जाओ out_proto;
	पूर्ण

	rc = sock_रेजिस्टर(&smc_sock_family_ops);
	अगर (rc) अणु
		pr_err("%s: sock_register fails with %d\n", __func__, rc);
		जाओ out_proto6;
	पूर्ण
	INIT_HLIST_HEAD(&smc_v4_hashinfo.ht);
	INIT_HLIST_HEAD(&smc_v6_hashinfo.ht);

	rc = smc_ib_रेजिस्टर_client();
	अगर (rc) अणु
		pr_err("%s: ib_register fails with %d\n", __func__, rc);
		जाओ out_sock;
	पूर्ण

	अटल_branch_enable(&tcp_have_smc);
	वापस 0;

out_sock:
	sock_unरेजिस्टर(PF_SMC);
out_proto6:
	proto_unरेजिस्टर(&smc_proto6);
out_proto:
	proto_unरेजिस्टर(&smc_proto);
out_core:
	smc_core_निकास();
out_alloc_wqs:
	destroy_workqueue(smc_बंद_wq);
out_alloc_hs_wq:
	destroy_workqueue(smc_hs_wq);
out_pnet:
	smc_pnet_निकास();
out_nl:
	smc_nl_निकास();
out_pernet_subsys:
	unरेजिस्टर_pernet_subsys(&smc_net_ops);

	वापस rc;
पूर्ण

अटल व्योम __निकास smc_निकास(व्योम)
अणु
	अटल_branch_disable(&tcp_have_smc);
	sock_unरेजिस्टर(PF_SMC);
	smc_core_निकास();
	smc_ib_unरेजिस्टर_client();
	destroy_workqueue(smc_बंद_wq);
	destroy_workqueue(smc_hs_wq);
	proto_unरेजिस्टर(&smc_proto6);
	proto_unरेजिस्टर(&smc_proto);
	smc_pnet_निकास();
	smc_nl_निकास();
	unरेजिस्टर_pernet_subsys(&smc_net_ops);
	rcu_barrier();
पूर्ण

module_init(smc_init);
module_निकास(smc_निकास);

MODULE_AUTHOR("Ursula Braun <ubraun@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("smc socket address family");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_SMC);
