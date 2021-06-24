<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Terry Dawson VK2KTJ (terry@animats.net)
 * Copyright (C) Tomi Manninen OH2BNS (oh2bns@sral.fi)
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/स्थिति.स>
#समावेश <net/net_namespace.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/rose.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/tcp_states.h>
#समावेश <net/ip.h>
#समावेश <net/arp.h>

अटल पूर्णांक rose_ndevs = 10;

पूर्णांक sysctl_rose_restart_request_समयout = ROSE_DEFAULT_T0;
पूर्णांक sysctl_rose_call_request_समयout    = ROSE_DEFAULT_T1;
पूर्णांक sysctl_rose_reset_request_समयout   = ROSE_DEFAULT_T2;
पूर्णांक sysctl_rose_clear_request_समयout   = ROSE_DEFAULT_T3;
पूर्णांक sysctl_rose_no_activity_समयout     = ROSE_DEFAULT_IDLE;
पूर्णांक sysctl_rose_ack_hold_back_समयout   = ROSE_DEFAULT_HB;
पूर्णांक sysctl_rose_routing_control         = ROSE_DEFAULT_ROUTING;
पूर्णांक sysctl_rose_link_fail_समयout       = ROSE_DEFAULT_FAIL_TIMEOUT;
पूर्णांक sysctl_rose_maximum_vcs             = ROSE_DEFAULT_MAXVC;
पूर्णांक sysctl_rose_winकरोw_size             = ROSE_DEFAULT_WINDOW_SIZE;

अटल HLIST_HEAD(rose_list);
अटल DEFINE_SPINLOCK(rose_list_lock);

अटल स्थिर काष्ठा proto_ops rose_proto_ops;

ax25_address rose_callsign;

/*
 * ROSE network devices are भव network devices encapsulating ROSE
 * frames पूर्णांकo AX.25 which will be sent through an AX.25 device, so क्रमm a
 * special "super class" of normal net devices; split their locks off पूर्णांकo a
 * separate class since they always nest.
 */
अटल काष्ठा lock_class_key rose_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key rose_netdev_addr_lock_key;

अटल व्योम rose_set_lockdep_one(काष्ठा net_device *dev,
				 काष्ठा netdev_queue *txq,
				 व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &rose_netdev_xmit_lock_key);
पूर्ण

अटल व्योम rose_set_lockdep_key(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock, &rose_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, rose_set_lockdep_one, शून्य);
पूर्ण

/*
 *	Convert a ROSE address पूर्णांकo text.
 */
अक्षर *rose2asc(अक्षर *buf, स्थिर rose_address *addr)
अणु
	अगर (addr->rose_addr[0] == 0x00 && addr->rose_addr[1] == 0x00 &&
	    addr->rose_addr[2] == 0x00 && addr->rose_addr[3] == 0x00 &&
	    addr->rose_addr[4] == 0x00) अणु
		म_नकल(buf, "*");
	पूर्ण अन्यथा अणु
		प्र_लिखो(buf, "%02X%02X%02X%02X%02X", addr->rose_addr[0] & 0xFF,
						addr->rose_addr[1] & 0xFF,
						addr->rose_addr[2] & 0xFF,
						addr->rose_addr[3] & 0xFF,
						addr->rose_addr[4] & 0xFF);
	पूर्ण

	वापस buf;
पूर्ण

/*
 *	Compare two ROSE addresses, 0 == equal.
 */
पूर्णांक rosecmp(rose_address *addr1, rose_address *addr2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++)
		अगर (addr1->rose_addr[i] != addr2->rose_addr[i])
			वापस 1;

	वापस 0;
पूर्ण

/*
 *	Compare two ROSE addresses क्रम only mask digits, 0 == equal.
 */
पूर्णांक rosecmpm(rose_address *addr1, rose_address *addr2, अचिन्हित लघु mask)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (mask > 10)
		वापस 1;

	क्रम (i = 0; i < mask; i++) अणु
		j = i / 2;

		अगर ((i % 2) != 0) अणु
			अगर ((addr1->rose_addr[j] & 0x0F) != (addr2->rose_addr[j] & 0x0F))
				वापस 1;
		पूर्ण अन्यथा अणु
			अगर ((addr1->rose_addr[j] & 0xF0) != (addr2->rose_addr[j] & 0xF0))
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Socket removal during an पूर्णांकerrupt is now safe.
 */
अटल व्योम rose_हटाओ_socket(काष्ठा sock *sk)
अणु
	spin_lock_bh(&rose_list_lock);
	sk_del_node_init(sk);
	spin_unlock_bh(&rose_list_lock);
पूर्ण

/*
 *	Kill all bound sockets on a broken link layer connection to a
 *	particular neighbour.
 */
व्योम rose_समाप्त_by_neigh(काष्ठा rose_neigh *neigh)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&rose_list_lock);
	sk_क्रम_each(s, &rose_list) अणु
		काष्ठा rose_sock *rose = rose_sk(s);

		अगर (rose->neighbour == neigh) अणु
			rose_disconnect(s, ENETUNREACH, ROSE_OUT_OF_ORDER, 0);
			rose->neighbour->use--;
			rose->neighbour = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&rose_list_lock);
पूर्ण

/*
 *	Kill all bound sockets on a dropped device.
 */
अटल व्योम rose_समाप्त_by_device(काष्ठा net_device *dev)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&rose_list_lock);
	sk_क्रम_each(s, &rose_list) अणु
		काष्ठा rose_sock *rose = rose_sk(s);

		अगर (rose->device == dev) अणु
			rose_disconnect(s, ENETUNREACH, ROSE_OUT_OF_ORDER, 0);
			अगर (rose->neighbour)
				rose->neighbour->use--;
			rose->device = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&rose_list_lock);
पूर्ण

/*
 *	Handle device status changes.
 */
अटल पूर्णांक rose_device_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (event != NETDEV_DOWN)
		वापस NOTIFY_DONE;

	चयन (dev->type) अणु
	हाल ARPHRD_ROSE:
		rose_समाप्त_by_device(dev);
		अवरोध;
	हाल ARPHRD_AX25:
		rose_link_device_करोwn(dev);
		rose_rt_device_करोwn(dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Add a socket to the bound sockets list.
 */
अटल व्योम rose_insert_socket(काष्ठा sock *sk)
अणु

	spin_lock_bh(&rose_list_lock);
	sk_add_node(sk, &rose_list);
	spin_unlock_bh(&rose_list_lock);
पूर्ण

/*
 *	Find a socket that wants to accept the Call Request we just
 *	received.
 */
अटल काष्ठा sock *rose_find_listener(rose_address *addr, ax25_address *call)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&rose_list_lock);
	sk_क्रम_each(s, &rose_list) अणु
		काष्ठा rose_sock *rose = rose_sk(s);

		अगर (!rosecmp(&rose->source_addr, addr) &&
		    !ax25cmp(&rose->source_call, call) &&
		    !rose->source_ndigis && s->sk_state == TCP_LISTEN)
			जाओ found;
	पूर्ण

	sk_क्रम_each(s, &rose_list) अणु
		काष्ठा rose_sock *rose = rose_sk(s);

		अगर (!rosecmp(&rose->source_addr, addr) &&
		    !ax25cmp(&rose->source_call, &null_ax25_address) &&
		    s->sk_state == TCP_LISTEN)
			जाओ found;
	पूर्ण
	s = शून्य;
found:
	spin_unlock_bh(&rose_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a connected ROSE socket given my LCI and device.
 */
काष्ठा sock *rose_find_socket(अचिन्हित पूर्णांक lci, काष्ठा rose_neigh *neigh)
अणु
	काष्ठा sock *s;

	spin_lock_bh(&rose_list_lock);
	sk_क्रम_each(s, &rose_list) अणु
		काष्ठा rose_sock *rose = rose_sk(s);

		अगर (rose->lci == lci && rose->neighbour == neigh)
			जाओ found;
	पूर्ण
	s = शून्य;
found:
	spin_unlock_bh(&rose_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a unique LCI क्रम a given device.
 */
अचिन्हित पूर्णांक rose_new_lci(काष्ठा rose_neigh *neigh)
अणु
	पूर्णांक lci;

	अगर (neigh->dce_mode) अणु
		क्रम (lci = 1; lci <= sysctl_rose_maximum_vcs; lci++)
			अगर (rose_find_socket(lci, neigh) == शून्य && rose_route_मुक्त_lci(lci, neigh) == शून्य)
				वापस lci;
	पूर्ण अन्यथा अणु
		क्रम (lci = sysctl_rose_maximum_vcs; lci > 0; lci--)
			अगर (rose_find_socket(lci, neigh) == शून्य && rose_route_मुक्त_lci(lci, neigh) == शून्य)
				वापस lci;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Deferred destroy.
 */
व्योम rose_destroy_socket(काष्ठा sock *);

/*
 *	Handler क्रम deferred समाप्तs.
 */
अटल व्योम rose_destroy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	rose_destroy_socket(sk);
पूर्ण

/*
 *	This is called from user mode and the समयrs. Thus it protects itself
 *	against पूर्णांकerrupt users but करोesn't worry about being called during
 *	work.  Once it is हटाओd from the queue no पूर्णांकerrupt or bottom half
 *	will touch it and we are (fairly 8-) ) safe.
 */
व्योम rose_destroy_socket(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	rose_हटाओ_socket(sk);
	rose_stop_heartbeat(sk);
	rose_stop_idleसमयr(sk);
	rose_stop_समयr(sk);

	rose_clear_queues(sk);		/* Flush the queues */

	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		अगर (skb->sk != sk) अणु	/* A pending connection */
			/* Queue the unaccepted socket क्रम death */
			sock_set_flag(skb->sk, SOCK_DEAD);
			rose_start_heartbeat(skb->sk);
			rose_sk(skb->sk)->state = ROSE_STATE_0;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण

	अगर (sk_has_allocations(sk)) अणु
		/* Defer: outstanding buffers */
		समयr_setup(&sk->sk_समयr, rose_destroy_समयr, 0);
		sk->sk_समयr.expires  = jअगरfies + 10 * HZ;
		add_समयr(&sk->sk_समयr);
	पूर्ण अन्यथा
		sock_put(sk);
पूर्ण

/*
 *	Handling क्रम प्रणाली calls applied via the various पूर्णांकerfaces to a
 *	ROSE socket object.
 */

अटल पूर्णांक rose_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	पूर्णांक opt;

	अगर (level != SOL_ROSE)
		वापस -ENOPROTOOPT;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&opt, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल ROSE_DEFER:
		rose->defer = opt ? 1 : 0;
		वापस 0;

	हाल ROSE_T1:
		अगर (opt < 1)
			वापस -EINVAL;
		rose->t1 = opt * HZ;
		वापस 0;

	हाल ROSE_T2:
		अगर (opt < 1)
			वापस -EINVAL;
		rose->t2 = opt * HZ;
		वापस 0;

	हाल ROSE_T3:
		अगर (opt < 1)
			वापस -EINVAL;
		rose->t3 = opt * HZ;
		वापस 0;

	हाल ROSE_HOLDBACK:
		अगर (opt < 1)
			वापस -EINVAL;
		rose->hb = opt * HZ;
		वापस 0;

	हाल ROSE_IDLE:
		अगर (opt < 0)
			वापस -EINVAL;
		rose->idle = opt * 60 * HZ;
		वापस 0;

	हाल ROSE_QBITINCL:
		rose->qbitincl = opt ? 1 : 0;
		वापस 0;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

अटल पूर्णांक rose_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
	अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	पूर्णांक val = 0;
	पूर्णांक len;

	अगर (level != SOL_ROSE)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल ROSE_DEFER:
		val = rose->defer;
		अवरोध;

	हाल ROSE_T1:
		val = rose->t1 / HZ;
		अवरोध;

	हाल ROSE_T2:
		val = rose->t2 / HZ;
		अवरोध;

	हाल ROSE_T3:
		val = rose->t3 / HZ;
		अवरोध;

	हाल ROSE_HOLDBACK:
		val = rose->hb / HZ;
		अवरोध;

	हाल ROSE_IDLE:
		val = rose->idle / (60 * HZ);
		अवरोध;

	हाल ROSE_QBITINCL:
		val = rose->qbitincl;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस copy_to_user(optval, &val, len) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक rose_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk->sk_state != TCP_LISTEN) अणु
		काष्ठा rose_sock *rose = rose_sk(sk);

		rose->dest_ndigis = 0;
		स_रखो(&rose->dest_addr, 0, ROSE_ADDR_LEN);
		स_रखो(&rose->dest_call, 0, AX25_ADDR_LEN);
		स_रखो(rose->dest_digis, 0, AX25_ADDR_LEN * ROSE_MAX_DIGIS);
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा proto rose_proto = अणु
	.name	  = "ROSE",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा rose_sock),
पूर्ण;

अटल पूर्णांक rose_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		       पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा rose_sock *rose;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	अगर (sock->type != SOCK_SEQPACKET || protocol != 0)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_ROSE, GFP_ATOMIC, &rose_proto, kern);
	अगर (sk == शून्य)
		वापस -ENOMEM;

	rose = rose_sk(sk);

	sock_init_data(sock, sk);

	skb_queue_head_init(&rose->ack_queue);
#अगर_घोषित M_BIT
	skb_queue_head_init(&rose->frag_queue);
	rose->fraglen    = 0;
#पूर्ण_अगर

	sock->ops    = &rose_proto_ops;
	sk->sk_protocol = protocol;

	समयr_setup(&rose->समयr, शून्य, 0);
	समयr_setup(&rose->idleसमयr, शून्य, 0);

	rose->t1   = msecs_to_jअगरfies(sysctl_rose_call_request_समयout);
	rose->t2   = msecs_to_jअगरfies(sysctl_rose_reset_request_समयout);
	rose->t3   = msecs_to_jअगरfies(sysctl_rose_clear_request_समयout);
	rose->hb   = msecs_to_jअगरfies(sysctl_rose_ack_hold_back_समयout);
	rose->idle = msecs_to_jअगरfies(sysctl_rose_no_activity_समयout);

	rose->state = ROSE_STATE_0;

	वापस 0;
पूर्ण

अटल काष्ठा sock *rose_make_new(काष्ठा sock *osk)
अणु
	काष्ठा sock *sk;
	काष्ठा rose_sock *rose, *orose;

	अगर (osk->sk_type != SOCK_SEQPACKET)
		वापस शून्य;

	sk = sk_alloc(sock_net(osk), PF_ROSE, GFP_ATOMIC, &rose_proto, 0);
	अगर (sk == शून्य)
		वापस शून्य;

	rose = rose_sk(sk);

	sock_init_data(शून्य, sk);

	skb_queue_head_init(&rose->ack_queue);
#अगर_घोषित M_BIT
	skb_queue_head_init(&rose->frag_queue);
	rose->fraglen  = 0;
#पूर्ण_अगर

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	समयr_setup(&rose->समयr, शून्य, 0);
	समयr_setup(&rose->idleसमयr, शून्य, 0);

	orose		= rose_sk(osk);
	rose->t1	= orose->t1;
	rose->t2	= orose->t2;
	rose->t3	= orose->t3;
	rose->hb	= orose->hb;
	rose->idle	= orose->idle;
	rose->defer	= orose->defer;
	rose->device	= orose->device;
	rose->qbitincl	= orose->qbitincl;

	वापस sk;
पूर्ण

अटल पूर्णांक rose_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose;

	अगर (sk == शून्य) वापस 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	rose = rose_sk(sk);

	चयन (rose->state) अणु
	हाल ROSE_STATE_0:
		release_sock(sk);
		rose_disconnect(sk, 0, -1, -1);
		lock_sock(sk);
		rose_destroy_socket(sk);
		अवरोध;

	हाल ROSE_STATE_2:
		rose->neighbour->use--;
		release_sock(sk);
		rose_disconnect(sk, 0, -1, -1);
		lock_sock(sk);
		rose_destroy_socket(sk);
		अवरोध;

	हाल ROSE_STATE_1:
	हाल ROSE_STATE_3:
	हाल ROSE_STATE_4:
	हाल ROSE_STATE_5:
		rose_clear_queues(sk);
		rose_stop_idleसमयr(sk);
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_REQUEST);
		rose_start_t3समयr(sk);
		rose->state  = ROSE_STATE_2;
		sk->sk_state    = TCP_CLOSE;
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
		sock_set_flag(sk, SOCK_DESTROY);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	sock->sk = शून्य;
	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक rose_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	काष्ठा sockaddr_rose *addr = (काष्ठा sockaddr_rose *)uaddr;
	काष्ठा net_device *dev;
	ax25_address *source;
	ax25_uid_assoc *user;
	पूर्णांक n;

	अगर (!sock_flag(sk, SOCK_ZAPPED))
		वापस -EINVAL;

	अगर (addr_len != माप(काष्ठा sockaddr_rose) && addr_len != माप(काष्ठा full_sockaddr_rose))
		वापस -EINVAL;

	अगर (addr->srose_family != AF_ROSE)
		वापस -EINVAL;

	अगर (addr_len == माप(काष्ठा sockaddr_rose) && addr->srose_ndigis > 1)
		वापस -EINVAL;

	अगर ((अचिन्हित पूर्णांक) addr->srose_ndigis > ROSE_MAX_DIGIS)
		वापस -EINVAL;

	अगर ((dev = rose_dev_get(&addr->srose_addr)) == शून्य)
		वापस -EADDRNOTAVAIL;

	source = &addr->srose_call;

	user = ax25_findbyuid(current_euid());
	अगर (user) अणु
		rose->source_call = user->call;
		ax25_uid_put(user);
	पूर्ण अन्यथा अणु
		अगर (ax25_uid_policy && !capable(CAP_NET_BIND_SERVICE)) अणु
			dev_put(dev);
			वापस -EACCES;
		पूर्ण
		rose->source_call   = *source;
	पूर्ण

	rose->source_addr   = addr->srose_addr;
	rose->device        = dev;
	rose->source_ndigis = addr->srose_ndigis;

	अगर (addr_len == माप(काष्ठा full_sockaddr_rose)) अणु
		काष्ठा full_sockaddr_rose *full_addr = (काष्ठा full_sockaddr_rose *)uaddr;
		क्रम (n = 0 ; n < addr->srose_ndigis ; n++)
			rose->source_digis[n] = full_addr->srose_digis[n];
	पूर्ण अन्यथा अणु
		अगर (rose->source_ndigis == 1) अणु
			rose->source_digis[0] = addr->srose_digi;
		पूर्ण
	पूर्ण

	rose_insert_socket(sk);

	sock_reset_flag(sk, SOCK_ZAPPED);

	वापस 0;
पूर्ण

अटल पूर्णांक rose_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	काष्ठा sockaddr_rose *addr = (काष्ठा sockaddr_rose *)uaddr;
	अचिन्हित अक्षर cause, diagnostic;
	काष्ठा net_device *dev;
	ax25_uid_assoc *user;
	पूर्णांक n, err = 0;

	अगर (addr_len != माप(काष्ठा sockaddr_rose) && addr_len != माप(काष्ठा full_sockaddr_rose))
		वापस -EINVAL;

	अगर (addr->srose_family != AF_ROSE)
		वापस -EINVAL;

	अगर (addr_len == माप(काष्ठा sockaddr_rose) && addr->srose_ndigis > 1)
		वापस -EINVAL;

	अगर ((अचिन्हित पूर्णांक) addr->srose_ndigis > ROSE_MAX_DIGIS)
		वापस -EINVAL;

	/* Source + Destination digis should not exceed ROSE_MAX_DIGIS */
	अगर ((rose->source_ndigis + addr->srose_ndigis) > ROSE_MAX_DIGIS)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (sk->sk_state == TCP_ESTABLISHED && sock->state == SS_CONNECTING) अणु
		/* Connect completed during a ERESTARTSYS event */
		sock->state = SS_CONNECTED;
		जाओ out_release;
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE && sock->state == SS_CONNECTING) अणु
		sock->state = SS_UNCONNECTED;
		err = -ECONNREFUSED;
		जाओ out_release;
	पूर्ण

	अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		/* No reconnect on a seqpacket socket */
		err = -EISCONN;
		जाओ out_release;
	पूर्ण

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	rose->neighbour = rose_get_neigh(&addr->srose_addr, &cause,
					 &diagnostic, 0);
	अगर (!rose->neighbour) अणु
		err = -ENETUNREACH;
		जाओ out_release;
	पूर्ण

	rose->lci = rose_new_lci(rose->neighbour);
	अगर (!rose->lci) अणु
		err = -ENETUNREACH;
		जाओ out_release;
	पूर्ण

	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु	/* Must bind first - स्वतःbinding in this may or may not work */
		sock_reset_flag(sk, SOCK_ZAPPED);

		अगर ((dev = rose_dev_first()) == शून्य) अणु
			err = -ENETUNREACH;
			जाओ out_release;
		पूर्ण

		user = ax25_findbyuid(current_euid());
		अगर (!user) अणु
			err = -EINVAL;
			जाओ out_release;
		पूर्ण

		स_नकल(&rose->source_addr, dev->dev_addr, ROSE_ADDR_LEN);
		rose->source_call = user->call;
		rose->device      = dev;
		ax25_uid_put(user);

		rose_insert_socket(sk);		/* Finish the bind */
	पूर्ण
	rose->dest_addr   = addr->srose_addr;
	rose->dest_call   = addr->srose_call;
	rose->अक्रम        = ((दीर्घ)rose & 0xFFFF) + rose->lci;
	rose->dest_ndigis = addr->srose_ndigis;

	अगर (addr_len == माप(काष्ठा full_sockaddr_rose)) अणु
		काष्ठा full_sockaddr_rose *full_addr = (काष्ठा full_sockaddr_rose *)uaddr;
		क्रम (n = 0 ; n < addr->srose_ndigis ; n++)
			rose->dest_digis[n] = full_addr->srose_digis[n];
	पूर्ण अन्यथा अणु
		अगर (rose->dest_ndigis == 1) अणु
			rose->dest_digis[0] = addr->srose_digi;
		पूर्ण
	पूर्ण

	/* Move to connecting socket, start sending Connect Requests */
	sock->state   = SS_CONNECTING;
	sk->sk_state     = TCP_SYN_SENT;

	rose->state = ROSE_STATE_1;

	rose->neighbour->use++;

	rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CALL_REQUEST);
	rose_start_heartbeat(sk);
	rose_start_t1समयr(sk);

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

अटल पूर्णांक rose_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
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
	skb->sk = शून्य;
	kमुक्त_skb(skb);
	sk_acceptq_हटाओd(sk);

out_release:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक rose_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
	पूर्णांक peer)
अणु
	काष्ठा full_sockaddr_rose *srose = (काष्ठा full_sockaddr_rose *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	पूर्णांक n;

	स_रखो(srose, 0, माप(*srose));
	अगर (peer != 0) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -ENOTCONN;
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->dest_addr;
		srose->srose_call   = rose->dest_call;
		srose->srose_ndigis = rose->dest_ndigis;
		क्रम (n = 0; n < rose->dest_ndigis; n++)
			srose->srose_digis[n] = rose->dest_digis[n];
	पूर्ण अन्यथा अणु
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->source_addr;
		srose->srose_call   = rose->source_call;
		srose->srose_ndigis = rose->source_ndigis;
		क्रम (n = 0; n < rose->source_ndigis; n++)
			srose->srose_digis[n] = rose->source_digis[n];
	पूर्ण

	वापस माप(काष्ठा full_sockaddr_rose);
पूर्ण

पूर्णांक rose_rx_call_request(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा rose_neigh *neigh, अचिन्हित पूर्णांक lci)
अणु
	काष्ठा sock *sk;
	काष्ठा sock *make;
	काष्ठा rose_sock *make_rose;
	काष्ठा rose_facilities_काष्ठा facilities;
	पूर्णांक n;

	skb->sk = शून्य;		/* Initially we करोn't know who it's क्रम */

	/*
	 *	skb->data poपूर्णांकs to the rose frame start
	 */
	स_रखो(&facilities, 0x00, माप(काष्ठा rose_facilities_काष्ठा));

	अगर (!rose_parse_facilities(skb->data + ROSE_CALL_REQ_FACILITIES_OFF,
				   skb->len - ROSE_CALL_REQ_FACILITIES_OFF,
				   &facilities)) अणु
		rose_transmit_clear_request(neigh, lci, ROSE_INVALID_FACILITY, 76);
		वापस 0;
	पूर्ण

	sk = rose_find_listener(&facilities.source_addr, &facilities.source_call);

	/*
	 * We can't accept the Call Request.
	 */
	अगर (sk == शून्य || sk_acceptq_is_full(sk) ||
	    (make = rose_make_new(sk)) == शून्य) अणु
		rose_transmit_clear_request(neigh, lci, ROSE_NETWORK_CONGESTION, 120);
		वापस 0;
	पूर्ण

	skb->sk     = make;
	make->sk_state = TCP_ESTABLISHED;
	make_rose = rose_sk(make);

	make_rose->lci           = lci;
	make_rose->dest_addr     = facilities.dest_addr;
	make_rose->dest_call     = facilities.dest_call;
	make_rose->dest_ndigis   = facilities.dest_ndigis;
	क्रम (n = 0 ; n < facilities.dest_ndigis ; n++)
		make_rose->dest_digis[n] = facilities.dest_digis[n];
	make_rose->source_addr   = facilities.source_addr;
	make_rose->source_call   = facilities.source_call;
	make_rose->source_ndigis = facilities.source_ndigis;
	क्रम (n = 0 ; n < facilities.source_ndigis ; n++)
		make_rose->source_digis[n] = facilities.source_digis[n];
	make_rose->neighbour     = neigh;
	make_rose->device        = dev;
	make_rose->facilities    = facilities;

	make_rose->neighbour->use++;

	अगर (rose_sk(sk)->defer) अणु
		make_rose->state = ROSE_STATE_5;
	पूर्ण अन्यथा अणु
		rose_ग_लिखो_पूर्णांकernal(make, ROSE_CALL_ACCEPTED);
		make_rose->state = ROSE_STATE_3;
		rose_start_idleसमयr(make);
	पूर्ण

	make_rose->condition = 0x00;
	make_rose->vs        = 0;
	make_rose->va        = 0;
	make_rose->vr        = 0;
	make_rose->vl        = 0;
	sk_acceptq_added(sk);

	rose_insert_socket(make);

	skb_queue_head(&sk->sk_receive_queue, skb);

	rose_start_heartbeat(make);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);

	वापस 1;
पूर्ण

अटल पूर्णांक rose_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_rose *, usrose, msg->msg_name);
	पूर्णांक err;
	काष्ठा full_sockaddr_rose srose;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *यंत्रptr;
	पूर्णांक n, size, qbit = 0;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_CMSG_COMPAT))
		वापस -EINVAL;

	अगर (sock_flag(sk, SOCK_ZAPPED))
		वापस -EADDRNOTAVAIL;

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		send_sig(SIGPIPE, current, 0);
		वापस -EPIPE;
	पूर्ण

	अगर (rose->neighbour == शून्य || rose->device == शून्य)
		वापस -ENETUNREACH;

	अगर (usrose != शून्य) अणु
		अगर (msg->msg_namelen != माप(काष्ठा sockaddr_rose) && msg->msg_namelen != माप(काष्ठा full_sockaddr_rose))
			वापस -EINVAL;
		स_रखो(&srose, 0, माप(काष्ठा full_sockaddr_rose));
		स_नकल(&srose, usrose, msg->msg_namelen);
		अगर (rosecmp(&rose->dest_addr, &srose.srose_addr) != 0 ||
		    ax25cmp(&rose->dest_call, &srose.srose_call) != 0)
			वापस -EISCONN;
		अगर (srose.srose_ndigis != rose->dest_ndigis)
			वापस -EISCONN;
		अगर (srose.srose_ndigis == rose->dest_ndigis) अणु
			क्रम (n = 0 ; n < srose.srose_ndigis ; n++)
				अगर (ax25cmp(&rose->dest_digis[n],
					    &srose.srose_digis[n]))
					वापस -EISCONN;
		पूर्ण
		अगर (srose.srose_family != AF_ROSE)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -ENOTCONN;

		srose.srose_family = AF_ROSE;
		srose.srose_addr   = rose->dest_addr;
		srose.srose_call   = rose->dest_call;
		srose.srose_ndigis = rose->dest_ndigis;
		क्रम (n = 0 ; n < rose->dest_ndigis ; n++)
			srose.srose_digis[n] = rose->dest_digis[n];
	पूर्ण

	/* Build a packet */
	/* Sanity check the packet size */
	अगर (len > 65535)
		वापस -EMSGSIZE;

	size = len + AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN;

	अगर ((skb = sock_alloc_send_skb(sk, size, msg->msg_flags & MSG_DONTWAIT, &err)) == शून्य)
		वापस err;

	skb_reserve(skb, AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN);

	/*
	 *	Put the data on the end
	 */

	skb_reset_transport_header(skb);
	skb_put(skb, len);

	err = स_नकल_from_msg(skb_transport_header(skb), msg, len);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	/*
	 *	If the Q BIT Include socket option is in क्रमce, the first
	 *	byte of the user data is the logical value of the Q Bit.
	 */
	अगर (rose->qbitincl) अणु
		qbit = skb->data[0];
		skb_pull(skb, 1);
	पूर्ण

	/*
	 *	Push करोwn the ROSE header
	 */
	यंत्रptr = skb_push(skb, ROSE_MIN_LEN);

	/* Build a ROSE Network header */
	यंत्रptr[0] = ((rose->lci >> 8) & 0x0F) | ROSE_GFI;
	यंत्रptr[1] = (rose->lci >> 0) & 0xFF;
	यंत्रptr[2] = ROSE_DATA;

	अगर (qbit)
		यंत्रptr[0] |= ROSE_Q_BIT;

	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		kमुक्त_skb(skb);
		वापस -ENOTCONN;
	पूर्ण

#अगर_घोषित M_BIT
#घोषणा ROSE_PACLEN (256-ROSE_MIN_LEN)
	अगर (skb->len - ROSE_MIN_LEN > ROSE_PACLEN) अणु
		अचिन्हित अक्षर header[ROSE_MIN_LEN];
		काष्ठा sk_buff *skbn;
		पूर्णांक frontlen;
		पूर्णांक lg;

		/* Save a copy of the Header */
		skb_copy_from_linear_data(skb, header, ROSE_MIN_LEN);
		skb_pull(skb, ROSE_MIN_LEN);

		frontlen = skb_headroom(skb);

		जबतक (skb->len > 0) अणु
			अगर ((skbn = sock_alloc_send_skb(sk, frontlen + ROSE_PACLEN, 0, &err)) == शून्य) अणु
				kमुक्त_skb(skb);
				वापस err;
			पूर्ण

			skbn->sk   = sk;
			skbn->मुक्त = 1;
			skbn->arp  = 1;

			skb_reserve(skbn, frontlen);

			lg = (ROSE_PACLEN > skb->len) ? skb->len : ROSE_PACLEN;

			/* Copy the user data */
			skb_copy_from_linear_data(skb, skb_put(skbn, lg), lg);
			skb_pull(skb, lg);

			/* Duplicate the Header */
			skb_push(skbn, ROSE_MIN_LEN);
			skb_copy_to_linear_data(skbn, header, ROSE_MIN_LEN);

			अगर (skb->len > 0)
				skbn->data[2] |= M_BIT;

			skb_queue_tail(&sk->sk_ग_लिखो_queue, skbn); /* Throw it on the queue */
		पूर्ण

		skb->मुक्त = 1;
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);		/* Throw it on the queue */
	पूर्ण
#अन्यथा
	skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);	/* Shove it onto the queue */
#पूर्ण_अगर

	rose_kick(sk);

	वापस len;
पूर्ण


अटल पूर्णांक rose_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	माप_प्रकार copied;
	अचिन्हित अक्षर *यंत्रptr;
	काष्ठा sk_buff *skb;
	पूर्णांक n, er, qbit;

	/*
	 * This works क्रम seqpacket too. The receiver has ordered the queue क्रम
	 * us! We करो one quick check first though
	 */
	अगर (sk->sk_state != TCP_ESTABLISHED)
		वापस -ENOTCONN;

	/* Now we can treat all alike */
	अगर ((skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT, flags & MSG_DONTWAIT, &er)) == शून्य)
		वापस er;

	qbit = (skb->data[0] & ROSE_Q_BIT) == ROSE_Q_BIT;

	skb_pull(skb, ROSE_MIN_LEN);

	अगर (rose->qbitincl) अणु
		यंत्रptr  = skb_push(skb, 1);
		*यंत्रptr = qbit;
	पूर्ण

	skb_reset_transport_header(skb);
	copied     = skb->len;

	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	skb_copy_datagram_msg(skb, 0, msg, copied);

	अगर (msg->msg_name) अणु
		काष्ठा sockaddr_rose *srose;
		DECLARE_SOCKADDR(काष्ठा full_sockaddr_rose *, full_srose,
				 msg->msg_name);

		स_रखो(msg->msg_name, 0, माप(काष्ठा full_sockaddr_rose));
		srose = msg->msg_name;
		srose->srose_family = AF_ROSE;
		srose->srose_addr   = rose->dest_addr;
		srose->srose_call   = rose->dest_call;
		srose->srose_ndigis = rose->dest_ndigis;
		क्रम (n = 0 ; n < rose->dest_ndigis ; n++)
			full_srose->srose_digis[n] = rose->dest_digis[n];
		msg->msg_namelen = माप(काष्ठा full_sockaddr_rose);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	वापस copied;
पूर्ण


अटल पूर्णांक rose_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rose_sock *rose = rose_sk(sk);
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल TIOCOUTQ: अणु
		दीर्घ amount;

		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		वापस put_user(amount, (अचिन्हित पूर्णांक __user *) argp);
	पूर्ण

	हाल TIOCINQ: अणु
		काष्ठा sk_buff *skb;
		दीर्घ amount = 0L;
		/* These two are safe on a single CPU प्रणाली as only user tasks fiddle here */
		अगर ((skb = skb_peek(&sk->sk_receive_queue)) != शून्य)
			amount = skb->len;
		वापस put_user(amount, (अचिन्हित पूर्णांक __user *) argp);
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
	हाल SIOCRSCLRRT:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		वापस rose_rt_ioctl(cmd, argp);

	हाल SIOCRSGCAUSE: अणु
		काष्ठा rose_cause_काष्ठा rose_cause;
		rose_cause.cause      = rose->cause;
		rose_cause.diagnostic = rose->diagnostic;
		वापस copy_to_user(argp, &rose_cause, माप(काष्ठा rose_cause_काष्ठा)) ? -EFAULT : 0;
	पूर्ण

	हाल SIOCRSSCAUSE: अणु
		काष्ठा rose_cause_काष्ठा rose_cause;
		अगर (copy_from_user(&rose_cause, argp, माप(काष्ठा rose_cause_काष्ठा)))
			वापस -EFAULT;
		rose->cause      = rose_cause.cause;
		rose->diagnostic = rose_cause.diagnostic;
		वापस 0;
	पूर्ण

	हाल SIOCRSSL2CALL:
		अगर (!capable(CAP_NET_ADMIN)) वापस -EPERM;
		अगर (ax25cmp(&rose_callsign, &null_ax25_address) != 0)
			ax25_listen_release(&rose_callsign, शून्य);
		अगर (copy_from_user(&rose_callsign, argp, माप(ax25_address)))
			वापस -EFAULT;
		अगर (ax25cmp(&rose_callsign, &null_ax25_address) != 0)
			वापस ax25_listen_रेजिस्टर(&rose_callsign, शून्य);

		वापस 0;

	हाल SIOCRSGL2CALL:
		वापस copy_to_user(argp, &rose_callsign, माप(ax25_address)) ? -EFAULT : 0;

	हाल SIOCRSACCEPT:
		अगर (rose->state == ROSE_STATE_5) अणु
			rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CALL_ACCEPTED);
			rose_start_idleसमयr(sk);
			rose->condition = 0x00;
			rose->vs        = 0;
			rose->va        = 0;
			rose->vr        = 0;
			rose->vl        = 0;
			rose->state     = ROSE_STATE_3;
		पूर्ण
		वापस 0;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *rose_info_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rose_list_lock)
अणु
	spin_lock_bh(&rose_list_lock);
	वापस seq_hlist_start_head(&rose_list, *pos);
पूर्ण

अटल व्योम *rose_info_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &rose_list, pos);
पूर्ण

अटल व्योम rose_info_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rose_list_lock)
अणु
	spin_unlock_bh(&rose_list_lock);
पूर्ण

अटल पूर्णांक rose_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11], rsbuf[11];

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "dest_addr  dest_call src_addr   src_call  dev   lci neigh st vs vr va   t  t1  t2  t3  hb    idle Snd-Q Rcv-Q inode\n");

	अन्यथा अणु
		काष्ठा sock *s = sk_entry(v);
		काष्ठा rose_sock *rose = rose_sk(s);
		स्थिर अक्षर *devname, *callsign;
		स्थिर काष्ठा net_device *dev = rose->device;

		अगर (!dev)
			devname = "???";
		अन्यथा
			devname = dev->name;

		seq_म_लिखो(seq, "%-10s %-9s ",
			   rose2asc(rsbuf, &rose->dest_addr),
			   ax2asc(buf, &rose->dest_call));

		अगर (ax25cmp(&rose->source_call, &null_ax25_address) == 0)
			callsign = "??????-?";
		अन्यथा
			callsign = ax2asc(buf, &rose->source_call);

		seq_म_लिखो(seq,
			   "%-10s %-9s %-5s %3.3X %05d  %d  %d  %d  %d %3lu %3lu %3lu %3lu %3lu %3lu/%03lu %5d %5d %ld\n",
			rose2asc(rsbuf, &rose->source_addr),
			callsign,
			devname,
			rose->lci & 0x0FFF,
			(rose->neighbour) ? rose->neighbour->number : 0,
			rose->state,
			rose->vs,
			rose->vr,
			rose->va,
			ax25_display_समयr(&rose->समयr) / HZ,
			rose->t1 / HZ,
			rose->t2 / HZ,
			rose->t3 / HZ,
			rose->hb / HZ,
			ax25_display_समयr(&rose->idleसमयr) / (60 * HZ),
			rose->idle / (60 * HZ),
			sk_wmem_alloc_get(s),
			sk_rmem_alloc_get(s),
			s->sk_socket ? SOCK_INODE(s->sk_socket)->i_ino : 0L);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations rose_info_seqops = अणु
	.start = rose_info_start,
	.next = rose_info_next,
	.stop = rose_info_stop,
	.show = rose_info_show,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_PROC_FS */

अटल स्थिर काष्ठा net_proto_family rose_family_ops = अणु
	.family		=	PF_ROSE,
	.create		=	rose_create,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops rose_proto_ops = अणु
	.family		=	PF_ROSE,
	.owner		=	THIS_MODULE,
	.release	=	rose_release,
	.bind		=	rose_bind,
	.connect	=	rose_connect,
	.socketpair	=	sock_no_socketpair,
	.accept		=	rose_accept,
	.getname	=	rose_getname,
	.poll		=	datagram_poll,
	.ioctl		=	rose_ioctl,
	.gettstamp	=	sock_gettstamp,
	.listen		=	rose_listen,
	.shutकरोwn	=	sock_no_shutकरोwn,
	.setsockopt	=	rose_setsockopt,
	.माला_लोockopt	=	rose_माला_लोockopt,
	.sendmsg	=	rose_sendmsg,
	.recvmsg	=	rose_recvmsg,
	.mmap		=	sock_no_mmap,
	.sendpage	=	sock_no_sendpage,
पूर्ण;

अटल काष्ठा notअगरier_block rose_dev_notअगरier = अणु
	.notअगरier_call	=	rose_device_event,
पूर्ण;

अटल काष्ठा net_device **dev_rose;

अटल काष्ठा ax25_protocol rose_pid = अणु
	.pid	= AX25_P_ROSE,
	.func	= rose_route_frame
पूर्ण;

अटल काष्ठा ax25_linkfail rose_linkfail_notअगरier = अणु
	.func	= rose_link_failed
पूर्ण;

अटल पूर्णांक __init rose_proto_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rc;

	अगर (rose_ndevs > 0x7FFFFFFF/माप(काष्ठा net_device *)) अणु
		prपूर्णांकk(KERN_ERR "ROSE: rose_proto_init - rose_ndevs parameter too large\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = proto_रेजिस्टर(&rose_proto, 0);
	अगर (rc != 0)
		जाओ out;

	rose_callsign = null_ax25_address;

	dev_rose = kसुस्मृति(rose_ndevs, माप(काष्ठा net_device *),
			   GFP_KERNEL);
	अगर (dev_rose == शून्य) अणु
		prपूर्णांकk(KERN_ERR "ROSE: rose_proto_init - unable to allocate device structure\n");
		rc = -ENOMEM;
		जाओ out_proto_unरेजिस्टर;
	पूर्ण

	क्रम (i = 0; i < rose_ndevs; i++) अणु
		काष्ठा net_device *dev;
		अक्षर name[IFNAMSIZ];

		प्र_लिखो(name, "rose%d", i);
		dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, rose_setup);
		अगर (!dev) अणु
			prपूर्णांकk(KERN_ERR "ROSE: rose_proto_init - unable to allocate memory\n");
			rc = -ENOMEM;
			जाओ fail;
		पूर्ण
		rc = रेजिस्टर_netdev(dev);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "ROSE: netdevice registration failed\n");
			मुक्त_netdev(dev);
			जाओ fail;
		पूर्ण
		rose_set_lockdep_key(dev);
		dev_rose[i] = dev;
	पूर्ण

	sock_रेजिस्टर(&rose_family_ops);
	रेजिस्टर_netdevice_notअगरier(&rose_dev_notअगरier);

	ax25_रेजिस्टर_pid(&rose_pid);
	ax25_linkfail_रेजिस्टर(&rose_linkfail_notअगरier);

#अगर_घोषित CONFIG_SYSCTL
	rose_रेजिस्टर_sysctl();
#पूर्ण_अगर
	rose_loopback_init();

	rose_add_loopback_neigh();

	proc_create_seq("rose", 0444, init_net.proc_net, &rose_info_seqops);
	proc_create_seq("rose_neigh", 0444, init_net.proc_net,
		    &rose_neigh_seqops);
	proc_create_seq("rose_nodes", 0444, init_net.proc_net,
		    &rose_node_seqops);
	proc_create_seq("rose_routes", 0444, init_net.proc_net,
		    &rose_route_seqops);
out:
	वापस rc;
fail:
	जबतक (--i >= 0) अणु
		unरेजिस्टर_netdev(dev_rose[i]);
		मुक्त_netdev(dev_rose[i]);
	पूर्ण
	kमुक्त(dev_rose);
out_proto_unरेजिस्टर:
	proto_unरेजिस्टर(&rose_proto);
	जाओ out;
पूर्ण
module_init(rose_proto_init);

module_param(rose_ndevs, पूर्णांक, 0);
MODULE_PARM_DESC(rose_ndevs, "number of ROSE devices");

MODULE_AUTHOR("Jonathan Naylor G4KLX <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The amateur radio ROSE network layer protocol");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_ROSE);

अटल व्योम __निकास rose_निकास(व्योम)
अणु
	पूर्णांक i;

	हटाओ_proc_entry("rose", init_net.proc_net);
	हटाओ_proc_entry("rose_neigh", init_net.proc_net);
	हटाओ_proc_entry("rose_nodes", init_net.proc_net);
	हटाओ_proc_entry("rose_routes", init_net.proc_net);
	rose_loopback_clear();

	rose_rt_मुक्त();

	ax25_protocol_release(AX25_P_ROSE);
	ax25_linkfail_release(&rose_linkfail_notअगरier);

	अगर (ax25cmp(&rose_callsign, &null_ax25_address) != 0)
		ax25_listen_release(&rose_callsign, शून्य);

#अगर_घोषित CONFIG_SYSCTL
	rose_unरेजिस्टर_sysctl();
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&rose_dev_notअगरier);

	sock_unरेजिस्टर(PF_ROSE);

	क्रम (i = 0; i < rose_ndevs; i++) अणु
		काष्ठा net_device *dev = dev_rose[i];

		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण

	kमुक्त(dev_rose);
	proto_unरेजिस्टर(&rose_proto);
पूर्ण

module_निकास(rose_निकास);
