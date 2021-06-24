<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/proto.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>

#समावेश <net/inet_sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/sock.h>
#समावेश <net/xfrm.h>

#समावेश <यंत्र/ioctls.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/poll.h>

#समावेश "ccid.h"
#समावेश "dccp.h"
#समावेश "feat.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

DEFINE_SNMP_STAT(काष्ठा dccp_mib, dccp_statistics) __पढ़ो_mostly;

EXPORT_SYMBOL_GPL(dccp_statistics);

काष्ठा percpu_counter dccp_orphan_count;
EXPORT_SYMBOL_GPL(dccp_orphan_count);

काष्ठा inet_hashinfo dccp_hashinfo;
EXPORT_SYMBOL_GPL(dccp_hashinfo);

/* the maximum queue length क्रम tx in packets. 0 is no limit */
पूर्णांक sysctl_dccp_tx_qlen __पढ़ो_mostly = 5;

#अगर_घोषित CONFIG_IP_DCCP_DEBUG
अटल स्थिर अक्षर *dccp_state_name(स्थिर पूर्णांक state)
अणु
	अटल स्थिर अक्षर *स्थिर dccp_state_names[] = अणु
	[DCCP_OPEN]		= "OPEN",
	[DCCP_REQUESTING]	= "REQUESTING",
	[DCCP_PARTOPEN]		= "PARTOPEN",
	[DCCP_LISTEN]		= "LISTEN",
	[DCCP_RESPOND]		= "RESPOND",
	[DCCP_CLOSING]		= "CLOSING",
	[DCCP_ACTIVE_CLOSEREQ]	= "CLOSEREQ",
	[DCCP_PASSIVE_CLOSE]	= "PASSIVE_CLOSE",
	[DCCP_PASSIVE_CLOSEREQ]	= "PASSIVE_CLOSEREQ",
	[DCCP_TIME_WAIT]	= "TIME_WAIT",
	[DCCP_CLOSED]		= "CLOSED",
	पूर्ण;

	अगर (state >= DCCP_MAX_STATES)
		वापस "INVALID STATE!";
	अन्यथा
		वापस dccp_state_names[state];
पूर्ण
#पूर्ण_अगर

व्योम dccp_set_state(काष्ठा sock *sk, स्थिर पूर्णांक state)
अणु
	स्थिर पूर्णांक oldstate = sk->sk_state;

	dccp_pr_debug("%s(%p)  %s  -->  %s\n", dccp_role(sk), sk,
		      dccp_state_name(oldstate), dccp_state_name(state));
	WARN_ON(state == oldstate);

	चयन (state) अणु
	हाल DCCP_OPEN:
		अगर (oldstate != DCCP_OPEN)
			DCCP_INC_STATS(DCCP_MIB_CURRESTAB);
		/* Client retransmits all Confirm options until entering OPEN */
		अगर (oldstate == DCCP_PARTOPEN)
			dccp_feat_list_purge(&dccp_sk(sk)->dccps_featneg);
		अवरोध;

	हाल DCCP_CLOSED:
		अगर (oldstate == DCCP_OPEN || oldstate == DCCP_ACTIVE_CLOSEREQ ||
		    oldstate == DCCP_CLOSING)
			DCCP_INC_STATS(DCCP_MIB_ESTABRESETS);

		sk->sk_prot->unhash(sk);
		अगर (inet_csk(sk)->icsk_bind_hash != शून्य &&
		    !(sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			inet_put_port(sk);
		fallthrough;
	शेष:
		अगर (oldstate == DCCP_OPEN)
			DCCP_DEC_STATS(DCCP_MIB_CURRESTAB);
	पूर्ण

	/* Change state AFTER socket is unhashed to aव्योम बंदd
	 * socket sitting in hash tables.
	 */
	inet_sk_set_state(sk, state);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_set_state);

अटल व्योम dccp_finish_passive_बंद(काष्ठा sock *sk)
अणु
	चयन (sk->sk_state) अणु
	हाल DCCP_PASSIVE_CLOSE:
		/* Node (client or server) has received Close packet. */
		dccp_send_reset(sk, DCCP_RESET_CODE_CLOSED);
		dccp_set_state(sk, DCCP_CLOSED);
		अवरोध;
	हाल DCCP_PASSIVE_CLOSEREQ:
		/*
		 * Client received CloseReq. We set the `active' flag so that
		 * dccp_send_बंद() retransmits the Close as per RFC 4340, 8.3.
		 */
		dccp_send_बंद(sk, 1);
		dccp_set_state(sk, DCCP_CLOSING);
	पूर्ण
पूर्ण

व्योम dccp_करोne(काष्ठा sock *sk)
अणु
	dccp_set_state(sk, DCCP_CLOSED);
	dccp_clear_xmit_समयrs(sk);

	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
	अन्यथा
		inet_csk_destroy_sock(sk);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_करोne);

स्थिर अक्षर *dccp_packet_name(स्थिर पूर्णांक type)
अणु
	अटल स्थिर अक्षर *स्थिर dccp_packet_names[] = अणु
		[DCCP_PKT_REQUEST]  = "REQUEST",
		[DCCP_PKT_RESPONSE] = "RESPONSE",
		[DCCP_PKT_DATA]	    = "DATA",
		[DCCP_PKT_ACK]	    = "ACK",
		[DCCP_PKT_DATAACK]  = "DATAACK",
		[DCCP_PKT_CLOSEREQ] = "CLOSEREQ",
		[DCCP_PKT_CLOSE]    = "CLOSE",
		[DCCP_PKT_RESET]    = "RESET",
		[DCCP_PKT_SYNC]	    = "SYNC",
		[DCCP_PKT_SYNCACK]  = "SYNCACK",
	पूर्ण;

	अगर (type >= DCCP_NR_PKT_TYPES)
		वापस "INVALID";
	अन्यथा
		वापस dccp_packet_names[type];
पूर्ण

EXPORT_SYMBOL_GPL(dccp_packet_name);

अटल व्योम dccp_sk_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	ccid_hc_tx_delete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_tx_ccid = शून्य;
	inet_sock_deकाष्ठा(sk);
पूर्ण

पूर्णांक dccp_init_sock(काष्ठा sock *sk, स्थिर __u8 ctl_sock_initialized)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_rto		= DCCP_TIMEOUT_INIT;
	icsk->icsk_syn_retries	= sysctl_dccp_request_retries;
	sk->sk_state		= DCCP_CLOSED;
	sk->sk_ग_लिखो_space	= dccp_ग_लिखो_space;
	sk->sk_deकाष्ठा		= dccp_sk_deकाष्ठा;
	icsk->icsk_sync_mss	= dccp_sync_mss;
	dp->dccps_mss_cache	= 536;
	dp->dccps_rate_last	= jअगरfies;
	dp->dccps_role		= DCCP_ROLE_UNDEFINED;
	dp->dccps_service	= DCCP_SERVICE_CODE_IS_ABSENT;
	dp->dccps_tx_qlen	= sysctl_dccp_tx_qlen;

	dccp_init_xmit_समयrs(sk);

	INIT_LIST_HEAD(&dp->dccps_featneg);
	/* control socket करोesn't need feat nego */
	अगर (likely(ctl_sock_initialized))
		वापस dccp_feat_init(sk);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_init_sock);

व्योम dccp_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	__skb_queue_purge(&sk->sk_ग_लिखो_queue);
	अगर (sk->sk_send_head != शून्य) अणु
		kमुक्त_skb(sk->sk_send_head);
		sk->sk_send_head = शून्य;
	पूर्ण

	/* Clean up a referenced DCCP bind bucket. */
	अगर (inet_csk(sk)->icsk_bind_hash != शून्य)
		inet_put_port(sk);

	kमुक्त(dp->dccps_service_list);
	dp->dccps_service_list = शून्य;

	अगर (dp->dccps_hc_rx_ackvec != शून्य) अणु
		dccp_ackvec_मुक्त(dp->dccps_hc_rx_ackvec);
		dp->dccps_hc_rx_ackvec = शून्य;
	पूर्ण
	ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
	dp->dccps_hc_rx_ccid = शून्य;

	/* clean up feature negotiation state */
	dccp_feat_list_purge(&dp->dccps_featneg);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_destroy_sock);

अटल अंतरभूत पूर्णांक dccp_listen_start(काष्ठा sock *sk, पूर्णांक backlog)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	dp->dccps_role = DCCP_ROLE_LISTEN;
	/* करो not start to listen अगर feature negotiation setup fails */
	अगर (dccp_feat_finalise_settings(dp))
		वापस -EPROTO;
	वापस inet_csk_listen_start(sk, backlog);
पूर्ण

अटल अंतरभूत पूर्णांक dccp_need_reset(पूर्णांक state)
अणु
	वापस state != DCCP_CLOSED && state != DCCP_LISTEN &&
	       state != DCCP_REQUESTING;
पूर्ण

पूर्णांक dccp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	स्थिर पूर्णांक old_state = sk->sk_state;

	अगर (old_state != DCCP_CLOSED)
		dccp_set_state(sk, DCCP_CLOSED);

	/*
	 * This corresponds to the ABORT function of RFC793, sec. 3.8
	 * TCP uses a RST segment, DCCP a Reset packet with Code 2, "Aborted".
	 */
	अगर (old_state == DCCP_LISTEN) अणु
		inet_csk_listen_stop(sk);
	पूर्ण अन्यथा अगर (dccp_need_reset(old_state)) अणु
		dccp_send_reset(sk, DCCP_RESET_CODE_ABORTED);
		sk->sk_err = ECONNRESET;
	पूर्ण अन्यथा अगर (old_state == DCCP_REQUESTING)
		sk->sk_err = ECONNRESET;

	dccp_clear_xmit_समयrs(sk);
	ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
	dp->dccps_hc_rx_ccid = शून्य;

	__skb_queue_purge(&sk->sk_receive_queue);
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);
	अगर (sk->sk_send_head != शून्य) अणु
		__kमुक्त_skb(sk->sk_send_head);
		sk->sk_send_head = शून्य;
	पूर्ण

	inet->inet_dport = 0;

	अगर (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	sk->sk_shutकरोwn = 0;
	sock_reset_flag(sk, SOCK_DONE);

	icsk->icsk_backoff = 0;
	inet_csk_delack_init(sk);
	__sk_dst_reset(sk);

	WARN_ON(inet->inet_num && !icsk->icsk_bind_hash);

	sk->sk_error_report(sk);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_disconnect);

/*
 *	Wait क्रम a DCCP event.
 *
 *	Note that we करोn't need to lock the socket, as the upper poll layers
 *	take care of normal races (between the test and the event) and we करोn't
 *	go look at any of the socket buffers directly.
 */
__poll_t dccp_poll(काष्ठा file *file, काष्ठा socket *sock,
		       poll_table *रुको)
अणु
	__poll_t mask;
	काष्ठा sock *sk = sock->sk;

	sock_poll_रुको(file, sock, रुको);
	अगर (sk->sk_state == DCCP_LISTEN)
		वापस inet_csk_listen_poll(sk);

	/* Socket is not locked. We are रक्षित from async events
	   by poll logic and correct handling of state changes
	   made by another thपढ़ोs is impossible in any हाल.
	 */

	mask = 0;
	अगर (sk->sk_err)
		mask = EPOLLERR;

	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK || sk->sk_state == DCCP_CLOSED)
		mask |= EPOLLHUP;
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;

	/* Connected? */
	अगर ((1 << sk->sk_state) & ~(DCCPF_REQUESTING | DCCPF_RESPOND)) अणु
		अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > 0)
			mask |= EPOLLIN | EPOLLRDNORM;

		अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
			अगर (sk_stream_is_ग_लिखोable(sk)) अणु
				mask |= EPOLLOUT | EPOLLWRNORM;
			पूर्ण अन्यथा अणु  /* send SIGIO later */
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

				/* Race अवरोधer. If space is मुक्तd after
				 * wspace test but beक्रमe the flags are set,
				 * IO संकेत will be lost.
				 */
				अगर (sk_stream_is_ग_लिखोable(sk))
					mask |= EPOLLOUT | EPOLLWRNORM;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस mask;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_poll);

पूर्णांक dccp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc = -ENOTCONN;

	lock_sock(sk);

	अगर (sk->sk_state == DCCP_LISTEN)
		जाओ out;

	चयन (cmd) अणु
	हाल SIOCOUTQ: अणु
		पूर्णांक amount = sk_wmem_alloc_get(sk);
		/* Using sk_wmem_alloc here because sk_wmem_queued is not used by DCCP and
		 * always 0, comparably to UDP.
		 */

		rc = put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
		अवरोध;
	हाल SIOCINQ: अणु
		काष्ठा sk_buff *skb;
		अचिन्हित दीर्घ amount = 0;

		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb != शून्य) अणु
			/*
			 * We will only वापस the amount of this packet since
			 * that is all that will be पढ़ो.
			 */
			amount = skb->len;
		पूर्ण
		rc = put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
		अवरोध;
	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
out:
	release_sock(sk);
	वापस rc;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_ioctl);

अटल पूर्णांक dccp_setsockopt_service(काष्ठा sock *sk, स्थिर __be32 service,
				   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा dccp_service_list *sl = शून्य;

	अगर (service == DCCP_SERVICE_INVALID_VALUE ||
	    optlen > DCCP_SERVICE_LIST_MAX_LEN * माप(u32))
		वापस -EINVAL;

	अगर (optlen > माप(service)) अणु
		sl = kदो_स्मृति(optlen, GFP_KERNEL);
		अगर (sl == शून्य)
			वापस -ENOMEM;

		sl->dccpsl_nr = optlen / माप(u32) - 1;
		अगर (copy_from_sockptr_offset(sl->dccpsl_list, optval,
				माप(service), optlen - माप(service)) ||
		    dccp_list_has_service(sl, DCCP_SERVICE_INVALID_VALUE)) अणु
			kमुक्त(sl);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	lock_sock(sk);
	dp->dccps_service = service;

	kमुक्त(dp->dccps_service_list);

	dp->dccps_service_list = sl;
	release_sock(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_setsockopt_cscov(काष्ठा sock *sk, पूर्णांक cscov, bool rx)
अणु
	u8 *list, len;
	पूर्णांक i, rc;

	अगर (cscov < 0 || cscov > 15)
		वापस -EINVAL;
	/*
	 * Populate a list of permissible values, in the range cscov...15. This
	 * is necessary since feature negotiation of single values only works अगर
	 * both sides incidentally choose the same value. Since the list starts
	 * lowest-value first, negotiation will pick the smallest shared value.
	 */
	अगर (cscov == 0)
		वापस 0;
	len = 16 - cscov;

	list = kदो_स्मृति(len, GFP_KERNEL);
	अगर (list == शून्य)
		वापस -ENOBUFS;

	क्रम (i = 0; i < len; i++)
		list[i] = cscov++;

	rc = dccp_feat_रेजिस्टर_sp(sk, DCCPF_MIN_CSUM_COVER, rx, list, len);

	अगर (rc == 0) अणु
		अगर (rx)
			dccp_sk(sk)->dccps_pcrlen = cscov;
		अन्यथा
			dccp_sk(sk)->dccps_pcslen = cscov;
	पूर्ण
	kमुक्त(list);
	वापस rc;
पूर्ण

अटल पूर्णांक dccp_setsockopt_ccid(काष्ठा sock *sk, पूर्णांक type,
				sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	u8 *val;
	पूर्णांक rc = 0;

	अगर (optlen < 1 || optlen > DCCP_FEAT_MAX_SP_VALS)
		वापस -EINVAL;

	val = memdup_sockptr(optval, optlen);
	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	lock_sock(sk);
	अगर (type == DCCP_SOCKOPT_TX_CCID || type == DCCP_SOCKOPT_CCID)
		rc = dccp_feat_रेजिस्टर_sp(sk, DCCPF_CCID, 1, val, optlen);

	अगर (!rc && (type == DCCP_SOCKOPT_RX_CCID || type == DCCP_SOCKOPT_CCID))
		rc = dccp_feat_रेजिस्टर_sp(sk, DCCPF_CCID, 0, val, optlen);
	release_sock(sk);

	kमुक्त(val);
	वापस rc;
पूर्ण

अटल पूर्णांक करो_dccp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	पूर्णांक val, err = 0;

	चयन (optname) अणु
	हाल DCCP_SOCKOPT_PACKET_SIZE:
		DCCP_WARN("sockopt(PACKET_SIZE) is deprecated: fix your app\n");
		वापस 0;
	हाल DCCP_SOCKOPT_CHANGE_L:
	हाल DCCP_SOCKOPT_CHANGE_R:
		DCCP_WARN("sockopt(CHANGE_L/R) is deprecated: fix your app\n");
		वापस 0;
	हाल DCCP_SOCKOPT_CCID:
	हाल DCCP_SOCKOPT_RX_CCID:
	हाल DCCP_SOCKOPT_TX_CCID:
		वापस dccp_setsockopt_ccid(sk, optname, optval, optlen);
	पूर्ण

	अगर (optlen < (पूर्णांक)माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	अगर (optname == DCCP_SOCKOPT_SERVICE)
		वापस dccp_setsockopt_service(sk, val, optval, optlen);

	lock_sock(sk);
	चयन (optname) अणु
	हाल DCCP_SOCKOPT_SERVER_TIMEWAIT:
		अगर (dp->dccps_role != DCCP_ROLE_SERVER)
			err = -EOPNOTSUPP;
		अन्यथा
			dp->dccps_server_समयरुको = (val != 0);
		अवरोध;
	हाल DCCP_SOCKOPT_SEND_CSCOV:
		err = dccp_setsockopt_cscov(sk, val, false);
		अवरोध;
	हाल DCCP_SOCKOPT_RECV_CSCOV:
		err = dccp_setsockopt_cscov(sk, val, true);
		अवरोध;
	हाल DCCP_SOCKOPT_QPOLICY_ID:
		अगर (sk->sk_state != DCCP_CLOSED)
			err = -EISCONN;
		अन्यथा अगर (val < 0 || val >= DCCPQ_POLICY_MAX)
			err = -EINVAL;
		अन्यथा
			dp->dccps_qpolicy = val;
		अवरोध;
	हाल DCCP_SOCKOPT_QPOLICY_TXQLEN:
		अगर (val < 0)
			err = -EINVAL;
		अन्यथा
			dp->dccps_tx_qlen = val;
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	release_sock(sk);

	वापस err;
पूर्ण

पूर्णांक dccp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		    अचिन्हित पूर्णांक optlen)
अणु
	अगर (level != SOL_DCCP)
		वापस inet_csk(sk)->icsk_af_ops->setsockopt(sk, level,
							     optname, optval,
							     optlen);
	वापस करो_dccp_setsockopt(sk, level, optname, optval, optlen);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_setsockopt);

अटल पूर्णांक dccp_माला_लोockopt_service(काष्ठा sock *sk, पूर्णांक len,
				   __be32 __user *optval,
				   पूर्णांक __user *optlen)
अणु
	स्थिर काष्ठा dccp_sock *dp = dccp_sk(sk);
	स्थिर काष्ठा dccp_service_list *sl;
	पूर्णांक err = -ENOENT, slen = 0, total_len = माप(u32);

	lock_sock(sk);
	अगर ((sl = dp->dccps_service_list) != शून्य) अणु
		slen = sl->dccpsl_nr * माप(u32);
		total_len += slen;
	पूर्ण

	err = -EINVAL;
	अगर (total_len > len)
		जाओ out;

	err = 0;
	अगर (put_user(total_len, optlen) ||
	    put_user(dp->dccps_service, optval) ||
	    (sl != शून्य && copy_to_user(optval + 1, sl->dccpsl_list, slen)))
		err = -EFAULT;
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक करो_dccp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा dccp_sock *dp;
	पूर्णांक val, len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < (पूर्णांक)माप(पूर्णांक))
		वापस -EINVAL;

	dp = dccp_sk(sk);

	चयन (optname) अणु
	हाल DCCP_SOCKOPT_PACKET_SIZE:
		DCCP_WARN("sockopt(PACKET_SIZE) is deprecated: fix your app\n");
		वापस 0;
	हाल DCCP_SOCKOPT_SERVICE:
		वापस dccp_माला_लोockopt_service(sk, len,
					       (__be32 __user *)optval, optlen);
	हाल DCCP_SOCKOPT_GET_CUR_MPS:
		val = dp->dccps_mss_cache;
		अवरोध;
	हाल DCCP_SOCKOPT_AVAILABLE_CCIDS:
		वापस ccid_माला_लोockopt_builtin_ccids(sk, len, optval, optlen);
	हाल DCCP_SOCKOPT_TX_CCID:
		val = ccid_get_current_tx_ccid(dp);
		अगर (val < 0)
			वापस -ENOPROTOOPT;
		अवरोध;
	हाल DCCP_SOCKOPT_RX_CCID:
		val = ccid_get_current_rx_ccid(dp);
		अगर (val < 0)
			वापस -ENOPROTOOPT;
		अवरोध;
	हाल DCCP_SOCKOPT_SERVER_TIMEWAIT:
		val = dp->dccps_server_समयरुको;
		अवरोध;
	हाल DCCP_SOCKOPT_SEND_CSCOV:
		val = dp->dccps_pcslen;
		अवरोध;
	हाल DCCP_SOCKOPT_RECV_CSCOV:
		val = dp->dccps_pcrlen;
		अवरोध;
	हाल DCCP_SOCKOPT_QPOLICY_ID:
		val = dp->dccps_qpolicy;
		अवरोध;
	हाल DCCP_SOCKOPT_QPOLICY_TXQLEN:
		val = dp->dccps_tx_qlen;
		अवरोध;
	हाल 128 ... 191:
		वापस ccid_hc_rx_माला_लोockopt(dp->dccps_hc_rx_ccid, sk, optname,
					     len, (u32 __user *)optval, optlen);
	हाल 192 ... 255:
		वापस ccid_hc_tx_माला_लोockopt(dp->dccps_hc_tx_ccid, sk, optname,
					     len, (u32 __user *)optval, optlen);
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	len = माप(val);
	अगर (put_user(len, optlen) || copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक dccp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (level != SOL_DCCP)
		वापस inet_csk(sk)->icsk_af_ops->माला_लोockopt(sk, level,
							     optname, optval,
							     optlen);
	वापस करो_dccp_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_माला_लोockopt);

अटल पूर्णांक dccp_msghdr_parse(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा cmsghdr *cmsg;

	/*
	 * Assign an (opaque) qpolicy priority value to skb->priority.
	 *
	 * We are overloading this skb field क्रम use with the qpolicy subystem.
	 * The skb->priority is normally used क्रम the SO_PRIORITY option, which
	 * is initialised from sk_priority. Since the assignment of sk_priority
	 * to skb->priority happens later (on layer 3), we overload this field
	 * क्रम use with queueing priorities as दीर्घ as the skb is on layer 4.
	 * The शेष priority value (अगर nothing is set) is 0.
	 */
	skb->priority = 0;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		अगर (cmsg->cmsg_level != SOL_DCCP)
			जारी;

		अगर (cmsg->cmsg_type <= DCCP_SCM_QPOLICY_MAX &&
		    !dccp_qpolicy_param_ok(skb->sk, cmsg->cmsg_type))
			वापस -EINVAL;

		चयन (cmsg->cmsg_type) अणु
		हाल DCCP_SCM_PRIORITY:
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(__u32)))
				वापस -EINVAL;
			skb->priority = *(__u32 *)CMSG_DATA(cmsg);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dccp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	स्थिर काष्ठा dccp_sock *dp = dccp_sk(sk);
	स्थिर पूर्णांक flags = msg->msg_flags;
	स्थिर पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sk_buff *skb;
	पूर्णांक rc, size;
	दीर्घ समयo;

	trace_dccp_probe(sk, len);

	अगर (len > dp->dccps_mss_cache)
		वापस -EMSGSIZE;

	lock_sock(sk);

	अगर (dccp_qpolicy_full(sk)) अणु
		rc = -EAGAIN;
		जाओ out_release;
	पूर्ण

	समयo = sock_sndसमयo(sk, noblock);

	/*
	 * We have to use sk_stream_रुको_connect here to set sk_ग_लिखो_pending,
	 * so that the trick in dccp_rcv_request_sent_state_process.
	 */
	/* Wait क्रम a connection to finish. */
	अगर ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PARTOPEN))
		अगर ((rc = sk_stream_रुको_connect(sk, &समयo)) != 0)
			जाओ out_release;

	size = sk->sk_prot->max_header + len;
	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, noblock, &rc);
	lock_sock(sk);
	अगर (skb == शून्य)
		जाओ out_release;

	अगर (sk->sk_state == DCCP_CLOSED) अणु
		rc = -ENOTCONN;
		जाओ out_discard;
	पूर्ण

	skb_reserve(skb, sk->sk_prot->max_header);
	rc = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (rc != 0)
		जाओ out_discard;

	rc = dccp_msghdr_parse(msg, skb);
	अगर (rc != 0)
		जाओ out_discard;

	dccp_qpolicy_push(sk, skb);
	/*
	 * The xmit_समयr is set अगर the TX CCID is rate-based and will expire
	 * when congestion control permits to release further packets पूर्णांकo the
	 * network. Winकरोw-based CCIDs करो not use this समयr.
	 */
	अगर (!समयr_pending(&dp->dccps_xmit_समयr))
		dccp_ग_लिखो_xmit(sk);
out_release:
	release_sock(sk);
	वापस rc ? : len;
out_discard:
	kमुक्त_skb(skb);
	जाओ out_release;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_sendmsg);

पूर्णांक dccp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक nonblock,
		 पूर्णांक flags, पूर्णांक *addr_len)
अणु
	स्थिर काष्ठा dccp_hdr *dh;
	दीर्घ समयo;

	lock_sock(sk);

	अगर (sk->sk_state == DCCP_LISTEN) अणु
		len = -ENOTCONN;
		जाओ out;
	पूर्ण

	समयo = sock_rcvसमयo(sk, nonblock);

	करो अणु
		काष्ठा sk_buff *skb = skb_peek(&sk->sk_receive_queue);

		अगर (skb == शून्य)
			जाओ verअगरy_sock_status;

		dh = dccp_hdr(skb);

		चयन (dh->dccph_type) अणु
		हाल DCCP_PKT_DATA:
		हाल DCCP_PKT_DATAACK:
			जाओ found_ok_skb;

		हाल DCCP_PKT_CLOSE:
		हाल DCCP_PKT_CLOSEREQ:
			अगर (!(flags & MSG_PEEK))
				dccp_finish_passive_बंद(sk);
			fallthrough;
		हाल DCCP_PKT_RESET:
			dccp_pr_debug("found fin (%s) ok!\n",
				      dccp_packet_name(dh->dccph_type));
			len = 0;
			जाओ found_fin_ok;
		शेष:
			dccp_pr_debug("packet_type=%s\n",
				      dccp_packet_name(dh->dccph_type));
			sk_eat_skb(sk, skb);
		पूर्ण
verअगरy_sock_status:
		अगर (sock_flag(sk, SOCK_DONE)) अणु
			len = 0;
			अवरोध;
		पूर्ण

		अगर (sk->sk_err) अणु
			len = sock_error(sk);
			अवरोध;
		पूर्ण

		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
			len = 0;
			अवरोध;
		पूर्ण

		अगर (sk->sk_state == DCCP_CLOSED) अणु
			अगर (!sock_flag(sk, SOCK_DONE)) अणु
				/* This occurs when user tries to पढ़ो
				 * from never connected socket.
				 */
				len = -ENOTCONN;
				अवरोध;
			पूर्ण
			len = 0;
			अवरोध;
		पूर्ण

		अगर (!समयo) अणु
			len = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			len = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण

		sk_रुको_data(sk, &समयo, शून्य);
		जारी;
	found_ok_skb:
		अगर (len > skb->len)
			len = skb->len;
		अन्यथा अगर (len < skb->len)
			msg->msg_flags |= MSG_TRUNC;

		अगर (skb_copy_datagram_msg(skb, 0, msg, len)) अणु
			/* Exception. Bailout! */
			len = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (flags & MSG_TRUNC)
			len = skb->len;
	found_fin_ok:
		अगर (!(flags & MSG_PEEK))
			sk_eat_skb(sk, skb);
		अवरोध;
	पूर्ण जबतक (1);
out:
	release_sock(sk);
	वापस len;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_recvmsg);

पूर्णांक inet_dccp_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	अचिन्हित अक्षर old_state;
	पूर्णांक err;

	lock_sock(sk);

	err = -EINVAL;
	अगर (sock->state != SS_UNCONNECTED || sock->type != SOCK_DCCP)
		जाओ out;

	old_state = sk->sk_state;
	अगर (!((1 << old_state) & (DCCPF_CLOSED | DCCPF_LISTEN)))
		जाओ out;

	WRITE_ONCE(sk->sk_max_ack_backlog, backlog);
	/* Really, अगर the socket is alपढ़ोy in listen state
	 * we can only allow the backlog to be adjusted.
	 */
	अगर (old_state != DCCP_LISTEN) अणु
		/*
		 * FIXME: here it probably should be sk->sk_prot->listen_start
		 * see tcp_listen_start
		 */
		err = dccp_listen_start(sk, backlog);
		अगर (err)
			जाओ out;
	पूर्ण
	err = 0;

out:
	release_sock(sk);
	वापस err;
पूर्ण

EXPORT_SYMBOL_GPL(inet_dccp_listen);

अटल व्योम dccp_terminate_connection(काष्ठा sock *sk)
अणु
	u8 next_state = DCCP_CLOSED;

	चयन (sk->sk_state) अणु
	हाल DCCP_PASSIVE_CLOSE:
	हाल DCCP_PASSIVE_CLOSEREQ:
		dccp_finish_passive_बंद(sk);
		अवरोध;
	हाल DCCP_PARTOPEN:
		dccp_pr_debug("Stop PARTOPEN timer (%p)\n", sk);
		inet_csk_clear_xmit_समयr(sk, ICSK_TIME_DACK);
		fallthrough;
	हाल DCCP_OPEN:
		dccp_send_बंद(sk, 1);

		अगर (dccp_sk(sk)->dccps_role == DCCP_ROLE_SERVER &&
		    !dccp_sk(sk)->dccps_server_समयरुको)
			next_state = DCCP_ACTIVE_CLOSEREQ;
		अन्यथा
			next_state = DCCP_CLOSING;
		fallthrough;
	शेष:
		dccp_set_state(sk, next_state);
	पूर्ण
पूर्ण

व्योम dccp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा sk_buff *skb;
	u32 data_was_unपढ़ो = 0;
	पूर्णांक state;

	lock_sock(sk);

	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर (sk->sk_state == DCCP_LISTEN) अणु
		dccp_set_state(sk, DCCP_CLOSED);

		/* Special हाल. */
		inet_csk_listen_stop(sk);

		जाओ adjudge_to_death;
	पूर्ण

	sk_stop_समयr(sk, &dp->dccps_xmit_समयr);

	/*
	 * We need to flush the recv. buffs.  We करो this only on the
	 * descriptor बंद, not protocol-sourced बंदs, because the
	  *पढ़ोer process may not have drained the data yet!
	 */
	जबतक ((skb = __skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		data_was_unपढ़ो += skb->len;
		__kमुक्त_skb(skb);
	पूर्ण

	/* If socket has been alपढ़ोy reset समाप्त it. */
	अगर (sk->sk_state == DCCP_CLOSED)
		जाओ adjudge_to_death;

	अगर (data_was_unपढ़ो) अणु
		/* Unपढ़ो data was tossed, send an appropriate Reset Code */
		DCCP_WARN("ABORT with %u bytes unread\n", data_was_unपढ़ो);
		dccp_send_reset(sk, DCCP_RESET_CODE_ABORTED);
		dccp_set_state(sk, DCCP_CLOSED);
	पूर्ण अन्यथा अगर (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingerसमय) अणु
		/* Check zero linger _after_ checking क्रम unपढ़ो data. */
		sk->sk_prot->disconnect(sk, 0);
	पूर्ण अन्यथा अगर (sk->sk_state != DCCP_CLOSED) अणु
		/*
		 * Normal connection termination. May need to रुको अगर there are
		 * still packets in the TX queue that are delayed by the CCID.
		 */
		dccp_flush_ग_लिखो_queue(sk, &समयout);
		dccp_terminate_connection(sk);
	पूर्ण

	/*
	 * Flush ग_लिखो queue. This may be necessary in several हालs:
	 * - we have been बंदd by the peer but still have application data;
	 * - पातive termination (unपढ़ो data or zero linger समय),
	 * - normal termination but queue could not be flushed within समय limit
	 */
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);

	sk_stream_रुको_बंद(sk, समयout);

adjudge_to_death:
	state = sk->sk_state;
	sock_hold(sk);
	sock_orphan(sk);

	/*
	 * It is the last release_sock in its lअगरe. It will हटाओ backlog.
	 */
	release_sock(sk);
	/*
	 * Now socket is owned by kernel and we acquire BH lock
	 * to finish बंद. No need to check क्रम user refs.
	 */
	local_bh_disable();
	bh_lock_sock(sk);
	WARN_ON(sock_owned_by_user(sk));

	percpu_counter_inc(sk->sk_prot->orphan_count);

	/* Have we alपढ़ोy been destroyed by a softirq or backlog? */
	अगर (state != DCCP_CLOSED && sk->sk_state == DCCP_CLOSED)
		जाओ out;

	अगर (sk->sk_state == DCCP_CLOSED)
		inet_csk_destroy_sock(sk);

	/* Otherwise, socket is reprieved until protocol बंद. */

out:
	bh_unlock_sock(sk);
	local_bh_enable();
	sock_put(sk);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_बंद);

व्योम dccp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how)
अणु
	dccp_pr_debug("called shutdown(%x)\n", how);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_shutकरोwn);

अटल अंतरभूत पूर्णांक __init dccp_mib_init(व्योम)
अणु
	dccp_statistics = alloc_percpu(काष्ठा dccp_mib);
	अगर (!dccp_statistics)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dccp_mib_निकास(व्योम)
अणु
	मुक्त_percpu(dccp_statistics);
पूर्ण

अटल पूर्णांक thash_entries;
module_param(thash_entries, पूर्णांक, 0444);
MODULE_PARM_DESC(thash_entries, "Number of ehash buckets");

#अगर_घोषित CONFIG_IP_DCCP_DEBUG
bool dccp_debug;
module_param(dccp_debug, bool, 0644);
MODULE_PARM_DESC(dccp_debug, "Enable debug messages");

EXPORT_SYMBOL_GPL(dccp_debug);
#पूर्ण_अगर

अटल पूर्णांक __init dccp_init(व्योम)
अणु
	अचिन्हित दीर्घ goal;
	अचिन्हित दीर्घ nr_pages = totalram_pages();
	पूर्णांक ehash_order, bhash_order, i;
	पूर्णांक rc;

	BUILD_BUG_ON(माप(काष्ठा dccp_skb_cb) >
		     माप_field(काष्ठा sk_buff, cb));
	rc = percpu_counter_init(&dccp_orphan_count, 0, GFP_KERNEL);
	अगर (rc)
		जाओ out_fail;
	inet_hashinfo_init(&dccp_hashinfo);
	rc = inet_hashinfo2_init_mod(&dccp_hashinfo);
	अगर (rc)
		जाओ out_मुक्त_percpu;
	rc = -ENOBUFS;
	dccp_hashinfo.bind_bucket_cachep =
		kmem_cache_create("dccp_bind_bucket",
				  माप(काष्ठा inet_bind_bucket), 0,
				  SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!dccp_hashinfo.bind_bucket_cachep)
		जाओ out_मुक्त_hashinfo2;

	/*
	 * Size and allocate the मुख्य established and bind bucket
	 * hash tables.
	 *
	 * The methoकरोlogy is similar to that of the buffer cache.
	 */
	अगर (nr_pages >= (128 * 1024))
		goal = nr_pages >> (21 - PAGE_SHIFT);
	अन्यथा
		goal = nr_pages >> (23 - PAGE_SHIFT);

	अगर (thash_entries)
		goal = (thash_entries *
			माप(काष्ठा inet_ehash_bucket)) >> PAGE_SHIFT;
	क्रम (ehash_order = 0; (1UL << ehash_order) < goal; ehash_order++)
		;
	करो अणु
		अचिन्हित दीर्घ hash_size = (1UL << ehash_order) * PAGE_SIZE /
					माप(काष्ठा inet_ehash_bucket);

		जबतक (hash_size & (hash_size - 1))
			hash_size--;
		dccp_hashinfo.ehash_mask = hash_size - 1;
		dccp_hashinfo.ehash = (काष्ठा inet_ehash_bucket *)
			__get_मुक्त_pages(GFP_ATOMIC|__GFP_NOWARN, ehash_order);
	पूर्ण जबतक (!dccp_hashinfo.ehash && --ehash_order > 0);

	अगर (!dccp_hashinfo.ehash) अणु
		DCCP_CRIT("Failed to allocate DCCP established hash table");
		जाओ out_मुक्त_bind_bucket_cachep;
	पूर्ण

	क्रम (i = 0; i <= dccp_hashinfo.ehash_mask; i++)
		INIT_HLIST_शून्यS_HEAD(&dccp_hashinfo.ehash[i].chain, i);

	अगर (inet_ehash_locks_alloc(&dccp_hashinfo))
			जाओ out_मुक्त_dccp_ehash;

	bhash_order = ehash_order;

	करो अणु
		dccp_hashinfo.bhash_size = (1UL << bhash_order) * PAGE_SIZE /
					माप(काष्ठा inet_bind_hashbucket);
		अगर ((dccp_hashinfo.bhash_size > (64 * 1024)) &&
		    bhash_order > 0)
			जारी;
		dccp_hashinfo.bhash = (काष्ठा inet_bind_hashbucket *)
			__get_मुक्त_pages(GFP_ATOMIC|__GFP_NOWARN, bhash_order);
	पूर्ण जबतक (!dccp_hashinfo.bhash && --bhash_order >= 0);

	अगर (!dccp_hashinfo.bhash) अणु
		DCCP_CRIT("Failed to allocate DCCP bind hash table");
		जाओ out_मुक्त_dccp_locks;
	पूर्ण

	क्रम (i = 0; i < dccp_hashinfo.bhash_size; i++) अणु
		spin_lock_init(&dccp_hashinfo.bhash[i].lock);
		INIT_HLIST_HEAD(&dccp_hashinfo.bhash[i].chain);
	पूर्ण

	rc = dccp_mib_init();
	अगर (rc)
		जाओ out_मुक्त_dccp_bhash;

	rc = dccp_ackvec_init();
	अगर (rc)
		जाओ out_मुक्त_dccp_mib;

	rc = dccp_sysctl_init();
	अगर (rc)
		जाओ out_ackvec_निकास;

	rc = ccid_initialize_builtins();
	अगर (rc)
		जाओ out_sysctl_निकास;

	dccp_बारtamping_init();

	वापस 0;

out_sysctl_निकास:
	dccp_sysctl_निकास();
out_ackvec_निकास:
	dccp_ackvec_निकास();
out_मुक्त_dccp_mib:
	dccp_mib_निकास();
out_मुक्त_dccp_bhash:
	मुक्त_pages((अचिन्हित दीर्घ)dccp_hashinfo.bhash, bhash_order);
out_मुक्त_dccp_locks:
	inet_ehash_locks_मुक्त(&dccp_hashinfo);
out_मुक्त_dccp_ehash:
	मुक्त_pages((अचिन्हित दीर्घ)dccp_hashinfo.ehash, ehash_order);
out_मुक्त_bind_bucket_cachep:
	kmem_cache_destroy(dccp_hashinfo.bind_bucket_cachep);
out_मुक्त_hashinfo2:
	inet_hashinfo2_मुक्त_mod(&dccp_hashinfo);
out_मुक्त_percpu:
	percpu_counter_destroy(&dccp_orphan_count);
out_fail:
	dccp_hashinfo.bhash = शून्य;
	dccp_hashinfo.ehash = शून्य;
	dccp_hashinfo.bind_bucket_cachep = शून्य;
	वापस rc;
पूर्ण

अटल व्योम __निकास dccp_fini(व्योम)
अणु
	ccid_cleanup_builtins();
	dccp_mib_निकास();
	मुक्त_pages((अचिन्हित दीर्घ)dccp_hashinfo.bhash,
		   get_order(dccp_hashinfo.bhash_size *
			     माप(काष्ठा inet_bind_hashbucket)));
	मुक्त_pages((अचिन्हित दीर्घ)dccp_hashinfo.ehash,
		   get_order((dccp_hashinfo.ehash_mask + 1) *
			     माप(काष्ठा inet_ehash_bucket)));
	inet_ehash_locks_मुक्त(&dccp_hashinfo);
	kmem_cache_destroy(dccp_hashinfo.bind_bucket_cachep);
	dccp_ackvec_निकास();
	dccp_sysctl_निकास();
	inet_hashinfo2_मुक्त_mod(&dccp_hashinfo);
	percpu_counter_destroy(&dccp_orphan_count);
पूर्ण

module_init(dccp_init);
module_निकास(dccp_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnaldo Carvalho de Melo <acme@conectiva.com.br>");
MODULE_DESCRIPTION("DCCP - Datagram Congestion Controlled Protocol");
