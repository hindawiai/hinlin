<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		PF_INET protocol family socket handler.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Florian La Roche, <flla@stud.uni-sb.de>
 *		Alan Cox, <A.Cox@swansea.ac.uk>
 *
 * Changes (see also sock.c)
 *
 *		piggy,
 *		Karl Knutson	:	Socket protocol table
 *		A.N.Kuznetsov	:	Socket death error in accept().
 *		John Riअक्षरdson :	Fix non blocking error in connect()
 *					so sockets that fail to connect
 *					करोn't वापस -EINPROGRESS.
 *		Alan Cox	:	Asynchronous I/O support
 *		Alan Cox	:	Keep correct socket poपूर्णांकer on sock
 *					काष्ठाures
 *					when accept() ed
 *		Alan Cox	:	Semantics of SO_LINGER aren't state
 *					moved to बंद when you look carefully.
 *					With this fixed and the accept bug fixed
 *					some RPC stuff seems happier.
 *		Niibe Yutaka	:	4.4BSD style ग_लिखो async I/O
 *		Alan Cox,
 *		Tony Gale 	:	Fixed reuse semantics.
 *		Alan Cox	:	bind() shouldn't पात existing but dead
 *					sockets. Stops FTP netin:.. I hope.
 *		Alan Cox	:	bind() works correctly क्रम RAW sockets.
 *					Note that FreeBSD at least was broken
 *					in this respect so be careful with
 *					compatibility tests...
 *		Alan Cox	:	routing cache support
 *		Alan Cox	:	memzero the socket काष्ठाure क्रम
 *					compactness.
 *		Matt Day	:	nonblock connect error handler
 *		Alan Cox	:	Allow large numbers of pending sockets
 *					(eg क्रम big web sites), but only अगर
 *					specअगरically application requested.
 *		Alan Cox	:	New buffering throughout IP. Used
 *					dumbly.
 *		Alan Cox	:	New buffering now used smartly.
 *		Alan Cox	:	BSD rather than common sense
 *					पूर्णांकerpretation of listen.
 *		Germano Caronni	:	Assorted small races.
 *		Alan Cox	:	sendmsg/recvmsg basic support.
 *		Alan Cox	:	Only sendmsg/recvmsg now supported.
 *		Alan Cox	:	Locked करोwn bind (see security list).
 *		Alan Cox	:	Loosened bind a little.
 *		Mike McLagan	:	ADD/DEL DLCI Ioctls
 *	Willy Konynenberg	:	Transparent proxying support.
 *		David S. Miller	:	New socket lookup architecture.
 *					Some other अक्रमom speedups.
 *		Cyrus Durgin	:	Cleaned up file क्रम kmod hacks.
 *		Andi Kleen	:	Fix inet_stream_connect TCP race.
 */

#घोषणा pr_fmt(fmt) "IPv4: " fmt

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/capability.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/inet.h>
#समावेश <linux/igmp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <net/checksum.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/arp.h>
#समावेश <net/route.h>
#समावेश <net/ip_fib.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <net/ping.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/raw.h>
#समावेश <net/icmp.h>
#समावेश <net/inet_common.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/secure_seq.h>
#अगर_घोषित CONFIG_IP_MROUTE
#समावेश <linux/mroute.h>
#पूर्ण_अगर
#समावेश <net/l3mdev.h>
#समावेश <net/compat.h>

#समावेश <trace/events/sock.h>

/* The inetsw table contains everything that inet_create needs to
 * build a new socket.
 */
अटल काष्ठा list_head inetsw[SOCK_MAX];
अटल DEFINE_SPINLOCK(inetsw_lock);

/* New deकाष्ठाion routine */

व्योम inet_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	__skb_queue_purge(&sk->sk_receive_queue);
	अगर (sk->sk_rx_skb_cache) अणु
		__kमुक्त_skb(sk->sk_rx_skb_cache);
		sk->sk_rx_skb_cache = शून्य;
	पूर्ण
	__skb_queue_purge(&sk->sk_error_queue);

	sk_mem_reclaim(sk);

	अगर (sk->sk_type == SOCK_STREAM && sk->sk_state != TCP_CLOSE) अणु
		pr_err("Attempt to release TCP socket in state %d %p\n",
		       sk->sk_state, sk);
		वापस;
	पूर्ण
	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Attempt to release alive inet socket %p\n", sk);
		वापस;
	पूर्ण

	WARN_ON(atomic_पढ़ो(&sk->sk_rmem_alloc));
	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));
	WARN_ON(sk->sk_wmem_queued);
	WARN_ON(sk->sk_क्रमward_alloc);

	kमुक्त(rcu_dereference_रक्षित(inet->inet_opt, 1));
	dst_release(rcu_dereference_रक्षित(sk->sk_dst_cache, 1));
	dst_release(sk->sk_rx_dst);
	sk_refcnt_debug_dec(sk);
पूर्ण
EXPORT_SYMBOL(inet_sock_deकाष्ठा);

/*
 *	The routines beyond this poपूर्णांक handle the behaviour of an AF_INET
 *	socket object. Mostly it punts to the subprotocols of IP to करो
 *	the work.
 */

/*
 *	Automatically bind an unbound socket.
 */

अटल पूर्णांक inet_स्वतःbind(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet;
	/* We may need to bind the socket. */
	lock_sock(sk);
	inet = inet_sk(sk);
	अगर (!inet->inet_num) अणु
		अगर (sk->sk_prot->get_port(sk, 0)) अणु
			release_sock(sk);
			वापस -EAGAIN;
		पूर्ण
		inet->inet_sport = htons(inet->inet_num);
	पूर्ण
	release_sock(sk);
	वापस 0;
पूर्ण

/*
 *	Move a socket पूर्णांकo listening state.
 */
पूर्णांक inet_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	अचिन्हित अक्षर old_state;
	पूर्णांक err, tcp_fastखोलो;

	lock_sock(sk);

	err = -EINVAL;
	अगर (sock->state != SS_UNCONNECTED || sock->type != SOCK_STREAM)
		जाओ out;

	old_state = sk->sk_state;
	अगर (!((1 << old_state) & (TCPF_CLOSE | TCPF_LISTEN)))
		जाओ out;

	WRITE_ONCE(sk->sk_max_ack_backlog, backlog);
	/* Really, अगर the socket is alपढ़ोy in listen state
	 * we can only allow the backlog to be adjusted.
	 */
	अगर (old_state != TCP_LISTEN) अणु
		/* Enable TFO w/o requiring TCP_FASTOPEN socket option.
		 * Note that only TCP sockets (SOCK_STREAM) will reach here.
		 * Also fastखोलो backlog may alपढ़ोy been set via the option
		 * because the socket was in TCP_LISTEN state previously but
		 * was shutकरोwn() rather than बंद().
		 */
		tcp_fastखोलो = sock_net(sk)->ipv4.sysctl_tcp_fastखोलो;
		अगर ((tcp_fastखोलो & TFO_SERVER_WO_SOCKOPT1) &&
		    (tcp_fastखोलो & TFO_SERVER_ENABLE) &&
		    !inet_csk(sk)->icsk_accept_queue.fastखोलोq.max_qlen) अणु
			fastखोलो_queue_tune(sk, backlog);
			tcp_fastखोलो_init_key_once(sock_net(sk));
		पूर्ण

		err = inet_csk_listen_start(sk, backlog);
		अगर (err)
			जाओ out;
		tcp_call_bpf(sk, BPF_SOCK_OPS_TCP_LISTEN_CB, 0, शून्य);
	पूर्ण
	err = 0;

out:
	release_sock(sk);
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_listen);

/*
 *	Create an inet socket.
 */

अटल पूर्णांक inet_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		       पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा inet_protosw *answer;
	काष्ठा inet_sock *inet;
	काष्ठा proto *answer_prot;
	अचिन्हित अक्षर answer_flags;
	पूर्णांक try_loading_module = 0;
	पूर्णांक err;

	अगर (protocol < 0 || protocol >= IPPROTO_MAX)
		वापस -EINVAL;

	sock->state = SS_UNCONNECTED;

	/* Look क्रम the requested type/protocol pair. */
lookup_protocol:
	err = -ESOCKTNOSUPPORT;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(answer, &inetsw[sock->type], list) अणु

		err = 0;
		/* Check the non-wild match. */
		अगर (protocol == answer->protocol) अणु
			अगर (protocol != IPPROTO_IP)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Check क्रम the two wild हालs. */
			अगर (IPPROTO_IP == protocol) अणु
				protocol = answer->protocol;
				अवरोध;
			पूर्ण
			अगर (IPPROTO_IP == answer->protocol)
				अवरोध;
		पूर्ण
		err = -EPROTONOSUPPORT;
	पूर्ण

	अगर (unlikely(err)) अणु
		अगर (try_loading_module < 2) अणु
			rcu_पढ़ो_unlock();
			/*
			 * Be more specअगरic, e.g. net-pf-2-proto-132-type-1
			 * (net-pf-PF_INET-proto-IPPROTO_SCTP-type-SOCK_STREAM)
			 */
			अगर (++try_loading_module == 1)
				request_module("net-pf-%d-proto-%d-type-%d",
					       PF_INET, protocol, sock->type);
			/*
			 * Fall back to generic, e.g. net-pf-2-proto-132
			 * (net-pf-PF_INET-proto-IPPROTO_SCTP)
			 */
			अन्यथा
				request_module("net-pf-%d-proto-%d",
					       PF_INET, protocol);
			जाओ lookup_protocol;
		पूर्ण अन्यथा
			जाओ out_rcu_unlock;
	पूर्ण

	err = -EPERM;
	अगर (sock->type == SOCK_RAW && !kern &&
	    !ns_capable(net->user_ns, CAP_NET_RAW))
		जाओ out_rcu_unlock;

	sock->ops = answer->ops;
	answer_prot = answer->prot;
	answer_flags = answer->flags;
	rcu_पढ़ो_unlock();

	WARN_ON(!answer_prot->slab);

	err = -ENOBUFS;
	sk = sk_alloc(net, PF_INET, GFP_KERNEL, answer_prot, kern);
	अगर (!sk)
		जाओ out;

	err = 0;
	अगर (INET_PROTOSW_REUSE & answer_flags)
		sk->sk_reuse = SK_CAN_REUSE;

	inet = inet_sk(sk);
	inet->is_icsk = (INET_PROTOSW_ICSK & answer_flags) != 0;

	inet->nodefrag = 0;

	अगर (SOCK_RAW == sock->type) अणु
		inet->inet_num = protocol;
		अगर (IPPROTO_RAW == protocol)
			inet->hdrincl = 1;
	पूर्ण

	अगर (net->ipv4.sysctl_ip_no_pmtu_disc)
		inet->pmtudisc = IP_PMTUDISC_DONT;
	अन्यथा
		inet->pmtudisc = IP_PMTUDISC_WANT;

	inet->inet_id = 0;

	sock_init_data(sock, sk);

	sk->sk_deकाष्ठा	   = inet_sock_deकाष्ठा;
	sk->sk_protocol	   = protocol;
	sk->sk_backlog_rcv = sk->sk_prot->backlog_rcv;

	inet->uc_ttl	= -1;
	inet->mc_loop	= 1;
	inet->mc_ttl	= 1;
	inet->mc_all	= 1;
	inet->mc_index	= 0;
	inet->mc_list	= शून्य;
	inet->rcv_tos	= 0;

	sk_refcnt_debug_inc(sk);

	अगर (inet->inet_num) अणु
		/* It assumes that any protocol which allows
		 * the user to assign a number at socket
		 * creation समय स्वतःmatically
		 * shares.
		 */
		inet->inet_sport = htons(inet->inet_num);
		/* Add to protocol hash chains. */
		err = sk->sk_prot->hash(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (sk->sk_prot->init) अणु
		err = sk->sk_prot->init(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!kern) अणु
		err = BPF_CGROUP_RUN_PROG_INET_SOCK(sk);
		अगर (err) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस err;
out_rcu_unlock:
	rcu_पढ़ो_unlock();
	जाओ out;
पूर्ण


/*
 *	The peer socket should always be शून्य (or अन्यथा). When we call this
 *	function we are destroying the object and from then on nobody
 *	should refer to it.
 */
पूर्णांक inet_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		दीर्घ समयout;

		अगर (!sk->sk_kern_sock)
			BPF_CGROUP_RUN_PROG_INET_SOCK_RELEASE(sk);

		/* Applications क्रमget to leave groups beक्रमe निकासing */
		ip_mc_drop_socket(sk);

		/* If linger is set, we करोn't वापस until the बंद
		 * is complete.  Otherwise we वापस immediately. The
		 * actually closing is करोne the same either way.
		 *
		 * If the बंद is due to the process निकासing, we never
		 * linger..
		 */
		समयout = 0;
		अगर (sock_flag(sk, SOCK_LINGER) &&
		    !(current->flags & PF_EXITING))
			समयout = sk->sk_lingerसमय;
		sk->sk_prot->बंद(sk, समयout);
		sock->sk = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(inet_release);

पूर्णांक inet_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	u32 flags = BIND_WITH_LOCK;
	पूर्णांक err;

	/* If the socket has its own bind function then use it. (RAW) */
	अगर (sk->sk_prot->bind) अणु
		वापस sk->sk_prot->bind(sk, uaddr, addr_len);
	पूर्ण
	अगर (addr_len < माप(काष्ठा sockaddr_in))
		वापस -EINVAL;

	/* BPF prog is run beक्रमe any checks are करोne so that अगर the prog
	 * changes context in a wrong way it will be caught.
	 */
	err = BPF_CGROUP_RUN_PROG_INET_BIND_LOCK(sk, uaddr,
						 BPF_CGROUP_INET4_BIND, &flags);
	अगर (err)
		वापस err;

	वापस __inet_bind(sk, uaddr, addr_len, flags);
पूर्ण
EXPORT_SYMBOL(inet_bind);

पूर्णांक __inet_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len,
		u32 flags)
अणु
	काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *)uaddr;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	अचिन्हित लघु snum;
	पूर्णांक chk_addr_ret;
	u32 tb_id = RT_TABLE_LOCAL;
	पूर्णांक err;

	अगर (addr->sin_family != AF_INET) अणु
		/* Compatibility games : accept AF_UNSPEC (mapped to AF_INET)
		 * only अगर s_addr is INADDR_ANY.
		 */
		err = -EAFNOSUPPORT;
		अगर (addr->sin_family != AF_UNSPEC ||
		    addr->sin_addr.s_addr != htonl(INADDR_ANY))
			जाओ out;
	पूर्ण

	tb_id = l3mdev_fib_table_by_index(net, sk->sk_bound_dev_अगर) ? : tb_id;
	chk_addr_ret = inet_addr_type_table(net, addr->sin_addr.s_addr, tb_id);

	/* Not specअगरied by any standard per-se, however it अवरोधs too
	 * many applications when हटाओd.  It is unक्रमtunate since
	 * allowing applications to make a non-local bind solves
	 * several problems with प्रणालीs using dynamic addressing.
	 * (ie. your servers still start up even अगर your ISDN link
	 *  is temporarily करोwn)
	 */
	err = -EADDRNOTAVAIL;
	अगर (!inet_can_nonlocal_bind(net, inet) &&
	    addr->sin_addr.s_addr != htonl(INADDR_ANY) &&
	    chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST &&
	    chk_addr_ret != RTN_BROADCAST)
		जाओ out;

	snum = ntohs(addr->sin_port);
	err = -EACCES;
	अगर (!(flags & BIND_NO_CAP_NET_BIND_SERVICE) &&
	    snum && inet_port_requires_bind_service(net, snum) &&
	    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
		जाओ out;

	/*      We keep a pair of addresses. rcv_saddr is the one
	 *      used by hash lookups, and saddr is used क्रम transmit.
	 *
	 *      In the BSD API these are the same except where it
	 *      would be illegal to use them (multicast/broadcast) in
	 *      which हाल the sending device address is used.
	 */
	अगर (flags & BIND_WITH_LOCK)
		lock_sock(sk);

	/* Check these errors (active socket, द्विगुन bind). */
	err = -EINVAL;
	अगर (sk->sk_state != TCP_CLOSE || inet->inet_num)
		जाओ out_release_sock;

	inet->inet_rcv_saddr = inet->inet_saddr = addr->sin_addr.s_addr;
	अगर (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */

	/* Make sure we are allowed to bind here. */
	अगर (snum || !(inet->bind_address_no_port ||
		      (flags & BIND_FORCE_ADDRESS_NO_PORT))) अणु
		अगर (sk->sk_prot->get_port(sk, snum)) अणु
			inet->inet_saddr = inet->inet_rcv_saddr = 0;
			err = -EADDRINUSE;
			जाओ out_release_sock;
		पूर्ण
		अगर (!(flags & BIND_FROM_BPF)) अणु
			err = BPF_CGROUP_RUN_PROG_INET4_POST_BIND(sk);
			अगर (err) अणु
				inet->inet_saddr = inet->inet_rcv_saddr = 0;
				जाओ out_release_sock;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (inet->inet_rcv_saddr)
		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
	अगर (snum)
		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
	inet->inet_sport = htons(inet->inet_num);
	inet->inet_daddr = 0;
	inet->inet_dport = 0;
	sk_dst_reset(sk);
	err = 0;
out_release_sock:
	अगर (flags & BIND_WITH_LOCK)
		release_sock(sk);
out:
	वापस err;
पूर्ण

पूर्णांक inet_dgram_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	अगर (addr_len < माप(uaddr->sa_family))
		वापस -EINVAL;
	अगर (uaddr->sa_family == AF_UNSPEC)
		वापस sk->sk_prot->disconnect(sk, flags);

	अगर (BPF_CGROUP_PRE_CONNECT_ENABLED(sk)) अणु
		err = sk->sk_prot->pre_connect(sk, uaddr, addr_len);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data_race(!inet_sk(sk)->inet_num) && inet_स्वतःbind(sk))
		वापस -EAGAIN;
	वापस sk->sk_prot->connect(sk, uaddr, addr_len);
पूर्ण
EXPORT_SYMBOL(inet_dgram_connect);

अटल दीर्घ inet_रुको_क्रम_connect(काष्ठा sock *sk, दीर्घ समयo, पूर्णांक ग_लिखोbias)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(sk_sleep(sk), &रुको);
	sk->sk_ग_लिखो_pending += ग_लिखोbias;

	/* Basic assumption: अगर someone sets sk->sk_err, he _must_
	 * change state of the socket from TCP_SYN_*.
	 * Connect() करोes not allow to get error notअगरications
	 * without closing the socket.
	 */
	जबतक ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) अणु
		release_sock(sk);
		समयo = रुको_woken(&रुको, TASK_INTERRUPTIBLE, समयo);
		lock_sock(sk);
		अगर (संकेत_pending(current) || !समयo)
			अवरोध;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	sk->sk_ग_लिखो_pending -= ग_लिखोbias;
	वापस समयo;
पूर्ण

/*
 *	Connect to a remote host. There is regrettably still a little
 *	TCP 'magic' in here.
 */
पूर्णांक __inet_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			  पूर्णांक addr_len, पूर्णांक flags, पूर्णांक is_sendmsg)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;
	दीर्घ समयo;

	/*
	 * uaddr can be शून्य and addr_len can be 0 अगर:
	 * sk is a TCP fastखोलो active socket and
	 * TCP_FASTOPEN_CONNECT sockopt is set and
	 * we alपढ़ोy have a valid cookie क्रम this socket.
	 * In this हाल, user can call ग_लिखो() after connect().
	 * ग_लिखो() will invoke tcp_sendmsg_fastखोलो() which calls
	 * __inet_stream_connect().
	 */
	अगर (uaddr) अणु
		अगर (addr_len < माप(uaddr->sa_family))
			वापस -EINVAL;

		अगर (uaddr->sa_family == AF_UNSPEC) अणु
			err = sk->sk_prot->disconnect(sk, flags);
			sock->state = err ? SS_DISCONNECTING : SS_UNCONNECTED;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (sock->state) अणु
	शेष:
		err = -EINVAL;
		जाओ out;
	हाल SS_CONNECTED:
		err = -EISCONN;
		जाओ out;
	हाल SS_CONNECTING:
		अगर (inet_sk(sk)->defer_connect)
			err = is_sendmsg ? -EINPROGRESS : -EISCONN;
		अन्यथा
			err = -EALREADY;
		/* Fall out of चयन with err, set क्रम this state */
		अवरोध;
	हाल SS_UNCONNECTED:
		err = -EISCONN;
		अगर (sk->sk_state != TCP_CLOSE)
			जाओ out;

		अगर (BPF_CGROUP_PRE_CONNECT_ENABLED(sk)) अणु
			err = sk->sk_prot->pre_connect(sk, uaddr, addr_len);
			अगर (err)
				जाओ out;
		पूर्ण

		err = sk->sk_prot->connect(sk, uaddr, addr_len);
		अगर (err < 0)
			जाओ out;

		sock->state = SS_CONNECTING;

		अगर (!err && inet_sk(sk)->defer_connect)
			जाओ out;

		/* Just entered SS_CONNECTING state; the only
		 * dअगरference is that वापस value in non-blocking
		 * हाल is EINPROGRESS, rather than EALREADY.
		 */
		err = -EINPROGRESS;
		अवरोध;
	पूर्ण

	समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

	अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) अणु
		पूर्णांक ग_लिखोbias = (sk->sk_protocol == IPPROTO_TCP) &&
				tcp_sk(sk)->fastखोलो_req &&
				tcp_sk(sk)->fastखोलो_req->data ? 1 : 0;

		/* Error code is set above */
		अगर (!समयo || !inet_रुको_क्रम_connect(sk, समयo, ग_लिखोbias))
			जाओ out;

		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			जाओ out;
	पूर्ण

	/* Connection was बंदd by RST, समयout, ICMP error
	 * or another process disconnected us.
	 */
	अगर (sk->sk_state == TCP_CLOSE)
		जाओ sock_error;

	/* sk->sk_err may be not zero now, अगर RECVERR was ordered by user
	 * and error was received after socket entered established state.
	 * Hence, it is handled normally after connect() वापस successfully.
	 */

	sock->state = SS_CONNECTED;
	err = 0;
out:
	वापस err;

sock_error:
	err = sock_error(sk) ? : -ECONNABORTED;
	sock->state = SS_UNCONNECTED;
	अगर (sk->sk_prot->disconnect(sk, flags))
		sock->state = SS_DISCONNECTING;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(__inet_stream_connect);

पूर्णांक inet_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			पूर्णांक addr_len, पूर्णांक flags)
अणु
	पूर्णांक err;

	lock_sock(sock->sk);
	err = __inet_stream_connect(sock, uaddr, addr_len, flags, 0);
	release_sock(sock->sk);
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_stream_connect);

/*
 *	Accept a pending connection. The TCP layer now gives BSD semantics.
 */

पूर्णांक inet_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		bool kern)
अणु
	काष्ठा sock *sk1 = sock->sk;
	पूर्णांक err = -EINVAL;
	काष्ठा sock *sk2 = sk1->sk_prot->accept(sk1, flags, &err, kern);

	अगर (!sk2)
		जाओ करो_err;

	lock_sock(sk2);

	sock_rps_record_flow(sk2);
	WARN_ON(!((1 << sk2->sk_state) &
		  (TCPF_ESTABLISHED | TCPF_SYN_RECV |
		  TCPF_CLOSE_WAIT | TCPF_CLOSE)));

	sock_graft(sk2, newsock);

	newsock->state = SS_CONNECTED;
	err = 0;
	release_sock(sk2);
करो_err:
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_accept);

/*
 *	This करोes both peername and sockname.
 */
पूर्णांक inet_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		 पूर्णांक peer)
अणु
	काष्ठा sock *sk		= sock->sk;
	काष्ठा inet_sock *inet	= inet_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, uaddr);

	sin->sin_family = AF_INET;
	अगर (peer) अणु
		अगर (!inet->inet_dport ||
		    (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_SYN_SENT)) &&
		     peer == 1))
			वापस -ENOTCONN;
		sin->sin_port = inet->inet_dport;
		sin->sin_addr.s_addr = inet->inet_daddr;
		BPF_CGROUP_RUN_SA_PROG_LOCK(sk, (काष्ठा sockaddr *)sin,
					    BPF_CGROUP_INET4_GETPEERNAME,
					    शून्य);
	पूर्ण अन्यथा अणु
		__be32 addr = inet->inet_rcv_saddr;
		अगर (!addr)
			addr = inet->inet_saddr;
		sin->sin_port = inet->inet_sport;
		sin->sin_addr.s_addr = addr;
		BPF_CGROUP_RUN_SA_PROG_LOCK(sk, (काष्ठा sockaddr *)sin,
					    BPF_CGROUP_INET4_GETSOCKNAME,
					    शून्य);
	पूर्ण
	स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
	वापस माप(*sin);
पूर्ण
EXPORT_SYMBOL(inet_getname);

पूर्णांक inet_send_prepare(काष्ठा sock *sk)
अणु
	sock_rps_record_flow(sk);

	/* We may need to bind the socket. */
	अगर (data_race(!inet_sk(sk)->inet_num) && !sk->sk_prot->no_स्वतःbind &&
	    inet_स्वतःbind(sk))
		वापस -EAGAIN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(inet_send_prepare);

पूर्णांक inet_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (unlikely(inet_send_prepare(sk)))
		वापस -EAGAIN;

	वापस INसूचीECT_CALL_2(sk->sk_prot->sendmsg, tcp_sendmsg, udp_sendmsg,
			       sk, msg, size);
पूर्ण
EXPORT_SYMBOL(inet_sendmsg);

sमाप_प्रकार inet_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset,
		      माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (unlikely(inet_send_prepare(sk)))
		वापस -EAGAIN;

	अगर (sk->sk_prot->sendpage)
		वापस sk->sk_prot->sendpage(sk, page, offset, size, flags);
	वापस sock_no_sendpage(sock, page, offset, size, flags);
पूर्ण
EXPORT_SYMBOL(inet_sendpage);

INसूचीECT_CALLABLE_DECLARE(पूर्णांक udp_recvmsg(काष्ठा sock *, काष्ठा msghdr *,
					  माप_प्रकार, पूर्णांक, पूर्णांक, पूर्णांक *));
पूर्णांक inet_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		 पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक addr_len = 0;
	पूर्णांक err;

	अगर (likely(!(flags & MSG_ERRQUEUE)))
		sock_rps_record_flow(sk);

	err = INसूचीECT_CALL_2(sk->sk_prot->recvmsg, tcp_recvmsg, udp_recvmsg,
			      sk, msg, size, flags & MSG_DONTWAIT,
			      flags & ~MSG_DONTWAIT, &addr_len);
	अगर (err >= 0)
		msg->msg_namelen = addr_len;
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_recvmsg);

पूर्णांक inet_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	/* This should really check to make sure
	 * the socket is a TCP socket. (WHY AC...)
	 */
	how++; /* maps 0->1 has the advantage of making bit 1 rcvs and
		       1->2 bit 2 snds.
		       2->3 */
	अगर ((how & ~SHUTDOWN_MASK) || !how)	/* MAXINT->0 */
		वापस -EINVAL;

	lock_sock(sk);
	अगर (sock->state == SS_CONNECTING) अणु
		अगर ((1 << sk->sk_state) &
		    (TCPF_SYN_SENT | TCPF_SYN_RECV | TCPF_CLOSE))
			sock->state = SS_DISCONNECTING;
		अन्यथा
			sock->state = SS_CONNECTED;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल TCP_CLOSE:
		err = -ENOTCONN;
		/* Hack to wake up other listeners, who can poll क्रम
		   EPOLLHUP, even on eg. unconnected UDP sockets -- RR */
		fallthrough;
	शेष:
		sk->sk_shutकरोwn |= how;
		अगर (sk->sk_prot->shutकरोwn)
			sk->sk_prot->shutकरोwn(sk, how);
		अवरोध;

	/* Reमुख्यing two branches are temporary solution क्रम missing
	 * बंद() in multithपढ़ोed environment. It is _not_ a good idea,
	 * but we have no choice until बंद() is repaired at VFS level.
	 */
	हाल TCP_LISTEN:
		अगर (!(how & RCV_SHUTDOWN))
			अवरोध;
		fallthrough;
	हाल TCP_SYN_SENT:
		err = sk->sk_prot->disconnect(sk, O_NONBLOCK);
		sock->state = err ? SS_DISCONNECTING : SS_UNCONNECTED;
		अवरोध;
	पूर्ण

	/* Wake up anyone sleeping in poll. */
	sk->sk_state_change(sk);
	release_sock(sk);
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_shutकरोwn);

/*
 *	ioctl() calls you can issue on an INET socket. Most of these are
 *	device configuration and stuff and very rarely used. Some ioctls
 *	pass on to the socket itself.
 *
 *	NOTE: I like the idea of a module क्रम the config stuff. ie अगरconfig
 *	loads the devconfigure module करोes its configuring and unloads it.
 *	There's a good 20K of config code hanging around the kernel.
 */

पूर्णांक inet_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;
	काष्ठा net *net = sock_net(sk);
	व्योम __user *p = (व्योम __user *)arg;
	काष्ठा अगरreq अगरr;
	काष्ठा rtentry rt;

	चयन (cmd) अणु
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		अगर (copy_from_user(&rt, p, माप(काष्ठा rtentry)))
			वापस -EFAULT;
		err = ip_rt_ioctl(net, cmd, &rt);
		अवरोध;
	हाल SIOCRTMSG:
		err = -EINVAL;
		अवरोध;
	हाल SIOCDARP:
	हाल SIOCGARP:
	हाल SIOCSARP:
		err = arp_ioctl(net, cmd, (व्योम __user *)arg);
		अवरोध;
	हाल SIOCGIFADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCGIFDSTADDR:
	हाल SIOCGIFPFLAGS:
		अगर (copy_from_user(&अगरr, p, माप(काष्ठा अगरreq)))
			वापस -EFAULT;
		err = devinet_ioctl(net, cmd, &अगरr);
		अगर (!err && copy_to_user(p, &अगरr, माप(काष्ठा अगरreq)))
			err = -EFAULT;
		अवरोध;

	हाल SIOCSIFADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCSIFNETMASK:
	हाल SIOCSIFDSTADDR:
	हाल SIOCSIFPFLAGS:
	हाल SIOCSIFFLAGS:
		अगर (copy_from_user(&अगरr, p, माप(काष्ठा अगरreq)))
			वापस -EFAULT;
		err = devinet_ioctl(net, cmd, &अगरr);
		अवरोध;
	शेष:
		अगर (sk->sk_prot->ioctl)
			err = sk->sk_prot->ioctl(sk, cmd, arg);
		अन्यथा
			err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_ioctl);

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक inet_compat_routing_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd,
		काष्ठा compat_rtentry __user *ur)
अणु
	compat_uptr_t rtdev;
	काष्ठा rtentry rt;

	अगर (copy_from_user(&rt.rt_dst, &ur->rt_dst,
			3 * माप(काष्ठा sockaddr)) ||
	    get_user(rt.rt_flags, &ur->rt_flags) ||
	    get_user(rt.rt_metric, &ur->rt_metric) ||
	    get_user(rt.rt_mtu, &ur->rt_mtu) ||
	    get_user(rt.rt_winकरोw, &ur->rt_winकरोw) ||
	    get_user(rt.rt_irtt, &ur->rt_irtt) ||
	    get_user(rtdev, &ur->rt_dev))
		वापस -EFAULT;

	rt.rt_dev = compat_ptr(rtdev);
	वापस ip_rt_ioctl(sock_net(sk), cmd, &rt);
पूर्ण

अटल पूर्णांक inet_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	काष्ठा sock *sk = sock->sk;

	चयन (cmd) अणु
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		वापस inet_compat_routing_ioctl(sk, cmd, argp);
	शेष:
		अगर (!sk->sk_prot->compat_ioctl)
			वापस -ENOIOCTLCMD;
		वापस sk->sk_prot->compat_ioctl(sk, cmd, arg);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

स्थिर काष्ठा proto_ops inet_stream_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = inet_getname,
	.poll		   = tcp_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = inet_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
#अगर_घोषित CONFIG_MMU
	.mmap		   = tcp_mmap,
#पूर्ण_अगर
	.sendpage	   = inet_sendpage,
	.splice_पढ़ो	   = tcp_splice_पढ़ो,
	.पढ़ो_sock	   = tcp_पढ़ो_sock,
	.sendmsg_locked    = tcp_sendmsg_locked,
	.sendpage_locked   = tcp_sendpage_locked,
	.peek_len	   = tcp_peek_len,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet_compat_ioctl,
#पूर्ण_अगर
	.set_rcvlowat	   = tcp_set_rcvlowat,
पूर्ण;
EXPORT_SYMBOL(inet_stream_ops);

स्थिर काष्ठा proto_ops inet_dgram_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_dgram_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = inet_getname,
	.poll		   = udp_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.पढ़ो_sock	   = udp_पढ़ो_sock,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
	.set_peek_off	   = sk_set_peek_off,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet_compat_ioctl,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(inet_dgram_ops);

/*
 * For SOCK_RAW sockets; should be the same as inet_dgram_ops but without
 * udp_poll
 */
अटल स्थिर काष्ठा proto_ops inet_sockraw_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_dgram_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = inet_getname,
	.poll		   = datagram_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_proto_family inet_family_ops = अणु
	.family = PF_INET,
	.create = inet_create,
	.owner	= THIS_MODULE,
पूर्ण;

/* Upon startup we insert all the elements in inetsw_array[] पूर्णांकo
 * the linked list inetsw.
 */
अटल काष्ठा inet_protosw inetsw_array[] =
अणु
	अणु
		.type =       SOCK_STREAM,
		.protocol =   IPPROTO_TCP,
		.prot =       &tcp_prot,
		.ops =        &inet_stream_ops,
		.flags =      INET_PROTOSW_PERMANENT |
			      INET_PROTOSW_ICSK,
	पूर्ण,

	अणु
		.type =       SOCK_DGRAM,
		.protocol =   IPPROTO_UDP,
		.prot =       &udp_prot,
		.ops =        &inet_dgram_ops,
		.flags =      INET_PROTOSW_PERMANENT,
       पूर्ण,

       अणु
		.type =       SOCK_DGRAM,
		.protocol =   IPPROTO_ICMP,
		.prot =       &ping_prot,
		.ops =        &inet_sockraw_ops,
		.flags =      INET_PROTOSW_REUSE,
       पूर्ण,

       अणु
	       .type =       SOCK_RAW,
	       .protocol =   IPPROTO_IP,	/* wild card */
	       .prot =       &raw_prot,
	       .ops =        &inet_sockraw_ops,
	       .flags =      INET_PROTOSW_REUSE,
       पूर्ण
पूर्ण;

#घोषणा INETSW_ARRAY_LEN ARRAY_SIZE(inetsw_array)

व्योम inet_रेजिस्टर_protosw(काष्ठा inet_protosw *p)
अणु
	काष्ठा list_head *lh;
	काष्ठा inet_protosw *answer;
	पूर्णांक protocol = p->protocol;
	काष्ठा list_head *last_perm;

	spin_lock_bh(&inetsw_lock);

	अगर (p->type >= SOCK_MAX)
		जाओ out_illegal;

	/* If we are trying to override a permanent protocol, bail. */
	last_perm = &inetsw[p->type];
	list_क्रम_each(lh, &inetsw[p->type]) अणु
		answer = list_entry(lh, काष्ठा inet_protosw, list);
		/* Check only the non-wild match. */
		अगर ((INET_PROTOSW_PERMANENT & answer->flags) == 0)
			अवरोध;
		अगर (protocol == answer->protocol)
			जाओ out_permanent;
		last_perm = lh;
	पूर्ण

	/* Add the new entry after the last permanent entry अगर any, so that
	 * the new entry करोes not override a permanent entry when matched with
	 * a wild-card protocol. But it is allowed to override any existing
	 * non-permanent entry.  This means that when we हटाओ this entry, the
	 * प्रणाली स्वतःmatically वापसs to the old behavior.
	 */
	list_add_rcu(&p->list, last_perm);
out:
	spin_unlock_bh(&inetsw_lock);

	वापस;

out_permanent:
	pr_err("Attempt to override permanent protocol %d\n", protocol);
	जाओ out;

out_illegal:
	pr_err("Ignoring attempt to register invalid socket type %d\n",
	       p->type);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(inet_रेजिस्टर_protosw);

व्योम inet_unरेजिस्टर_protosw(काष्ठा inet_protosw *p)
अणु
	अगर (INET_PROTOSW_PERMANENT & p->flags) अणु
		pr_err("Attempt to unregister permanent protocol %d\n",
		       p->protocol);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&inetsw_lock);
		list_del_rcu(&p->list);
		spin_unlock_bh(&inetsw_lock);

		synchronize_net();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(inet_unरेजिस्टर_protosw);

अटल पूर्णांक inet_sk_reselect_saddr(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	__be32 old_saddr = inet->inet_saddr;
	__be32 daddr = inet->inet_daddr;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;
	__be32 new_saddr;
	काष्ठा ip_options_rcu *inet_opt;

	inet_opt = rcu_dereference_रक्षित(inet->inet_opt,
					     lockdep_sock_is_held(sk));
	अगर (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;

	/* Query new route. */
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_connect(fl4, daddr, 0, RT_CONN_FLAGS(sk),
			      sk->sk_bound_dev_अगर, sk->sk_protocol,
			      inet->inet_sport, inet->inet_dport, sk);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	sk_setup_caps(sk, &rt->dst);

	new_saddr = fl4->saddr;

	अगर (new_saddr == old_saddr)
		वापस 0;

	अगर (sock_net(sk)->ipv4.sysctl_ip_dynaddr > 1) अणु
		pr_info("%s(): shifting inet->saddr from %pI4 to %pI4\n",
			__func__, &old_saddr, &new_saddr);
	पूर्ण

	inet->inet_saddr = inet->inet_rcv_saddr = new_saddr;

	/*
	 * XXX The only one ugly spot where we need to
	 * XXX really change the sockets identity after
	 * XXX it has entered the hashes. -DaveM
	 *
	 * Besides that, it करोes not check क्रम connection
	 * uniqueness. Wait क्रम troubles.
	 */
	वापस __sk_prot_rehash(sk);
पूर्ण

पूर्णांक inet_sk_rebuild_header(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा rtable *rt = (काष्ठा rtable *)__sk_dst_check(sk, 0);
	__be32 daddr;
	काष्ठा ip_options_rcu *inet_opt;
	काष्ठा flowi4 *fl4;
	पूर्णांक err;

	/* Route is OK, nothing to करो. */
	अगर (rt)
		वापस 0;

	/* Reroute. */
	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	daddr = inet->inet_daddr;
	अगर (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	rcu_पढ़ो_unlock();
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_output_ports(sock_net(sk), fl4, sk, daddr, inet->inet_saddr,
				   inet->inet_dport, inet->inet_sport,
				   sk->sk_protocol, RT_CONN_FLAGS(sk),
				   sk->sk_bound_dev_अगर);
	अगर (!IS_ERR(rt)) अणु
		err = 0;
		sk_setup_caps(sk, &rt->dst);
	पूर्ण अन्यथा अणु
		err = PTR_ERR(rt);

		/* Routing failed... */
		sk->sk_route_caps = 0;
		/*
		 * Other protocols have to map its equivalent state to TCP_SYN_SENT.
		 * DCCP maps its DCCP_REQUESTING state to TCP_SYN_SENT. -acme
		 */
		अगर (!sock_net(sk)->ipv4.sysctl_ip_dynaddr ||
		    sk->sk_state != TCP_SYN_SENT ||
		    (sk->sk_userlocks & SOCK_BINDADDR_LOCK) ||
		    (err = inet_sk_reselect_saddr(sk)) != 0)
			sk->sk_err_soft = -err;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_sk_rebuild_header);

व्योम inet_sk_set_state(काष्ठा sock *sk, पूर्णांक state)
अणु
	trace_inet_sock_set_state(sk, sk->sk_state, state);
	sk->sk_state = state;
पूर्ण
EXPORT_SYMBOL(inet_sk_set_state);

व्योम inet_sk_state_store(काष्ठा sock *sk, पूर्णांक newstate)
अणु
	trace_inet_sock_set_state(sk, sk->sk_state, newstate);
	smp_store_release(&sk->sk_state, newstate);
पूर्ण

काष्ठा sk_buff *inet_gso_segment(काष्ठा sk_buff *skb,
				 netdev_features_t features)
अणु
	bool udpfrag = false, fixedid = false, gso_partial, encap;
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	स्थिर काष्ठा net_offload *ops;
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा iphdr *iph;
	पूर्णांक proto, tot_len;
	पूर्णांक nhoff;
	पूर्णांक ihl;
	पूर्णांक id;

	skb_reset_network_header(skb);
	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	अगर (unlikely(!pskb_may_pull(skb, माप(*iph))))
		जाओ out;

	iph = ip_hdr(skb);
	ihl = iph->ihl * 4;
	अगर (ihl < माप(*iph))
		जाओ out;

	id = ntohs(iph->id);
	proto = iph->protocol;

	/* Warning: after this poपूर्णांक, iph might be no दीर्घer valid */
	अगर (unlikely(!pskb_may_pull(skb, ihl)))
		जाओ out;
	__skb_pull(skb, ihl);

	encap = SKB_GSO_CB(skb)->encap_level > 0;
	अगर (encap)
		features &= skb->dev->hw_enc_features;
	SKB_GSO_CB(skb)->encap_level += ihl;

	skb_reset_transport_header(skb);

	segs = ERR_PTR(-EPROTONOSUPPORT);

	अगर (!skb->encapsulation || encap) अणु
		udpfrag = !!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP);
		fixedid = !!(skb_shinfo(skb)->gso_type & SKB_GSO_TCP_FIXEDID);

		/* fixed ID is invalid अगर DF bit is not set */
		अगर (fixedid && !(ip_hdr(skb)->frag_off & htons(IP_DF)))
			जाओ out;
	पूर्ण

	ops = rcu_dereference(inet_offloads[proto]);
	अगर (likely(ops && ops->callbacks.gso_segment))
		segs = ops->callbacks.gso_segment(skb, features);

	अगर (IS_ERR_OR_शून्य(segs))
		जाओ out;

	gso_partial = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PARTIAL);

	skb = segs;
	करो अणु
		iph = (काष्ठा iphdr *)(skb_mac_header(skb) + nhoff);
		अगर (udpfrag) अणु
			iph->frag_off = htons(offset >> 3);
			अगर (skb->next)
				iph->frag_off |= htons(IP_MF);
			offset += skb->len - nhoff - ihl;
			tot_len = skb->len - nhoff;
		पूर्ण अन्यथा अगर (skb_is_gso(skb)) अणु
			अगर (!fixedid) अणु
				iph->id = htons(id);
				id += skb_shinfo(skb)->gso_segs;
			पूर्ण

			अगर (gso_partial)
				tot_len = skb_shinfo(skb)->gso_size +
					  SKB_GSO_CB(skb)->data_offset +
					  skb->head - (अचिन्हित अक्षर *)iph;
			अन्यथा
				tot_len = skb->len - nhoff;
		पूर्ण अन्यथा अणु
			अगर (!fixedid)
				iph->id = htons(id++);
			tot_len = skb->len - nhoff;
		पूर्ण
		iph->tot_len = htons(tot_len);
		ip_send_check(iph);
		अगर (encap)
			skb_reset_inner_headers(skb);
		skb->network_header = (u8 *)iph - skb->head;
		skb_reset_mac_len(skb);
	पूर्ण जबतक ((skb = skb->next));

out:
	वापस segs;
पूर्ण

अटल काष्ठा sk_buff *ipip_gso_segment(काष्ठा sk_buff *skb,
					netdev_features_t features)
अणु
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_IPXIP4))
		वापस ERR_PTR(-EINVAL);

	वापस inet_gso_segment(skb, features);
पूर्ण

काष्ठा sk_buff *inet_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *pp = शून्य;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा sk_buff *p;
	अचिन्हित पूर्णांक hlen;
	अचिन्हित पूर्णांक off;
	अचिन्हित पूर्णांक id;
	पूर्णांक flush = 1;
	पूर्णांक proto;

	off = skb_gro_offset(skb);
	hlen = off + माप(*iph);
	iph = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		iph = skb_gro_header_slow(skb, hlen, off);
		अगर (unlikely(!iph))
			जाओ out;
	पूर्ण

	proto = iph->protocol;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(inet_offloads[proto]);
	अगर (!ops || !ops->callbacks.gro_receive)
		जाओ out_unlock;

	अगर (*(u8 *)iph != 0x45)
		जाओ out_unlock;

	अगर (ip_is_fragment(iph))
		जाओ out_unlock;

	अगर (unlikely(ip_fast_csum((u8 *)iph, 5)))
		जाओ out_unlock;

	id = ntohl(*(__be32 *)&iph->id);
	flush = (u16)((ntohl(*(__be32 *)iph) ^ skb_gro_len(skb)) | (id & ~IP_DF));
	id >>= 16;

	list_क्रम_each_entry(p, head, list) अणु
		काष्ठा iphdr *iph2;
		u16 flush_id;

		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		iph2 = (काष्ठा iphdr *)(p->data + off);
		/* The above works because, with the exception of the top
		 * (inner most) layer, we only aggregate pkts with the same
		 * hdr length so all the hdrs we'll need to verअगरy will start
		 * at the same offset.
		 */
		अगर ((iph->protocol ^ iph2->protocol) |
		    ((__क्रमce u32)iph->saddr ^ (__क्रमce u32)iph2->saddr) |
		    ((__क्रमce u32)iph->daddr ^ (__क्रमce u32)iph2->daddr)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण

		/* All fields must match except length and checksum. */
		NAPI_GRO_CB(p)->flush |=
			(iph->ttl ^ iph2->ttl) |
			(iph->tos ^ iph2->tos) |
			((iph->frag_off ^ iph2->frag_off) & htons(IP_DF));

		NAPI_GRO_CB(p)->flush |= flush;

		/* We need to store of the IP ID check to be included later
		 * when we can verअगरy that this packet करोes in fact beदीर्घ
		 * to a given flow.
		 */
		flush_id = (u16)(id - ntohs(iph2->id));

		/* This bit of code makes it much easier क्रम us to identअगरy
		 * the हालs where we are करोing atomic vs non-atomic IP ID
		 * checks.  Specअगरically an atomic check can वापस IP ID
		 * values 0 - 0xFFFF, जबतक a non-atomic check can only
		 * वापस 0 or 0xFFFF.
		 */
		अगर (!NAPI_GRO_CB(p)->is_atomic ||
		    !(iph->frag_off & htons(IP_DF))) अणु
			flush_id ^= NAPI_GRO_CB(p)->count;
			flush_id = flush_id ? 0xFFFF : 0;
		पूर्ण

		/* If the previous IP ID value was based on an atomic
		 * datagram we can overग_लिखो the value and ignore it.
		 */
		अगर (NAPI_GRO_CB(skb)->is_atomic)
			NAPI_GRO_CB(p)->flush_id = flush_id;
		अन्यथा
			NAPI_GRO_CB(p)->flush_id |= flush_id;
	पूर्ण

	NAPI_GRO_CB(skb)->is_atomic = !!(iph->frag_off & htons(IP_DF));
	NAPI_GRO_CB(skb)->flush |= flush;
	skb_set_network_header(skb, off);
	/* The above will be needed by the transport layer अगर there is one
	 * immediately following this IP hdr.
	 */

	/* Note : No need to call skb_gro_postpull_rcsum() here,
	 * as we alपढ़ोy checked checksum over ipv4 header was 0
	 */
	skb_gro_pull(skb, माप(*iph));
	skb_set_transport_header(skb, skb_gro_offset(skb));

	pp = indirect_call_gro_receive(tcp4_gro_receive, udp4_gro_receive,
				       ops->callbacks.gro_receive, head, skb);

out_unlock:
	rcu_पढ़ो_unlock();

out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण

अटल काष्ठा sk_buff *ipip_gro_receive(काष्ठा list_head *head,
					काष्ठा sk_buff *skb)
अणु
	अगर (NAPI_GRO_CB(skb)->encap_mark) अणु
		NAPI_GRO_CB(skb)->flush = 1;
		वापस शून्य;
	पूर्ण

	NAPI_GRO_CB(skb)->encap_mark = 1;

	वापस inet_gro_receive(head, skb);
पूर्ण

#घोषणा SECONDS_PER_DAY	86400

/* inet_current_बारtamp - Return IP network बारtamp
 *
 * Return milliseconds since midnight in network byte order.
 */
__be32 inet_current_बारtamp(व्योम)
अणु
	u32 secs;
	u32 msecs;
	काष्ठा बारpec64 ts;

	kसमय_get_real_ts64(&ts);

	/* Get secs since midnight. */
	(व्योम)भाग_u64_rem(ts.tv_sec, SECONDS_PER_DAY, &secs);
	/* Convert to msecs. */
	msecs = secs * MSEC_PER_SEC;
	/* Convert nsec to msec. */
	msecs += (u32)ts.tv_nsec / NSEC_PER_MSEC;

	/* Convert to network byte order. */
	वापस htonl(msecs);
पूर्ण
EXPORT_SYMBOL(inet_current_बारtamp);

पूर्णांक inet_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक *addr_len)
अणु
	अगर (sk->sk_family == AF_INET)
		वापस ip_recv_error(sk, msg, len, addr_len);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस pingv6_ops.ipv6_recv_error(sk, msg, len, addr_len);
#पूर्ण_अगर
	वापस -EINVAL;
पूर्ण

पूर्णांक inet_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	__be16 newlen = htons(skb->len - nhoff);
	काष्ठा iphdr *iph = (काष्ठा iphdr *)(skb->data + nhoff);
	स्थिर काष्ठा net_offload *ops;
	पूर्णांक proto = iph->protocol;
	पूर्णांक err = -ENOSYS;

	अगर (skb->encapsulation) अणु
		skb_set_inner_protocol(skb, cpu_to_be16(ETH_P_IP));
		skb_set_inner_network_header(skb, nhoff);
	पूर्ण

	csum_replace2(&iph->check, iph->tot_len, newlen);
	iph->tot_len = newlen;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(inet_offloads[proto]);
	अगर (WARN_ON(!ops || !ops->callbacks.gro_complete))
		जाओ out_unlock;

	/* Only need to add माप(*iph) to get to the next hdr below
	 * because any hdr with option will have been flushed in
	 * inet_gro_receive().
	 */
	err = INसूचीECT_CALL_2(ops->callbacks.gro_complete,
			      tcp4_gro_complete, udp4_gro_complete,
			      skb, nhoff + माप(*iph));

out_unlock:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक ipip_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP4;
	वापस inet_gro_complete(skb, nhoff);
पूर्ण

पूर्णांक inet_ctl_sock_create(काष्ठा sock **sk, अचिन्हित लघु family,
			 अचिन्हित लघु type, अचिन्हित अक्षर protocol,
			 काष्ठा net *net)
अणु
	काष्ठा socket *sock;
	पूर्णांक rc = sock_create_kern(net, family, type, protocol, &sock);

	अगर (rc == 0) अणु
		*sk = sock->sk;
		(*sk)->sk_allocation = GFP_ATOMIC;
		/*
		 * Unhash it so that IP input processing करोes not even see it,
		 * we करो not wish this socket to see incoming packets.
		 */
		(*sk)->sk_prot->unhash(*sk);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(inet_ctl_sock_create);

u64 snmp_get_cpu_field(व्योम __percpu *mib, पूर्णांक cpu, पूर्णांक offt)
अणु
	वापस  *(((अचिन्हित दीर्घ *)per_cpu_ptr(mib, cpu)) + offt);
पूर्ण
EXPORT_SYMBOL_GPL(snmp_get_cpu_field);

अचिन्हित दीर्घ snmp_fold_field(व्योम __percpu *mib, पूर्णांक offt)
अणु
	अचिन्हित दीर्घ res = 0;
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		res += snmp_get_cpu_field(mib, i, offt);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(snmp_fold_field);

#अगर BITS_PER_LONG==32

u64 snmp_get_cpu_field64(व्योम __percpu *mib, पूर्णांक cpu, पूर्णांक offt,
			 माप_प्रकार syncp_offset)
अणु
	व्योम *bhptr;
	काष्ठा u64_stats_sync *syncp;
	u64 v;
	अचिन्हित पूर्णांक start;

	bhptr = per_cpu_ptr(mib, cpu);
	syncp = (काष्ठा u64_stats_sync *)(bhptr + syncp_offset);
	करो अणु
		start = u64_stats_fetch_begin_irq(syncp);
		v = *(((u64 *)bhptr) + offt);
	पूर्ण जबतक (u64_stats_fetch_retry_irq(syncp, start));

	वापस v;
पूर्ण
EXPORT_SYMBOL_GPL(snmp_get_cpu_field64);

u64 snmp_fold_field64(व्योम __percpu *mib, पूर्णांक offt, माप_प्रकार syncp_offset)
अणु
	u64 res = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		res += snmp_get_cpu_field64(mib, cpu, offt, syncp_offset);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(snmp_fold_field64);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_MULTICAST
अटल स्थिर काष्ठा net_protocol igmp_protocol = अणु
	.handler =	igmp_rcv,
	.netns_ok =	1,
पूर्ण;
#पूर्ण_अगर

/* thinking of making this स्थिर? Don't.
 * early_demux can change based on sysctl.
 */
अटल काष्ठा net_protocol tcp_protocol = अणु
	.early_demux	=	tcp_v4_early_demux,
	.early_demux_handler =  tcp_v4_early_demux,
	.handler	=	tcp_v4_rcv,
	.err_handler	=	tcp_v4_err,
	.no_policy	=	1,
	.netns_ok	=	1,
	.icmp_strict_tag_validation = 1,
पूर्ण;

/* thinking of making this स्थिर? Don't.
 * early_demux can change based on sysctl.
 */
अटल काष्ठा net_protocol udp_protocol = अणु
	.early_demux =	udp_v4_early_demux,
	.early_demux_handler =	udp_v4_early_demux,
	.handler =	udp_rcv,
	.err_handler =	udp_err,
	.no_policy =	1,
	.netns_ok =	1,
पूर्ण;

अटल स्थिर काष्ठा net_protocol icmp_protocol = अणु
	.handler =	icmp_rcv,
	.err_handler =	icmp_err,
	.no_policy =	1,
	.netns_ok =	1,
पूर्ण;

अटल __net_init पूर्णांक ipv4_mib_init_net(काष्ठा net *net)
अणु
	पूर्णांक i;

	net->mib.tcp_statistics = alloc_percpu(काष्ठा tcp_mib);
	अगर (!net->mib.tcp_statistics)
		जाओ err_tcp_mib;
	net->mib.ip_statistics = alloc_percpu(काष्ठा ipstats_mib);
	अगर (!net->mib.ip_statistics)
		जाओ err_ip_mib;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ipstats_mib *af_inet_stats;
		af_inet_stats = per_cpu_ptr(net->mib.ip_statistics, i);
		u64_stats_init(&af_inet_stats->syncp);
	पूर्ण

	net->mib.net_statistics = alloc_percpu(काष्ठा linux_mib);
	अगर (!net->mib.net_statistics)
		जाओ err_net_mib;
	net->mib.udp_statistics = alloc_percpu(काष्ठा udp_mib);
	अगर (!net->mib.udp_statistics)
		जाओ err_udp_mib;
	net->mib.udplite_statistics = alloc_percpu(काष्ठा udp_mib);
	अगर (!net->mib.udplite_statistics)
		जाओ err_udplite_mib;
	net->mib.icmp_statistics = alloc_percpu(काष्ठा icmp_mib);
	अगर (!net->mib.icmp_statistics)
		जाओ err_icmp_mib;
	net->mib.icmpmsg_statistics = kzalloc(माप(काष्ठा icmpmsg_mib),
					      GFP_KERNEL);
	अगर (!net->mib.icmpmsg_statistics)
		जाओ err_icmpmsg_mib;

	tcp_mib_init(net);
	वापस 0;

err_icmpmsg_mib:
	मुक्त_percpu(net->mib.icmp_statistics);
err_icmp_mib:
	मुक्त_percpu(net->mib.udplite_statistics);
err_udplite_mib:
	मुक्त_percpu(net->mib.udp_statistics);
err_udp_mib:
	मुक्त_percpu(net->mib.net_statistics);
err_net_mib:
	मुक्त_percpu(net->mib.ip_statistics);
err_ip_mib:
	मुक्त_percpu(net->mib.tcp_statistics);
err_tcp_mib:
	वापस -ENOMEM;
पूर्ण

अटल __net_निकास व्योम ipv4_mib_निकास_net(काष्ठा net *net)
अणु
	kमुक्त(net->mib.icmpmsg_statistics);
	मुक्त_percpu(net->mib.icmp_statistics);
	मुक्त_percpu(net->mib.udplite_statistics);
	मुक्त_percpu(net->mib.udp_statistics);
	मुक्त_percpu(net->mib.net_statistics);
	मुक्त_percpu(net->mib.ip_statistics);
	मुक्त_percpu(net->mib.tcp_statistics);
#अगर_घोषित CONFIG_MPTCP
	/* allocated on demand, see mptcp_init_sock() */
	मुक्त_percpu(net->mib.mptcp_statistics);
#पूर्ण_अगर
पूर्ण

अटल __net_initdata काष्ठा pernet_operations ipv4_mib_ops = अणु
	.init = ipv4_mib_init_net,
	.निकास = ipv4_mib_निकास_net,
पूर्ण;

अटल पूर्णांक __init init_ipv4_mibs(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ipv4_mib_ops);
पूर्ण

अटल __net_init पूर्णांक inet_init_net(काष्ठा net *net)
अणु
	/*
	 * Set शेषs क्रम local port range
	 */
	seqlock_init(&net->ipv4.ip_local_ports.lock);
	net->ipv4.ip_local_ports.range[0] =  32768;
	net->ipv4.ip_local_ports.range[1] =  60999;

	seqlock_init(&net->ipv4.ping_group_range.lock);
	/*
	 * Sane शेषs - nobody may create ping sockets.
	 * Boot scripts should set this to distro-specअगरic group.
	 */
	net->ipv4.ping_group_range.range[0] = make_kgid(&init_user_ns, 1);
	net->ipv4.ping_group_range.range[1] = make_kgid(&init_user_ns, 0);

	/* Default values क्रम sysctl-controlled parameters.
	 * We set them here, in हाल sysctl is not compiled.
	 */
	net->ipv4.sysctl_ip_शेष_ttl = IPDEFTTL;
	net->ipv4.sysctl_ip_fwd_update_priority = 1;
	net->ipv4.sysctl_ip_dynaddr = 0;
	net->ipv4.sysctl_ip_early_demux = 1;
	net->ipv4.sysctl_udp_early_demux = 1;
	net->ipv4.sysctl_tcp_early_demux = 1;
	net->ipv4.sysctl_nexthop_compat_mode = 1;
#अगर_घोषित CONFIG_SYSCTL
	net->ipv4.sysctl_ip_prot_sock = PROT_SOCK;
#पूर्ण_अगर

	/* Some igmp sysctl, whose values are always used */
	net->ipv4.sysctl_igmp_max_memberships = 20;
	net->ipv4.sysctl_igmp_max_msf = 10;
	/* IGMP reports क्रम link-local multicast groups are enabled by शेष */
	net->ipv4.sysctl_igmp_llm_reports = 1;
	net->ipv4.sysctl_igmp_qrv = 2;

	net->ipv4.sysctl_fib_notअगरy_on_flag_change = 0;

	वापस 0;
पूर्ण

अटल __net_initdata काष्ठा pernet_operations af_inet_ops = अणु
	.init = inet_init_net,
पूर्ण;

अटल पूर्णांक __init init_inet_pernet_ops(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&af_inet_ops);
पूर्ण

अटल पूर्णांक ipv4_proc_init(व्योम);

/*
 *	IP protocol layer initialiser
 */

अटल काष्ठा packet_offload ip_packet_offload __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_IP),
	.callbacks = अणु
		.gso_segment = inet_gso_segment,
		.gro_receive = inet_gro_receive,
		.gro_complete = inet_gro_complete,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा net_offload ipip_offload = अणु
	.callbacks = अणु
		.gso_segment	= ipip_gso_segment,
		.gro_receive	= ipip_gro_receive,
		.gro_complete	= ipip_gro_complete,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ipip_offload_init(व्योम)
अणु
	वापस inet_add_offload(&ipip_offload, IPPROTO_IPIP);
पूर्ण

अटल पूर्णांक __init ipv4_offload_init(व्योम)
अणु
	/*
	 * Add offloads
	 */
	अगर (udpv4_offload_init() < 0)
		pr_crit("%s: Cannot add UDP protocol offload\n", __func__);
	अगर (tcpv4_offload_init() < 0)
		pr_crit("%s: Cannot add TCP protocol offload\n", __func__);
	अगर (ipip_offload_init() < 0)
		pr_crit("%s: Cannot add IPIP protocol offload\n", __func__);

	dev_add_offload(&ip_packet_offload);
	वापस 0;
पूर्ण

fs_initcall(ipv4_offload_init);

अटल काष्ठा packet_type ip_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_IP),
	.func = ip_rcv,
	.list_func = ip_list_rcv,
पूर्ण;

अटल पूर्णांक __init inet_init(व्योम)
अणु
	काष्ठा inet_protosw *q;
	काष्ठा list_head *r;
	पूर्णांक rc;

	sock_skb_cb_check_size(माप(काष्ठा inet_skb_parm));

	rc = proto_रेजिस्टर(&tcp_prot, 1);
	अगर (rc)
		जाओ out;

	rc = proto_रेजिस्टर(&udp_prot, 1);
	अगर (rc)
		जाओ out_unरेजिस्टर_tcp_proto;

	rc = proto_रेजिस्टर(&raw_prot, 1);
	अगर (rc)
		जाओ out_unरेजिस्टर_udp_proto;

	rc = proto_रेजिस्टर(&ping_prot, 1);
	अगर (rc)
		जाओ out_unरेजिस्टर_raw_proto;

	/*
	 *	Tell SOCKET that we are alive...
	 */

	(व्योम)sock_रेजिस्टर(&inet_family_ops);

#अगर_घोषित CONFIG_SYSCTL
	ip_अटल_sysctl_init();
#पूर्ण_अगर

	/*
	 *	Add all the base protocols.
	 */

	अगर (inet_add_protocol(&icmp_protocol, IPPROTO_ICMP) < 0)
		pr_crit("%s: Cannot add ICMP protocol\n", __func__);
	अगर (inet_add_protocol(&udp_protocol, IPPROTO_UDP) < 0)
		pr_crit("%s: Cannot add UDP protocol\n", __func__);
	अगर (inet_add_protocol(&tcp_protocol, IPPROTO_TCP) < 0)
		pr_crit("%s: Cannot add TCP protocol\n", __func__);
#अगर_घोषित CONFIG_IP_MULTICAST
	अगर (inet_add_protocol(&igmp_protocol, IPPROTO_IGMP) < 0)
		pr_crit("%s: Cannot add IGMP protocol\n", __func__);
#पूर्ण_अगर

	/* Register the socket-side inक्रमmation क्रम inet_create. */
	क्रम (r = &inetsw[0]; r < &inetsw[SOCK_MAX]; ++r)
		INIT_LIST_HEAD(r);

	क्रम (q = inetsw_array; q < &inetsw_array[INETSW_ARRAY_LEN]; ++q)
		inet_रेजिस्टर_protosw(q);

	/*
	 *	Set the ARP module up
	 */

	arp_init();

	/*
	 *	Set the IP module up
	 */

	ip_init();

	/* Setup TCP slab cache क्रम खोलो requests. */
	tcp_init();

	/* Setup UDP memory threshold */
	udp_init();

	/* Add UDP-Lite (RFC 3828) */
	udplite4_रेजिस्टर();

	raw_init();

	ping_init();

	/*
	 *	Set the ICMP layer up
	 */

	अगर (icmp_init() < 0)
		panic("Failed to create the ICMP control socket.\n");

	/*
	 *	Initialise the multicast router
	 */
#अगर defined(CONFIG_IP_MROUTE)
	अगर (ip_mr_init())
		pr_crit("%s: Cannot init ipv4 mroute\n", __func__);
#पूर्ण_अगर

	अगर (init_inet_pernet_ops())
		pr_crit("%s: Cannot init ipv4 inet pernet ops\n", __func__);
	/*
	 *	Initialise per-cpu ipv4 mibs
	 */

	अगर (init_ipv4_mibs())
		pr_crit("%s: Cannot init ipv4 mibs\n", __func__);

	ipv4_proc_init();

	ipfrag_init();

	dev_add_pack(&ip_packet_type);

	ip_tunnel_core_init();

	rc = 0;
out:
	वापस rc;
out_unरेजिस्टर_raw_proto:
	proto_unरेजिस्टर(&raw_prot);
out_unरेजिस्टर_udp_proto:
	proto_unरेजिस्टर(&udp_prot);
out_unरेजिस्टर_tcp_proto:
	proto_unरेजिस्टर(&tcp_prot);
	जाओ out;
पूर्ण

fs_initcall(inet_init);

/* ------------------------------------------------------------------------ */

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक __init ipv4_proc_init(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (raw_proc_init())
		जाओ out_raw;
	अगर (tcp4_proc_init())
		जाओ out_tcp;
	अगर (udp4_proc_init())
		जाओ out_udp;
	अगर (ping_proc_init())
		जाओ out_ping;
	अगर (ip_misc_proc_init())
		जाओ out_misc;
out:
	वापस rc;
out_misc:
	ping_proc_निकास();
out_ping:
	udp4_proc_निकास();
out_udp:
	tcp4_proc_निकास();
out_tcp:
	raw_proc_निकास();
out_raw:
	rc = -ENOMEM;
	जाओ out;
पूर्ण

#अन्यथा /* CONFIG_PROC_FS */
अटल पूर्णांक __init ipv4_proc_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */
