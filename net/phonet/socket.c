<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: socket.c
 *
 * Phonet sockets
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Authors: Sakari Ailus <sakari.ailus@nokia.com>
 *          Rथऊmi Denis-Courmont
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>

#समावेश <linux/phonet.h>
#समावेश <linux/export.h>
#समावेश <net/phonet/phonet.h>
#समावेश <net/phonet/pep.h>
#समावेश <net/phonet/pn_dev.h>

अटल पूर्णांक pn_socket_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		sock->sk = शून्य;
		sk->sk_prot->बंद(sk, 0);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PN_HASHSIZE	16
#घोषणा PN_HASHMASK	(PN_HASHSIZE-1)


अटल काष्ठा  अणु
	काष्ठा hlist_head hlist[PN_HASHSIZE];
	काष्ठा mutex lock;
पूर्ण pnsocks;

व्योम __init pn_sock_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PN_HASHSIZE; i++)
		INIT_HLIST_HEAD(pnsocks.hlist + i);
	mutex_init(&pnsocks.lock);
पूर्ण

अटल काष्ठा hlist_head *pn_hash_list(u16 obj)
अणु
	वापस pnsocks.hlist + (obj & PN_HASHMASK);
पूर्ण

/*
 * Find address based on socket address, match only certain fields.
 * Also grab sock अगर it was found. Remember to sock_put it later.
 */
काष्ठा sock *pn_find_sock_by_sa(काष्ठा net *net, स्थिर काष्ठा sockaddr_pn *spn)
अणु
	काष्ठा sock *sknode;
	काष्ठा sock *rval = शून्य;
	u16 obj = pn_sockaddr_get_object(spn);
	u8 res = spn->spn_resource;
	काष्ठा hlist_head *hlist = pn_hash_list(obj);

	rcu_पढ़ो_lock();
	sk_क्रम_each_rcu(sknode, hlist) अणु
		काष्ठा pn_sock *pn = pn_sk(sknode);
		BUG_ON(!pn->sobject); /* unbound socket */

		अगर (!net_eq(sock_net(sknode), net))
			जारी;
		अगर (pn_port(obj)) अणु
			/* Look up socket by port */
			अगर (pn_port(pn->sobject) != pn_port(obj))
				जारी;
		पूर्ण अन्यथा अणु
			/* If port is zero, look up by resource */
			अगर (pn->resource != res)
				जारी;
		पूर्ण
		अगर (pn_addr(pn->sobject) &&
		    pn_addr(pn->sobject) != pn_addr(obj))
			जारी;

		rval = sknode;
		sock_hold(sknode);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rval;
पूर्ण

/* Deliver a broadcast packet (only in bottom-half) */
व्योम pn_deliver_sock_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा hlist_head *hlist = pnsocks.hlist;
	अचिन्हित पूर्णांक h;

	rcu_पढ़ो_lock();
	क्रम (h = 0; h < PN_HASHSIZE; h++) अणु
		काष्ठा sock *sknode;

		sk_क्रम_each(sknode, hlist) अणु
			काष्ठा sk_buff *clone;

			अगर (!net_eq(sock_net(sknode), net))
				जारी;
			अगर (!sock_flag(sknode, SOCK_BROADCAST))
				जारी;

			clone = skb_clone(skb, GFP_ATOMIC);
			अगर (clone) अणु
				sock_hold(sknode);
				sk_receive_skb(sknode, clone, 0);
			पूर्ण
		पूर्ण
		hlist++;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक pn_sock_hash(काष्ठा sock *sk)
अणु
	काष्ठा hlist_head *hlist = pn_hash_list(pn_sk(sk)->sobject);

	mutex_lock(&pnsocks.lock);
	sk_add_node_rcu(sk, hlist);
	mutex_unlock(&pnsocks.lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pn_sock_hash);

व्योम pn_sock_unhash(काष्ठा sock *sk)
अणु
	mutex_lock(&pnsocks.lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&pnsocks.lock);
	pn_sock_unbind_all_res(sk);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(pn_sock_unhash);

अटल DEFINE_MUTEX(port_mutex);

अटल पूर्णांक pn_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pn_sock *pn = pn_sk(sk);
	काष्ठा sockaddr_pn *spn = (काष्ठा sockaddr_pn *)addr;
	पूर्णांक err;
	u16 handle;
	u8 saddr;

	अगर (sk->sk_prot->bind)
		वापस sk->sk_prot->bind(sk, addr, len);

	अगर (len < माप(काष्ठा sockaddr_pn))
		वापस -EINVAL;
	अगर (spn->spn_family != AF_PHONET)
		वापस -EAFNOSUPPORT;

	handle = pn_sockaddr_get_object((काष्ठा sockaddr_pn *)addr);
	saddr = pn_addr(handle);
	अगर (saddr && phonet_address_lookup(sock_net(sk), saddr))
		वापस -EADDRNOTAVAIL;

	lock_sock(sk);
	अगर (sk->sk_state != TCP_CLOSE || pn_port(pn->sobject)) अणु
		err = -EINVAL; /* attempt to rebind */
		जाओ out;
	पूर्ण
	WARN_ON(sk_hashed(sk));
	mutex_lock(&port_mutex);
	err = sk->sk_prot->get_port(sk, pn_port(handle));
	अगर (err)
		जाओ out_port;

	/* get_port() sets the port, bind() sets the address अगर applicable */
	pn->sobject = pn_object(saddr, pn_port(pn->sobject));
	pn->resource = spn->spn_resource;

	/* Enable RX on the socket */
	err = sk->sk_prot->hash(sk);
out_port:
	mutex_unlock(&port_mutex);
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक pn_socket_स्वतःbind(काष्ठा socket *sock)
अणु
	काष्ठा sockaddr_pn sa;
	पूर्णांक err;

	स_रखो(&sa, 0, माप(sa));
	sa.spn_family = AF_PHONET;
	err = pn_socket_bind(sock, (काष्ठा sockaddr *)&sa,
				माप(काष्ठा sockaddr_pn));
	अगर (err != -EINVAL)
		वापस err;
	BUG_ON(!pn_port(pn_sk(sock->sk)->sobject));
	वापस 0; /* socket was alपढ़ोy bound */
पूर्ण

अटल पूर्णांक pn_socket_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
		पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pn_sock *pn = pn_sk(sk);
	काष्ठा sockaddr_pn *spn = (काष्ठा sockaddr_pn *)addr;
	काष्ठा task_काष्ठा *tsk = current;
	दीर्घ समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);
	पूर्णांक err;

	अगर (pn_socket_स्वतःbind(sock))
		वापस -ENOBUFS;
	अगर (len < माप(काष्ठा sockaddr_pn))
		वापस -EINVAL;
	अगर (spn->spn_family != AF_PHONET)
		वापस -EAFNOSUPPORT;

	lock_sock(sk);

	चयन (sock->state) अणु
	हाल SS_UNCONNECTED:
		अगर (sk->sk_state != TCP_CLOSE) अणु
			err = -EISCONN;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल SS_CONNECTING:
		err = -EALREADY;
		जाओ out;
	शेष:
		err = -EISCONN;
		जाओ out;
	पूर्ण

	pn->करोbject = pn_sockaddr_get_object(spn);
	pn->resource = pn_sockaddr_get_resource(spn);
	sock->state = SS_CONNECTING;

	err = sk->sk_prot->connect(sk, addr, len);
	अगर (err) अणु
		sock->state = SS_UNCONNECTED;
		pn->करोbject = 0;
		जाओ out;
	पूर्ण

	जबतक (sk->sk_state == TCP_SYN_SENT) अणु
		DEFINE_WAIT(रुको);

		अगर (!समयo) अणु
			err = -EINPROGRESS;
			जाओ out;
		पूर्ण
		अगर (संकेत_pending(tsk)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			जाओ out;
		पूर्ण

		prepare_to_रुको_exclusive(sk_sleep(sk), &रुको,
						TASK_INTERRUPTIBLE);
		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock(sk);
		finish_रुको(sk_sleep(sk), &रुको);
	पूर्ण

	अगर ((1 << sk->sk_state) & (TCPF_SYN_RECV|TCPF_ESTABLISHED))
		err = 0;
	अन्यथा अगर (sk->sk_state == TCP_CLOSE_WAIT)
		err = -ECONNRESET;
	अन्यथा
		err = -ECONNREFUSED;
	sock->state = err ? SS_UNCONNECTED : SS_CONNECTED;
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक pn_socket_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			    पूर्णांक flags, bool kern)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *newsk;
	पूर्णांक err;

	अगर (unlikely(sk->sk_state != TCP_LISTEN))
		वापस -EINVAL;

	newsk = sk->sk_prot->accept(sk, flags, &err, kern);
	अगर (!newsk)
		वापस err;

	lock_sock(newsk);
	sock_graft(newsk, newsock);
	newsock->state = SS_CONNECTED;
	release_sock(newsk);
	वापस 0;
पूर्ण

अटल पूर्णांक pn_socket_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				पूर्णांक peer)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pn_sock *pn = pn_sk(sk);

	स_रखो(addr, 0, माप(काष्ठा sockaddr_pn));
	addr->sa_family = AF_PHONET;
	अगर (!peer) /* Race with bind() here is userland's problem. */
		pn_sockaddr_set_object((काष्ठा sockaddr_pn *)addr,
					pn->sobject);

	वापस माप(काष्ठा sockaddr_pn);
पूर्ण

अटल __poll_t pn_socket_poll(काष्ठा file *file, काष्ठा socket *sock,
					poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pep_sock *pn = pep_sk(sk);
	__poll_t mask = 0;

	poll_रुको(file, sk_sleep(sk), रुको);

	अगर (sk->sk_state == TCP_CLOSE)
		वापस EPOLLERR;
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (!skb_queue_empty_lockless(&pn->ctrlreq_queue))
		mask |= EPOLLPRI;
	अगर (!mask && sk->sk_state == TCP_CLOSE_WAIT)
		वापस EPOLLHUP;

	अगर (sk->sk_state == TCP_ESTABLISHED &&
		refcount_पढ़ो(&sk->sk_wmem_alloc) < sk->sk_sndbuf &&
		atomic_पढ़ो(&pn->tx_credits))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	वापस mask;
पूर्ण

अटल पूर्णांक pn_socket_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pn_sock *pn = pn_sk(sk);

	अगर (cmd == SIOCPNGETOBJECT) अणु
		काष्ठा net_device *dev;
		u16 handle;
		u8 saddr;

		अगर (get_user(handle, (__u16 __user *)arg))
			वापस -EFAULT;

		lock_sock(sk);
		अगर (sk->sk_bound_dev_अगर)
			dev = dev_get_by_index(sock_net(sk),
						sk->sk_bound_dev_अगर);
		अन्यथा
			dev = phonet_device_get(sock_net(sk));
		अगर (dev && (dev->flags & IFF_UP))
			saddr = phonet_address_get(dev, pn_addr(handle));
		अन्यथा
			saddr = PN_NO_ADDR;
		release_sock(sk);

		अगर (dev)
			dev_put(dev);
		अगर (saddr == PN_NO_ADDR)
			वापस -EHOSTUNREACH;

		handle = pn_object(saddr, pn_port(pn->sobject));
		वापस put_user(handle, (__u16 __user *)arg);
	पूर्ण

	वापस sk->sk_prot->ioctl(sk, cmd, arg);
पूर्ण

अटल पूर्णांक pn_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	अगर (pn_socket_स्वतःbind(sock))
		वापस -ENOBUFS;

	lock_sock(sk);
	अगर (sock->state != SS_UNCONNECTED) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (sk->sk_state != TCP_LISTEN) अणु
		sk->sk_state = TCP_LISTEN;
		sk->sk_ack_backlog = 0;
	पूर्ण
	sk->sk_max_ack_backlog = backlog;
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक pn_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			     माप_प्रकार total_len)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (pn_socket_स्वतःbind(sock))
		वापस -EAGAIN;

	वापस sk->sk_prot->sendmsg(sk, m, total_len);
पूर्ण

स्थिर काष्ठा proto_ops phonet_dgram_ops = अणु
	.family		= AF_PHONET,
	.owner		= THIS_MODULE,
	.release	= pn_socket_release,
	.bind		= pn_socket_bind,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= pn_socket_getname,
	.poll		= datagram_poll,
	.ioctl		= pn_socket_ioctl,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.sendmsg	= pn_socket_sendmsg,
	.recvmsg	= sock_common_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

स्थिर काष्ठा proto_ops phonet_stream_ops = अणु
	.family		= AF_PHONET,
	.owner		= THIS_MODULE,
	.release	= pn_socket_release,
	.bind		= pn_socket_bind,
	.connect	= pn_socket_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= pn_socket_accept,
	.getname	= pn_socket_getname,
	.poll		= pn_socket_poll,
	.ioctl		= pn_socket_ioctl,
	.listen		= pn_socket_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.setsockopt	= sock_common_setsockopt,
	.माला_लोockopt	= sock_common_माला_लोockopt,
	.sendmsg	= pn_socket_sendmsg,
	.recvmsg	= sock_common_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;
EXPORT_SYMBOL(phonet_stream_ops);

/* allocate port क्रम a socket */
पूर्णांक pn_sock_get_port(काष्ठा sock *sk, अचिन्हित लघु sport)
अणु
	अटल पूर्णांक port_cur;
	काष्ठा net *net = sock_net(sk);
	काष्ठा pn_sock *pn = pn_sk(sk);
	काष्ठा sockaddr_pn try_sa;
	काष्ठा sock *पंचांगpsk;

	स_रखो(&try_sa, 0, माप(काष्ठा sockaddr_pn));
	try_sa.spn_family = AF_PHONET;
	WARN_ON(!mutex_is_locked(&port_mutex));
	अगर (!sport) अणु
		/* search मुक्त port */
		पूर्णांक port, pmin, pmax;

		phonet_get_local_port_range(&pmin, &pmax);
		क्रम (port = pmin; port <= pmax; port++) अणु
			port_cur++;
			अगर (port_cur < pmin || port_cur > pmax)
				port_cur = pmin;

			pn_sockaddr_set_port(&try_sa, port_cur);
			पंचांगpsk = pn_find_sock_by_sa(net, &try_sa);
			अगर (पंचांगpsk == शून्य) अणु
				sport = port_cur;
				जाओ found;
			पूर्ण अन्यथा
				sock_put(पंचांगpsk);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* try to find specअगरic port */
		pn_sockaddr_set_port(&try_sa, sport);
		पंचांगpsk = pn_find_sock_by_sa(net, &try_sa);
		अगर (पंचांगpsk == शून्य)
			/* No sock there! We can use that port... */
			जाओ found;
		अन्यथा
			sock_put(पंचांगpsk);
	पूर्ण
	/* the port must be in use alपढ़ोy */
	वापस -EADDRINUSE;

found:
	pn->sobject = pn_object(pn_addr(pn->sobject), sport);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pn_sock_get_port);

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा sock *pn_sock_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा hlist_head *hlist = pnsocks.hlist;
	काष्ठा sock *sknode;
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < PN_HASHSIZE; h++) अणु
		sk_क्रम_each_rcu(sknode, hlist) अणु
			अगर (!net_eq(net, sock_net(sknode)))
				जारी;
			अगर (!pos)
				वापस sknode;
			pos--;
		पूर्ण
		hlist++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sock *pn_sock_get_next(काष्ठा seq_file *seq, काष्ठा sock *sk)
अणु
	काष्ठा net *net = seq_file_net(seq);

	करो
		sk = sk_next(sk);
	जबतक (sk && !net_eq(net, sock_net(sk)));

	वापस sk;
पूर्ण

अटल व्योम *pn_sock_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? pn_sock_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *pn_sock_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock *sk;

	अगर (v == SEQ_START_TOKEN)
		sk = pn_sock_get_idx(seq, 0);
	अन्यथा
		sk = pn_sock_get_next(seq, v);
	(*pos)++;
	वापस sk;
पूर्ण

अटल व्योम pn_sock_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक pn_sock_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_setwidth(seq, 127);
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "pt  loc  rem rs st tx_queue rx_queue "
			"  uid inode ref pointer drops");
	अन्यथा अणु
		काष्ठा sock *sk = v;
		काष्ठा pn_sock *pn = pn_sk(sk);

		seq_म_लिखो(seq, "%2d %04X:%04X:%02X %02X %08X:%08X %5d %lu "
			"%d %pK %u",
			sk->sk_protocol, pn->sobject, pn->करोbject,
			pn->resource, sk->sk_state,
			sk_wmem_alloc_get(sk), sk_rmem_alloc_get(sk),
			from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk)),
			sock_i_ino(sk),
			refcount_पढ़ो(&sk->sk_refcnt), sk,
			atomic_पढ़ो(&sk->sk_drops));
	पूर्ण
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations pn_sock_seq_ops = अणु
	.start = pn_sock_seq_start,
	.next = pn_sock_seq_next,
	.stop = pn_sock_seq_stop,
	.show = pn_sock_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा  अणु
	काष्ठा sock *sk[256];
पूर्ण pnres;

/*
 * Find and hold socket based on resource.
 */
काष्ठा sock *pn_find_sock_by_res(काष्ठा net *net, u8 res)
अणु
	काष्ठा sock *sk;

	अगर (!net_eq(net, &init_net))
		वापस शून्य;

	rcu_पढ़ो_lock();
	sk = rcu_dereference(pnres.sk[res]);
	अगर (sk)
		sock_hold(sk);
	rcu_पढ़ो_unlock();
	वापस sk;
पूर्ण

अटल DEFINE_MUTEX(resource_mutex);

पूर्णांक pn_sock_bind_res(काष्ठा sock *sk, u8 res)
अणु
	पूर्णांक ret = -EADDRINUSE;

	अगर (!net_eq(sock_net(sk), &init_net))
		वापस -ENOIOCTLCMD;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (pn_socket_स्वतःbind(sk->sk_socket))
		वापस -EAGAIN;

	mutex_lock(&resource_mutex);
	अगर (pnres.sk[res] == शून्य) अणु
		sock_hold(sk);
		rcu_assign_poपूर्णांकer(pnres.sk[res], sk);
		ret = 0;
	पूर्ण
	mutex_unlock(&resource_mutex);
	वापस ret;
पूर्ण

पूर्णांक pn_sock_unbind_res(काष्ठा sock *sk, u8 res)
अणु
	पूर्णांक ret = -ENOENT;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	mutex_lock(&resource_mutex);
	अगर (pnres.sk[res] == sk) अणु
		RCU_INIT_POINTER(pnres.sk[res], शून्य);
		ret = 0;
	पूर्ण
	mutex_unlock(&resource_mutex);

	अगर (ret == 0) अणु
		synchronize_rcu();
		sock_put(sk);
	पूर्ण
	वापस ret;
पूर्ण

व्योम pn_sock_unbind_all_res(काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक res, match = 0;

	mutex_lock(&resource_mutex);
	क्रम (res = 0; res < 256; res++) अणु
		अगर (pnres.sk[res] == sk) अणु
			RCU_INIT_POINTER(pnres.sk[res], शून्य);
			match++;
		पूर्ण
	पूर्ण
	mutex_unlock(&resource_mutex);

	जबतक (match > 0) अणु
		__sock_put(sk);
		match--;
	पूर्ण
	/* Caller is responsible क्रम RCU sync beक्रमe final sock_put() */
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा sock **pn_res_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	अचिन्हित पूर्णांक i;

	अगर (!net_eq(net, &init_net))
		वापस शून्य;

	क्रम (i = 0; i < 256; i++) अणु
		अगर (pnres.sk[i] == शून्य)
			जारी;
		अगर (!pos)
			वापस pnres.sk + i;
		pos--;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sock **pn_res_get_next(काष्ठा seq_file *seq, काष्ठा sock **sk)
अणु
	काष्ठा net *net = seq_file_net(seq);
	अचिन्हित पूर्णांक i;

	BUG_ON(!net_eq(net, &init_net));

	क्रम (i = (sk - pnres.sk) + 1; i < 256; i++)
		अगर (pnres.sk[i])
			वापस pnres.sk + i;
	वापस शून्य;
पूर्ण

अटल व्योम *pn_res_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(resource_mutex)
अणु
	mutex_lock(&resource_mutex);
	वापस *pos ? pn_res_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *pn_res_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock **sk;

	अगर (v == SEQ_START_TOKEN)
		sk = pn_res_get_idx(seq, 0);
	अन्यथा
		sk = pn_res_get_next(seq, v);
	(*pos)++;
	वापस sk;
पूर्ण

अटल व्योम pn_res_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(resource_mutex)
अणु
	mutex_unlock(&resource_mutex);
पूर्ण

अटल पूर्णांक pn_res_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_setwidth(seq, 63);
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "rs   uid inode");
	अन्यथा अणु
		काष्ठा sock **psk = v;
		काष्ठा sock *sk = *psk;

		seq_म_लिखो(seq, "%02X %5u %lu",
			   (पूर्णांक) (psk - pnres.sk),
			   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk)),
			   sock_i_ino(sk));
	पूर्ण
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations pn_res_seq_ops = अणु
	.start = pn_res_seq_start,
	.next = pn_res_seq_next,
	.stop = pn_res_seq_stop,
	.show = pn_res_seq_show,
पूर्ण;
#पूर्ण_अगर
