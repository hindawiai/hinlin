<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright Darryl Miles G7LED (dlm@g7led.demon.co.uk)
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/स्थिति.स>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/netrom.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/ip.h>
#समावेश <net/tcp_states.h>
#समावेश <net/arp.h>
#समावेश <linux/init.h>

अटल पूर्णांक nr_ndevs = 4;

पूर्णांक sysctl_netrom_शेष_path_quality            = NR_DEFAULT_QUAL;
पूर्णांक sysctl_netrom_obsolescence_count_initialiser  = NR_DEFAULT_OBS;
पूर्णांक sysctl_netrom_network_ttl_initialiser         = NR_DEFAULT_TTL;
पूर्णांक sysctl_netrom_transport_समयout               = NR_DEFAULT_T1;
पूर्णांक sysctl_netrom_transport_maximum_tries         = NR_DEFAULT_N2;
पूर्णांक sysctl_netrom_transport_acknowledge_delay     = NR_DEFAULT_T2;
पूर्णांक sysctl_netrom_transport_busy_delay            = NR_DEFAULT_T4;
पूर्णांक sysctl_netrom_transport_requested_winकरोw_size = NR_DEFAULT_WINDOW;
पूर्णांक sysctl_netrom_transport_no_activity_समयout   = NR_DEFAULT_IDLE;
पूर्णांक sysctl_netrom_routing_control                 = NR_DEFAULT_ROUTING;
पूर्णांक sysctl_netrom_link_fails_count                = NR_DEFAULT_FAILS;
पूर्णांक sysctl_netrom_reset_circuit                   = NR_DEFAULT_RESET;

अटल अचिन्हित लघु circuit = 0x101;

अटल HLIST_HEAD(nr_list);
अटल DEFINE_SPINLOCK(nr_list_lock);

अटल स्थिर काष्ठा proto_ops nr_proto_ops;

/*
 * NETROM network devices are भव network devices encapsulating NETROM
 * frames पूर्णांकo AX.25 which will be sent through an AX.25 device, so क्रमm a
 * special "super class" of normal net devices; split their locks off पूर्णांकo a
 * separate class since they always nest.
 */
अटल काष्ठा lock_class_key nr_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key nr_netdev_addr_lock_key;

अटल व्योम nr_set_lockdep_one(काष्ठा net_device *dev,
			       काष्ठा netdev_queue *txq,
			       व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &nr_netdev_xmit_lock_key);
पूर्ण

अटल व्योम nr_set_lockdep_key(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock, &nr_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, nr_set_lockdep_one, शून्य);
पूर्ण

/*
 *	Socket removal during an पूर्णांकerrupt is now safe.
 */
अटल व्योम nr_हटाओ_socket(काष्ठा sock *sk)
अणु
	spin_lock_bh(&nr_list_lock);
	sk_del_node_init(sk);
	spin_unlock_bh(&nr_list_lock);
पूर्ण

/*
 *	Kill all bound sockets on a dropped device.
 */
अटल व्योम nr_समाप्त_by_device(काष्ठा net_device *dev)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&nr_list_lock);
	sk_क्रम_each(s, &nr_list)
		अगर (nr_sk(s)->device == dev)
			nr_disconnect(s, ENETUNREACH);
	spin_unlock_bh(&nr_list_lock);
पूर्ण

/*
 *	Handle device status changes.
 */
अटल पूर्णांक nr_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (event != NETDEV_DOWN)
		वापस NOTIFY_DONE;

	nr_समाप्त_by_device(dev);
	nr_rt_device_करोwn(dev);

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Add a socket to the bound sockets list.
 */
अटल व्योम nr_insert_socket(काष्ठा sock *sk)
अणु
	spin_lock_bh(&nr_list_lock);
	sk_add_node(sk, &nr_list);
	spin_unlock_bh(&nr_list_lock);
पूर्ण

/*
 *	Find a socket that wants to accept the Connect Request we just
 *	received.
 */
अटल काष्ठा sock *nr_find_listener(ax25_address *addr)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&nr_list_lock);
	sk_क्रम_each(s, &nr_list)
		अगर (!ax25cmp(&nr_sk(s)->source_addr, addr) &&
		    s->sk_state == TCP_LISTEN) अणु
			sock_hold(s);
			जाओ found;
		पूर्ण
	s = शून्य;
found:
	spin_unlock_bh(&nr_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a connected NET/ROM socket given my circuit IDs.
 */
अटल काष्ठा sock *nr_find_socket(अचिन्हित अक्षर index, अचिन्हित अक्षर id)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&nr_list_lock);
	sk_क्रम_each(s, &nr_list) अणु
		काष्ठा nr_sock *nr = nr_sk(s);

		अगर (nr->my_index == index && nr->my_id == id) अणु
			sock_hold(s);
			जाओ found;
		पूर्ण
	पूर्ण
	s = शून्य;
found:
	spin_unlock_bh(&nr_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a connected NET/ROM socket given their circuit IDs.
 */
अटल काष्ठा sock *nr_find_peer(अचिन्हित अक्षर index, अचिन्हित अक्षर id,
	ax25_address *dest)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&nr_list_lock);
	sk_क्रम_each(s, &nr_list) अणु
		काष्ठा nr_sock *nr = nr_sk(s);

		अगर (nr->your_index == index && nr->your_id == id &&
		    !ax25cmp(&nr->dest_addr, dest)) अणु
			sock_hold(s);
			जाओ found;
		पूर्ण
	पूर्ण
	s = शून्य;
found:
	spin_unlock_bh(&nr_list_lock);
	वापस s;
पूर्ण

/*
 *	Find next मुक्त circuit ID.
 */
अटल अचिन्हित लघु nr_find_next_circuit(व्योम)
अणु
	अचिन्हित लघु id = circuit;
	अचिन्हित अक्षर i, j;
	काष्ठा sock *sk;

	क्रम (;;) अणु
		i = id / 256;
		j = id % 256;

		अगर (i != 0 && j != 0) अणु
			अगर ((sk=nr_find_socket(i, j)) == शून्य)
				अवरोध;
			sock_put(sk);
		पूर्ण

		id++;
	पूर्ण

	वापस id;
पूर्ण

/*
 *	Deferred destroy.
 */
व्योम nr_destroy_socket(काष्ठा sock *);

/*
 *	Handler क्रम deferred समाप्तs.
 */
अटल व्योम nr_destroy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	bh_lock_sock(sk);
	sock_hold(sk);
	nr_destroy_socket(sk);
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/*
 *	This is called from user mode and the समयrs. Thus it protects itself
 *	against पूर्णांकerrupt users but करोesn't worry about being called during
 *	work. Once it is हटाओd from the queue no पूर्णांकerrupt or bottom half
 *	will touch it and we are (fairly 8-) ) safe.
 */
व्योम nr_destroy_socket(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	nr_हटाओ_socket(sk);

	nr_stop_heartbeat(sk);
	nr_stop_t1समयr(sk);
	nr_stop_t2समयr(sk);
	nr_stop_t4समयr(sk);
	nr_stop_idleसमयr(sk);

	nr_clear_queues(sk);		/* Flush the queues */

	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		अगर (skb->sk != sk) अणु /* A pending connection */
			/* Queue the unaccepted socket क्रम death */
			sock_set_flag(skb->sk, SOCK_DEAD);
			nr_start_heartbeat(skb->sk);
			nr_sk(skb->sk)->state = NR_STATE_0;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण

	अगर (sk_has_allocations(sk)) अणु
		/* Defer: outstanding buffers */
		sk->sk_समयr.function = nr_destroy_समयr;
		sk->sk_समयr.expires  = jअगरfies + 2 * HZ;
		add_समयr(&sk->sk_समयr);
	पूर्ण अन्यथा
		sock_put(sk);
पूर्ण

/*
 *	Handling क्रम प्रणाली calls applied via the various पूर्णांकerfaces to a
 *	NET/ROM socket object.
 */

अटल पूर्णांक nr_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	अचिन्हित दीर्घ opt;

	अगर (level != SOL_NETROM)
		वापस -ENOPROTOOPT;

	अगर (optlen < माप(अचिन्हित पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&opt, optval, माप(अचिन्हित पूर्णांक)))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल NETROM_T1:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ)
			वापस -EINVAL;
		nr->t1 = opt * HZ;
		वापस 0;

	हाल NETROM_T2:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ)
			वापस -EINVAL;
		nr->t2 = opt * HZ;
		वापस 0;

	हाल NETROM_N2:
		अगर (opt < 1 || opt > 31)
			वापस -EINVAL;
		nr->n2 = opt;
		वापस 0;

	हाल NETROM_T4:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ)
			वापस -EINVAL;
		nr->t4 = opt * HZ;
		वापस 0;

	हाल NETROM_IDLE:
		अगर (opt > अच_दीर्घ_उच्च / (60 * HZ))
			वापस -EINVAL;
		nr->idle = opt * 60 * HZ;
		वापस 0;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

अटल पूर्णांक nr_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
	अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	पूर्णांक val = 0;
	पूर्णांक len;

	अगर (level != SOL_NETROM)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल NETROM_T1:
		val = nr->t1 / HZ;
		अवरोध;

	हाल NETROM_T2:
		val = nr->t2 / HZ;
		अवरोध;

	हाल NETROM_N2:
		val = nr->n2;
		अवरोध;

	हाल NETROM_T4:
		val = nr->t4 / HZ;
		अवरोध;

	हाल NETROM_IDLE:
		val = nr->idle / (60 * HZ);
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस copy_to_user(optval, &val, len) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक nr_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;

	lock_sock(sk);
	अगर (sk->sk_state != TCP_LISTEN) अणु
		स_रखो(&nr_sk(sk)->user_addr, 0, AX25_ADDR_LEN);
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		release_sock(sk);
		वापस 0;
	पूर्ण
	release_sock(sk);

	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा proto nr_proto = अणु
	.name	  = "NETROM",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा nr_sock),
पूर्ण;

अटल पूर्णांक nr_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		     पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा nr_sock *nr;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	अगर (sock->type != SOCK_SEQPACKET || protocol != 0)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_NETROM, GFP_ATOMIC, &nr_proto, kern);
	अगर (sk  == शून्य)
		वापस -ENOMEM;

	nr = nr_sk(sk);

	sock_init_data(sock, sk);

	sock->ops    = &nr_proto_ops;
	sk->sk_protocol = protocol;

	skb_queue_head_init(&nr->ack_queue);
	skb_queue_head_init(&nr->reseq_queue);
	skb_queue_head_init(&nr->frag_queue);

	nr_init_समयrs(sk);

	nr->t1     =
		msecs_to_jअगरfies(sysctl_netrom_transport_समयout);
	nr->t2     =
		msecs_to_jअगरfies(sysctl_netrom_transport_acknowledge_delay);
	nr->n2     =
		msecs_to_jअगरfies(sysctl_netrom_transport_maximum_tries);
	nr->t4     =
		msecs_to_jअगरfies(sysctl_netrom_transport_busy_delay);
	nr->idle   =
		msecs_to_jअगरfies(sysctl_netrom_transport_no_activity_समयout);
	nr->winकरोw = sysctl_netrom_transport_requested_winकरोw_size;

	nr->bpqext = 1;
	nr->state  = NR_STATE_0;

	वापस 0;
पूर्ण

अटल काष्ठा sock *nr_make_new(काष्ठा sock *osk)
अणु
	काष्ठा sock *sk;
	काष्ठा nr_sock *nr, *onr;

	अगर (osk->sk_type != SOCK_SEQPACKET)
		वापस शून्य;

	sk = sk_alloc(sock_net(osk), PF_NETROM, GFP_ATOMIC, osk->sk_prot, 0);
	अगर (sk == शून्य)
		वापस शून्य;

	nr = nr_sk(sk);

	sock_init_data(शून्य, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	skb_queue_head_init(&nr->ack_queue);
	skb_queue_head_init(&nr->reseq_queue);
	skb_queue_head_init(&nr->frag_queue);

	nr_init_समयrs(sk);

	onr = nr_sk(osk);

	nr->t1      = onr->t1;
	nr->t2      = onr->t2;
	nr->n2      = onr->n2;
	nr->t4      = onr->t4;
	nr->idle    = onr->idle;
	nr->winकरोw  = onr->winकरोw;

	nr->device  = onr->device;
	nr->bpqext  = onr->bpqext;

	वापस sk;
पूर्ण

अटल पूर्णांक nr_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr;

	अगर (sk == शून्य) वापस 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	nr = nr_sk(sk);

	चयन (nr->state) अणु
	हाल NR_STATE_0:
	हाल NR_STATE_1:
	हाल NR_STATE_2:
		nr_disconnect(sk, 0);
		nr_destroy_socket(sk);
		अवरोध;

	हाल NR_STATE_3:
		nr_clear_queues(sk);
		nr->n2count = 0;
		nr_ग_लिखो_पूर्णांकernal(sk, NR_DISCREQ);
		nr_start_t1समयr(sk);
		nr_stop_t2समयr(sk);
		nr_stop_t4समयr(sk);
		nr_stop_idleसमयr(sk);
		nr->state    = NR_STATE_2;
		sk->sk_state    = TCP_CLOSE;
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DESTROY);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	sock->sk   = शून्य;
	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक nr_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	काष्ठा full_sockaddr_ax25 *addr = (काष्ठा full_sockaddr_ax25 *)uaddr;
	काष्ठा net_device *dev;
	ax25_uid_assoc *user;
	ax25_address *source;

	lock_sock(sk);
	अगर (!sock_flag(sk, SOCK_ZAPPED)) अणु
		release_sock(sk);
		वापस -EINVAL;
	पूर्ण
	अगर (addr_len < माप(काष्ठा sockaddr_ax25) || addr_len > माप(काष्ठा full_sockaddr_ax25)) अणु
		release_sock(sk);
		वापस -EINVAL;
	पूर्ण
	अगर (addr_len < (addr->fsa_ax25.sax25_ndigis * माप(ax25_address) + माप(काष्ठा sockaddr_ax25))) अणु
		release_sock(sk);
		वापस -EINVAL;
	पूर्ण
	अगर (addr->fsa_ax25.sax25_family != AF_NETROM) अणु
		release_sock(sk);
		वापस -EINVAL;
	पूर्ण
	अगर ((dev = nr_dev_get(&addr->fsa_ax25.sax25_call)) == शून्य) अणु
		release_sock(sk);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	/*
	 * Only the super user can set an arbitrary user callsign.
	 */
	अगर (addr->fsa_ax25.sax25_ndigis == 1) अणु
		अगर (!capable(CAP_NET_BIND_SERVICE)) अणु
			dev_put(dev);
			release_sock(sk);
			वापस -EPERM;
		पूर्ण
		nr->user_addr   = addr->fsa_digipeater[0];
		nr->source_addr = addr->fsa_ax25.sax25_call;
	पूर्ण अन्यथा अणु
		source = &addr->fsa_ax25.sax25_call;

		user = ax25_findbyuid(current_euid());
		अगर (user) अणु
			nr->user_addr   = user->call;
			ax25_uid_put(user);
		पूर्ण अन्यथा अणु
			अगर (ax25_uid_policy && !capable(CAP_NET_BIND_SERVICE)) अणु
				release_sock(sk);
				dev_put(dev);
				वापस -EPERM;
			पूर्ण
			nr->user_addr   = *source;
		पूर्ण

		nr->source_addr = *source;
	पूर्ण

	nr->device = dev;
	nr_insert_socket(sk);

	sock_reset_flag(sk, SOCK_ZAPPED);
	dev_put(dev);
	release_sock(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक nr_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
	पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	काष्ठा sockaddr_ax25 *addr = (काष्ठा sockaddr_ax25 *)uaddr;
	ax25_address *source = शून्य;
	ax25_uid_assoc *user;
	काष्ठा net_device *dev;
	पूर्णांक err = 0;

	lock_sock(sk);
	अगर (sk->sk_state == TCP_ESTABLISHED && sock->state == SS_CONNECTING) अणु
		sock->state = SS_CONNECTED;
		जाओ out_release;	/* Connect completed during a ERESTARTSYS event */
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE && sock->state == SS_CONNECTING) अणु
		sock->state = SS_UNCONNECTED;
		err = -ECONNREFUSED;
		जाओ out_release;
	पूर्ण

	अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		err = -EISCONN;	/* No reconnect on a seqpacket socket */
		जाओ out_release;
	पूर्ण

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	अगर (addr_len != माप(काष्ठा sockaddr_ax25) && addr_len != माप(काष्ठा full_sockaddr_ax25)) अणु
		err = -EINVAL;
		जाओ out_release;
	पूर्ण
	अगर (addr->sax25_family != AF_NETROM) अणु
		err = -EINVAL;
		जाओ out_release;
	पूर्ण
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु	/* Must bind first - स्वतःbinding in this may or may not work */
		sock_reset_flag(sk, SOCK_ZAPPED);

		अगर ((dev = nr_dev_first()) == शून्य) अणु
			err = -ENETUNREACH;
			जाओ out_release;
		पूर्ण
		source = (ax25_address *)dev->dev_addr;

		user = ax25_findbyuid(current_euid());
		अगर (user) अणु
			nr->user_addr   = user->call;
			ax25_uid_put(user);
		पूर्ण अन्यथा अणु
			अगर (ax25_uid_policy && !capable(CAP_NET_ADMIN)) अणु
				dev_put(dev);
				err = -EPERM;
				जाओ out_release;
			पूर्ण
			nr->user_addr   = *source;
		पूर्ण

		nr->source_addr = *source;
		nr->device      = dev;

		dev_put(dev);
		nr_insert_socket(sk);		/* Finish the bind */
	पूर्ण

	nr->dest_addr = addr->sax25_call;

	release_sock(sk);
	circuit = nr_find_next_circuit();
	lock_sock(sk);

	nr->my_index = circuit / 256;
	nr->my_id    = circuit % 256;

	circuit++;

	/* Move to connecting socket, start sending Connect Requests */
	sock->state  = SS_CONNECTING;
	sk->sk_state = TCP_SYN_SENT;

	nr_establish_data_link(sk);

	nr->state = NR_STATE_1;

	nr_start_heartbeat(sk);

	/* Now the loop */
	अगर (sk->sk_state != TCP_ESTABLISHED && (flags & O_NONBLOCK)) अणु
		err = -EINPROGRESS;
		जाओ out_release;
	पूर्ण

	/*
	 * A Connect Ack with Choke or समयout or failed routing will go to
	 * बंदd.
	 */
	अगर (sk->sk_state == TCP_SYN_SENT) अणु
		DEFINE_WAIT(रुको);

		क्रम (;;) अणु
			prepare_to_रुको(sk_sleep(sk), &रुको,
					TASK_INTERRUPTIBLE);
			अगर (sk->sk_state != TCP_SYN_SENT)
				अवरोध;
			अगर (!संकेत_pending(current)) अणु
				release_sock(sk);
				schedule();
				lock_sock(sk);
				जारी;
			पूर्ण
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		finish_रुको(sk_sleep(sk), &रुको);
		अगर (err)
			जाओ out_release;
	पूर्ण

	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		sock->state = SS_UNCONNECTED;
		err = sock_error(sk);	/* Always set at this poपूर्णांक */
		जाओ out_release;
	पूर्ण

	sock->state = SS_CONNECTED;

out_release:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक nr_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		     bool kern)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *newsk;
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk;
	पूर्णांक err = 0;

	अगर ((sk = sock->sk) == शून्य)
		वापस -EINVAL;

	lock_sock(sk);
	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		err = -EOPNOTSUPP;
		जाओ out_release;
	पूर्ण

	अगर (sk->sk_state != TCP_LISTEN) अणु
		err = -EINVAL;
		जाओ out_release;
	पूर्ण

	/*
	 *	The ग_लिखो queue this समय is holding sockets पढ़ोy to use
	 *	hooked पूर्णांकo the SABM we saved
	 */
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		skb = skb_dequeue(&sk->sk_receive_queue);
		अगर (skb)
			अवरोध;

		अगर (flags & O_NONBLOCK) अणु
			err = -EWOULDBLOCK;
			अवरोध;
		पूर्ण
		अगर (!संकेत_pending(current)) अणु
			release_sock(sk);
			schedule();
			lock_sock(sk);
			जारी;
		पूर्ण
		err = -ERESTARTSYS;
		अवरोध;
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (err)
		जाओ out_release;

	newsk = skb->sk;
	sock_graft(newsk, newsock);

	/* Now attach up the new socket */
	kमुक्त_skb(skb);
	sk_acceptq_हटाओd(sk);

out_release:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक nr_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
	पूर्णांक peer)
अणु
	काष्ठा full_sockaddr_ax25 *sax = (काष्ठा full_sockaddr_ax25 *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	पूर्णांक uaddr_len;

	स_रखो(&sax->fsa_ax25, 0, माप(काष्ठा sockaddr_ax25));

	lock_sock(sk);
	अगर (peer != 0) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			release_sock(sk);
			वापस -ENOTCONN;
		पूर्ण
		sax->fsa_ax25.sax25_family = AF_NETROM;
		sax->fsa_ax25.sax25_ndigis = 1;
		sax->fsa_ax25.sax25_call   = nr->user_addr;
		स_रखो(sax->fsa_digipeater, 0, माप(sax->fsa_digipeater));
		sax->fsa_digipeater[0]     = nr->dest_addr;
		uaddr_len = माप(काष्ठा full_sockaddr_ax25);
	पूर्ण अन्यथा अणु
		sax->fsa_ax25.sax25_family = AF_NETROM;
		sax->fsa_ax25.sax25_ndigis = 0;
		sax->fsa_ax25.sax25_call   = nr->source_addr;
		uaddr_len = माप(काष्ठा sockaddr_ax25);
	पूर्ण
	release_sock(sk);

	वापस uaddr_len;
पूर्ण

पूर्णांक nr_rx_frame(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sock *sk;
	काष्ठा sock *make;
	काष्ठा nr_sock *nr_make;
	ax25_address *src, *dest, *user;
	अचिन्हित लघु circuit_index, circuit_id;
	अचिन्हित लघु peer_circuit_index, peer_circuit_id;
	अचिन्हित लघु frametype, flags, winकरोw, समयout;
	पूर्णांक ret;

	skb_orphan(skb);

	/*
	 *	skb->data poपूर्णांकs to the netrom frame start
	 */

	src  = (ax25_address *)(skb->data + 0);
	dest = (ax25_address *)(skb->data + 7);

	circuit_index      = skb->data[15];
	circuit_id         = skb->data[16];
	peer_circuit_index = skb->data[17];
	peer_circuit_id    = skb->data[18];
	frametype          = skb->data[19] & 0x0F;
	flags              = skb->data[19] & 0xF0;

	/*
	 * Check क्रम an incoming IP over NET/ROM frame.
	 */
	अगर (frametype == NR_PROTOEXT &&
	    circuit_index == NR_PROTO_IP && circuit_id == NR_PROTO_IP) अणु
		skb_pull(skb, NR_NETWORK_LEN + NR_TRANSPORT_LEN);
		skb_reset_transport_header(skb);

		वापस nr_rx_ip(skb, dev);
	पूर्ण

	/*
	 * Find an existing socket connection, based on circuit ID, अगर it's
	 * a Connect Request base it on their circuit ID.
	 *
	 * Circuit ID 0/0 is not valid but it could still be a "reset" क्रम a
	 * circuit that no दीर्घer exists at the other end ...
	 */

	sk = शून्य;

	अगर (circuit_index == 0 && circuit_id == 0) अणु
		अगर (frametype == NR_CONNACK && flags == NR_CHOKE_FLAG)
			sk = nr_find_peer(peer_circuit_index, peer_circuit_id, src);
	पूर्ण अन्यथा अणु
		अगर (frametype == NR_CONNREQ)
			sk = nr_find_peer(circuit_index, circuit_id, src);
		अन्यथा
			sk = nr_find_socket(circuit_index, circuit_id);
	पूर्ण

	अगर (sk != शून्य) अणु
		bh_lock_sock(sk);
		skb_reset_transport_header(skb);

		अगर (frametype == NR_CONNACK && skb->len == 22)
			nr_sk(sk)->bpqext = 1;
		अन्यथा
			nr_sk(sk)->bpqext = 0;

		ret = nr_process_rx_frame(sk, skb);
		bh_unlock_sock(sk);
		sock_put(sk);
		वापस ret;
	पूर्ण

	/*
	 * Now it should be a CONNREQ.
	 */
	अगर (frametype != NR_CONNREQ) अणु
		/*
		 * Here it would be nice to be able to send a reset but
		 * NET/ROM करोesn't have one.  We've tried to extend the protocol
		 * by sending NR_CONNACK | NR_CHOKE_FLAGS replies but that
		 * apparently समाप्तs BPQ boxes... :-(
		 * So now we try to follow the established behaviour of
		 * G8PZT's Xrouter which is sending packets with command type 7
		 * as an extension of the protocol.
		 */
		अगर (sysctl_netrom_reset_circuit &&
		    (frametype != NR_RESET || flags != 0))
			nr_transmit_reset(skb, 1);

		वापस 0;
	पूर्ण

	sk = nr_find_listener(dest);

	user = (ax25_address *)(skb->data + 21);

	अगर (sk == शून्य || sk_acceptq_is_full(sk) ||
	    (make = nr_make_new(sk)) == शून्य) अणु
		nr_transmit_refusal(skb, 0);
		अगर (sk)
			sock_put(sk);
		वापस 0;
	पूर्ण

	bh_lock_sock(sk);

	winकरोw = skb->data[20];

	sock_hold(make);
	skb->sk             = make;
	skb->deकाष्ठाor     = sock_eमुक्त;
	make->sk_state	    = TCP_ESTABLISHED;

	/* Fill in his circuit details */
	nr_make = nr_sk(make);
	nr_make->source_addr = *dest;
	nr_make->dest_addr   = *src;
	nr_make->user_addr   = *user;

	nr_make->your_index  = circuit_index;
	nr_make->your_id     = circuit_id;

	bh_unlock_sock(sk);
	circuit = nr_find_next_circuit();
	bh_lock_sock(sk);

	nr_make->my_index    = circuit / 256;
	nr_make->my_id       = circuit % 256;

	circuit++;

	/* Winकरोw negotiation */
	अगर (winकरोw < nr_make->winकरोw)
		nr_make->winकरोw = winकरोw;

	/* L4 समयout negotiation */
	अगर (skb->len == 37) अणु
		समयout = skb->data[36] * 256 + skb->data[35];
		अगर (समयout * HZ < nr_make->t1)
			nr_make->t1 = समयout * HZ;
		nr_make->bpqext = 1;
	पूर्ण अन्यथा अणु
		nr_make->bpqext = 0;
	पूर्ण

	nr_ग_लिखो_पूर्णांकernal(make, NR_CONNACK);

	nr_make->condition = 0x00;
	nr_make->vs        = 0;
	nr_make->va        = 0;
	nr_make->vr        = 0;
	nr_make->vl        = 0;
	nr_make->state     = NR_STATE_3;
	sk_acceptq_added(sk);
	skb_queue_head(&sk->sk_receive_queue, skb);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);

	bh_unlock_sock(sk);
	sock_put(sk);

	nr_insert_socket(make);

	nr_start_heartbeat(make);
	nr_start_idleसमयr(make);

	वापस 1;
पूर्ण

अटल पूर्णांक nr_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nr_sock *nr = nr_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_ax25 *, usax, msg->msg_name);
	पूर्णांक err;
	काष्ठा sockaddr_ax25 sax;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *यंत्रptr;
	पूर्णांक size;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_CMSG_COMPAT))
		वापस -EINVAL;

	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		err = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		send_sig(SIGPIPE, current, 0);
		err = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (nr->device == शून्य) अणु
		err = -ENETUNREACH;
		जाओ out;
	पूर्ण

	अगर (usax) अणु
		अगर (msg->msg_namelen < माप(sax)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		sax = *usax;
		अगर (ax25cmp(&nr->dest_addr, &sax.sax25_call) != 0) अणु
			err = -EISCONN;
			जाओ out;
		पूर्ण
		अगर (sax.sax25_family != AF_NETROM) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			err = -ENOTCONN;
			जाओ out;
		पूर्ण
		sax.sax25_family = AF_NETROM;
		sax.sax25_call   = nr->dest_addr;
	पूर्ण

	/* Build a packet - the conventional user limit is 236 bytes. We can
	   करो ludicrously large NetROM frames but must not overflow */
	अगर (len > 65536) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	size = len + NR_NETWORK_LEN + NR_TRANSPORT_LEN;

	अगर ((skb = sock_alloc_send_skb(sk, size, msg->msg_flags & MSG_DONTWAIT, &err)) == शून्य)
		जाओ out;

	skb_reserve(skb, size - len);
	skb_reset_transport_header(skb);

	/*
	 *	Push करोwn the NET/ROM header
	 */

	यंत्रptr = skb_push(skb, NR_TRANSPORT_LEN);

	/* Build a NET/ROM Transport header */

	*यंत्रptr++ = nr->your_index;
	*यंत्रptr++ = nr->your_id;
	*यंत्रptr++ = 0;		/* To be filled in later */
	*यंत्रptr++ = 0;		/*      Ditto            */
	*यंत्रptr++ = NR_INFO;

	/*
	 *	Put the data on the end
	 */
	skb_put(skb, len);

	/* User data follows immediately after the NET/ROM transport header */
	अगर (स_नकल_from_msg(skb_transport_header(skb), msg, len)) अणु
		kमुक्त_skb(skb);
		err = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		kमुक्त_skb(skb);
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	nr_output(sk, skb);	/* Shove it onto the queue */

	err = len;
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक nr_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		      पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	DECLARE_SOCKADDR(काष्ठा sockaddr_ax25 *, sax, msg->msg_name);
	माप_प्रकार copied;
	काष्ठा sk_buff *skb;
	पूर्णांक er;

	/*
	 * This works क्रम seqpacket too. The receiver has ordered the queue क्रम
	 * us! We करो one quick check first though
	 */

	lock_sock(sk);
	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		release_sock(sk);
		वापस -ENOTCONN;
	पूर्ण

	/* Now we can treat all alike */
	अगर ((skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT, flags & MSG_DONTWAIT, &er)) == शून्य) अणु
		release_sock(sk);
		वापस er;
	पूर्ण

	skb_reset_transport_header(skb);
	copied     = skb->len;

	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	er = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (er < 0) अणु
		skb_मुक्त_datagram(sk, skb);
		release_sock(sk);
		वापस er;
	पूर्ण

	अगर (sax != शून्य) अणु
		स_रखो(sax, 0, माप(*sax));
		sax->sax25_family = AF_NETROM;
		skb_copy_from_linear_data_offset(skb, 7, sax->sax25_call.ax25_call,
			      AX25_ADDR_LEN);
		msg->msg_namelen = माप(*sax);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	release_sock(sk);
	वापस copied;
पूर्ण


अटल पूर्णांक nr_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल TIOCOUTQ: अणु
		दीर्घ amount;

		lock_sock(sk);
		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		release_sock(sk);
		वापस put_user(amount, (पूर्णांक __user *)argp);
	पूर्ण

	हाल TIOCINQ: अणु
		काष्ठा sk_buff *skb;
		दीर्घ amount = 0L;

		lock_sock(sk);
		/* These two are safe on a single CPU प्रणाली as only user tasks fiddle here */
		अगर ((skb = skb_peek(&sk->sk_receive_queue)) != शून्य)
			amount = skb->len;
		release_sock(sk);
		वापस put_user(amount, (पूर्णांक __user *)argp);
	पूर्ण

	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
	हाल SIOCGIFDSTADDR:
	हाल SIOCSIFDSTADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCSIFNETMASK:
	हाल SIOCGIFMETRIC:
	हाल SIOCSIFMETRIC:
		वापस -EINVAL;

	हाल SIOCADDRT:
	हाल SIOCDELRT:
	हाल SIOCNRDECOBS:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस nr_rt_ioctl(cmd, argp);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *nr_info_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(&nr_list_lock)
अणु
	spin_lock_bh(&nr_list_lock);
	वापस seq_hlist_start_head(&nr_list, *pos);
पूर्ण

अटल व्योम *nr_info_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &nr_list, pos);
पूर्ण

अटल व्योम nr_info_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(&nr_list_lock)
अणु
	spin_unlock_bh(&nr_list_lock);
पूर्ण

अटल पूर्णांक nr_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sock *s = sk_entry(v);
	काष्ठा net_device *dev;
	काष्ठा nr_sock *nr;
	स्थिर अक्षर *devname;
	अक्षर buf[11];

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
"user_addr dest_node src_node  dev    my  your  st  vs  vr  va    t1     t2     t4      idle   n2  wnd Snd-Q Rcv-Q inode\n");

	अन्यथा अणु

		bh_lock_sock(s);
		nr = nr_sk(s);

		अगर ((dev = nr->device) == शून्य)
			devname = "???";
		अन्यथा
			devname = dev->name;

		seq_म_लिखो(seq, "%-9s ", ax2asc(buf, &nr->user_addr));
		seq_म_लिखो(seq, "%-9s ", ax2asc(buf, &nr->dest_addr));
		seq_म_लिखो(seq,
"%-9s %-3s  %02X/%02X %02X/%02X %2d %3d %3d %3d %3lu/%03lu %2lu/%02lu %3lu/%03lu %3lu/%03lu %2d/%02d %3d %5d %5d %ld\n",
			ax2asc(buf, &nr->source_addr),
			devname,
			nr->my_index,
			nr->my_id,
			nr->your_index,
			nr->your_id,
			nr->state,
			nr->vs,
			nr->vr,
			nr->va,
			ax25_display_समयr(&nr->t1समयr) / HZ,
			nr->t1 / HZ,
			ax25_display_समयr(&nr->t2समयr) / HZ,
			nr->t2 / HZ,
			ax25_display_समयr(&nr->t4समयr) / HZ,
			nr->t4 / HZ,
			ax25_display_समयr(&nr->idleसमयr) / (60 * HZ),
			nr->idle / (60 * HZ),
			nr->n2count,
			nr->n2,
			nr->winकरोw,
			sk_wmem_alloc_get(s),
			sk_rmem_alloc_get(s),
			s->sk_socket ? SOCK_INODE(s->sk_socket)->i_ino : 0L);

		bh_unlock_sock(s);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations nr_info_seqops = अणु
	.start = nr_info_start,
	.next = nr_info_next,
	.stop = nr_info_stop,
	.show = nr_info_show,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_PROC_FS */

अटल स्थिर काष्ठा net_proto_family nr_family_ops = अणु
	.family		=	PF_NETROM,
	.create		=	nr_create,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops nr_proto_ops = अणु
	.family		=	PF_NETROM,
	.owner		=	THIS_MODULE,
	.release	=	nr_release,
	.bind		=	nr_bind,
	.connect	=	nr_connect,
	.socketpair	=	sock_no_socketpair,
	.accept		=	nr_accept,
	.getname	=	nr_getname,
	.poll		=	datagram_poll,
	.ioctl		=	nr_ioctl,
	.gettstamp	=	sock_gettstamp,
	.listen		=	nr_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.setsockopt	=	nr_setsockopt,
	.माला_लोockopt	=	nr_माला_लोockopt,
	.sendmsg	=	nr_sendmsg,
	.recvmsg	=	nr_recvmsg,
	.mmap		=	sock_no_mmap,
	.sendpage	=	sock_no_sendpage,
पूर्ण;

अटल काष्ठा notअगरier_block nr_dev_notअगरier = अणु
	.notअगरier_call	=	nr_device_event,
पूर्ण;

अटल काष्ठा net_device **dev_nr;

अटल काष्ठा ax25_protocol nr_pid = अणु
	.pid	= AX25_P_NETROM,
	.func	= nr_route_frame
पूर्ण;

अटल काष्ठा ax25_linkfail nr_linkfail_notअगरier = अणु
	.func	= nr_link_failed,
पूर्ण;

अटल पूर्णांक __init nr_proto_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rc = proto_रेजिस्टर(&nr_proto, 0);

	अगर (rc)
		वापस rc;

	अगर (nr_ndevs > 0x7fffffff/माप(काष्ठा net_device *)) अणु
		pr_err("NET/ROM: %s - nr_ndevs parameter too large\n",
		       __func__);
		rc = -EINVAL;
		जाओ unरेजिस्टर_proto;
	पूर्ण

	dev_nr = kसुस्मृति(nr_ndevs, माप(काष्ठा net_device *), GFP_KERNEL);
	अगर (!dev_nr) अणु
		pr_err("NET/ROM: %s - unable to allocate device array\n",
		       __func__);
		rc = -ENOMEM;
		जाओ unरेजिस्टर_proto;
	पूर्ण

	क्रम (i = 0; i < nr_ndevs; i++) अणु
		अक्षर name[IFNAMSIZ];
		काष्ठा net_device *dev;

		प्र_लिखो(name, "nr%d", i);
		dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, nr_setup);
		अगर (!dev) अणु
			rc = -ENOMEM;
			जाओ fail;
		पूर्ण

		dev->base_addr = i;
		rc = रेजिस्टर_netdev(dev);
		अगर (rc) अणु
			मुक्त_netdev(dev);
			जाओ fail;
		पूर्ण
		nr_set_lockdep_key(dev);
		dev_nr[i] = dev;
	पूर्ण

	rc = sock_रेजिस्टर(&nr_family_ops);
	अगर (rc)
		जाओ fail;

	rc = रेजिस्टर_netdevice_notअगरier(&nr_dev_notअगरier);
	अगर (rc)
		जाओ out_sock;

	ax25_रेजिस्टर_pid(&nr_pid);
	ax25_linkfail_रेजिस्टर(&nr_linkfail_notअगरier);

#अगर_घोषित CONFIG_SYSCTL
	rc = nr_रेजिस्टर_sysctl();
	अगर (rc)
		जाओ out_sysctl;
#पूर्ण_अगर

	nr_loopback_init();

	rc = -ENOMEM;
	अगर (!proc_create_seq("nr", 0444, init_net.proc_net, &nr_info_seqops))
		जाओ proc_हटाओ1;
	अगर (!proc_create_seq("nr_neigh", 0444, init_net.proc_net,
			     &nr_neigh_seqops))
		जाओ proc_हटाओ2;
	अगर (!proc_create_seq("nr_nodes", 0444, init_net.proc_net,
			     &nr_node_seqops))
		जाओ proc_हटाओ3;

	वापस 0;

proc_हटाओ3:
	हटाओ_proc_entry("nr_neigh", init_net.proc_net);
proc_हटाओ2:
	हटाओ_proc_entry("nr", init_net.proc_net);
proc_हटाओ1:

	nr_loopback_clear();
	nr_rt_मुक्त();

#अगर_घोषित CONFIG_SYSCTL
	nr_unरेजिस्टर_sysctl();
out_sysctl:
#पूर्ण_अगर
	ax25_linkfail_release(&nr_linkfail_notअगरier);
	ax25_protocol_release(AX25_P_NETROM);
	unरेजिस्टर_netdevice_notअगरier(&nr_dev_notअगरier);
out_sock:
	sock_unरेजिस्टर(PF_NETROM);
fail:
	जबतक (--i >= 0) अणु
		unरेजिस्टर_netdev(dev_nr[i]);
		मुक्त_netdev(dev_nr[i]);
	पूर्ण
	kमुक्त(dev_nr);
unरेजिस्टर_proto:
	proto_unरेजिस्टर(&nr_proto);
	वापस rc;
पूर्ण

module_init(nr_proto_init);

module_param(nr_ndevs, पूर्णांक, 0);
MODULE_PARM_DESC(nr_ndevs, "number of NET/ROM devices");

MODULE_AUTHOR("Jonathan Naylor G4KLX <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The amateur radio NET/ROM network and transport layer protocol");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_NETROM);

अटल व्योम __निकास nr_निकास(व्योम)
अणु
	पूर्णांक i;

	हटाओ_proc_entry("nr", init_net.proc_net);
	हटाओ_proc_entry("nr_neigh", init_net.proc_net);
	हटाओ_proc_entry("nr_nodes", init_net.proc_net);
	nr_loopback_clear();

	nr_rt_मुक्त();

#अगर_घोषित CONFIG_SYSCTL
	nr_unरेजिस्टर_sysctl();
#पूर्ण_अगर

	ax25_linkfail_release(&nr_linkfail_notअगरier);
	ax25_protocol_release(AX25_P_NETROM);

	unरेजिस्टर_netdevice_notअगरier(&nr_dev_notअगरier);

	sock_unरेजिस्टर(PF_NETROM);

	क्रम (i = 0; i < nr_ndevs; i++) अणु
		काष्ठा net_device *dev = dev_nr[i];
		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण

	kमुक्त(dev_nr);
	proto_unरेजिस्टर(&nr_proto);
पूर्ण
module_निकास(nr_निकास);
