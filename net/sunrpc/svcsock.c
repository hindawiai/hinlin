<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/svcsock.c
 *
 * These are the RPC server socket पूर्णांकernals.
 *
 * The server scheduling algorithm करोes not always distribute the load
 * evenly when servicing a single client. May need to modअगरy the
 * svc_xprt_enqueue procedure...
 *
 * TCP support is largely untested and may be a little slow. The problem
 * is that we currently करो two separate recvfrom's, one क्रम the 4-byte
 * record length, and the second क्रम the actual record. This could possibly
 * be improved by always पढ़ोing a minimum size of around 100 bytes and
 * tucking any superfluous bytes away in a temporary store. Still, that
 * leaves ग_लिखो requests out in the rain. An alternative may be to peek at
 * the first skb in the queue, and अगर it matches the next TCP sequence
 * number, to extract the record marker. Yuck.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/file.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <net/sock.h>
#समावेश <net/checksum.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/ioctls.h>

#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/xprt.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "socklib.h"
#समावेश "sunrpc.h"

#घोषणा RPCDBG_FACILITY	RPCDBG_SVCXPRT


अटल काष्ठा svc_sock *svc_setup_socket(काष्ठा svc_serv *, काष्ठा socket *,
					 पूर्णांक flags);
अटल पूर्णांक		svc_udp_recvfrom(काष्ठा svc_rqst *);
अटल पूर्णांक		svc_udp_sendto(काष्ठा svc_rqst *);
अटल व्योम		svc_sock_detach(काष्ठा svc_xprt *);
अटल व्योम		svc_tcp_sock_detach(काष्ठा svc_xprt *);
अटल व्योम		svc_sock_मुक्त(काष्ठा svc_xprt *);

अटल काष्ठा svc_xprt *svc_create_socket(काष्ठा svc_serv *, पूर्णांक,
					  काष्ठा net *, काष्ठा sockaddr *,
					  पूर्णांक, पूर्णांक);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key svc_key[2];
अटल काष्ठा lock_class_key svc_slock_key[2];

अटल व्योम svc_reclassअगरy_socket(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (WARN_ON_ONCE(!sock_allow_reclassअगरication(sk)))
		वापस;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		sock_lock_init_class_and_name(sk, "slock-AF_INET-NFSD",
					      &svc_slock_key[0],
					      "sk_xprt.xpt_lock-AF_INET-NFSD",
					      &svc_key[0]);
		अवरोध;

	हाल AF_INET6:
		sock_lock_init_class_and_name(sk, "slock-AF_INET6-NFSD",
					      &svc_slock_key[1],
					      "sk_xprt.xpt_lock-AF_INET6-NFSD",
					      &svc_key[1]);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम svc_reclassअगरy_socket(काष्ठा socket *sock)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * svc_tcp_release_rqst - Release transport-related resources
 * @rqstp: request काष्ठाure with resources to be released
 *
 */
अटल व्योम svc_tcp_release_rqst(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा sk_buff *skb = rqstp->rq_xprt_ctxt;

	अगर (skb) अणु
		काष्ठा svc_sock *svsk =
			container_of(rqstp->rq_xprt, काष्ठा svc_sock, sk_xprt);

		rqstp->rq_xprt_ctxt = शून्य;
		skb_मुक्त_datagram_locked(svsk->sk_sk, skb);
	पूर्ण
पूर्ण

/**
 * svc_udp_release_rqst - Release transport-related resources
 * @rqstp: request काष्ठाure with resources to be released
 *
 */
अटल व्योम svc_udp_release_rqst(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा sk_buff *skb = rqstp->rq_xprt_ctxt;

	अगर (skb) अणु
		rqstp->rq_xprt_ctxt = शून्य;
		consume_skb(skb);
	पूर्ण
पूर्ण

जोड़ svc_pktinfo_u अणु
	काष्ठा in_pktinfo pkti;
	काष्ठा in6_pktinfo pkti6;
पूर्ण;
#घोषणा SVC_PKTINFO_SPACE \
	CMSG_SPACE(माप(जोड़ svc_pktinfo_u))

अटल व्योम svc_set_cmsg_data(काष्ठा svc_rqst *rqstp, काष्ठा cmsghdr *cmh)
अणु
	काष्ठा svc_sock *svsk =
		container_of(rqstp->rq_xprt, काष्ठा svc_sock, sk_xprt);
	चयन (svsk->sk_sk->sk_family) अणु
	हाल AF_INET: अणु
			काष्ठा in_pktinfo *pki = CMSG_DATA(cmh);

			cmh->cmsg_level = SOL_IP;
			cmh->cmsg_type = IP_PKTINFO;
			pki->ipi_अगरindex = 0;
			pki->ipi_spec_dst.s_addr =
				 svc_daddr_in(rqstp)->sin_addr.s_addr;
			cmh->cmsg_len = CMSG_LEN(माप(*pki));
		पूर्ण
		अवरोध;

	हाल AF_INET6: अणु
			काष्ठा in6_pktinfo *pki = CMSG_DATA(cmh);
			काष्ठा sockaddr_in6 *daddr = svc_daddr_in6(rqstp);

			cmh->cmsg_level = SOL_IPV6;
			cmh->cmsg_type = IPV6_PKTINFO;
			pki->ipi6_अगरindex = daddr->sin6_scope_id;
			pki->ipi6_addr = daddr->sin6_addr;
			cmh->cmsg_len = CMSG_LEN(माप(*pki));
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक svc_sock_result_payload(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक length)
अणु
	वापस 0;
पूर्ण

/*
 * Report socket names क्रम nfsdfs
 */
अटल पूर्णांक svc_one_sock_name(काष्ठा svc_sock *svsk, अक्षर *buf, पूर्णांक reमुख्यing)
अणु
	स्थिर काष्ठा sock *sk = svsk->sk_sk;
	स्थिर अक्षर *proto_name = sk->sk_protocol == IPPROTO_UDP ?
							"udp" : "tcp";
	पूर्णांक len;

	चयन (sk->sk_family) अणु
	हाल PF_INET:
		len = snम_लिखो(buf, reमुख्यing, "ipv4 %s %pI4 %d\n",
				proto_name,
				&inet_sk(sk)->inet_rcv_saddr,
				inet_sk(sk)->inet_num);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		len = snम_लिखो(buf, reमुख्यing, "ipv6 %s %pI6 %d\n",
				proto_name,
				&sk->sk_v6_rcv_saddr,
				inet_sk(sk)->inet_num);
		अवरोध;
#पूर्ण_अगर
	शेष:
		len = snम_लिखो(buf, reमुख्यing, "*unknown-%d*\n",
				sk->sk_family);
	पूर्ण

	अगर (len >= reमुख्यing) अणु
		*buf = '\0';
		वापस -ENAMETOOLONG;
	पूर्ण
	वापस len;
पूर्ण

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
अटल व्योम svc_flush_bvec(स्थिर काष्ठा bio_vec *bvec, माप_प्रकार size, माप_प्रकार seek)
अणु
	काष्ठा bvec_iter bi = अणु
		.bi_size	= size + seek,
	पूर्ण;
	काष्ठा bio_vec bv;

	bvec_iter_advance(bvec, &bi, seek & PAGE_MASK);
	क्रम_each_bvec(bv, bvec, bi, bi)
		flush_dcache_page(bv.bv_page);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम svc_flush_bvec(स्थिर काष्ठा bio_vec *bvec, माप_प्रकार size,
				  माप_प्रकार seek)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Read from @rqstp's transport socket. The incoming message fills whole
 * pages in @rqstp's rq_pages array until the last page of the message
 * has been received पूर्णांकo a partial page.
 */
अटल sमाप_प्रकार svc_tcp_पढ़ो_msg(काष्ठा svc_rqst *rqstp, माप_प्रकार buflen,
				माप_प्रकार seek)
अणु
	काष्ठा svc_sock *svsk =
		container_of(rqstp->rq_xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा bio_vec *bvec = rqstp->rq_bvec;
	काष्ठा msghdr msg = अणु शून्य पूर्ण;
	अचिन्हित पूर्णांक i;
	sमाप_प्रकार len;
	माप_प्रकार t;

	rqstp->rq_xprt_hlen = 0;

	clear_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);

	क्रम (i = 0, t = 0; t < buflen; i++, t += PAGE_SIZE) अणु
		bvec[i].bv_page = rqstp->rq_pages[i];
		bvec[i].bv_len = PAGE_SIZE;
		bvec[i].bv_offset = 0;
	पूर्ण
	rqstp->rq_respages = &rqstp->rq_pages[i];
	rqstp->rq_next_page = rqstp->rq_respages + 1;

	iov_iter_bvec(&msg.msg_iter, READ, bvec, i, buflen);
	अगर (seek) अणु
		iov_iter_advance(&msg.msg_iter, seek);
		buflen -= seek;
	पूर्ण
	len = sock_recvmsg(svsk->sk_sock, &msg, MSG_DONTWAIT);
	अगर (len > 0)
		svc_flush_bvec(bvec, len, seek);

	/* If we पढ़ो a full record, then assume there may be more
	 * data to पढ़ो (stream based sockets only!)
	 */
	अगर (len == buflen)
		set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);

	वापस len;
पूर्ण

/*
 * Set socket snd and rcv buffer lengths
 */
अटल व्योम svc_sock_रखो_बफsize(काष्ठा svc_sock *svsk, अचिन्हित पूर्णांक nreqs)
अणु
	अचिन्हित पूर्णांक max_mesg = svsk->sk_xprt.xpt_server->sv_max_mesg;
	काष्ठा socket *sock = svsk->sk_sock;

	nreqs = min(nreqs, पूर्णांक_उच्च / 2 / max_mesg);

	lock_sock(sock->sk);
	sock->sk->sk_sndbuf = nreqs * max_mesg * 2;
	sock->sk->sk_rcvbuf = nreqs * max_mesg * 2;
	sock->sk->sk_ग_लिखो_space(sock->sk);
	release_sock(sock->sk);
पूर्ण

अटल व्योम svc_sock_secure_port(काष्ठा svc_rqst *rqstp)
अणु
	अगर (svc_port_is_privileged(svc_addr(rqstp)))
		set_bit(RQ_SECURE, &rqstp->rq_flags);
	अन्यथा
		clear_bit(RQ_SECURE, &rqstp->rq_flags);
पूर्ण

/*
 * INET callback when data has been received on the socket.
 */
अटल व्योम svc_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा svc_sock	*svsk = (काष्ठा svc_sock *)sk->sk_user_data;

	अगर (svsk) अणु
		/* Refer to svc_setup_socket() क्रम details. */
		rmb();
		svsk->sk_odata(sk);
		trace_svcsock_data_पढ़ोy(&svsk->sk_xprt, 0);
		अगर (!test_and_set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags))
			svc_xprt_enqueue(&svsk->sk_xprt);
	पूर्ण
पूर्ण

/*
 * INET callback when space is newly available on the socket.
 */
अटल व्योम svc_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा svc_sock	*svsk = (काष्ठा svc_sock *)(sk->sk_user_data);

	अगर (svsk) अणु
		/* Refer to svc_setup_socket() क्रम details. */
		rmb();
		trace_svcsock_ग_लिखो_space(&svsk->sk_xprt, 0);
		svsk->sk_owspace(sk);
		svc_xprt_enqueue(&svsk->sk_xprt);
	पूर्ण
पूर्ण

अटल पूर्णांक svc_tcp_has_wspace(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);

	अगर (test_bit(XPT_LISTENER, &xprt->xpt_flags))
		वापस 1;
	वापस !test_bit(SOCK_NOSPACE, &svsk->sk_sock->flags);
पूर्ण

अटल व्योम svc_tcp_समाप्त_temp_xprt(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);

	sock_no_linger(svsk->sk_sock->sk);
पूर्ण

/*
 * See net/ipv6/ip_sockglue.c : ip_cmsg_recv_pktinfo
 */
अटल पूर्णांक svc_udp_get_dest_address4(काष्ठा svc_rqst *rqstp,
				     काष्ठा cmsghdr *cmh)
अणु
	काष्ठा in_pktinfo *pki = CMSG_DATA(cmh);
	काष्ठा sockaddr_in *daddr = svc_daddr_in(rqstp);

	अगर (cmh->cmsg_type != IP_PKTINFO)
		वापस 0;

	daddr->sin_family = AF_INET;
	daddr->sin_addr.s_addr = pki->ipi_spec_dst.s_addr;
	वापस 1;
पूर्ण

/*
 * See net/ipv6/datagram.c : ip6_datagram_recv_ctl
 */
अटल पूर्णांक svc_udp_get_dest_address6(काष्ठा svc_rqst *rqstp,
				     काष्ठा cmsghdr *cmh)
अणु
	काष्ठा in6_pktinfo *pki = CMSG_DATA(cmh);
	काष्ठा sockaddr_in6 *daddr = svc_daddr_in6(rqstp);

	अगर (cmh->cmsg_type != IPV6_PKTINFO)
		वापस 0;

	daddr->sin6_family = AF_INET6;
	daddr->sin6_addr = pki->ipi6_addr;
	daddr->sin6_scope_id = pki->ipi6_अगरindex;
	वापस 1;
पूर्ण

/*
 * Copy the UDP datagram's destination address to the rqstp काष्ठाure.
 * The 'destination' address in this हाल is the address to which the
 * peer sent the datagram, i.e. our local address. For multihomed
 * hosts, this can change from msg to msg. Note that only the IP
 * address changes, the port number should reमुख्य the same.
 */
अटल पूर्णांक svc_udp_get_dest_address(काष्ठा svc_rqst *rqstp,
				    काष्ठा cmsghdr *cmh)
अणु
	चयन (cmh->cmsg_level) अणु
	हाल SOL_IP:
		वापस svc_udp_get_dest_address4(rqstp, cmh);
	हाल SOL_IPV6:
		वापस svc_udp_get_dest_address6(rqstp, cmh);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * svc_udp_recvfrom - Receive a datagram from a UDP socket.
 * @rqstp: request काष्ठाure पूर्णांकo which to receive an RPC Call
 *
 * Called in a loop when XPT_DATA has been set.
 *
 * Returns:
 *   On success, the number of bytes in a received RPC Call, or
 *   %0 अगर a complete RPC Call message was not पढ़ोy to वापस
 */
अटल पूर्णांक svc_udp_recvfrom(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_sock	*svsk =
		container_of(rqstp->rq_xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा svc_serv	*serv = svsk->sk_xprt.xpt_server;
	काष्ठा sk_buff	*skb;
	जोड़ अणु
		काष्ठा cmsghdr	hdr;
		दीर्घ		all[SVC_PKTINFO_SPACE / माप(दीर्घ)];
	पूर्ण buffer;
	काष्ठा cmsghdr *cmh = &buffer.hdr;
	काष्ठा msghdr msg = अणु
		.msg_name = svc_addr(rqstp),
		.msg_control = cmh,
		.msg_controllen = माप(buffer),
		.msg_flags = MSG_DONTWAIT,
	पूर्ण;
	माप_प्रकार len;
	पूर्णांक err;

	अगर (test_and_clear_bit(XPT_CHNGBUF, &svsk->sk_xprt.xpt_flags))
	    /* udp sockets need large rcvbuf as all pending
	     * requests are still in that buffer.  sndbuf must
	     * also be large enough that there is enough space
	     * क्रम one reply per thपढ़ो.  We count all thपढ़ोs
	     * rather than thपढ़ोs in a particular pool, which
	     * provides an upper bound on the number of thपढ़ोs
	     * which will access the socket.
	     */
	    svc_sock_रखो_बफsize(svsk, serv->sv_nrthपढ़ोs + 3);

	clear_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
	err = kernel_recvmsg(svsk->sk_sock, &msg, शून्य,
			     0, 0, MSG_PEEK | MSG_DONTWAIT);
	अगर (err < 0)
		जाओ out_recv_err;
	skb = skb_recv_udp(svsk->sk_sk, 0, 1, &err);
	अगर (!skb)
		जाओ out_recv_err;

	len = svc_addr_len(svc_addr(rqstp));
	rqstp->rq_addrlen = len;
	अगर (skb->tstamp == 0) अणु
		skb->tstamp = kसमय_get_real();
		/* Don't enable netstamp, sunrpc doesn't
		   need that much accuracy */
	पूर्ण
	sock_ग_लिखो_बारtamp(svsk->sk_sk, skb->tstamp);
	set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags); /* there may be more data... */

	len = skb->len;
	rqstp->rq_arg.len = len;
	trace_svcsock_udp_recv(&svsk->sk_xprt, len);

	rqstp->rq_prot = IPPROTO_UDP;

	अगर (!svc_udp_get_dest_address(rqstp, cmh))
		जाओ out_cmsg_err;
	rqstp->rq_daddrlen = svc_addr_len(svc_daddr(rqstp));

	अगर (skb_is_nonlinear(skb)) अणु
		/* we have to copy */
		local_bh_disable();
		अगर (csum_partial_copy_to_xdr(&rqstp->rq_arg, skb))
			जाओ out_bh_enable;
		local_bh_enable();
		consume_skb(skb);
	पूर्ण अन्यथा अणु
		/* we can use it in-place */
		rqstp->rq_arg.head[0].iov_base = skb->data;
		rqstp->rq_arg.head[0].iov_len = len;
		अगर (skb_checksum_complete(skb))
			जाओ out_मुक्त;
		rqstp->rq_xprt_ctxt = skb;
	पूर्ण

	rqstp->rq_arg.page_base = 0;
	अगर (len <= rqstp->rq_arg.head[0].iov_len) अणु
		rqstp->rq_arg.head[0].iov_len = len;
		rqstp->rq_arg.page_len = 0;
		rqstp->rq_respages = rqstp->rq_pages+1;
	पूर्ण अन्यथा अणु
		rqstp->rq_arg.page_len = len - rqstp->rq_arg.head[0].iov_len;
		rqstp->rq_respages = rqstp->rq_pages + 1 +
			DIV_ROUND_UP(rqstp->rq_arg.page_len, PAGE_SIZE);
	पूर्ण
	rqstp->rq_next_page = rqstp->rq_respages+1;

	अगर (serv->sv_stats)
		serv->sv_stats->netudpcnt++;

	svc_xprt_received(rqstp->rq_xprt);
	वापस len;

out_recv_err:
	अगर (err != -EAGAIN) अणु
		/* possibly an icmp error */
		set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
	पूर्ण
	trace_svcsock_udp_recv_err(&svsk->sk_xprt, err);
	जाओ out_clear_busy;
out_cmsg_err:
	net_warn_ratelimited("svc: received unknown control message %d/%d; dropping RPC reply datagram\n",
			     cmh->cmsg_level, cmh->cmsg_type);
	जाओ out_मुक्त;
out_bh_enable:
	local_bh_enable();
out_मुक्त:
	kमुक्त_skb(skb);
out_clear_busy:
	svc_xprt_received(rqstp->rq_xprt);
	वापस 0;
पूर्ण

/**
 * svc_udp_sendto - Send out a reply on a UDP socket
 * @rqstp: completed svc_rqst
 *
 * xpt_mutex ensures @rqstp's whole message is written to the socket
 * without पूर्णांकerruption.
 *
 * Returns the number of bytes sent, or a negative त्रुटि_सं.
 */
अटल पूर्णांक svc_udp_sendto(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा svc_sock	*svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा xdr_buf *xdr = &rqstp->rq_res;
	जोड़ अणु
		काष्ठा cmsghdr	hdr;
		दीर्घ		all[SVC_PKTINFO_SPACE / माप(दीर्घ)];
	पूर्ण buffer;
	काष्ठा cmsghdr *cmh = &buffer.hdr;
	काष्ठा msghdr msg = अणु
		.msg_name	= &rqstp->rq_addr,
		.msg_namelen	= rqstp->rq_addrlen,
		.msg_control	= cmh,
		.msg_controllen	= माप(buffer),
	पूर्ण;
	अचिन्हित पूर्णांक sent;
	पूर्णांक err;

	svc_udp_release_rqst(rqstp);

	svc_set_cmsg_data(rqstp, cmh);

	mutex_lock(&xprt->xpt_mutex);

	अगर (svc_xprt_is_dead(xprt))
		जाओ out_notconn;

	err = xprt_sock_sendmsg(svsk->sk_sock, &msg, xdr, 0, 0, &sent);
	xdr_मुक्त_bvec(xdr);
	अगर (err == -ECONNREFUSED) अणु
		/* ICMP error on earlier request. */
		err = xprt_sock_sendmsg(svsk->sk_sock, &msg, xdr, 0, 0, &sent);
		xdr_मुक्त_bvec(xdr);
	पूर्ण
	trace_svcsock_udp_send(xprt, err);

	mutex_unlock(&xprt->xpt_mutex);
	अगर (err < 0)
		वापस err;
	वापस sent;

out_notconn:
	mutex_unlock(&xprt->xpt_mutex);
	वापस -ENOTCONN;
पूर्ण

अटल पूर्णांक svc_udp_has_wspace(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा svc_serv	*serv = xprt->xpt_server;
	अचिन्हित दीर्घ required;

	/*
	 * Set the SOCK_NOSPACE flag beक्रमe checking the available
	 * sock space.
	 */
	set_bit(SOCK_NOSPACE, &svsk->sk_sock->flags);
	required = atomic_पढ़ो(&svsk->sk_xprt.xpt_reserved) + serv->sv_max_mesg;
	अगर (required*2 > sock_wspace(svsk->sk_sk))
		वापस 0;
	clear_bit(SOCK_NOSPACE, &svsk->sk_sock->flags);
	वापस 1;
पूर्ण

अटल काष्ठा svc_xprt *svc_udp_accept(काष्ठा svc_xprt *xprt)
अणु
	BUG();
	वापस शून्य;
पूर्ण

अटल व्योम svc_udp_समाप्त_temp_xprt(काष्ठा svc_xprt *xprt)
अणु
पूर्ण

अटल काष्ठा svc_xprt *svc_udp_create(काष्ठा svc_serv *serv,
				       काष्ठा net *net,
				       काष्ठा sockaddr *sa, पूर्णांक salen,
				       पूर्णांक flags)
अणु
	वापस svc_create_socket(serv, IPPROTO_UDP, net, sa, salen, flags);
पूर्ण

अटल स्थिर काष्ठा svc_xprt_ops svc_udp_ops = अणु
	.xpo_create = svc_udp_create,
	.xpo_recvfrom = svc_udp_recvfrom,
	.xpo_sendto = svc_udp_sendto,
	.xpo_result_payload = svc_sock_result_payload,
	.xpo_release_rqst = svc_udp_release_rqst,
	.xpo_detach = svc_sock_detach,
	.xpo_मुक्त = svc_sock_मुक्त,
	.xpo_has_wspace = svc_udp_has_wspace,
	.xpo_accept = svc_udp_accept,
	.xpo_secure_port = svc_sock_secure_port,
	.xpo_समाप्त_temp_xprt = svc_udp_समाप्त_temp_xprt,
पूर्ण;

अटल काष्ठा svc_xprt_class svc_udp_class = अणु
	.xcl_name = "udp",
	.xcl_owner = THIS_MODULE,
	.xcl_ops = &svc_udp_ops,
	.xcl_max_payload = RPCSVC_MAXPAYLOAD_UDP,
	.xcl_ident = XPRT_TRANSPORT_UDP,
पूर्ण;

अटल व्योम svc_udp_init(काष्ठा svc_sock *svsk, काष्ठा svc_serv *serv)
अणु
	svc_xprt_init(sock_net(svsk->sk_sock->sk), &svc_udp_class,
		      &svsk->sk_xprt, serv);
	clear_bit(XPT_CACHE_AUTH, &svsk->sk_xprt.xpt_flags);
	svsk->sk_sk->sk_data_पढ़ोy = svc_data_पढ़ोy;
	svsk->sk_sk->sk_ग_लिखो_space = svc_ग_लिखो_space;

	/* initialise setting must have enough space to
	 * receive and respond to one request.
	 * svc_udp_recvfrom will re-adjust अगर necessary
	 */
	svc_sock_रखो_बफsize(svsk, 3);

	/* data might have come in beक्रमe data_पढ़ोy set up */
	set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
	set_bit(XPT_CHNGBUF, &svsk->sk_xprt.xpt_flags);

	/* make sure we get destination address info */
	चयन (svsk->sk_sk->sk_family) अणु
	हाल AF_INET:
		ip_sock_set_pktinfo(svsk->sk_sock->sk);
		अवरोध;
	हाल AF_INET6:
		ip6_sock_set_recvpktinfo(svsk->sk_sock->sk);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * A data_पढ़ोy event on a listening socket means there's a connection
 * pending. Do not use state_change as a substitute क्रम it.
 */
अटल व्योम svc_tcp_listen_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा svc_sock	*svsk = (काष्ठा svc_sock *)sk->sk_user_data;

	अगर (svsk) अणु
		/* Refer to svc_setup_socket() क्रम details. */
		rmb();
		svsk->sk_odata(sk);
	पूर्ण

	/*
	 * This callback may called twice when a new connection
	 * is established as a child socket inherits everything
	 * from a parent LISTEN socket.
	 * 1) data_पढ़ोy method of the parent socket will be called
	 *    when one of child sockets become ESTABLISHED.
	 * 2) data_पढ़ोy method of the child socket may be called
	 *    when it receives data beक्रमe the socket is accepted.
	 * In हाल of 2, we should ignore it silently.
	 */
	अगर (sk->sk_state == TCP_LISTEN) अणु
		अगर (svsk) अणु
			set_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);
			svc_xprt_enqueue(&svsk->sk_xprt);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * A state change on a connected socket means it's dying or dead.
 */
अटल व्योम svc_tcp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा svc_sock	*svsk = (काष्ठा svc_sock *)sk->sk_user_data;

	अगर (svsk) अणु
		/* Refer to svc_setup_socket() क्रम details. */
		rmb();
		svsk->sk_ostate(sk);
		trace_svcsock_tcp_state(&svsk->sk_xprt, svsk->sk_sock);
		अगर (sk->sk_state != TCP_ESTABLISHED)
			svc_xprt_deferred_बंद(&svsk->sk_xprt);
	पूर्ण
पूर्ण

/*
 * Accept a TCP connection
 */
अटल काष्ठा svc_xprt *svc_tcp_accept(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr	*sin = (काष्ठा sockaddr *) &addr;
	काष्ठा svc_serv	*serv = svsk->sk_xprt.xpt_server;
	काष्ठा socket	*sock = svsk->sk_sock;
	काष्ठा socket	*newsock;
	काष्ठा svc_sock	*newsvsk;
	पूर्णांक		err, slen;

	अगर (!sock)
		वापस शून्य;

	clear_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);
	err = kernel_accept(sock, &newsock, O_NONBLOCK);
	अगर (err < 0) अणु
		अगर (err == -ENOMEM)
			prपूर्णांकk(KERN_WARNING "%s: no more sockets!\n",
			       serv->sv_name);
		अन्यथा अगर (err != -EAGAIN)
			net_warn_ratelimited("%s: accept failed (err %d)!\n",
					     serv->sv_name, -err);
		trace_svcsock_accept_err(xprt, serv->sv_name, err);
		वापस शून्य;
	पूर्ण
	set_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);

	err = kernel_getpeername(newsock, sin);
	अगर (err < 0) अणु
		trace_svcsock_getpeername_err(xprt, serv->sv_name, err);
		जाओ failed;		/* पातed connection or whatever */
	पूर्ण
	slen = err;

	/* Reset the inherited callbacks beक्रमe calling svc_setup_socket */
	newsock->sk->sk_state_change = svsk->sk_ostate;
	newsock->sk->sk_data_पढ़ोy = svsk->sk_odata;
	newsock->sk->sk_ग_लिखो_space = svsk->sk_owspace;

	/* make sure that a ग_लिखो करोesn't block क्रमever when
	 * low on memory
	 */
	newsock->sk->sk_sndसमयo = HZ*30;

	newsvsk = svc_setup_socket(serv, newsock,
				 (SVC_SOCK_ANONYMOUS | SVC_SOCK_TEMPORARY));
	अगर (IS_ERR(newsvsk))
		जाओ failed;
	svc_xprt_set_remote(&newsvsk->sk_xprt, sin, slen);
	err = kernel_माला_लोockname(newsock, sin);
	slen = err;
	अगर (unlikely(err < 0))
		slen = दुरत्व(काष्ठा sockaddr, sa_data);
	svc_xprt_set_local(&newsvsk->sk_xprt, sin, slen);

	अगर (sock_is_loopback(newsock->sk))
		set_bit(XPT_LOCAL, &newsvsk->sk_xprt.xpt_flags);
	अन्यथा
		clear_bit(XPT_LOCAL, &newsvsk->sk_xprt.xpt_flags);
	अगर (serv->sv_stats)
		serv->sv_stats->nettcpconn++;

	वापस &newsvsk->sk_xprt;

failed:
	sock_release(newsock);
	वापस शून्य;
पूर्ण

अटल माप_प्रकार svc_tcp_restore_pages(काष्ठा svc_sock *svsk,
				    काष्ठा svc_rqst *rqstp)
अणु
	माप_प्रकार len = svsk->sk_datalen;
	अचिन्हित पूर्णांक i, npages;

	अगर (!len)
		वापस 0;
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < npages; i++) अणु
		अगर (rqstp->rq_pages[i] != शून्य)
			put_page(rqstp->rq_pages[i]);
		BUG_ON(svsk->sk_pages[i] == शून्य);
		rqstp->rq_pages[i] = svsk->sk_pages[i];
		svsk->sk_pages[i] = शून्य;
	पूर्ण
	rqstp->rq_arg.head[0].iov_base = page_address(rqstp->rq_pages[0]);
	वापस len;
पूर्ण

अटल व्योम svc_tcp_save_pages(काष्ठा svc_sock *svsk, काष्ठा svc_rqst *rqstp)
अणु
	अचिन्हित पूर्णांक i, len, npages;

	अगर (svsk->sk_datalen == 0)
		वापस;
	len = svsk->sk_datalen;
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < npages; i++) अणु
		svsk->sk_pages[i] = rqstp->rq_pages[i];
		rqstp->rq_pages[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम svc_tcp_clear_pages(काष्ठा svc_sock *svsk)
अणु
	अचिन्हित पूर्णांक i, len, npages;

	अगर (svsk->sk_datalen == 0)
		जाओ out;
	len = svsk->sk_datalen;
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < npages; i++) अणु
		अगर (svsk->sk_pages[i] == शून्य) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण
		put_page(svsk->sk_pages[i]);
		svsk->sk_pages[i] = शून्य;
	पूर्ण
out:
	svsk->sk_tcplen = 0;
	svsk->sk_datalen = 0;
पूर्ण

/*
 * Receive fragment record header पूर्णांकo sk_marker.
 */
अटल sमाप_प्रकार svc_tcp_पढ़ो_marker(काष्ठा svc_sock *svsk,
				   काष्ठा svc_rqst *rqstp)
अणु
	sमाप_प्रकार want, len;

	/* If we haven't gotten the record length yet,
	 * get the next four bytes.
	 */
	अगर (svsk->sk_tcplen < माप(rpc_fraghdr)) अणु
		काष्ठा msghdr	msg = अणु शून्य पूर्ण;
		काष्ठा kvec	iov;

		want = माप(rpc_fraghdr) - svsk->sk_tcplen;
		iov.iov_base = ((अक्षर *)&svsk->sk_marker) + svsk->sk_tcplen;
		iov.iov_len  = want;
		iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, want);
		len = sock_recvmsg(svsk->sk_sock, &msg, MSG_DONTWAIT);
		अगर (len < 0)
			वापस len;
		svsk->sk_tcplen += len;
		अगर (len < want) अणु
			/* call again to पढ़ो the reमुख्यing bytes */
			जाओ err_लघु;
		पूर्ण
		trace_svcsock_marker(&svsk->sk_xprt, svsk->sk_marker);
		अगर (svc_sock_reclen(svsk) + svsk->sk_datalen >
		    svsk->sk_xprt.xpt_server->sv_max_mesg)
			जाओ err_too_large;
	पूर्ण
	वापस svc_sock_reclen(svsk);

err_too_large:
	net_notice_ratelimited("svc: %s %s RPC fragment too large: %d\n",
			       __func__, svsk->sk_xprt.xpt_server->sv_name,
			       svc_sock_reclen(svsk));
	svc_xprt_deferred_बंद(&svsk->sk_xprt);
err_लघु:
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक receive_cb_reply(काष्ठा svc_sock *svsk, काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा rpc_xprt *bc_xprt = svsk->sk_xprt.xpt_bc_xprt;
	काष्ठा rpc_rqst *req = शून्य;
	काष्ठा kvec *src, *dst;
	__be32 *p = (__be32 *)rqstp->rq_arg.head[0].iov_base;
	__be32 xid;
	__be32 calldir;

	xid = *p++;
	calldir = *p;

	अगर (!bc_xprt)
		वापस -EAGAIN;
	spin_lock(&bc_xprt->queue_lock);
	req = xprt_lookup_rqst(bc_xprt, xid);
	अगर (!req)
		जाओ unlock_notfound;

	स_नकल(&req->rq_निजी_buf, &req->rq_rcv_buf, माप(काष्ठा xdr_buf));
	/*
	 * XXX!: cheating क्रम now!  Only copying HEAD.
	 * But we know this is good enough क्रम now (in fact, क्रम any
	 * callback reply in the क्रमseeable future).
	 */
	dst = &req->rq_निजी_buf.head[0];
	src = &rqstp->rq_arg.head[0];
	अगर (dst->iov_len < src->iov_len)
		जाओ unlock_eagain; /* whatever; just giving up. */
	स_नकल(dst->iov_base, src->iov_base, src->iov_len);
	xprt_complete_rqst(req->rq_task, rqstp->rq_arg.len);
	rqstp->rq_arg.len = 0;
	spin_unlock(&bc_xprt->queue_lock);
	वापस 0;
unlock_notfound:
	prपूर्णांकk(KERN_NOTICE
		"%s: Got unrecognized reply: "
		"calldir 0x%x xpt_bc_xprt %p xid %08x\n",
		__func__, ntohl(calldir),
		bc_xprt, ntohl(xid));
unlock_eagain:
	spin_unlock(&bc_xprt->queue_lock);
	वापस -EAGAIN;
पूर्ण

अटल व्योम svc_tcp_fragment_received(काष्ठा svc_sock *svsk)
अणु
	/* If we have more data, संकेत svc_xprt_enqueue() to try again */
	svsk->sk_tcplen = 0;
	svsk->sk_marker = xdr_zero;
पूर्ण

/**
 * svc_tcp_recvfrom - Receive data from a TCP socket
 * @rqstp: request काष्ठाure पूर्णांकo which to receive an RPC Call
 *
 * Called in a loop when XPT_DATA has been set.
 *
 * Read the 4-byte stream record marker, then use the record length
 * in that marker to set up exactly the resources needed to receive
 * the next RPC message पूर्णांकo @rqstp.
 *
 * Returns:
 *   On success, the number of bytes in a received RPC Call, or
 *   %0 अगर a complete RPC Call message was not पढ़ोy to वापस
 *
 * The zero वापस हाल handles partial receives and callback Replies.
 * The state of a partial receive is preserved in the svc_sock क्रम
 * the next call to svc_tcp_recvfrom.
 */
अटल पूर्णांक svc_tcp_recvfrom(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_sock	*svsk =
		container_of(rqstp->rq_xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा svc_serv	*serv = svsk->sk_xprt.xpt_server;
	माप_प्रकार want, base;
	sमाप_प्रकार len;
	__be32 *p;
	__be32 calldir;

	clear_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
	len = svc_tcp_पढ़ो_marker(svsk, rqstp);
	अगर (len < 0)
		जाओ error;

	base = svc_tcp_restore_pages(svsk, rqstp);
	want = len - (svsk->sk_tcplen - माप(rpc_fraghdr));
	len = svc_tcp_पढ़ो_msg(rqstp, base + want, base);
	अगर (len >= 0) अणु
		trace_svcsock_tcp_recv(&svsk->sk_xprt, len);
		svsk->sk_tcplen += len;
		svsk->sk_datalen += len;
	पूर्ण
	अगर (len != want || !svc_sock_final_rec(svsk))
		जाओ err_incomplete;
	अगर (svsk->sk_datalen < 8)
		जाओ err_nuts;

	rqstp->rq_arg.len = svsk->sk_datalen;
	rqstp->rq_arg.page_base = 0;
	अगर (rqstp->rq_arg.len <= rqstp->rq_arg.head[0].iov_len) अणु
		rqstp->rq_arg.head[0].iov_len = rqstp->rq_arg.len;
		rqstp->rq_arg.page_len = 0;
	पूर्ण अन्यथा
		rqstp->rq_arg.page_len = rqstp->rq_arg.len - rqstp->rq_arg.head[0].iov_len;

	rqstp->rq_xprt_ctxt   = शून्य;
	rqstp->rq_prot	      = IPPROTO_TCP;
	अगर (test_bit(XPT_LOCAL, &svsk->sk_xprt.xpt_flags))
		set_bit(RQ_LOCAL, &rqstp->rq_flags);
	अन्यथा
		clear_bit(RQ_LOCAL, &rqstp->rq_flags);

	p = (__be32 *)rqstp->rq_arg.head[0].iov_base;
	calldir = p[1];
	अगर (calldir)
		len = receive_cb_reply(svsk, rqstp);

	/* Reset TCP पढ़ो info */
	svsk->sk_datalen = 0;
	svc_tcp_fragment_received(svsk);

	अगर (len < 0)
		जाओ error;

	svc_xprt_copy_addrs(rqstp, &svsk->sk_xprt);
	अगर (serv->sv_stats)
		serv->sv_stats->nettcpcnt++;

	svc_xprt_received(rqstp->rq_xprt);
	वापस rqstp->rq_arg.len;

err_incomplete:
	svc_tcp_save_pages(svsk, rqstp);
	अगर (len < 0 && len != -EAGAIN)
		जाओ err_delete;
	अगर (len == want)
		svc_tcp_fragment_received(svsk);
	अन्यथा
		trace_svcsock_tcp_recv_लघु(&svsk->sk_xprt,
				svc_sock_reclen(svsk),
				svsk->sk_tcplen - माप(rpc_fraghdr));
	जाओ err_noबंद;
error:
	अगर (len != -EAGAIN)
		जाओ err_delete;
	trace_svcsock_tcp_recv_eagain(&svsk->sk_xprt, 0);
	जाओ err_noबंद;
err_nuts:
	svsk->sk_datalen = 0;
err_delete:
	trace_svcsock_tcp_recv_err(&svsk->sk_xprt, len);
	svc_xprt_deferred_बंद(&svsk->sk_xprt);
err_noबंद:
	svc_xprt_received(rqstp->rq_xprt);
	वापस 0;	/* record not complete */
पूर्ण

अटल पूर्णांक svc_tcp_send_kvec(काष्ठा socket *sock, स्थिर काष्ठा kvec *vec,
			      पूर्णांक flags)
अणु
	वापस kernel_sendpage(sock, virt_to_page(vec->iov_base),
			       offset_in_page(vec->iov_base),
			       vec->iov_len, flags);
पूर्ण

/*
 * kernel_sendpage() is used exclusively to reduce the number of
 * copy operations in this path. Thereक्रमe the caller must ensure
 * that the pages backing @xdr are unchanging.
 *
 * In addition, the logic assumes that * .bv_len is never larger
 * than PAGE_SIZE.
 */
अटल पूर्णांक svc_tcp_sendmsg(काष्ठा socket *sock, काष्ठा xdr_buf *xdr,
			   rpc_fraghdr marker, अचिन्हित पूर्णांक *sentp)
अणु
	स्थिर काष्ठा kvec *head = xdr->head;
	स्थिर काष्ठा kvec *tail = xdr->tail;
	काष्ठा kvec rm = अणु
		.iov_base	= &marker,
		.iov_len	= माप(marker),
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_flags	= 0,
	पूर्ण;
	पूर्णांक ret;

	*sentp = 0;
	xdr_alloc_bvec(xdr, GFP_KERNEL);

	ret = kernel_sendmsg(sock, &msg, &rm, 1, rm.iov_len);
	अगर (ret < 0)
		वापस ret;
	*sentp += ret;
	अगर (ret != rm.iov_len)
		वापस -EAGAIN;

	ret = svc_tcp_send_kvec(sock, head, 0);
	अगर (ret < 0)
		वापस ret;
	*sentp += ret;
	अगर (ret != head->iov_len)
		जाओ out;

	अगर (xdr->page_len) अणु
		अचिन्हित पूर्णांक offset, len, reमुख्यing;
		काष्ठा bio_vec *bvec;

		bvec = xdr->bvec + (xdr->page_base >> PAGE_SHIFT);
		offset = offset_in_page(xdr->page_base);
		reमुख्यing = xdr->page_len;
		जबतक (reमुख्यing > 0) अणु
			len = min(reमुख्यing, bvec->bv_len - offset);
			ret = kernel_sendpage(sock, bvec->bv_page,
					      bvec->bv_offset + offset,
					      len, 0);
			अगर (ret < 0)
				वापस ret;
			*sentp += ret;
			अगर (ret != len)
				जाओ out;
			reमुख्यing -= len;
			offset = 0;
			bvec++;
		पूर्ण
	पूर्ण

	अगर (tail->iov_len) अणु
		ret = svc_tcp_send_kvec(sock, tail, 0);
		अगर (ret < 0)
			वापस ret;
		*sentp += ret;
	पूर्ण

out:
	वापस 0;
पूर्ण

/**
 * svc_tcp_sendto - Send out a reply on a TCP socket
 * @rqstp: completed svc_rqst
 *
 * xpt_mutex ensures @rqstp's whole message is written to the socket
 * without पूर्णांकerruption.
 *
 * Returns the number of bytes sent, or a negative त्रुटि_सं.
 */
अटल पूर्णांक svc_tcp_sendto(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा svc_sock	*svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा xdr_buf *xdr = &rqstp->rq_res;
	rpc_fraghdr marker = cpu_to_be32(RPC_LAST_STREAM_FRAGMENT |
					 (u32)xdr->len);
	अचिन्हित पूर्णांक sent;
	पूर्णांक err;

	svc_tcp_release_rqst(rqstp);

	atomic_inc(&svsk->sk_sendqlen);
	mutex_lock(&xprt->xpt_mutex);
	अगर (svc_xprt_is_dead(xprt))
		जाओ out_notconn;
	tcp_sock_set_cork(svsk->sk_sk, true);
	err = svc_tcp_sendmsg(svsk->sk_sock, xdr, marker, &sent);
	xdr_मुक्त_bvec(xdr);
	trace_svcsock_tcp_send(xprt, err < 0 ? (दीर्घ)err : sent);
	अगर (err < 0 || sent != (xdr->len + माप(marker)))
		जाओ out_बंद;
	अगर (atomic_dec_and_test(&svsk->sk_sendqlen))
		tcp_sock_set_cork(svsk->sk_sk, false);
	mutex_unlock(&xprt->xpt_mutex);
	वापस sent;

out_notconn:
	atomic_dec(&svsk->sk_sendqlen);
	mutex_unlock(&xprt->xpt_mutex);
	वापस -ENOTCONN;
out_बंद:
	pr_notice("rpc-srv/tcp: %s: %s %d when sending %d bytes - shutting down socket\n",
		  xprt->xpt_server->sv_name,
		  (err < 0) ? "got error" : "sent",
		  (err < 0) ? err : sent, xdr->len);
	svc_xprt_deferred_बंद(xprt);
	atomic_dec(&svsk->sk_sendqlen);
	mutex_unlock(&xprt->xpt_mutex);
	वापस -EAGAIN;
पूर्ण

अटल काष्ठा svc_xprt *svc_tcp_create(काष्ठा svc_serv *serv,
				       काष्ठा net *net,
				       काष्ठा sockaddr *sa, पूर्णांक salen,
				       पूर्णांक flags)
अणु
	वापस svc_create_socket(serv, IPPROTO_TCP, net, sa, salen, flags);
पूर्ण

अटल स्थिर काष्ठा svc_xprt_ops svc_tcp_ops = अणु
	.xpo_create = svc_tcp_create,
	.xpo_recvfrom = svc_tcp_recvfrom,
	.xpo_sendto = svc_tcp_sendto,
	.xpo_result_payload = svc_sock_result_payload,
	.xpo_release_rqst = svc_tcp_release_rqst,
	.xpo_detach = svc_tcp_sock_detach,
	.xpo_मुक्त = svc_sock_मुक्त,
	.xpo_has_wspace = svc_tcp_has_wspace,
	.xpo_accept = svc_tcp_accept,
	.xpo_secure_port = svc_sock_secure_port,
	.xpo_समाप्त_temp_xprt = svc_tcp_समाप्त_temp_xprt,
पूर्ण;

अटल काष्ठा svc_xprt_class svc_tcp_class = अणु
	.xcl_name = "tcp",
	.xcl_owner = THIS_MODULE,
	.xcl_ops = &svc_tcp_ops,
	.xcl_max_payload = RPCSVC_MAXPAYLOAD_TCP,
	.xcl_ident = XPRT_TRANSPORT_TCP,
पूर्ण;

व्योम svc_init_xprt_sock(व्योम)
अणु
	svc_reg_xprt_class(&svc_tcp_class);
	svc_reg_xprt_class(&svc_udp_class);
पूर्ण

व्योम svc_cleanup_xprt_sock(व्योम)
अणु
	svc_unreg_xprt_class(&svc_tcp_class);
	svc_unreg_xprt_class(&svc_udp_class);
पूर्ण

अटल व्योम svc_tcp_init(काष्ठा svc_sock *svsk, काष्ठा svc_serv *serv)
अणु
	काष्ठा sock	*sk = svsk->sk_sk;

	svc_xprt_init(sock_net(svsk->sk_sock->sk), &svc_tcp_class,
		      &svsk->sk_xprt, serv);
	set_bit(XPT_CACHE_AUTH, &svsk->sk_xprt.xpt_flags);
	set_bit(XPT_CONG_CTRL, &svsk->sk_xprt.xpt_flags);
	अगर (sk->sk_state == TCP_LISTEN) अणु
		म_नकल(svsk->sk_xprt.xpt_remotebuf, "listener");
		set_bit(XPT_LISTENER, &svsk->sk_xprt.xpt_flags);
		sk->sk_data_पढ़ोy = svc_tcp_listen_data_पढ़ोy;
		set_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);
	पूर्ण अन्यथा अणु
		sk->sk_state_change = svc_tcp_state_change;
		sk->sk_data_पढ़ोy = svc_data_पढ़ोy;
		sk->sk_ग_लिखो_space = svc_ग_लिखो_space;

		svsk->sk_marker = xdr_zero;
		svsk->sk_tcplen = 0;
		svsk->sk_datalen = 0;
		स_रखो(&svsk->sk_pages[0], 0, माप(svsk->sk_pages));

		tcp_sock_set_nodelay(sk);

		set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
		चयन (sk->sk_state) अणु
		हाल TCP_SYN_RECV:
		हाल TCP_ESTABLISHED:
			अवरोध;
		शेष:
			svc_xprt_deferred_बंद(&svsk->sk_xprt);
		पूर्ण
	पूर्ण
पूर्ण

व्योम svc_sock_update_bufs(काष्ठा svc_serv *serv)
अणु
	/*
	 * The number of server thपढ़ोs has changed. Update
	 * rcvbuf and sndbuf accordingly on all sockets
	 */
	काष्ठा svc_sock *svsk;

	spin_lock_bh(&serv->sv_lock);
	list_क्रम_each_entry(svsk, &serv->sv_permsocks, sk_xprt.xpt_list)
		set_bit(XPT_CHNGBUF, &svsk->sk_xprt.xpt_flags);
	spin_unlock_bh(&serv->sv_lock);
पूर्ण
EXPORT_SYMBOL_GPL(svc_sock_update_bufs);

/*
 * Initialize socket क्रम RPC use and create svc_sock काष्ठा
 */
अटल काष्ठा svc_sock *svc_setup_socket(काष्ठा svc_serv *serv,
						काष्ठा socket *sock,
						पूर्णांक flags)
अणु
	काष्ठा svc_sock	*svsk;
	काष्ठा sock	*inet;
	पूर्णांक		pmap_रेजिस्टर = !(flags & SVC_SOCK_ANONYMOUS);
	पूर्णांक		err = 0;

	svsk = kzalloc(माप(*svsk), GFP_KERNEL);
	अगर (!svsk)
		वापस ERR_PTR(-ENOMEM);

	inet = sock->sk;

	/* Register socket with porपंचांगapper */
	अगर (pmap_रेजिस्टर)
		err = svc_रेजिस्टर(serv, sock_net(sock->sk), inet->sk_family,
				     inet->sk_protocol,
				     ntohs(inet_sk(inet)->inet_sport));

	अगर (err < 0) अणु
		kमुक्त(svsk);
		वापस ERR_PTR(err);
	पूर्ण

	svsk->sk_sock = sock;
	svsk->sk_sk = inet;
	svsk->sk_ostate = inet->sk_state_change;
	svsk->sk_odata = inet->sk_data_पढ़ोy;
	svsk->sk_owspace = inet->sk_ग_लिखो_space;
	/*
	 * This barrier is necessary in order to prevent race condition
	 * with svc_data_पढ़ोy(), svc_listen_data_पढ़ोy() and others
	 * when calling callbacks above.
	 */
	wmb();
	inet->sk_user_data = svsk;

	/* Initialize the socket */
	अगर (sock->type == SOCK_DGRAM)
		svc_udp_init(svsk, serv);
	अन्यथा
		svc_tcp_init(svsk, serv);

	trace_svcsock_new_socket(sock);
	वापस svsk;
पूर्ण

bool svc_alien_sock(काष्ठा net *net, पूर्णांक fd)
अणु
	पूर्णांक err;
	काष्ठा socket *sock = sockfd_lookup(fd, &err);
	bool ret = false;

	अगर (!sock)
		जाओ out;
	अगर (sock_net(sock->sk) != net)
		ret = true;
	sockfd_put(sock);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(svc_alien_sock);

/**
 * svc_addsock - add a listener socket to an RPC service
 * @serv: poपूर्णांकer to RPC service to which to add a new listener
 * @fd: file descriptor of the new listener
 * @name_वापस: poपूर्णांकer to buffer to fill in with name of listener
 * @len: size of the buffer
 * @cred: credential
 *
 * Fills in socket name and वापसs positive length of name अगर successful.
 * Name is terminated with '\n'.  On error, वापसs a negative त्रुटि_सं
 * value.
 */
पूर्णांक svc_addsock(काष्ठा svc_serv *serv, स्थिर पूर्णांक fd, अक्षर *name_वापस,
		स्थिर माप_प्रकार len, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक err = 0;
	काष्ठा socket *so = sockfd_lookup(fd, &err);
	काष्ठा svc_sock *svsk = शून्य;
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr *sin = (काष्ठा sockaddr *)&addr;
	पूर्णांक salen;

	अगर (!so)
		वापस err;
	err = -EAFNOSUPPORT;
	अगर ((so->sk->sk_family != PF_INET) && (so->sk->sk_family != PF_INET6))
		जाओ out;
	err =  -EPROTONOSUPPORT;
	अगर (so->sk->sk_protocol != IPPROTO_TCP &&
	    so->sk->sk_protocol != IPPROTO_UDP)
		जाओ out;
	err = -EISCONN;
	अगर (so->state > SS_UNCONNECTED)
		जाओ out;
	err = -ENOENT;
	अगर (!try_module_get(THIS_MODULE))
		जाओ out;
	svsk = svc_setup_socket(serv, so, SVC_SOCK_DEFAULTS);
	अगर (IS_ERR(svsk)) अणु
		module_put(THIS_MODULE);
		err = PTR_ERR(svsk);
		जाओ out;
	पूर्ण
	salen = kernel_माला_लोockname(svsk->sk_sock, sin);
	अगर (salen >= 0)
		svc_xprt_set_local(&svsk->sk_xprt, sin, salen);
	svsk->sk_xprt.xpt_cred = get_cred(cred);
	svc_add_new_perm_xprt(serv, &svsk->sk_xprt);
	वापस svc_one_sock_name(svsk, name_वापस, len);
out:
	sockfd_put(so);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(svc_addsock);

/*
 * Create socket क्रम RPC service.
 */
अटल काष्ठा svc_xprt *svc_create_socket(काष्ठा svc_serv *serv,
					  पूर्णांक protocol,
					  काष्ठा net *net,
					  काष्ठा sockaddr *sin, पूर्णांक len,
					  पूर्णांक flags)
अणु
	काष्ठा svc_sock	*svsk;
	काष्ठा socket	*sock;
	पूर्णांक		error;
	पूर्णांक		type;
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr *newsin = (काष्ठा sockaddr *)&addr;
	पूर्णांक		newlen;
	पूर्णांक		family;

	अगर (protocol != IPPROTO_UDP && protocol != IPPROTO_TCP) अणु
		prपूर्णांकk(KERN_WARNING "svc: only UDP and TCP "
				"sockets supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	type = (protocol == IPPROTO_UDP)? SOCK_DGRAM : SOCK_STREAM;
	चयन (sin->sa_family) अणु
	हाल AF_INET6:
		family = PF_INET6;
		अवरोध;
	हाल AF_INET:
		family = PF_INET;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	error = __sock_create(net, family, type, protocol, &sock, 1);
	अगर (error < 0)
		वापस ERR_PTR(error);

	svc_reclassअगरy_socket(sock);

	/*
	 * If this is an PF_INET6 listener, we want to aव्योम
	 * getting requests from IPv4 remotes.  Those should
	 * be shunted to a PF_INET listener via rpcbind.
	 */
	अगर (family == PF_INET6)
		ip6_sock_set_v6only(sock->sk);
	अगर (type == SOCK_STREAM)
		sock->sk->sk_reuse = SK_CAN_REUSE; /* allow address reuse */
	error = kernel_bind(sock, sin, len);
	अगर (error < 0)
		जाओ bummer;

	error = kernel_माला_लोockname(sock, newsin);
	अगर (error < 0)
		जाओ bummer;
	newlen = error;

	अगर (protocol == IPPROTO_TCP) अणु
		अगर ((error = kernel_listen(sock, 64)) < 0)
			जाओ bummer;
	पूर्ण

	svsk = svc_setup_socket(serv, sock, flags);
	अगर (IS_ERR(svsk)) अणु
		error = PTR_ERR(svsk);
		जाओ bummer;
	पूर्ण
	svc_xprt_set_local(&svsk->sk_xprt, newsin, newlen);
	वापस (काष्ठा svc_xprt *)svsk;
bummer:
	sock_release(sock);
	वापस ERR_PTR(error);
पूर्ण

/*
 * Detach the svc_sock from the socket so that no
 * more callbacks occur.
 */
अटल व्योम svc_sock_detach(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);
	काष्ठा sock *sk = svsk->sk_sk;

	/* put back the old socket callbacks */
	lock_sock(sk);
	sk->sk_state_change = svsk->sk_ostate;
	sk->sk_data_पढ़ोy = svsk->sk_odata;
	sk->sk_ग_लिखो_space = svsk->sk_owspace;
	sk->sk_user_data = शून्य;
	release_sock(sk);
पूर्ण

/*
 * Disconnect the socket, and reset the callbacks
 */
अटल व्योम svc_tcp_sock_detach(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);

	svc_sock_detach(xprt);

	अगर (!test_bit(XPT_LISTENER, &xprt->xpt_flags)) अणु
		svc_tcp_clear_pages(svsk);
		kernel_sock_shutकरोwn(svsk->sk_sock, SHUT_RDWR);
	पूर्ण
पूर्ण

/*
 * Free the svc_sock's socket resources and the svc_sock itself.
 */
अटल व्योम svc_sock_मुक्त(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_sock *svsk = container_of(xprt, काष्ठा svc_sock, sk_xprt);

	अगर (svsk->sk_sock->file)
		sockfd_put(svsk->sk_sock);
	अन्यथा
		sock_release(svsk->sk_sock);
	kमुक्त(svsk);
पूर्ण
