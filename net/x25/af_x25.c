<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Jonathan Naylor	Started coding.
 *	X.25 002	Jonathan Naylor	Centralised disconnect handling.
 *					New समयr architecture.
 *	2000-03-11	Henner Eisen	MSG_EOR handling more POSIX compliant.
 *	2000-03-22	Daniela Squassoni Allowed disabling/enabling of
 *					  facilities negotiation and increased
 *					  the throughput upper limit.
 *	2000-08-27	Arnalकरो C. Melo s/suser/capable/ + micro cleanups
 *	2000-09-04	Henner Eisen	Set sock->state in x25_accept().
 *					Fixed x25_output() related skb leakage.
 *	2000-10-02	Henner Eisen	Made x25_kick() single thपढ़ोed per socket.
 *	2000-10-27	Henner Eisen    MSG_DONTWAIT क्रम fragment allocation.
 *	2000-11-14	Henner Eisen    Closing datalink from NETDEV_GOING_DOWN
 *	2002-10-06	Arnalकरो C. Melo Get rid of cli/sti, move proc stuff to
 *					x25_proc.c, using seq_file
 *	2005-04-02	Shaun Pereira	Selective sub address matching
 *					with call user data
 *	2005-04-15	Shaun Pereira	Fast select with no restriction on
 *					response
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/compat.h>
#समावेश <linux/प्रकार.स>

#समावेश <net/x25.h>
#समावेश <net/compat.h>

पूर्णांक sysctl_x25_restart_request_समयout = X25_DEFAULT_T20;
पूर्णांक sysctl_x25_call_request_समयout    = X25_DEFAULT_T21;
पूर्णांक sysctl_x25_reset_request_समयout   = X25_DEFAULT_T22;
पूर्णांक sysctl_x25_clear_request_समयout   = X25_DEFAULT_T23;
पूर्णांक sysctl_x25_ack_holdback_समयout    = X25_DEFAULT_T2;
पूर्णांक sysctl_x25_क्रमward                 = 0;

HLIST_HEAD(x25_list);
DEFINE_RWLOCK(x25_list_lock);

अटल स्थिर काष्ठा proto_ops x25_proto_ops;

अटल स्थिर काष्ठा x25_address null_x25_address = अणु"               "पूर्ण;

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_x25_subscrip_काष्ठा अणु
	अक्षर device[200-माप(compat_uदीर्घ_t)];
	compat_uदीर्घ_t global_facil_mask;
	compat_uपूर्णांक_t extended;
पूर्ण;
#पूर्ण_अगर


पूर्णांक x25_parse_address_block(काष्ठा sk_buff *skb,
		काष्ठा x25_address *called_addr,
		काष्ठा x25_address *calling_addr)
अणु
	अचिन्हित अक्षर len;
	पूर्णांक needed;
	पूर्णांक rc;

	अगर (!pskb_may_pull(skb, 1)) अणु
		/* packet has no address block */
		rc = 0;
		जाओ empty;
	पूर्ण

	len = *skb->data;
	needed = 1 + ((len >> 4) + (len & 0x0f) + 1) / 2;

	अगर (!pskb_may_pull(skb, needed)) अणु
		/* packet is too लघु to hold the addresses it claims
		   to hold */
		rc = -1;
		जाओ empty;
	पूर्ण

	वापस x25_addr_ntoa(skb->data, called_addr, calling_addr);

empty:
	*called_addr->x25_addr = 0;
	*calling_addr->x25_addr = 0;

	वापस rc;
पूर्ण


पूर्णांक x25_addr_ntoa(अचिन्हित अक्षर *p, काष्ठा x25_address *called_addr,
		  काष्ठा x25_address *calling_addr)
अणु
	अचिन्हित पूर्णांक called_len, calling_len;
	अक्षर *called, *calling;
	अचिन्हित पूर्णांक i;

	called_len  = (*p >> 0) & 0x0F;
	calling_len = (*p >> 4) & 0x0F;

	called  = called_addr->x25_addr;
	calling = calling_addr->x25_addr;
	p++;

	क्रम (i = 0; i < (called_len + calling_len); i++) अणु
		अगर (i < called_len) अणु
			अगर (i % 2 != 0) अणु
				*called++ = ((*p >> 0) & 0x0F) + '0';
				p++;
			पूर्ण अन्यथा अणु
				*called++ = ((*p >> 4) & 0x0F) + '0';
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i % 2 != 0) अणु
				*calling++ = ((*p >> 0) & 0x0F) + '0';
				p++;
			पूर्ण अन्यथा अणु
				*calling++ = ((*p >> 4) & 0x0F) + '0';
			पूर्ण
		पूर्ण
	पूर्ण

	*called = *calling = '\0';

	वापस 1 + (called_len + calling_len + 1) / 2;
पूर्ण

पूर्णांक x25_addr_aton(अचिन्हित अक्षर *p, काष्ठा x25_address *called_addr,
		  काष्ठा x25_address *calling_addr)
अणु
	अचिन्हित पूर्णांक called_len, calling_len;
	अक्षर *called, *calling;
	पूर्णांक i;

	called  = called_addr->x25_addr;
	calling = calling_addr->x25_addr;

	called_len  = म_माप(called);
	calling_len = म_माप(calling);

	*p++ = (calling_len << 4) | (called_len << 0);

	क्रम (i = 0; i < (called_len + calling_len); i++) अणु
		अगर (i < called_len) अणु
			अगर (i % 2 != 0) अणु
				*p |= (*called++ - '0') << 0;
				p++;
			पूर्ण अन्यथा अणु
				*p = 0x00;
				*p |= (*called++ - '0') << 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i % 2 != 0) अणु
				*p |= (*calling++ - '0') << 0;
				p++;
			पूर्ण अन्यथा अणु
				*p = 0x00;
				*p |= (*calling++ - '0') << 4;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1 + (called_len + calling_len + 1) / 2;
पूर्ण

/*
 *	Socket removal during an पूर्णांकerrupt is now safe.
 */
अटल व्योम x25_हटाओ_socket(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&x25_list_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&x25_list_lock);
पूर्ण

/*
 *	Handle device status changes.
 */
अटल पूर्णांक x25_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा x25_neigh *nb;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (dev->type == ARPHRD_X25) अणु
		चयन (event) अणु
		हाल NETDEV_REGISTER:
		हाल NETDEV_POST_TYPE_CHANGE:
			x25_link_device_up(dev);
			अवरोध;
		हाल NETDEV_DOWN:
			nb = x25_get_neigh(dev);
			अगर (nb) अणु
				x25_link_terminated(nb);
				x25_neigh_put(nb);
			पूर्ण
			x25_route_device_करोwn(dev);
			अवरोध;
		हाल NETDEV_PRE_TYPE_CHANGE:
		हाल NETDEV_UNREGISTER:
			x25_link_device_करोwn(dev);
			अवरोध;
		हाल NETDEV_CHANGE:
			अगर (!netअगर_carrier_ok(dev)) अणु
				nb = x25_get_neigh(dev);
				अगर (nb) अणु
					x25_link_terminated(nb);
					x25_neigh_put(nb);
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Add a socket to the bound sockets list.
 */
अटल व्योम x25_insert_socket(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&x25_list_lock);
	sk_add_node(sk, &x25_list);
	ग_लिखो_unlock_bh(&x25_list_lock);
पूर्ण

/*
 *	Find a socket that wants to accept the Call Request we just
 *	received. Check the full list क्रम an address/cud match.
 *	If no cuds match वापस the next_best thing, an address match.
 *	Note: अगर a listening socket has cud set it must only get calls
 *	with matching cud.
 */
अटल काष्ठा sock *x25_find_listener(काष्ठा x25_address *addr,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *s;
	काष्ठा sock *next_best;

	पढ़ो_lock_bh(&x25_list_lock);
	next_best = शून्य;

	sk_क्रम_each(s, &x25_list)
		अगर ((!म_भेद(addr->x25_addr,
			x25_sk(s)->source_addr.x25_addr) ||
				!म_भेद(x25_sk(s)->source_addr.x25_addr,
					null_x25_address.x25_addr)) &&
					s->sk_state == TCP_LISTEN) अणु
			/*
			 * Found a listening socket, now check the incoming
			 * call user data vs this sockets call user data
			 */
			अगर (x25_sk(s)->cudmatchlength > 0 &&
				skb->len >= x25_sk(s)->cudmatchlength) अणु
				अगर((स_भेद(x25_sk(s)->calluserdata.cuddata,
					skb->data,
					x25_sk(s)->cudmatchlength)) == 0) अणु
					sock_hold(s);
					जाओ found;
				 पूर्ण
			पूर्ण अन्यथा
				next_best = s;
		पूर्ण
	अगर (next_best) अणु
		s = next_best;
		sock_hold(s);
		जाओ found;
	पूर्ण
	s = शून्य;
found:
	पढ़ो_unlock_bh(&x25_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a connected X.25 socket given my LCI and neighbour.
 */
अटल काष्ठा sock *__x25_find_socket(अचिन्हित पूर्णांक lci, काष्ठा x25_neigh *nb)
अणु
	काष्ठा sock *s;

	sk_क्रम_each(s, &x25_list)
		अगर (x25_sk(s)->lci == lci && x25_sk(s)->neighbour == nb) अणु
			sock_hold(s);
			जाओ found;
		पूर्ण
	s = शून्य;
found:
	वापस s;
पूर्ण

काष्ठा sock *x25_find_socket(अचिन्हित पूर्णांक lci, काष्ठा x25_neigh *nb)
अणु
	काष्ठा sock *s;

	पढ़ो_lock_bh(&x25_list_lock);
	s = __x25_find_socket(lci, nb);
	पढ़ो_unlock_bh(&x25_list_lock);
	वापस s;
पूर्ण

/*
 *	Find a unique LCI क्रम a given device.
 */
अटल अचिन्हित पूर्णांक x25_new_lci(काष्ठा x25_neigh *nb)
अणु
	अचिन्हित पूर्णांक lci = 1;
	काष्ठा sock *sk;

	जबतक ((sk = x25_find_socket(lci, nb)) != शून्य) अणु
		sock_put(sk);
		अगर (++lci == 4096) अणु
			lci = 0;
			अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण

	वापस lci;
पूर्ण

/*
 *	Deferred destroy.
 */
अटल व्योम __x25_destroy_socket(काष्ठा sock *);

/*
 *	handler क्रम deferred समाप्तs.
 */
अटल व्योम x25_destroy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	x25_destroy_socket_from_समयr(sk);
पूर्ण

/*
 *	This is called from user mode and the समयrs. Thus it protects itself
 *	against पूर्णांकerrupt users but करोesn't worry about being called during
 *	work. Once it is हटाओd from the queue no पूर्णांकerrupt or bottom half
 *	will touch it and we are (fairly 8-) ) safe.
 *	Not अटल as it's used by the समयr
 */
अटल व्योम __x25_destroy_socket(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	x25_stop_heartbeat(sk);
	x25_stop_समयr(sk);

	x25_हटाओ_socket(sk);
	x25_clear_queues(sk);		/* Flush the queues */

	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		अगर (skb->sk != sk) अणु		/* A pending connection */
			/*
			 * Queue the unaccepted socket क्रम death
			 */
			skb->sk->sk_state = TCP_LISTEN;
			sock_set_flag(skb->sk, SOCK_DEAD);
			x25_start_heartbeat(skb->sk);
			x25_sk(skb->sk)->state = X25_STATE_0;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण

	अगर (sk_has_allocations(sk)) अणु
		/* Defer: outstanding buffers */
		sk->sk_समयr.expires  = jअगरfies + 10 * HZ;
		sk->sk_समयr.function = x25_destroy_समयr;
		add_समयr(&sk->sk_समयr);
	पूर्ण अन्यथा अणु
		/* drop last reference so sock_put will मुक्त */
		__sock_put(sk);
	पूर्ण
पूर्ण

व्योम x25_destroy_socket_from_समयr(काष्ठा sock *sk)
अणु
	sock_hold(sk);
	bh_lock_sock(sk);
	__x25_destroy_socket(sk);
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/*
 *	Handling क्रम प्रणाली calls applied via the various पूर्णांकerfaces to a
 *	X.25 socket object.
 */

अटल पूर्णांक x25_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक opt;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc = -ENOPROTOOPT;

	अगर (level != SOL_X25 || optname != X25_QBITINCL)
		जाओ out;

	rc = -EINVAL;
	अगर (optlen < माप(पूर्णांक))
		जाओ out;

	rc = -EFAULT;
	अगर (copy_from_sockptr(&opt, optval, माप(पूर्णांक)))
		जाओ out;

	अगर (opt)
		set_bit(X25_Q_BIT_FLAG, &x25_sk(sk)->flags);
	अन्यथा
		clear_bit(X25_Q_BIT_FLAG, &x25_sk(sk)->flags);
	rc = 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक x25_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक val, len, rc = -ENOPROTOOPT;

	अगर (level != SOL_X25 || optname != X25_QBITINCL)
		जाओ out;

	rc = -EFAULT;
	अगर (get_user(len, optlen))
		जाओ out;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	rc = -EINVAL;
	अगर (len < 0)
		जाओ out;

	rc = -EFAULT;
	अगर (put_user(len, optlen))
		जाओ out;

	val = test_bit(X25_Q_BIT_FLAG, &x25_sk(sk)->flags);
	rc = copy_to_user(optval, &val, len) ? -EFAULT : 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक x25_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक rc = -EOPNOTSUPP;

	lock_sock(sk);
	अगर (sk->sk_state != TCP_LISTEN) अणु
		स_रखो(&x25_sk(sk)->dest_addr, 0, X25_ADDR_LEN);
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		rc = 0;
	पूर्ण
	release_sock(sk);

	वापस rc;
पूर्ण

अटल काष्ठा proto x25_proto = अणु
	.name	  = "X25",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा x25_sock),
पूर्ण;

अटल काष्ठा sock *x25_alloc_socket(काष्ठा net *net, पूर्णांक kern)
अणु
	काष्ठा x25_sock *x25;
	काष्ठा sock *sk = sk_alloc(net, AF_X25, GFP_ATOMIC, &x25_proto, kern);

	अगर (!sk)
		जाओ out;

	sock_init_data(शून्य, sk);

	x25 = x25_sk(sk);
	skb_queue_head_init(&x25->ack_queue);
	skb_queue_head_init(&x25->fragment_queue);
	skb_queue_head_init(&x25->पूर्णांकerrupt_in_queue);
	skb_queue_head_init(&x25->पूर्णांकerrupt_out_queue);
out:
	वापस sk;
पूर्ण

अटल पूर्णांक x25_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा x25_sock *x25;
	पूर्णांक rc = -EAFNOSUPPORT;

	अगर (!net_eq(net, &init_net))
		जाओ out;

	rc = -ESOCKTNOSUPPORT;
	अगर (sock->type != SOCK_SEQPACKET)
		जाओ out;

	rc = -EINVAL;
	अगर (protocol)
		जाओ out;

	rc = -ENOMEM;
	अगर ((sk = x25_alloc_socket(net, kern)) == शून्य)
		जाओ out;

	x25 = x25_sk(sk);

	sock_init_data(sock, sk);

	x25_init_समयrs(sk);

	sock->ops    = &x25_proto_ops;
	sk->sk_protocol = protocol;
	sk->sk_backlog_rcv = x25_backlog_rcv;

	x25->t21   = sysctl_x25_call_request_समयout;
	x25->t22   = sysctl_x25_reset_request_समयout;
	x25->t23   = sysctl_x25_clear_request_समयout;
	x25->t2    = sysctl_x25_ack_holdback_समयout;
	x25->state = X25_STATE_0;
	x25->cudmatchlength = 0;
	set_bit(X25_ACCPT_APPRV_FLAG, &x25->flags);	/* normally no cud  */
							/* on call accept   */

	x25->facilities.winsize_in  = X25_DEFAULT_WINDOW_SIZE;
	x25->facilities.winsize_out = X25_DEFAULT_WINDOW_SIZE;
	x25->facilities.pacsize_in  = X25_DEFAULT_PACKET_SIZE;
	x25->facilities.pacsize_out = X25_DEFAULT_PACKET_SIZE;
	x25->facilities.throughput  = 0;	/* by शेष करोn't negotiate
						   throughput */
	x25->facilities.reverse     = X25_DEFAULT_REVERSE;
	x25->dte_facilities.calling_len = 0;
	x25->dte_facilities.called_len = 0;
	स_रखो(x25->dte_facilities.called_ae, '\0',
			माप(x25->dte_facilities.called_ae));
	स_रखो(x25->dte_facilities.calling_ae, '\0',
			माप(x25->dte_facilities.calling_ae));

	rc = 0;
out:
	वापस rc;
पूर्ण

अटल काष्ठा sock *x25_make_new(काष्ठा sock *osk)
अणु
	काष्ठा sock *sk = शून्य;
	काष्ठा x25_sock *x25, *ox25;

	अगर (osk->sk_type != SOCK_SEQPACKET)
		जाओ out;

	अगर ((sk = x25_alloc_socket(sock_net(osk), 0)) == शून्य)
		जाओ out;

	x25 = x25_sk(sk);

	sk->sk_type        = osk->sk_type;
	sk->sk_priority    = osk->sk_priority;
	sk->sk_protocol    = osk->sk_protocol;
	sk->sk_rcvbuf      = osk->sk_rcvbuf;
	sk->sk_sndbuf      = osk->sk_sndbuf;
	sk->sk_state       = TCP_ESTABLISHED;
	sk->sk_backlog_rcv = osk->sk_backlog_rcv;
	sock_copy_flags(sk, osk);

	ox25 = x25_sk(osk);
	x25->t21        = ox25->t21;
	x25->t22        = ox25->t22;
	x25->t23        = ox25->t23;
	x25->t2         = ox25->t2;
	x25->flags	= ox25->flags;
	x25->facilities = ox25->facilities;
	x25->dte_facilities = ox25->dte_facilities;
	x25->cudmatchlength = ox25->cudmatchlength;

	clear_bit(X25_INTERRUPT_FLAG, &x25->flags);
	x25_init_समयrs(sk);
out:
	वापस sk;
पूर्ण

अटल पूर्णांक x25_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25;

	अगर (!sk)
		वापस 0;

	x25 = x25_sk(sk);

	sock_hold(sk);
	lock_sock(sk);
	चयन (x25->state) अणु

		हाल X25_STATE_0:
		हाल X25_STATE_2:
			x25_disconnect(sk, 0, 0, 0);
			__x25_destroy_socket(sk);
			जाओ out;

		हाल X25_STATE_1:
		हाल X25_STATE_3:
		हाल X25_STATE_4:
			x25_clear_queues(sk);
			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
			x25_start_t23समयr(sk);
			x25->state = X25_STATE_2;
			sk->sk_state	= TCP_CLOSE;
			sk->sk_shutकरोwn	|= SEND_SHUTDOWN;
			sk->sk_state_change(sk);
			sock_set_flag(sk, SOCK_DEAD);
			sock_set_flag(sk, SOCK_DESTROY);
			अवरोध;

		हाल X25_STATE_5:
			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
			x25_disconnect(sk, 0, 0, 0);
			__x25_destroy_socket(sk);
			जाओ out;
	पूर्ण

	sock_orphan(sk);
out:
	release_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक x25_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_x25 *addr = (काष्ठा sockaddr_x25 *)uaddr;
	पूर्णांक len, i, rc = 0;

	अगर (addr_len != माप(काष्ठा sockaddr_x25) ||
	    addr->sx25_family != AF_X25 ||
	    strnlen(addr->sx25_addr.x25_addr, X25_ADDR_LEN) == X25_ADDR_LEN) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* check क्रम the null_x25_address */
	अगर (म_भेद(addr->sx25_addr.x25_addr, null_x25_address.x25_addr)) अणु

		len = म_माप(addr->sx25_addr.x25_addr);
		क्रम (i = 0; i < len; i++) अणु
			अगर (!है_अंक(addr->sx25_addr.x25_addr[i])) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		x25_sk(sk)->source_addr = addr->sx25_addr;
		x25_insert_socket(sk);
		sock_reset_flag(sk, SOCK_ZAPPED);
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
	पूर्ण
	release_sock(sk);
	SOCK_DEBUG(sk, "x25_bind: socket is bound\n");
out:
	वापस rc;
पूर्ण

अटल पूर्णांक x25_रुको_क्रम_connection_establishment(काष्ठा sock *sk)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक rc;

	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	क्रम (;;) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		rc = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		rc = sock_error(sk);
		अगर (rc) अणु
			sk->sk_socket->state = SS_UNCONNECTED;
			अवरोध;
		पूर्ण
		rc = 0;
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			release_sock(sk);
			schedule();
			lock_sock(sk);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

अटल पूर्णांक x25_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	काष्ठा sockaddr_x25 *addr = (काष्ठा sockaddr_x25 *)uaddr;
	काष्ठा x25_route *rt;
	पूर्णांक rc = 0;

	lock_sock(sk);
	अगर (sk->sk_state == TCP_ESTABLISHED && sock->state == SS_CONNECTING) अणु
		sock->state = SS_CONNECTED;
		जाओ out; /* Connect completed during a ERESTARTSYS event */
	पूर्ण

	rc = -ECONNREFUSED;
	अगर (sk->sk_state == TCP_CLOSE && sock->state == SS_CONNECTING) अणु
		sock->state = SS_UNCONNECTED;
		जाओ out;
	पूर्ण

	rc = -EISCONN;	/* No reconnect on a seqpacket socket */
	अगर (sk->sk_state == TCP_ESTABLISHED)
		जाओ out;

	rc = -EALREADY;	/* Do nothing अगर call is alपढ़ोy in progress */
	अगर (sk->sk_state == TCP_SYN_SENT)
		जाओ out;

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	rc = -EINVAL;
	अगर (addr_len != माप(काष्ठा sockaddr_x25) ||
	    addr->sx25_family != AF_X25 ||
	    strnlen(addr->sx25_addr.x25_addr, X25_ADDR_LEN) == X25_ADDR_LEN)
		जाओ out;

	rc = -ENETUNREACH;
	rt = x25_get_route(&addr->sx25_addr);
	अगर (!rt)
		जाओ out;

	x25->neighbour = x25_get_neigh(rt->dev);
	अगर (!x25->neighbour)
		जाओ out_put_route;

	x25_limit_facilities(&x25->facilities, x25->neighbour);

	x25->lci = x25_new_lci(x25->neighbour);
	अगर (!x25->lci)
		जाओ out_put_neigh;

	rc = -EINVAL;
	अगर (sock_flag(sk, SOCK_ZAPPED)) /* Must bind first - स्वतःbinding करोes not work */
		जाओ out_put_neigh;

	अगर (!म_भेद(x25->source_addr.x25_addr, null_x25_address.x25_addr))
		स_रखो(&x25->source_addr, '\0', X25_ADDR_LEN);

	x25->dest_addr = addr->sx25_addr;

	/* Move to connecting socket, start sending Connect Requests */
	sock->state   = SS_CONNECTING;
	sk->sk_state  = TCP_SYN_SENT;

	x25->state = X25_STATE_1;

	x25_ग_लिखो_पूर्णांकernal(sk, X25_CALL_REQUEST);

	x25_start_heartbeat(sk);
	x25_start_t21समयr(sk);

	/* Now the loop */
	rc = -EINPROGRESS;
	अगर (sk->sk_state != TCP_ESTABLISHED && (flags & O_NONBLOCK))
		जाओ out;

	rc = x25_रुको_क्रम_connection_establishment(sk);
	अगर (rc)
		जाओ out_put_neigh;

	sock->state = SS_CONNECTED;
	rc = 0;
out_put_neigh:
	अगर (rc && x25->neighbour) अणु
		पढ़ो_lock_bh(&x25_list_lock);
		x25_neigh_put(x25->neighbour);
		x25->neighbour = शून्य;
		पढ़ो_unlock_bh(&x25_list_lock);
		x25->state = X25_STATE_0;
	पूर्ण
out_put_route:
	x25_route_put(rt);
out:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल पूर्णांक x25_रुको_क्रम_data(काष्ठा sock *sk, दीर्घ समयout)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक rc = 0;

	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	क्रम (;;) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			अवरोध;
		rc = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		rc = -EAGAIN;
		अगर (!समयout)
			अवरोध;
		rc = 0;
		अगर (skb_queue_empty(&sk->sk_receive_queue)) अणु
			release_sock(sk);
			समयout = schedule_समयout(समयout);
			lock_sock(sk);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

अटल पूर्णांक x25_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		      bool kern)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *newsk;
	काष्ठा sk_buff *skb;
	पूर्णांक rc = -EINVAL;

	अगर (!sk)
		जाओ out;

	rc = -EOPNOTSUPP;
	अगर (sk->sk_type != SOCK_SEQPACKET)
		जाओ out;

	lock_sock(sk);
	rc = -EINVAL;
	अगर (sk->sk_state != TCP_LISTEN)
		जाओ out2;

	rc = x25_रुको_क्रम_data(sk, sk->sk_rcvसमयo);
	अगर (rc)
		जाओ out2;
	skb = skb_dequeue(&sk->sk_receive_queue);
	rc = -EINVAL;
	अगर (!skb->sk)
		जाओ out2;
	newsk		 = skb->sk;
	sock_graft(newsk, newsock);

	/* Now attach up the new socket */
	skb->sk = शून्य;
	kमुक्त_skb(skb);
	sk_acceptq_हटाओd(sk);
	newsock->state = SS_CONNECTED;
	rc = 0;
out2:
	release_sock(sk);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक x25_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक peer)
अणु
	काष्ठा sockaddr_x25 *sx25 = (काष्ठा sockaddr_x25 *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	पूर्णांक rc = 0;

	अगर (peer) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			rc = -ENOTCONN;
			जाओ out;
		पूर्ण
		sx25->sx25_addr = x25->dest_addr;
	पूर्ण अन्यथा
		sx25->sx25_addr = x25->source_addr;

	sx25->sx25_family = AF_X25;
	rc = माप(*sx25);

out:
	वापस rc;
पूर्ण

पूर्णांक x25_rx_call_request(काष्ठा sk_buff *skb, काष्ठा x25_neigh *nb,
			अचिन्हित पूर्णांक lci)
अणु
	काष्ठा sock *sk;
	काष्ठा sock *make;
	काष्ठा x25_sock *makex25;
	काष्ठा x25_address source_addr, dest_addr;
	काष्ठा x25_facilities facilities;
	काष्ठा x25_dte_facilities dte_facilities;
	पूर्णांक len, addr_len, rc;

	/*
	 *	Remove the LCI and frame type.
	 */
	skb_pull(skb, X25_STD_MIN_LEN);

	/*
	 *	Extract the X.25 addresses and convert them to ASCII strings,
	 *	and हटाओ them.
	 *
	 *	Address block is mandatory in call request packets
	 */
	addr_len = x25_parse_address_block(skb, &source_addr, &dest_addr);
	अगर (addr_len <= 0)
		जाओ out_clear_request;
	skb_pull(skb, addr_len);

	/*
	 *	Get the length of the facilities, skip past them क्रम the moment
	 *	get the call user data because this is needed to determine
	 *	the correct listener
	 *
	 *	Facilities length is mandatory in call request packets
	 */
	अगर (!pskb_may_pull(skb, 1))
		जाओ out_clear_request;
	len = skb->data[0] + 1;
	अगर (!pskb_may_pull(skb, len))
		जाओ out_clear_request;
	skb_pull(skb,len);

	/*
	 *	Ensure that the amount of call user data is valid.
	 */
	अगर (skb->len > X25_MAX_CUD_LEN)
		जाओ out_clear_request;

	/*
	 *	Get all the call user data so it can be used in
	 *	x25_find_listener and skb_copy_from_linear_data up ahead.
	 */
	अगर (!pskb_may_pull(skb, skb->len))
		जाओ out_clear_request;

	/*
	 *	Find a listener क्रम the particular address/cud pair.
	 */
	sk = x25_find_listener(&source_addr,skb);
	skb_push(skb,len);

	अगर (sk != शून्य && sk_acceptq_is_full(sk)) अणु
		जाओ out_sock_put;
	पूर्ण

	/*
	 *	We करोnt have any listeners क्रम this incoming call.
	 *	Try क्रमwarding it.
	 */
	अगर (sk == शून्य) अणु
		skb_push(skb, addr_len + X25_STD_MIN_LEN);
		अगर (sysctl_x25_क्रमward &&
				x25_क्रमward_call(&dest_addr, nb, skb, lci) > 0)
		अणु
			/* Call was क्रमwarded, करोnt process it any more */
			kमुक्त_skb(skb);
			rc = 1;
			जाओ out;
		पूर्ण अन्यथा अणु
			/* No listeners, can't क्रमward, clear the call */
			जाओ out_clear_request;
		पूर्ण
	पूर्ण

	/*
	 *	Try to reach a compromise on the requested facilities.
	 */
	len = x25_negotiate_facilities(skb, sk, &facilities, &dte_facilities);
	अगर (len == -1)
		जाओ out_sock_put;

	/*
	 * current neighbour/link might impose additional limits
	 * on certain facilities
	 */

	x25_limit_facilities(&facilities, nb);

	/*
	 *	Try to create a new socket.
	 */
	make = x25_make_new(sk);
	अगर (!make)
		जाओ out_sock_put;

	/*
	 *	Remove the facilities
	 */
	skb_pull(skb, len);

	skb->sk     = make;
	make->sk_state = TCP_ESTABLISHED;

	makex25 = x25_sk(make);
	makex25->lci           = lci;
	makex25->dest_addr     = dest_addr;
	makex25->source_addr   = source_addr;
	x25_neigh_hold(nb);
	makex25->neighbour     = nb;
	makex25->facilities    = facilities;
	makex25->dte_facilities= dte_facilities;
	makex25->vc_facil_mask = x25_sk(sk)->vc_facil_mask;
	/* ensure no reverse facil on accept */
	makex25->vc_facil_mask &= ~X25_MASK_REVERSE;
	/* ensure no calling address extension on accept */
	makex25->vc_facil_mask &= ~X25_MASK_CALLING_AE;
	makex25->cudmatchlength = x25_sk(sk)->cudmatchlength;

	/* Normally all calls are accepted immediately */
	अगर (test_bit(X25_ACCPT_APPRV_FLAG, &makex25->flags)) अणु
		x25_ग_लिखो_पूर्णांकernal(make, X25_CALL_ACCEPTED);
		makex25->state = X25_STATE_3;
	पूर्ण अन्यथा अणु
		makex25->state = X25_STATE_5;
	पूर्ण

	/*
	 *	Incoming Call User Data.
	 */
	skb_copy_from_linear_data(skb, makex25->calluserdata.cuddata, skb->len);
	makex25->calluserdata.cudlength = skb->len;

	sk_acceptq_added(sk);

	x25_insert_socket(make);

	skb_queue_head(&sk->sk_receive_queue, skb);

	x25_start_heartbeat(make);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);
	rc = 1;
	sock_put(sk);
out:
	वापस rc;
out_sock_put:
	sock_put(sk);
out_clear_request:
	rc = 0;
	x25_transmit_clear_request(nb, lci, 0x01);
	जाओ out;
पूर्ण

अटल पूर्णांक x25_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_x25 *, usx25, msg->msg_name);
	काष्ठा sockaddr_x25 sx25;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *यंत्रptr;
	पूर्णांक noblock = msg->msg_flags & MSG_DONTWAIT;
	माप_प्रकार size;
	पूर्णांक qbit = 0, rc = -EINVAL;

	lock_sock(sk);
	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_OOB|MSG_EOR|MSG_CMSG_COMPAT))
		जाओ out;

	/* we currently करोn't support segmented records at the user पूर्णांकerface */
	अगर (!(msg->msg_flags & (MSG_EOR|MSG_OOB)))
		जाओ out;

	rc = -EADDRNOTAVAIL;
	अगर (sock_flag(sk, SOCK_ZAPPED))
		जाओ out;

	rc = -EPIPE;
	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		send_sig(SIGPIPE, current, 0);
		जाओ out;
	पूर्ण

	rc = -ENETUNREACH;
	अगर (!x25->neighbour)
		जाओ out;

	अगर (usx25) अणु
		rc = -EINVAL;
		अगर (msg->msg_namelen < माप(sx25))
			जाओ out;
		स_नकल(&sx25, usx25, माप(sx25));
		rc = -EISCONN;
		अगर (म_भेद(x25->dest_addr.x25_addr, sx25.sx25_addr.x25_addr))
			जाओ out;
		rc = -EINVAL;
		अगर (sx25.sx25_family != AF_X25)
			जाओ out;
	पूर्ण अन्यथा अणु
		/*
		 *	FIXME 1003.1g - अगर the socket is like this because
		 *	it has become बंदd (not started बंदd) we ought
		 *	to SIGPIPE, EPIPE;
		 */
		rc = -ENOTCONN;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;

		sx25.sx25_family = AF_X25;
		sx25.sx25_addr   = x25->dest_addr;
	पूर्ण

	/* Sanity check the packet size */
	अगर (len > 65535) अणु
		rc = -EMSGSIZE;
		जाओ out;
	पूर्ण

	SOCK_DEBUG(sk, "x25_sendmsg: sendto: Addresses built.\n");

	/* Build a packet */
	SOCK_DEBUG(sk, "x25_sendmsg: sendto: building packet.\n");

	अगर ((msg->msg_flags & MSG_OOB) && len > 32)
		len = 32;

	size = len + X25_MAX_L2_LEN + X25_EXT_MIN_LEN;

	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, noblock, &rc);
	lock_sock(sk);
	अगर (!skb)
		जाओ out;
	X25_SKB_CB(skb)->flags = msg->msg_flags;

	skb_reserve(skb, X25_MAX_L2_LEN + X25_EXT_MIN_LEN);

	/*
	 *	Put the data on the end
	 */
	SOCK_DEBUG(sk, "x25_sendmsg: Copying user data\n");

	skb_reset_transport_header(skb);
	skb_put(skb, len);

	rc = स_नकल_from_msg(skb_transport_header(skb), msg, len);
	अगर (rc)
		जाओ out_kमुक्त_skb;

	/*
	 *	If the Q BIT Include socket option is in क्रमce, the first
	 *	byte of the user data is the logical value of the Q Bit.
	 */
	अगर (test_bit(X25_Q_BIT_FLAG, &x25->flags)) अणु
		अगर (!pskb_may_pull(skb, 1))
			जाओ out_kमुक्त_skb;

		qbit = skb->data[0];
		skb_pull(skb, 1);
	पूर्ण

	/*
	 *	Push करोwn the X.25 header
	 */
	SOCK_DEBUG(sk, "x25_sendmsg: Building X.25 Header.\n");

	अगर (msg->msg_flags & MSG_OOB) अणु
		अगर (x25->neighbour->extended) अणु
			यंत्रptr    = skb_push(skb, X25_STD_MIN_LEN);
			*यंत्रptr++ = ((x25->lci >> 8) & 0x0F) | X25_GFI_EXTSEQ;
			*यंत्रptr++ = (x25->lci >> 0) & 0xFF;
			*यंत्रptr++ = X25_INTERRUPT;
		पूर्ण अन्यथा अणु
			यंत्रptr    = skb_push(skb, X25_STD_MIN_LEN);
			*यंत्रptr++ = ((x25->lci >> 8) & 0x0F) | X25_GFI_STDSEQ;
			*यंत्रptr++ = (x25->lci >> 0) & 0xFF;
			*यंत्रptr++ = X25_INTERRUPT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (x25->neighbour->extended) अणु
			/* Build an Extended X.25 header */
			यंत्रptr    = skb_push(skb, X25_EXT_MIN_LEN);
			*यंत्रptr++ = ((x25->lci >> 8) & 0x0F) | X25_GFI_EXTSEQ;
			*यंत्रptr++ = (x25->lci >> 0) & 0xFF;
			*यंत्रptr++ = X25_DATA;
			*यंत्रptr++ = X25_DATA;
		पूर्ण अन्यथा अणु
			/* Build an Standard X.25 header */
			यंत्रptr    = skb_push(skb, X25_STD_MIN_LEN);
			*यंत्रptr++ = ((x25->lci >> 8) & 0x0F) | X25_GFI_STDSEQ;
			*यंत्रptr++ = (x25->lci >> 0) & 0xFF;
			*यंत्रptr++ = X25_DATA;
		पूर्ण

		अगर (qbit)
			skb->data[0] |= X25_Q_BIT;
	पूर्ण

	SOCK_DEBUG(sk, "x25_sendmsg: Built header.\n");
	SOCK_DEBUG(sk, "x25_sendmsg: Transmitting buffer\n");

	rc = -ENOTCONN;
	अगर (sk->sk_state != TCP_ESTABLISHED)
		जाओ out_kमुक्त_skb;

	अगर (msg->msg_flags & MSG_OOB)
		skb_queue_tail(&x25->पूर्णांकerrupt_out_queue, skb);
	अन्यथा अणु
		rc = x25_output(sk, skb);
		len = rc;
		अगर (rc < 0)
			kमुक्त_skb(skb);
		अन्यथा अगर (test_bit(X25_Q_BIT_FLAG, &x25->flags))
			len++;
	पूर्ण

	x25_kick(sk);
	rc = len;
out:
	release_sock(sk);
	वापस rc;
out_kमुक्त_skb:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण


अटल पूर्णांक x25_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		       पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_x25 *, sx25, msg->msg_name);
	माप_प्रकार copied;
	पूर्णांक qbit, header_len;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *यंत्रptr;
	पूर्णांक rc = -ENOTCONN;

	lock_sock(sk);

	अगर (x25->neighbour == शून्य)
		जाओ out;

	header_len = x25->neighbour->extended ?
		X25_EXT_MIN_LEN : X25_STD_MIN_LEN;

	/*
	 * This works क्रम seqpacket too. The receiver has ordered the queue क्रम
	 * us! We करो one quick check first though
	 */
	अगर (sk->sk_state != TCP_ESTABLISHED)
		जाओ out;

	अगर (flags & MSG_OOB) अणु
		rc = -EINVAL;
		अगर (sock_flag(sk, SOCK_URGINLINE) ||
		    !skb_peek(&x25->पूर्णांकerrupt_in_queue))
			जाओ out;

		skb = skb_dequeue(&x25->पूर्णांकerrupt_in_queue);

		अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN))
			जाओ out_मुक्त_dgram;

		skb_pull(skb, X25_STD_MIN_LEN);

		/*
		 *	No Q bit inक्रमmation on Interrupt data.
		 */
		अगर (test_bit(X25_Q_BIT_FLAG, &x25->flags)) अणु
			यंत्रptr  = skb_push(skb, 1);
			*यंत्रptr = 0x00;
		पूर्ण

		msg->msg_flags |= MSG_OOB;
	पूर्ण अन्यथा अणु
		/* Now we can treat all alike */
		release_sock(sk);
		skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
					flags & MSG_DONTWAIT, &rc);
		lock_sock(sk);
		अगर (!skb)
			जाओ out;

		अगर (!pskb_may_pull(skb, header_len))
			जाओ out_मुक्त_dgram;

		qbit = (skb->data[0] & X25_Q_BIT) == X25_Q_BIT;

		skb_pull(skb, header_len);

		अगर (test_bit(X25_Q_BIT_FLAG, &x25->flags)) अणु
			यंत्रptr  = skb_push(skb, 1);
			*यंत्रptr = qbit;
		पूर्ण
	पूर्ण

	skb_reset_transport_header(skb);
	copied = skb->len;

	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	/* Currently, each datagram always contains a complete record */
	msg->msg_flags |= MSG_EOR;

	rc = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (rc)
		जाओ out_मुक्त_dgram;

	अगर (sx25) अणु
		sx25->sx25_family = AF_X25;
		sx25->sx25_addr   = x25->dest_addr;
		msg->msg_namelen = माप(*sx25);
	पूर्ण

	x25_check_rbuf(sk);
	rc = copied;
out_मुक्त_dgram:
	skb_मुक्त_datagram(sk, skb);
out:
	release_sock(sk);
	वापस rc;
पूर्ण


अटल पूर्णांक x25_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक rc;

	चयन (cmd) अणु
	हाल TIOCOUTQ: अणु
		पूर्णांक amount;

		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		rc = put_user(amount, (अचिन्हित पूर्णांक __user *)argp);
		अवरोध;
	पूर्ण

	हाल TIOCINQ: अणु
		काष्ठा sk_buff *skb;
		पूर्णांक amount = 0;
		/*
		 * These two are safe on a single CPU प्रणाली as
		 * only user tasks fiddle here
		 */
		lock_sock(sk);
		अगर ((skb = skb_peek(&sk->sk_receive_queue)) != शून्य)
			amount = skb->len;
		release_sock(sk);
		rc = put_user(amount, (अचिन्हित पूर्णांक __user *)argp);
		अवरोध;
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
		rc = -EINVAL;
		अवरोध;
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		rc = -EPERM;
		अगर (!capable(CAP_NET_ADMIN))
			अवरोध;
		rc = x25_route_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25GSUBSCRIP:
		rc = x25_subscr_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25SSUBSCRIP:
		rc = -EPERM;
		अगर (!capable(CAP_NET_ADMIN))
			अवरोध;
		rc = x25_subscr_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25GFACILITIES: अणु
		lock_sock(sk);
		rc = copy_to_user(argp, &x25->facilities,
				  माप(x25->facilities))
			? -EFAULT : 0;
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25SFACILITIES: अणु
		काष्ठा x25_facilities facilities;
		rc = -EFAULT;
		अगर (copy_from_user(&facilities, argp, माप(facilities)))
			अवरोध;
		rc = -EINVAL;
		lock_sock(sk);
		अगर (sk->sk_state != TCP_LISTEN &&
		    sk->sk_state != TCP_CLOSE)
			जाओ out_fac_release;
		अगर (facilities.pacsize_in < X25_PS16 ||
		    facilities.pacsize_in > X25_PS4096)
			जाओ out_fac_release;
		अगर (facilities.pacsize_out < X25_PS16 ||
		    facilities.pacsize_out > X25_PS4096)
			जाओ out_fac_release;
		अगर (facilities.winsize_in < 1 ||
		    facilities.winsize_in > 127)
			जाओ out_fac_release;
		अगर (facilities.throughput) अणु
			पूर्णांक out = facilities.throughput & 0xf0;
			पूर्णांक in  = facilities.throughput & 0x0f;
			अगर (!out)
				facilities.throughput |=
					X25_DEFAULT_THROUGHPUT << 4;
			अन्यथा अगर (out < 0x30 || out > 0xD0)
				जाओ out_fac_release;
			अगर (!in)
				facilities.throughput |=
					X25_DEFAULT_THROUGHPUT;
			अन्यथा अगर (in < 0x03 || in > 0x0D)
				जाओ out_fac_release;
		पूर्ण
		अगर (facilities.reverse &&
		    (facilities.reverse & 0x81) != 0x81)
			जाओ out_fac_release;
		x25->facilities = facilities;
		rc = 0;
out_fac_release:
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25GDTEFACILITIES: अणु
		lock_sock(sk);
		rc = copy_to_user(argp, &x25->dte_facilities,
				  माप(x25->dte_facilities));
		release_sock(sk);
		अगर (rc)
			rc = -EFAULT;
		अवरोध;
	पूर्ण

	हाल SIOCX25SDTEFACILITIES: अणु
		काष्ठा x25_dte_facilities dtefacs;
		rc = -EFAULT;
		अगर (copy_from_user(&dtefacs, argp, माप(dtefacs)))
			अवरोध;
		rc = -EINVAL;
		lock_sock(sk);
		अगर (sk->sk_state != TCP_LISTEN &&
		    sk->sk_state != TCP_CLOSE)
			जाओ out_dtefac_release;
		अगर (dtefacs.calling_len > X25_MAX_AE_LEN)
			जाओ out_dtefac_release;
		अगर (dtefacs.called_len > X25_MAX_AE_LEN)
			जाओ out_dtefac_release;
		x25->dte_facilities = dtefacs;
		rc = 0;
out_dtefac_release:
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25GCALLUSERDATA: अणु
		lock_sock(sk);
		rc = copy_to_user(argp, &x25->calluserdata,
				  माप(x25->calluserdata))
			? -EFAULT : 0;
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25SCALLUSERDATA: अणु
		काष्ठा x25_calluserdata calluserdata;

		rc = -EFAULT;
		अगर (copy_from_user(&calluserdata, argp, माप(calluserdata)))
			अवरोध;
		rc = -EINVAL;
		अगर (calluserdata.cudlength > X25_MAX_CUD_LEN)
			अवरोध;
		lock_sock(sk);
		x25->calluserdata = calluserdata;
		release_sock(sk);
		rc = 0;
		अवरोध;
	पूर्ण

	हाल SIOCX25GCAUSEDIAG: अणु
		lock_sock(sk);
		rc = copy_to_user(argp, &x25->causediag, माप(x25->causediag))
			? -EFAULT : 0;
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25SCAUSEDIAG: अणु
		काष्ठा x25_causediag causediag;
		rc = -EFAULT;
		अगर (copy_from_user(&causediag, argp, माप(causediag)))
			अवरोध;
		lock_sock(sk);
		x25->causediag = causediag;
		release_sock(sk);
		rc = 0;
		अवरोध;

	पूर्ण

	हाल SIOCX25SCUDMATCHLEN: अणु
		काष्ठा x25_subaddr sub_addr;
		rc = -EINVAL;
		lock_sock(sk);
		अगर(sk->sk_state != TCP_CLOSE)
			जाओ out_cud_release;
		rc = -EFAULT;
		अगर (copy_from_user(&sub_addr, argp,
				   माप(sub_addr)))
			जाओ out_cud_release;
		rc = -EINVAL;
		अगर (sub_addr.cudmatchlength > X25_MAX_CUD_LEN)
			जाओ out_cud_release;
		x25->cudmatchlength = sub_addr.cudmatchlength;
		rc = 0;
out_cud_release:
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25CALLACCPTAPPRV: अणु
		rc = -EINVAL;
		lock_sock(sk);
		अगर (sk->sk_state == TCP_CLOSE) अणु
			clear_bit(X25_ACCPT_APPRV_FLAG, &x25->flags);
			rc = 0;
		पूर्ण
		release_sock(sk);
		अवरोध;
	पूर्ण

	हाल SIOCX25SENDCALLACCPT:  अणु
		rc = -EINVAL;
		lock_sock(sk);
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out_sendcallaccpt_release;
		/* must call accptapprv above */
		अगर (test_bit(X25_ACCPT_APPRV_FLAG, &x25->flags))
			जाओ out_sendcallaccpt_release;
		x25_ग_लिखो_पूर्णांकernal(sk, X25_CALL_ACCEPTED);
		x25->state = X25_STATE_3;
		rc = 0;
out_sendcallaccpt_release:
		release_sock(sk);
		अवरोध;
	पूर्ण

	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family x25_family_ops = अणु
	.family =	AF_X25,
	.create =	x25_create,
	.owner	=	THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_x25_subscr_ioctl(अचिन्हित पूर्णांक cmd,
		काष्ठा compat_x25_subscrip_काष्ठा __user *x25_subscr32)
अणु
	काष्ठा compat_x25_subscrip_काष्ठा x25_subscr;
	काष्ठा x25_neigh *nb;
	काष्ठा net_device *dev;
	पूर्णांक rc = -EINVAL;

	rc = -EFAULT;
	अगर (copy_from_user(&x25_subscr, x25_subscr32, माप(*x25_subscr32)))
		जाओ out;

	rc = -EINVAL;
	dev = x25_dev_get(x25_subscr.device);
	अगर (dev == शून्य)
		जाओ out;

	nb = x25_get_neigh(dev);
	अगर (nb == शून्य)
		जाओ out_dev_put;

	dev_put(dev);

	अगर (cmd == SIOCX25GSUBSCRIP) अणु
		पढ़ो_lock_bh(&x25_neigh_list_lock);
		x25_subscr.extended = nb->extended;
		x25_subscr.global_facil_mask = nb->global_facil_mask;
		पढ़ो_unlock_bh(&x25_neigh_list_lock);
		rc = copy_to_user(x25_subscr32, &x25_subscr,
				माप(*x25_subscr32)) ? -EFAULT : 0;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		अगर (x25_subscr.extended == 0 || x25_subscr.extended == 1) अणु
			rc = 0;
			ग_लिखो_lock_bh(&x25_neigh_list_lock);
			nb->extended = x25_subscr.extended;
			nb->global_facil_mask = x25_subscr.global_facil_mask;
			ग_लिखो_unlock_bh(&x25_neigh_list_lock);
		पूर्ण
	पूर्ण
	x25_neigh_put(nb);
out:
	वापस rc;
out_dev_put:
	dev_put(dev);
	जाओ out;
पूर्ण

अटल पूर्णांक compat_x25_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक rc = -ENOIOCTLCMD;

	चयन(cmd) अणु
	हाल TIOCOUTQ:
	हाल TIOCINQ:
		rc = x25_ioctl(sock, cmd, (अचिन्हित दीर्घ)argp);
		अवरोध;
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
		rc = -EINVAL;
		अवरोध;
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		rc = -EPERM;
		अगर (!capable(CAP_NET_ADMIN))
			अवरोध;
		rc = x25_route_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25GSUBSCRIP:
		rc = compat_x25_subscr_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25SSUBSCRIP:
		rc = -EPERM;
		अगर (!capable(CAP_NET_ADMIN))
			अवरोध;
		rc = compat_x25_subscr_ioctl(cmd, argp);
		अवरोध;
	हाल SIOCX25GFACILITIES:
	हाल SIOCX25SFACILITIES:
	हाल SIOCX25GDTEFACILITIES:
	हाल SIOCX25SDTEFACILITIES:
	हाल SIOCX25GCALLUSERDATA:
	हाल SIOCX25SCALLUSERDATA:
	हाल SIOCX25GCAUSEDIAG:
	हाल SIOCX25SCAUSEDIAG:
	हाल SIOCX25SCUDMATCHLEN:
	हाल SIOCX25CALLACCPTAPPRV:
	हाल SIOCX25SENDCALLACCPT:
		rc = x25_ioctl(sock, cmd, (अचिन्हित दीर्घ)argp);
		अवरोध;
	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा proto_ops x25_proto_ops = अणु
	.family =	AF_X25,
	.owner =	THIS_MODULE,
	.release =	x25_release,
	.bind =		x25_bind,
	.connect =	x25_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	x25_accept,
	.getname =	x25_getname,
	.poll =		datagram_poll,
	.ioctl =	x25_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = compat_x25_ioctl,
#पूर्ण_अगर
	.gettstamp =	sock_gettstamp,
	.listen =	x25_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	x25_setsockopt,
	.माला_लोockopt =	x25_माला_लोockopt,
	.sendmsg =	x25_sendmsg,
	.recvmsg =	x25_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

अटल काष्ठा packet_type x25_packet_type __पढ़ो_mostly = अणु
	.type =	cpu_to_be16(ETH_P_X25),
	.func =	x25_lapb_receive_frame,
पूर्ण;

अटल काष्ठा notअगरier_block x25_dev_notअगरier = अणु
	.notअगरier_call = x25_device_event,
पूर्ण;

व्योम x25_समाप्त_by_neigh(काष्ठा x25_neigh *nb)
अणु
	काष्ठा sock *s;

	ग_लिखो_lock_bh(&x25_list_lock);

	sk_क्रम_each(s, &x25_list)
		अगर (x25_sk(s)->neighbour == nb)
			x25_disconnect(s, ENETUNREACH, 0, 0);

	ग_लिखो_unlock_bh(&x25_list_lock);

	/* Remove any related क्रमwards */
	x25_clear_क्रमward_by_dev(nb->dev);
पूर्ण

अटल पूर्णांक __init x25_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&x25_proto, 0);
	अगर (rc)
		जाओ out;

	rc = sock_रेजिस्टर(&x25_family_ops);
	अगर (rc)
		जाओ out_proto;

	dev_add_pack(&x25_packet_type);

	rc = रेजिस्टर_netdevice_notअगरier(&x25_dev_notअगरier);
	अगर (rc)
		जाओ out_sock;

	rc = x25_रेजिस्टर_sysctl();
	अगर (rc)
		जाओ out_dev;

	rc = x25_proc_init();
	अगर (rc)
		जाओ out_sysctl;

	pr_info("Linux Version 0.2\n");

out:
	वापस rc;
out_sysctl:
	x25_unरेजिस्टर_sysctl();
out_dev:
	unरेजिस्टर_netdevice_notअगरier(&x25_dev_notअगरier);
out_sock:
	dev_हटाओ_pack(&x25_packet_type);
	sock_unरेजिस्टर(AF_X25);
out_proto:
	proto_unरेजिस्टर(&x25_proto);
	जाओ out;
पूर्ण
module_init(x25_init);

अटल व्योम __निकास x25_निकास(व्योम)
अणु
	x25_proc_निकास();
	x25_link_मुक्त();
	x25_route_मुक्त();

	x25_unरेजिस्टर_sysctl();

	unरेजिस्टर_netdevice_notअगरier(&x25_dev_notअगरier);

	dev_हटाओ_pack(&x25_packet_type);

	sock_unरेजिस्टर(AF_X25);
	proto_unरेजिस्टर(&x25_proto);
पूर्ण
module_निकास(x25_निकास);

MODULE_AUTHOR("Jonathan Naylor <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The X.25 Packet Layer network layer protocol");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_X25);
