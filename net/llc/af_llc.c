<शैली गुरु>
/*
 * af_llc.c - LLC User Interface SAPs
 * Description:
 *   Functions in this module are implementation of socket based llc
 *   communications क्रम the Linux operating प्रणाली. Support of llc class
 *   one and class two is provided via SOCK_DGRAM and SOCK_STREAM
 *   respectively.
 *
 *   An llc2 connection is (mac + sap), only one llc2 sap connection
 *   is allowed per mac. Though one sap may have multiple mac + sap
 *   connections.
 *
 * Copyright (c) 2001 by Jay Schulist <jschlst@samba.org>
 *		 2002-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/llc.h>
#समावेश <net/llc_sap.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/llc_conn.h>
#समावेश <net/tcp_states.h>

/* remember: uninitialized global data is zeroed because its in .bss */
अटल u16 llc_ui_sap_last_स्वतःport = LLC_SAP_DYN_START;
अटल u16 llc_ui_sap_link_no_max[256];
अटल काष्ठा sockaddr_llc llc_ui_addrnull;
अटल स्थिर काष्ठा proto_ops llc_ui_ops;

अटल bool llc_ui_रुको_क्रम_conn(काष्ठा sock *sk, दीर्घ समयout);
अटल पूर्णांक llc_ui_रुको_क्रम_disc(काष्ठा sock *sk, दीर्घ समयout);
अटल पूर्णांक llc_ui_रुको_क्रम_busy_core(काष्ठा sock *sk, दीर्घ समयout);

#अगर 0
#घोषणा dprपूर्णांकk(args...) prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
#घोषणा dprपूर्णांकk(args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* Maybe we'll add some more in the future. */
#घोषणा LLC_CMSG_PKTINFO	1


/**
 *	llc_ui_next_link_no - वापस the next unused link number क्रम a sap
 *	@sap: Address of sap to get link number from.
 *
 *	Return the next unused link number क्रम a given sap.
 */
अटल अंतरभूत u16 llc_ui_next_link_no(पूर्णांक sap)
अणु
	वापस llc_ui_sap_link_no_max[sap]++;
पूर्ण

/**
 *	llc_proto_type - वापस eth protocol क्रम ARP header type
 *	@arphrd: ARP header type.
 *
 *	Given an ARP header type वापस the corresponding ethernet protocol.
 */
अटल अंतरभूत __be16 llc_proto_type(u16 arphrd)
अणु
	वापस htons(ETH_P_802_2);
पूर्ण

/**
 *	llc_ui_addr_null - determines अगर a address काष्ठाure is null
 *	@addr: Address to test अगर null.
 */
अटल अंतरभूत u8 llc_ui_addr_null(काष्ठा sockaddr_llc *addr)
अणु
	वापस !स_भेद(addr, &llc_ui_addrnull, माप(*addr));
पूर्ण

/**
 *	llc_ui_header_len - वापस length of llc header based on operation
 *	@sk: Socket which contains a valid llc socket type.
 *	@addr: Complete sockaddr_llc काष्ठाure received from the user.
 *
 *	Provide the length of the llc header depending on what kind of
 *	operation the user would like to perक्रमm and the type of socket.
 *	Returns the correct llc header length.
 */
अटल अंतरभूत u8 llc_ui_header_len(काष्ठा sock *sk, काष्ठा sockaddr_llc *addr)
अणु
	u8 rc = LLC_PDU_LEN_U;

	अगर (addr->sllc_test || addr->sllc_xid)
		rc = LLC_PDU_LEN_U;
	अन्यथा अगर (sk->sk_type == SOCK_STREAM)
		rc = LLC_PDU_LEN_I;
	वापस rc;
पूर्ण

/**
 *	llc_ui_send_data - send data via reliable llc2 connection
 *	@sk: Connection the socket is using.
 *	@skb: Data the user wishes to send.
 *	@noblock: can we block रुकोing क्रम data?
 *
 *	Send data via reliable llc2 connection.
 *	Returns 0 upon success, non-zero अगर action did not succeed.
 *
 *	This function always consumes a reference to the skb.
 */
अटल पूर्णांक llc_ui_send_data(काष्ठा sock* sk, काष्ठा sk_buff *skb, पूर्णांक noblock)
अणु
	काष्ठा llc_sock* llc = llc_sk(sk);

	अगर (unlikely(llc_data_accept_state(llc->state) ||
		     llc->remote_busy_flag ||
		     llc->p_flag)) अणु
		दीर्घ समयout = sock_sndसमयo(sk, noblock);
		पूर्णांक rc;

		rc = llc_ui_रुको_क्रम_busy_core(sk, समयout);
		अगर (rc) अणु
			kमुक्त_skb(skb);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस llc_build_and_send_pkt(sk, skb);
पूर्ण

अटल व्योम llc_ui_sk_init(काष्ठा socket *sock, काष्ठा sock *sk)
अणु
	sock_graft(sk, sock);
	sk->sk_type	= sock->type;
	sock->ops	= &llc_ui_ops;
पूर्ण

अटल काष्ठा proto llc_proto = अणु
	.name	  = "LLC",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा llc_sock),
	.slab_flags = SLAB_TYPESAFE_BY_RCU,
पूर्ण;

/**
 *	llc_ui_create - alloc and init a new llc_ui socket
 *	@net: network namespace (must be शेष network)
 *	@sock: Socket to initialize and attach allocated sk to.
 *	@protocol: Unused.
 *	@kern: on behalf of kernel or userspace
 *
 *	Allocate and initialize a new llc_ui socket, validate the user wants a
 *	socket type we have available.
 *	Returns 0 upon success, negative upon failure.
 */
अटल पूर्णांक llc_ui_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			 पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	पूर्णांक rc = -ESOCKTNOSUPPORT;

	अगर (!ns_capable(net->user_ns, CAP_NET_RAW))
		वापस -EPERM;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	अगर (likely(sock->type == SOCK_DGRAM || sock->type == SOCK_STREAM)) अणु
		rc = -ENOMEM;
		sk = llc_sk_alloc(net, PF_LLC, GFP_KERNEL, &llc_proto, kern);
		अगर (sk) अणु
			rc = 0;
			llc_ui_sk_init(sock, sk);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	llc_ui_release - shutकरोwn socket
 *	@sock: Socket to release.
 *
 *	Shutकरोwn and deallocate an existing socket.
 */
अटल पूर्णांक llc_ui_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc;

	अगर (unlikely(sk == शून्य))
		जाओ out;
	sock_hold(sk);
	lock_sock(sk);
	llc = llc_sk(sk);
	dprपूर्णांकk("%s: closing local(%02X) remote(%02X)\n", __func__,
		llc->laddr.lsap, llc->daddr.lsap);
	अगर (!llc_send_disc(sk))
		llc_ui_रुको_क्रम_disc(sk, sk->sk_rcvसमयo);
	अगर (!sock_flag(sk, SOCK_ZAPPED)) अणु
		काष्ठा llc_sap *sap = llc->sap;

		/* Hold this क्रम release_sock(), so that llc_backlog_rcv()
		 * could still use it.
		 */
		llc_sap_hold(sap);
		llc_sap_हटाओ_socket(llc->sap, sk);
		release_sock(sk);
		llc_sap_put(sap);
	पूर्ण अन्यथा अणु
		release_sock(sk);
	पूर्ण
	अगर (llc->dev)
		dev_put(llc->dev);
	sock_put(sk);
	llc_sk_मुक्त(sk);
out:
	वापस 0;
पूर्ण

/**
 *	llc_ui_स्वतःport - provide dynamically allocate SAP number
 *
 *	Provide the caller with a dynamically allocated SAP number according
 *	to the rules that are set in this function. Returns: 0, upon failure,
 *	SAP number otherwise.
 */
अटल पूर्णांक llc_ui_स्वतःport(व्योम)
अणु
	काष्ठा llc_sap *sap;
	पूर्णांक i, tries = 0;

	जबतक (tries < LLC_SAP_DYN_TRIES) अणु
		क्रम (i = llc_ui_sap_last_स्वतःport;
		     i < LLC_SAP_DYN_STOP; i += 2) अणु
			sap = llc_sap_find(i);
			अगर (!sap) अणु
				llc_ui_sap_last_स्वतःport = i + 2;
				जाओ out;
			पूर्ण
			llc_sap_put(sap);
		पूर्ण
		llc_ui_sap_last_स्वतःport = LLC_SAP_DYN_START;
		tries++;
	पूर्ण
	i = 0;
out:
	वापस i;
पूर्ण

/**
 *	llc_ui_स्वतःbind - स्वतःmatically bind a socket to a sap
 *	@sock: socket to bind
 *	@addr: address to connect to
 *
 * 	Used by llc_ui_connect and llc_ui_sendmsg when the user hasn't
 * 	specअगरically used llc_ui_bind to bind to an specअगरic address/sap
 *
 *	Returns: 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_स्वतःbind(काष्ठा socket *sock, काष्ठा sockaddr_llc *addr)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap;
	पूर्णांक rc = -EINVAL;

	अगर (!sock_flag(sk, SOCK_ZAPPED))
		जाओ out;
	अगर (!addr->sllc_arphrd)
		addr->sllc_arphrd = ARPHRD_ETHER;
	अगर (addr->sllc_arphrd != ARPHRD_ETHER)
		जाओ out;
	rc = -ENODEV;
	अगर (sk->sk_bound_dev_अगर) अणु
		llc->dev = dev_get_by_index(&init_net, sk->sk_bound_dev_अगर);
		अगर (llc->dev && addr->sllc_arphrd != llc->dev->type) अणु
			dev_put(llc->dev);
			llc->dev = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		llc->dev = dev_getfirstbyhwtype(&init_net, addr->sllc_arphrd);
	अगर (!llc->dev)
		जाओ out;
	rc = -EUSERS;
	llc->laddr.lsap = llc_ui_स्वतःport();
	अगर (!llc->laddr.lsap)
		जाओ out;
	rc = -EBUSY; /* some other network layer is using the sap */
	sap = llc_sap_खोलो(llc->laddr.lsap, शून्य);
	अगर (!sap)
		जाओ out;
	स_नकल(llc->laddr.mac, llc->dev->dev_addr, IFHWADDRLEN);
	स_नकल(&llc->addr, addr, माप(llc->addr));
	/* assign new connection to its SAP */
	llc_sap_add_socket(sap, sk);
	sock_reset_flag(sk, SOCK_ZAPPED);
	rc = 0;
out:
	वापस rc;
पूर्ण

/**
 *	llc_ui_bind - bind a socket to a specअगरic address.
 *	@sock: Socket to bind an address to.
 *	@uaddr: Address the user wants the socket bound to.
 *	@addrlen: Length of the uaddr काष्ठाure.
 *
 *	Bind a socket to a specअगरic address. For llc a user is able to bind to
 *	a specअगरic sap only or mac + sap.
 *	If the user desires to bind to a specअगरic mac + sap, it is possible to
 *	have multiple sap connections via multiple macs.
 *	Bind and स्वतःbind क्रम that matter must enक्रमce the correct sap usage
 *	otherwise all hell will अवरोध loose.
 *	Returns: 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addrlen)
अणु
	काष्ठा sockaddr_llc *addr = (काष्ठा sockaddr_llc *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा llc_sap *sap;
	पूर्णांक rc = -EINVAL;

	lock_sock(sk);
	अगर (unlikely(!sock_flag(sk, SOCK_ZAPPED) || addrlen != माप(*addr)))
		जाओ out;
	rc = -EAFNOSUPPORT;
	अगर (!addr->sllc_arphrd)
		addr->sllc_arphrd = ARPHRD_ETHER;
	अगर (unlikely(addr->sllc_family != AF_LLC || addr->sllc_arphrd != ARPHRD_ETHER))
		जाओ out;
	dprपूर्णांकk("%s: binding %02X\n", __func__, addr->sllc_sap);
	rc = -ENODEV;
	rcu_पढ़ो_lock();
	अगर (sk->sk_bound_dev_अगर) अणु
		llc->dev = dev_get_by_index_rcu(&init_net, sk->sk_bound_dev_अगर);
		अगर (llc->dev) अणु
			अगर (is_zero_ether_addr(addr->sllc_mac))
				स_नकल(addr->sllc_mac, llc->dev->dev_addr,
				       IFHWADDRLEN);
			अगर (addr->sllc_arphrd != llc->dev->type ||
			    !ether_addr_equal(addr->sllc_mac,
					      llc->dev->dev_addr)) अणु
				rc = -EINVAL;
				llc->dev = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		llc->dev = dev_getbyhwaddr_rcu(&init_net, addr->sllc_arphrd,
					   addr->sllc_mac);
	अगर (llc->dev)
		dev_hold(llc->dev);
	rcu_पढ़ो_unlock();
	अगर (!llc->dev)
		जाओ out;
	अगर (!addr->sllc_sap) अणु
		rc = -EUSERS;
		addr->sllc_sap = llc_ui_स्वतःport();
		अगर (!addr->sllc_sap)
			जाओ out;
	पूर्ण
	sap = llc_sap_find(addr->sllc_sap);
	अगर (!sap) अणु
		sap = llc_sap_खोलो(addr->sllc_sap, शून्य);
		rc = -EBUSY; /* some other network layer is using the sap */
		अगर (!sap)
			जाओ out;
	पूर्ण अन्यथा अणु
		काष्ठा llc_addr laddr, daddr;
		काष्ठा sock *ask;

		स_रखो(&laddr, 0, माप(laddr));
		स_रखो(&daddr, 0, माप(daddr));
		/*
		 * FIXME: check अगर the address is multicast,
		 * 	  only SOCK_DGRAM can करो this.
		 */
		स_नकल(laddr.mac, addr->sllc_mac, IFHWADDRLEN);
		laddr.lsap = addr->sllc_sap;
		rc = -EADDRINUSE; /* mac + sap clash. */
		ask = llc_lookup_established(sap, &daddr, &laddr);
		अगर (ask) अणु
			sock_put(ask);
			जाओ out_put;
		पूर्ण
	पूर्ण
	llc->laddr.lsap = addr->sllc_sap;
	स_नकल(llc->laddr.mac, addr->sllc_mac, IFHWADDRLEN);
	स_नकल(&llc->addr, addr, माप(llc->addr));
	/* assign new connection to its SAP */
	llc_sap_add_socket(sap, sk);
	sock_reset_flag(sk, SOCK_ZAPPED);
	rc = 0;
out_put:
	llc_sap_put(sap);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/**
 *	llc_ui_shutकरोwn - shutकरोwn a connect llc2 socket.
 *	@sock: Socket to shutकरोwn.
 *	@how: What part of the socket to shutकरोwn.
 *
 *	Shutकरोwn a connected llc2 socket. Currently this function only supports
 *	shutting करोwn both sends and receives (2), we could probably make this
 *	function such that a user can shutकरोwn only half the connection but not
 *	right now.
 *	Returns: 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc = -ENOTCONN;

	lock_sock(sk);
	अगर (unlikely(sk->sk_state != TCP_ESTABLISHED))
		जाओ out;
	rc = -EINVAL;
	अगर (how != 2)
		जाओ out;
	rc = llc_send_disc(sk);
	अगर (!rc)
		rc = llc_ui_रुको_क्रम_disc(sk, sk->sk_rcvसमयo);
	/* Wake up anyone sleeping in poll */
	sk->sk_state_change(sk);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/**
 *	llc_ui_connect - Connect to a remote llc2 mac + sap.
 *	@sock: Socket which will be connected to the remote destination.
 *	@uaddr: Remote and possibly the local address of the new connection.
 *	@addrlen: Size of uaddr काष्ठाure.
 *	@flags: Operational flags specअगरied by the user.
 *
 *	Connect to a remote llc2 mac + sap. The caller must specअगरy the
 *	destination mac and address to connect to. If the user hasn't previously
 *	called bind(2) with a smac the address of the first पूर्णांकerface of the
 *	specअगरied arp type will be used.
 *	This function will स्वतःbind अगर user did not previously call bind.
 *	Returns: 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			  पूर्णांक addrlen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	काष्ठा sockaddr_llc *addr = (काष्ठा sockaddr_llc *)uaddr;
	पूर्णांक rc = -EINVAL;

	lock_sock(sk);
	अगर (unlikely(addrlen != माप(*addr)))
		जाओ out;
	rc = -EAFNOSUPPORT;
	अगर (unlikely(addr->sllc_family != AF_LLC))
		जाओ out;
	अगर (unlikely(sk->sk_type != SOCK_STREAM))
		जाओ out;
	rc = -EALREADY;
	अगर (unlikely(sock->state == SS_CONNECTING))
		जाओ out;
	/* bind connection to sap अगर user hasn't करोne it. */
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		/* bind to sap with null dev, exclusive */
		rc = llc_ui_स्वतःbind(sock, addr);
		अगर (rc)
			जाओ out;
	पूर्ण
	llc->daddr.lsap = addr->sllc_sap;
	स_नकल(llc->daddr.mac, addr->sllc_mac, IFHWADDRLEN);
	sock->state = SS_CONNECTING;
	sk->sk_state   = TCP_SYN_SENT;
	llc->link   = llc_ui_next_link_no(llc->sap->laddr.lsap);
	rc = llc_establish_connection(sk, llc->dev->dev_addr,
				      addr->sllc_mac, addr->sllc_sap);
	अगर (rc) अणु
		dprपूर्णांकk("%s: llc_ui_send_conn failed :-(\n", __func__);
		sock->state  = SS_UNCONNECTED;
		sk->sk_state = TCP_CLOSE;
		जाओ out;
	पूर्ण

	अगर (sk->sk_state == TCP_SYN_SENT) अणु
		स्थिर दीर्घ समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

		अगर (!समयo || !llc_ui_रुको_क्रम_conn(sk, समयo))
			जाओ out;

		rc = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			जाओ out;
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE)
		जाओ sock_error;

	sock->state = SS_CONNECTED;
	rc = 0;
out:
	release_sock(sk);
	वापस rc;
sock_error:
	rc = sock_error(sk) ? : -ECONNABORTED;
	sock->state = SS_UNCONNECTED;
	जाओ out;
पूर्ण

/**
 *	llc_ui_listen - allow a normal socket to accept incoming connections
 *	@sock: Socket to allow incoming connections on.
 *	@backlog: Number of connections to queue.
 *
 *	Allow a normal socket to accept incoming connections.
 *	Returns 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc = -EINVAL;

	lock_sock(sk);
	अगर (unlikely(sock->state != SS_UNCONNECTED))
		जाओ out;
	rc = -EOPNOTSUPP;
	अगर (unlikely(sk->sk_type != SOCK_STREAM))
		जाओ out;
	rc = -EAGAIN;
	अगर (sock_flag(sk, SOCK_ZAPPED))
		जाओ out;
	rc = 0;
	अगर (!(अचिन्हित पूर्णांक)backlog)	/* BSDism */
		backlog = 1;
	sk->sk_max_ack_backlog = backlog;
	अगर (sk->sk_state != TCP_LISTEN) अणु
		sk->sk_ack_backlog = 0;
		sk->sk_state	   = TCP_LISTEN;
	पूर्ण
	sk->sk_socket->flags |= __SO_ACCEPTCON;
out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल पूर्णांक llc_ui_रुको_क्रम_disc(काष्ठा sock *sk, दीर्घ समयout)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक rc = 0;

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (sk_रुको_event(sk, &समयout, sk->sk_state == TCP_CLOSE, &रुको))
			अवरोध;
		rc = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		rc = -EAGAIN;
		अगर (!समयout)
			अवरोध;
		rc = 0;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

अटल bool llc_ui_रुको_क्रम_conn(काष्ठा sock *sk, दीर्घ समयout)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (sk_रुको_event(sk, &समयout, sk->sk_state != TCP_SYN_SENT, &रुको))
			अवरोध;
		अगर (संकेत_pending(current) || !समयout)
			अवरोध;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस समयout;
पूर्ण

अटल पूर्णांक llc_ui_रुको_क्रम_busy_core(काष्ठा sock *sk, दीर्घ समयout)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक rc;

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		rc = 0;
		अगर (sk_रुको_event(sk, &समयout,
				  (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
				  (!llc_data_accept_state(llc->state) &&
				   !llc->remote_busy_flag &&
				   !llc->p_flag), &रुको))
			अवरोध;
		rc = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		rc = -EAGAIN;
		अगर (!समयout)
			अवरोध;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

अटल पूर्णांक llc_रुको_data(काष्ठा sock *sk, दीर्घ समयo)
अणु
	पूर्णांक rc;

	जबतक (1) अणु
		/*
		 * POSIX 1003.1g mandates this order.
		 */
		rc = sock_error(sk);
		अगर (rc)
			अवरोध;
		rc = 0;
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			अवरोध;
		rc = -EAGAIN;
		अगर (!समयo)
			अवरोध;
		rc = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			अवरोध;
		rc = 0;
		अगर (sk_रुको_data(sk, &समयo, शून्य))
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम llc_cmsg_rcv(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_sock *llc = llc_sk(skb->sk);

	अगर (llc->cmsg_flags & LLC_CMSG_PKTINFO) अणु
		काष्ठा llc_pktinfo info;

		स_रखो(&info, 0, माप(info));
		info.lpi_अगरindex = llc_sk(skb->sk)->dev->अगरindex;
		llc_pdu_decode_dsap(skb, &info.lpi_sap);
		llc_pdu_decode_da(skb, info.lpi_mac);
		put_cmsg(msg, SOL_LLC, LLC_OPT_PKTINFO, माप(info), &info);
	पूर्ण
पूर्ण

/**
 *	llc_ui_accept - accept a new incoming connection.
 *	@sock: Socket which connections arrive on.
 *	@newsock: Socket to move incoming connection to.
 *	@flags: User specअगरied operational flags.
 *	@kern: If the socket is kernel पूर्णांकernal
 *
 *	Accept a new incoming connection.
 *	Returns 0 upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
			 bool kern)
अणु
	काष्ठा sock *sk = sock->sk, *newsk;
	काष्ठा llc_sock *llc, *newllc;
	काष्ठा sk_buff *skb;
	पूर्णांक rc = -EOPNOTSUPP;

	dprपूर्णांकk("%s: accepting on %02X\n", __func__,
		llc_sk(sk)->laddr.lsap);
	lock_sock(sk);
	अगर (unlikely(sk->sk_type != SOCK_STREAM))
		जाओ out;
	rc = -EINVAL;
	अगर (unlikely(sock->state != SS_UNCONNECTED ||
		     sk->sk_state != TCP_LISTEN))
		जाओ out;
	/* रुको क्रम a connection to arrive. */
	अगर (skb_queue_empty(&sk->sk_receive_queue)) अणु
		rc = llc_रुको_data(sk, sk->sk_rcvसमयo);
		अगर (rc)
			जाओ out;
	पूर्ण
	dprपूर्णांकk("%s: got a new connection on %02X\n", __func__,
		llc_sk(sk)->laddr.lsap);
	skb = skb_dequeue(&sk->sk_receive_queue);
	rc = -EINVAL;
	अगर (!skb->sk)
		जाओ मुक्तs;
	rc = 0;
	newsk = skb->sk;
	/* attach connection to a new socket. */
	llc_ui_sk_init(newsock, newsk);
	sock_reset_flag(newsk, SOCK_ZAPPED);
	newsk->sk_state		= TCP_ESTABLISHED;
	newsock->state		= SS_CONNECTED;
	llc			= llc_sk(sk);
	newllc			= llc_sk(newsk);
	स_नकल(&newllc->addr, &llc->addr, माप(newllc->addr));
	newllc->link = llc_ui_next_link_no(newllc->laddr.lsap);

	/* put original socket back पूर्णांकo a clean listen state. */
	sk->sk_state = TCP_LISTEN;
	sk_acceptq_हटाओd(sk);
	dprपूर्णांकk("%s: ok success on %02X, client on %02X\n", __func__,
		llc_sk(sk)->addr.sllc_sap, newllc->daddr.lsap);
मुक्तs:
	kमुक्त_skb(skb);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/**
 *	llc_ui_recvmsg - copy received data to the socket user.
 *	@sock: Socket to copy data from.
 *	@msg: Various user space related inक्रमmation.
 *	@len: Size of user buffer.
 *	@flags: User specअगरied flags.
 *
 *	Copy received data to the socket user.
 *	Returns non-negative upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			  पूर्णांक flags)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_llc *, uaddr, msg->msg_name);
	स्थिर पूर्णांक nonblock = flags & MSG_DONTWAIT;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	माप_प्रकार copied = 0;
	u32 peek_seq = 0;
	u32 *seq, skb_len;
	अचिन्हित दीर्घ used;
	पूर्णांक target;	/* Read at least this many bytes */
	दीर्घ समयo;

	lock_sock(sk);
	copied = -ENOTCONN;
	अगर (unlikely(sk->sk_type == SOCK_STREAM && sk->sk_state == TCP_LISTEN))
		जाओ out;

	समयo = sock_rcvसमयo(sk, nonblock);

	seq = &llc->copied_seq;
	अगर (flags & MSG_PEEK) अणु
		peek_seq = llc->copied_seq;
		seq = &peek_seq;
	पूर्ण

	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);
	copied = 0;

	करो अणु
		u32 offset;

		/*
		 * We need to check संकेतs first, to get correct SIGURG
		 * handling. FIXME: Need to check this करोesn't impact 1003.1g
		 * and move it करोwn to the bottom of the loop
		 */
		अगर (संकेत_pending(current)) अणु
			अगर (copied)
				अवरोध;
			copied = समयo ? sock_पूर्णांकr_त्रुटि_सं(समयo) : -EAGAIN;
			अवरोध;
		पूर्ण

		/* Next get a buffer. */

		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb) अणु
			offset = *seq;
			जाओ found_ok_skb;
		पूर्ण
		/* Well, अगर we have backlog, try to process it now yet. */

		अगर (copied >= target && !READ_ONCE(sk->sk_backlog.tail))
			अवरोध;

		अगर (copied) अणु
			अगर (sk->sk_err ||
			    sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    !समयo ||
			    (flags & MSG_PEEK))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sock_flag(sk, SOCK_DONE))
				अवरोध;

			अगर (sk->sk_err) अणु
				copied = sock_error(sk);
				अवरोध;
			पूर्ण
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;

			अगर (sk->sk_type == SOCK_STREAM && sk->sk_state == TCP_CLOSE) अणु
				अगर (!sock_flag(sk, SOCK_DONE)) अणु
					/*
					 * This occurs when user tries to पढ़ो
					 * from never connected socket.
					 */
					copied = -ENOTCONN;
					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (!समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (copied >= target) अणु /* Do not sleep, just process backlog. */
			release_sock(sk);
			lock_sock(sk);
		पूर्ण अन्यथा
			sk_रुको_data(sk, &समयo, शून्य);

		अगर ((flags & MSG_PEEK) && peek_seq != llc->copied_seq) अणु
			net_dbg_ratelimited("LLC(%s:%d): Application bug, race in MSG_PEEK\n",
					    current->comm,
					    task_pid_nr(current));
			peek_seq = llc->copied_seq;
		पूर्ण
		जारी;
	found_ok_skb:
		skb_len = skb->len;
		/* Ok so how much can we use? */
		used = skb->len - offset;
		अगर (len < used)
			used = len;

		अगर (!(flags & MSG_TRUNC)) अणु
			पूर्णांक rc = skb_copy_datagram_msg(skb, offset, msg, used);
			अगर (rc) अणु
				/* Exception. Bailout! */
				अगर (!copied)
					copied = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण

		*seq += used;
		copied += used;
		len -= used;

		/* For non stream protcols we get one packet per recvmsg call */
		अगर (sk->sk_type != SOCK_STREAM)
			जाओ copy_uaddr;

		अगर (!(flags & MSG_PEEK)) अणु
			skb_unlink(skb, &sk->sk_receive_queue);
			kमुक्त_skb(skb);
			*seq = 0;
		पूर्ण

		/* Partial पढ़ो */
		अगर (used + offset < skb_len)
			जारी;
	पूर्ण जबतक (len > 0);

out:
	release_sock(sk);
	वापस copied;
copy_uaddr:
	अगर (uaddr != शून्य && skb != शून्य) अणु
		स_नकल(uaddr, llc_ui_skb_cb(skb), माप(*uaddr));
		msg->msg_namelen = माप(*uaddr);
	पूर्ण
	अगर (llc_sk(sk)->cmsg_flags)
		llc_cmsg_rcv(msg, skb);

	अगर (!(flags & MSG_PEEK)) अणु
		skb_unlink(skb, &sk->sk_receive_queue);
		kमुक्त_skb(skb);
		*seq = 0;
	पूर्ण

	जाओ out;
पूर्ण

/**
 *	llc_ui_sendmsg - Transmit data provided by the socket user.
 *	@sock: Socket to transmit data from.
 *	@msg: Various user related inक्रमmation.
 *	@len: Length of data to transmit.
 *
 *	Transmit data provided by the socket user.
 *	Returns non-negative upon success, negative otherwise.
 */
अटल पूर्णांक llc_ui_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_llc *, addr, msg->msg_name);
	पूर्णांक flags = msg->msg_flags;
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sk_buff *skb = शून्य;
	माप_प्रकार size = 0;
	पूर्णांक rc = -EINVAL, copied = 0, hdrlen;

	dprपूर्णांकk("%s: sending from %02X to %02X\n", __func__,
		llc->laddr.lsap, llc->daddr.lsap);
	lock_sock(sk);
	अगर (addr) अणु
		अगर (msg->msg_namelen < माप(*addr))
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (llc_ui_addr_null(&llc->addr))
			जाओ out;
		addr = &llc->addr;
	पूर्ण
	/* must bind connection to sap अगर user hasn't करोne it. */
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		/* bind to sap with null dev, exclusive. */
		rc = llc_ui_स्वतःbind(sock, addr);
		अगर (rc)
			जाओ out;
	पूर्ण
	hdrlen = llc->dev->hard_header_len + llc_ui_header_len(sk, addr);
	size = hdrlen + len;
	अगर (size > llc->dev->mtu)
		size = llc->dev->mtu;
	copied = size - hdrlen;
	rc = -EINVAL;
	अगर (copied < 0)
		जाओ out;
	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, noblock, &rc);
	lock_sock(sk);
	अगर (!skb)
		जाओ out;
	skb->dev      = llc->dev;
	skb->protocol = llc_proto_type(addr->sllc_arphrd);
	skb_reserve(skb, hdrlen);
	rc = स_नकल_from_msg(skb_put(skb, copied), msg, copied);
	अगर (rc)
		जाओ out;
	अगर (sk->sk_type == SOCK_DGRAM || addr->sllc_ua) अणु
		llc_build_and_send_ui_pkt(llc->sap, skb, addr->sllc_mac,
					  addr->sllc_sap);
		skb = शून्य;
		जाओ out;
	पूर्ण
	अगर (addr->sllc_test) अणु
		llc_build_and_send_test_pkt(llc->sap, skb, addr->sllc_mac,
					    addr->sllc_sap);
		skb = शून्य;
		जाओ out;
	पूर्ण
	अगर (addr->sllc_xid) अणु
		llc_build_and_send_xid_pkt(llc->sap, skb, addr->sllc_mac,
					   addr->sllc_sap);
		skb = शून्य;
		जाओ out;
	पूर्ण
	rc = -ENOPROTOOPT;
	अगर (!(sk->sk_type == SOCK_STREAM && !addr->sllc_ua))
		जाओ out;
	rc = llc_ui_send_data(sk, skb, noblock);
	skb = शून्य;
out:
	kमुक्त_skb(skb);
	अगर (rc)
		dprपूर्णांकk("%s: failed sending from %02X to %02X: %d\n",
			__func__, llc->laddr.lsap, llc->daddr.lsap, rc);
	release_sock(sk);
	वापस rc ? : copied;
पूर्ण

/**
 *	llc_ui_getname - वापस the address info of a socket
 *	@sock: Socket to get address of.
 *	@uaddr: Address काष्ठाure to वापस inक्रमmation.
 *	@peer: Does user want local or remote address inक्रमmation.
 *
 *	Return the address inक्रमmation of a socket.
 */
अटल पूर्णांक llc_ui_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			  पूर्णांक peer)
अणु
	काष्ठा sockaddr_llc sllc;
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक rc = -EBADF;

	स_रखो(&sllc, 0, माप(sllc));
	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_ZAPPED))
		जाओ out;
	अगर (peer) अणु
		rc = -ENOTCONN;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
		अगर(llc->dev)
			sllc.sllc_arphrd = llc->dev->type;
		sllc.sllc_sap = llc->daddr.lsap;
		स_नकल(&sllc.sllc_mac, &llc->daddr.mac, IFHWADDRLEN);
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		अगर (!llc->sap)
			जाओ out;
		sllc.sllc_sap = llc->sap->laddr.lsap;

		अगर (llc->dev) अणु
			sllc.sllc_arphrd = llc->dev->type;
			स_नकल(&sllc.sllc_mac, llc->dev->dev_addr,
			       IFHWADDRLEN);
		पूर्ण
	पूर्ण
	sllc.sllc_family = AF_LLC;
	स_नकल(uaddr, &sllc, माप(sllc));
	rc = माप(sllc);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/**
 *	llc_ui_ioctl - io controls क्रम PF_LLC
 *	@sock: Socket to get/set info
 *	@cmd: command
 *	@arg: optional argument क्रम cmd
 *
 *	get/set info on llc sockets
 */
अटल पूर्णांक llc_ui_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण

/**
 *	llc_ui_setsockopt - set various connection specअगरic parameters.
 *	@sock: Socket to set options on.
 *	@level: Socket level user is requesting operations on.
 *	@optname: Operation name.
 *	@optval: User provided operation data.
 *	@optlen: Length of optval.
 *
 *	Set various connection specअगरic parameters.
 */
अटल पूर्णांक llc_ui_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			     sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	अचिन्हित पूर्णांक opt;
	पूर्णांक rc = -EINVAL;

	lock_sock(sk);
	अगर (unlikely(level != SOL_LLC || optlen != माप(पूर्णांक)))
		जाओ out;
	rc = copy_from_sockptr(&opt, optval, माप(opt));
	अगर (rc)
		जाओ out;
	rc = -EINVAL;
	चयन (optname) अणु
	हाल LLC_OPT_RETRY:
		अगर (opt > LLC_OPT_MAX_RETRY)
			जाओ out;
		llc->n2 = opt;
		अवरोध;
	हाल LLC_OPT_SIZE:
		अगर (opt > LLC_OPT_MAX_SIZE)
			जाओ out;
		llc->n1 = opt;
		अवरोध;
	हाल LLC_OPT_ACK_TMR_EXP:
		अगर (opt > LLC_OPT_MAX_ACK_TMR_EXP)
			जाओ out;
		llc->ack_समयr.expire = opt * HZ;
		अवरोध;
	हाल LLC_OPT_P_TMR_EXP:
		अगर (opt > LLC_OPT_MAX_P_TMR_EXP)
			जाओ out;
		llc->pf_cycle_समयr.expire = opt * HZ;
		अवरोध;
	हाल LLC_OPT_REJ_TMR_EXP:
		अगर (opt > LLC_OPT_MAX_REJ_TMR_EXP)
			जाओ out;
		llc->rej_sent_समयr.expire = opt * HZ;
		अवरोध;
	हाल LLC_OPT_BUSY_TMR_EXP:
		अगर (opt > LLC_OPT_MAX_BUSY_TMR_EXP)
			जाओ out;
		llc->busy_state_समयr.expire = opt * HZ;
		अवरोध;
	हाल LLC_OPT_TX_WIN:
		अगर (opt > LLC_OPT_MAX_WIN)
			जाओ out;
		llc->k = opt;
		अवरोध;
	हाल LLC_OPT_RX_WIN:
		अगर (opt > LLC_OPT_MAX_WIN)
			जाओ out;
		llc->rw = opt;
		अवरोध;
	हाल LLC_OPT_PKTINFO:
		अगर (opt)
			llc->cmsg_flags |= LLC_CMSG_PKTINFO;
		अन्यथा
			llc->cmsg_flags &= ~LLC_CMSG_PKTINFO;
		अवरोध;
	शेष:
		rc = -ENOPROTOOPT;
		जाओ out;
	पूर्ण
	rc = 0;
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/**
 *	llc_ui_माला_लोockopt - get connection specअगरic socket info
 *	@sock: Socket to get inक्रमmation from.
 *	@level: Socket level user is requesting operations on.
 *	@optname: Operation name.
 *	@optval: Variable to वापस operation data in.
 *	@optlen: Length of optval.
 *
 *	Get connection specअगरic socket inक्रमmation.
 */
अटल पूर्णांक llc_ui_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			     अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा llc_sock *llc = llc_sk(sk);
	पूर्णांक val = 0, len = 0, rc = -EINVAL;

	lock_sock(sk);
	अगर (unlikely(level != SOL_LLC))
		जाओ out;
	rc = get_user(len, optlen);
	अगर (rc)
		जाओ out;
	rc = -EINVAL;
	अगर (len != माप(पूर्णांक))
		जाओ out;
	चयन (optname) अणु
	हाल LLC_OPT_RETRY:
		val = llc->n2;					अवरोध;
	हाल LLC_OPT_SIZE:
		val = llc->n1;					अवरोध;
	हाल LLC_OPT_ACK_TMR_EXP:
		val = llc->ack_समयr.expire / HZ;		अवरोध;
	हाल LLC_OPT_P_TMR_EXP:
		val = llc->pf_cycle_समयr.expire / HZ;		अवरोध;
	हाल LLC_OPT_REJ_TMR_EXP:
		val = llc->rej_sent_समयr.expire / HZ;		अवरोध;
	हाल LLC_OPT_BUSY_TMR_EXP:
		val = llc->busy_state_समयr.expire / HZ;	अवरोध;
	हाल LLC_OPT_TX_WIN:
		val = llc->k;				अवरोध;
	हाल LLC_OPT_RX_WIN:
		val = llc->rw;				अवरोध;
	हाल LLC_OPT_PKTINFO:
		val = (llc->cmsg_flags & LLC_CMSG_PKTINFO) != 0;
		अवरोध;
	शेष:
		rc = -ENOPROTOOPT;
		जाओ out;
	पूर्ण
	rc = 0;
	अगर (put_user(len, optlen) || copy_to_user(optval, &val, len))
		rc = -EFAULT;
out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family llc_ui_family_ops = अणु
	.family = PF_LLC,
	.create = llc_ui_create,
	.owner	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops llc_ui_ops = अणु
	.family	     = PF_LLC,
	.owner       = THIS_MODULE,
	.release     = llc_ui_release,
	.bind	     = llc_ui_bind,
	.connect     = llc_ui_connect,
	.socketpair  = sock_no_socketpair,
	.accept      = llc_ui_accept,
	.getname     = llc_ui_getname,
	.poll	     = datagram_poll,
	.ioctl       = llc_ui_ioctl,
	.listen      = llc_ui_listen,
	.shutकरोwn    = llc_ui_shutकरोwn,
	.setsockopt  = llc_ui_setsockopt,
	.माला_लोockopt  = llc_ui_माला_लोockopt,
	.sendmsg     = llc_ui_sendmsg,
	.recvmsg     = llc_ui_recvmsg,
	.mmap	     = sock_no_mmap,
	.sendpage    = sock_no_sendpage,
पूर्ण;

अटल स्थिर अक्षर llc_proc_err_msg[] __initस्थिर =
	KERN_CRIT "LLC: Unable to register the proc_fs entries\n";
अटल स्थिर अक्षर llc_sysctl_err_msg[] __initस्थिर =
	KERN_CRIT "LLC: Unable to register the sysctl entries\n";
अटल स्थिर अक्षर llc_sock_err_msg[] __initस्थिर =
	KERN_CRIT "LLC: Unable to register the network family\n";

अटल पूर्णांक __init llc2_init(व्योम)
अणु
	पूर्णांक rc = proto_रेजिस्टर(&llc_proto, 0);

	अगर (rc != 0)
		जाओ out;

	llc_build_offset_table();
	llc_station_init();
	llc_ui_sap_last_स्वतःport = LLC_SAP_DYN_START;
	rc = llc_proc_init();
	अगर (rc != 0) अणु
		prपूर्णांकk(llc_proc_err_msg);
		जाओ out_station;
	पूर्ण
	rc = llc_sysctl_init();
	अगर (rc) अणु
		prपूर्णांकk(llc_sysctl_err_msg);
		जाओ out_proc;
	पूर्ण
	rc = sock_रेजिस्टर(&llc_ui_family_ops);
	अगर (rc) अणु
		prपूर्णांकk(llc_sock_err_msg);
		जाओ out_sysctl;
	पूर्ण
	llc_add_pack(LLC_DEST_SAP, llc_sap_handler);
	llc_add_pack(LLC_DEST_CONN, llc_conn_handler);
out:
	वापस rc;
out_sysctl:
	llc_sysctl_निकास();
out_proc:
	llc_proc_निकास();
out_station:
	llc_station_निकास();
	proto_unरेजिस्टर(&llc_proto);
	जाओ out;
पूर्ण

अटल व्योम __निकास llc2_निकास(व्योम)
अणु
	llc_station_निकास();
	llc_हटाओ_pack(LLC_DEST_SAP);
	llc_हटाओ_pack(LLC_DEST_CONN);
	sock_unरेजिस्टर(PF_LLC);
	llc_proc_निकास();
	llc_sysctl_निकास();
	proto_unरेजिस्टर(&llc_proto);
पूर्ण

module_init(llc2_init);
module_निकास(llc2_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Procom 1997, Jay Schullist 2001, Arnaldo C. Melo 2001-2003");
MODULE_DESCRIPTION("IEEE 802.2 PF_LLC support");
MODULE_ALIAS_NETPROTO(PF_LLC);
