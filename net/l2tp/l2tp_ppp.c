<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************
 * Linux PPP over L2TP (PPPoX/PPPoL2TP) Sockets
 *
 * PPPoX    --- Generic PPP encapsulation socket family
 * PPPoL2TP --- PPP over L2TP (RFC 2661)
 *
 * Version:	2.0.0
 *
 * Authors:	James Chapman (jchapman@katalix.com)
 *
 * Based on original work by Martijn van Oosterhout <kleptog@svana.org>
 *
 * License:
 */

/* This driver handles only L2TP data frames; control frames are handled by a
 * userspace application.
 *
 * To send data in an L2TP session, userspace खोलोs a PPPoL2TP socket and
 * attaches it to a bound UDP socket with local tunnel_id / session_id and
 * peer tunnel_id / session_id set. Data can then be sent or received using
 * regular socket sendmsg() / recvmsg() calls. Kernel parameters of the socket
 * can be पढ़ो or modअगरied using ioctl() or [gs]etsockopt() calls.
 *
 * When a PPPoL2TP socket is connected with local and peer session_id values
 * zero, the socket is treated as a special tunnel management socket.
 *
 * Here's example userspace code to create a socket क्रम sending/receiving data
 * over an L2TP session:-
 *
 *	काष्ठा sockaddr_pppol2tp sax;
 *	पूर्णांक fd;
 *	पूर्णांक session_fd;
 *
 *	fd = socket(AF_PPPOX, SOCK_DGRAM, PX_PROTO_OL2TP);
 *
 *	sax.sa_family = AF_PPPOX;
 *	sax.sa_protocol = PX_PROTO_OL2TP;
 *	sax.pppol2tp.fd = tunnel_fd;	// bound UDP socket
 *	sax.pppol2tp.addr.sin_addr.s_addr = addr->sin_addr.s_addr;
 *	sax.pppol2tp.addr.sin_port = addr->sin_port;
 *	sax.pppol2tp.addr.sin_family = AF_INET;
 *	sax.pppol2tp.s_tunnel  = tunnel_id;
 *	sax.pppol2tp.s_session = session_id;
 *	sax.pppol2tp.d_tunnel  = peer_tunnel_id;
 *	sax.pppol2tp.d_session = peer_session_id;
 *
 *	session_fd = connect(fd, (काष्ठा sockaddr *)&sax, माप(sax));
 *
 * A pppd plugin that allows PPP traffic to be carried over L2TP using
 * this driver is available from the OpenL2TP project at
 * http://खोलोl2tp.sourceक्रमge.net.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/अगर_pppol2tp.h>
#समावेश <net/sock.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/file.h>
#समावेश <linux/hash.h>
#समावेश <linux/sort.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/nsproxy.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>

#समावेश "l2tp_core.h"

#घोषणा PPPOL2TP_DRV_VERSION	"V2.0"

/* Space क्रम UDP, L2TP and PPP headers */
#घोषणा PPPOL2TP_HEADER_OVERHEAD	40

/* Number of bytes to build transmit L2TP headers.
 * Unक्रमtunately the size is dअगरferent depending on whether sequence numbers
 * are enabled.
 */
#घोषणा PPPOL2TP_L2TP_HDR_SIZE_SEQ		10
#घोषणा PPPOL2TP_L2TP_HDR_SIZE_NOSEQ		6

/* Private data of each session. This data lives at the end of काष्ठा
 * l2tp_session, referenced via session->priv[].
 */
काष्ठा pppol2tp_session अणु
	पूर्णांक			owner;		/* pid that खोलोed the socket */

	काष्ठा mutex		sk_lock;	/* Protects .sk */
	काष्ठा sock __rcu	*sk;		/* Poपूर्णांकer to the session PPPoX socket */
	काष्ठा sock		*__sk;		/* Copy of .sk, क्रम cleanup */
	काष्ठा rcu_head		rcu;		/* For asynchronous release */
पूर्ण;

अटल पूर्णांक pppol2tp_xmit(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb);

अटल स्थिर काष्ठा ppp_channel_ops pppol2tp_chan_ops = अणु
	.start_xmit =  pppol2tp_xmit,
पूर्ण;

अटल स्थिर काष्ठा proto_ops pppol2tp_ops;

/* Retrieves the pppol2tp socket associated to a session.
 * A reference is held on the वापसed socket, so this function must be paired
 * with sock_put().
 */
अटल काष्ठा sock *pppol2tp_session_get_sock(काष्ठा l2tp_session *session)
अणु
	काष्ठा pppol2tp_session *ps = l2tp_session_priv(session);
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	sk = rcu_dereference(ps->sk);
	अगर (sk)
		sock_hold(sk);
	rcu_पढ़ो_unlock();

	वापस sk;
पूर्ण

/* Helpers to obtain tunnel/session contexts from sockets.
 */
अटल अंतरभूत काष्ठा l2tp_session *pppol2tp_sock_to_session(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_session *session;

	अगर (!sk)
		वापस शून्य;

	sock_hold(sk);
	session = (काष्ठा l2tp_session *)(sk->sk_user_data);
	अगर (!session) अणु
		sock_put(sk);
		जाओ out;
	पूर्ण
	अगर (WARN_ON(session->magic != L2TP_SESSION_MAGIC)) अणु
		session = शून्य;
		sock_put(sk);
		जाओ out;
	पूर्ण

out:
	वापस session;
पूर्ण

/*****************************************************************************
 * Receive data handling
 *****************************************************************************/

/* Receive message. This is the recvmsg क्रम the PPPoL2TP socket.
 */
अटल पूर्णांक pppol2tp_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = sock->sk;

	err = -EIO;
	अगर (sk->sk_state & PPPOX_BOUND)
		जाओ end;

	err = 0;
	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
				flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ end;

	अगर (len > skb->len)
		len = skb->len;
	अन्यथा अगर (len < skb->len)
		msg->msg_flags |= MSG_TRUNC;

	err = skb_copy_datagram_msg(skb, 0, msg, len);
	अगर (likely(err == 0))
		err = len;

	kमुक्त_skb(skb);
end:
	वापस err;
पूर्ण

अटल व्योम pppol2tp_recv(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb, पूर्णांक data_len)
अणु
	काष्ठा pppol2tp_session *ps = l2tp_session_priv(session);
	काष्ठा sock *sk = शून्य;

	/* If the socket is bound, send it in to PPP's input queue. Otherwise
	 * queue it on the session socket.
	 */
	rcu_पढ़ो_lock();
	sk = rcu_dereference(ps->sk);
	अगर (!sk)
		जाओ no_sock;

	/* If the first two bytes are 0xFF03, consider that it is the PPP's
	 * Address and Control fields and skip them. The L2TP module has always
	 * worked this way, although, in theory, the use of these fields should
	 * be negociated and handled at the PPP layer. These fields are
	 * स्थिरant: 0xFF is the All-Stations Address and 0x03 the Unnumbered
	 * Inक्रमmation command with Poll/Final bit set to zero (RFC 1662).
	 */
	अगर (pskb_may_pull(skb, 2) && skb->data[0] == PPP_ALLSTATIONS &&
	    skb->data[1] == PPP_UI)
		skb_pull(skb, 2);

	अगर (sk->sk_state & PPPOX_BOUND) अणु
		काष्ठा pppox_sock *po;

		po = pppox_sk(sk);
		ppp_input(&po->chan, skb);
	पूर्ण अन्यथा अणु
		अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
			atomic_दीर्घ_inc(&session->stats.rx_errors);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस;

no_sock:
	rcu_पढ़ो_unlock();
	pr_warn_ratelimited("%s: no socket in recv\n", session->name);
	kमुक्त_skb(skb);
पूर्ण

/************************************************************************
 * Transmit handling
 ***********************************************************************/

/* This is the sendmsg क्रम the PPPoL2TP pppol2tp_session socket.  We come here
 * when a user application करोes a sendmsg() on the session socket. L2TP and
 * PPP headers must be inserted पूर्णांकo the user's data.
 */
अटल पूर्णांक pppol2tp_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			    माप_प्रकार total_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक error;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel;
	पूर्णांक uhlen;

	error = -ENOTCONN;
	अगर (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		जाओ error;

	/* Get session and tunnel contexts */
	error = -EBADF;
	session = pppol2tp_sock_to_session(sk);
	अगर (!session)
		जाओ error;

	tunnel = session->tunnel;

	uhlen = (tunnel->encap == L2TP_ENCAPTYPE_UDP) ? माप(काष्ठा udphdr) : 0;

	/* Allocate a socket buffer */
	error = -ENOMEM;
	skb = sock_wदो_स्मृति(sk, NET_SKB_PAD + माप(काष्ठा iphdr) +
			   uhlen + session->hdr_len +
			   2 + total_len, /* 2 bytes क्रम PPP_ALLSTATIONS & PPP_UI */
			   0, GFP_KERNEL);
	अगर (!skb)
		जाओ error_put_sess;

	/* Reserve space क्रम headers. */
	skb_reserve(skb, NET_SKB_PAD);
	skb_reset_network_header(skb);
	skb_reserve(skb, माप(काष्ठा iphdr));
	skb_reset_transport_header(skb);
	skb_reserve(skb, uhlen);

	/* Add PPP header */
	skb->data[0] = PPP_ALLSTATIONS;
	skb->data[1] = PPP_UI;
	skb_put(skb, 2);

	/* Copy user data पूर्णांकo skb */
	error = स_नकल_from_msg(skb_put(skb, total_len), m, total_len);
	अगर (error < 0) अणु
		kमुक्त_skb(skb);
		जाओ error_put_sess;
	पूर्ण

	local_bh_disable();
	l2tp_xmit_skb(session, skb);
	local_bh_enable();

	sock_put(sk);

	वापस total_len;

error_put_sess:
	sock_put(sk);
error:
	वापस error;
पूर्ण

/* Transmit function called by generic PPP driver.  Sends PPP frame
 * over PPPoL2TP socket.
 *
 * This is almost the same as pppol2tp_sendmsg(), but rather than
 * being called with a msghdr from userspace, it is called with a skb
 * from the kernel.
 *
 * The supplied skb from ppp करोesn't have enough headroom क्रम the
 * insertion of L2TP, UDP and IP headers so we need to allocate more
 * headroom in the skb. This will create a cloned skb. But we must be
 * careful in the error हाल because the caller will expect to मुक्त
 * the skb it supplied, not our cloned skb. So we take care to always
 * leave the original skb unमुक्तd अगर we वापस an error.
 */
अटल पूर्णांक pppol2tp_xmit(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)chan->निजी;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel;
	पूर्णांक uhlen, headroom;

	अगर (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		जाओ पात;

	/* Get session and tunnel contexts from the socket */
	session = pppol2tp_sock_to_session(sk);
	अगर (!session)
		जाओ पात;

	tunnel = session->tunnel;

	uhlen = (tunnel->encap == L2TP_ENCAPTYPE_UDP) ? माप(काष्ठा udphdr) : 0;
	headroom = NET_SKB_PAD +
		   माप(काष्ठा iphdr) + /* IP header */
		   uhlen +		/* UDP header (अगर L2TP_ENCAPTYPE_UDP) */
		   session->hdr_len +	/* L2TP header */
		   2;			/* 2 bytes क्रम PPP_ALLSTATIONS & PPP_UI */
	अगर (skb_cow_head(skb, headroom))
		जाओ पात_put_sess;

	/* Setup PPP header */
	__skb_push(skb, 2);
	skb->data[0] = PPP_ALLSTATIONS;
	skb->data[1] = PPP_UI;

	local_bh_disable();
	l2tp_xmit_skb(session, skb);
	local_bh_enable();

	sock_put(sk);

	वापस 1;

पात_put_sess:
	sock_put(sk);
पात:
	/* Free the original skb */
	kमुक्त_skb(skb);
	वापस 1;
पूर्ण

/*****************************************************************************
 * Session (and tunnel control) socket create/destroy.
 *****************************************************************************/

अटल व्योम pppol2tp_put_sk(काष्ठा rcu_head *head)
अणु
	काष्ठा pppol2tp_session *ps;

	ps = container_of(head, typeof(*ps), rcu);
	sock_put(ps->__sk);
पूर्ण

/* Really समाप्त the session socket. (Called from sock_put() अगर
 * refcnt == 0.)
 */
अटल व्योम pppol2tp_session_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा l2tp_session *session = sk->sk_user_data;

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);

	अगर (session) अणु
		sk->sk_user_data = शून्य;
		अगर (WARN_ON(session->magic != L2TP_SESSION_MAGIC))
			वापस;
		l2tp_session_dec_refcount(session);
	पूर्ण
पूर्ण

/* Called when the PPPoX socket (session) is बंदd.
 */
अटल पूर्णांक pppol2tp_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2tp_session *session;
	पूर्णांक error;

	अगर (!sk)
		वापस 0;

	error = -EBADF;
	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_DEAD) != 0)
		जाओ error;

	pppox_unbind_sock(sk);

	/* Signal the death of the socket. */
	sk->sk_state = PPPOX_DEAD;
	sock_orphan(sk);
	sock->sk = शून्य;

	session = pppol2tp_sock_to_session(sk);
	अगर (session) अणु
		काष्ठा pppol2tp_session *ps;

		l2tp_session_delete(session);

		ps = l2tp_session_priv(session);
		mutex_lock(&ps->sk_lock);
		ps->__sk = rcu_dereference_रक्षित(ps->sk,
						     lockdep_is_held(&ps->sk_lock));
		RCU_INIT_POINTER(ps->sk, शून्य);
		mutex_unlock(&ps->sk_lock);
		call_rcu(&ps->rcu, pppol2tp_put_sk);

		/* Rely on the sock_put() call at the end of the function क्रम
		 * dropping the reference held by pppol2tp_sock_to_session().
		 * The last reference will be dropped by pppol2tp_put_sk().
		 */
	पूर्ण

	release_sock(sk);

	/* This will delete the session context via
	 * pppol2tp_session_deकाष्ठा() अगर the socket's refcnt drops to
	 * zero.
	 */
	sock_put(sk);

	वापस 0;

error:
	release_sock(sk);
	वापस error;
पूर्ण

अटल काष्ठा proto pppol2tp_sk_proto = अणु
	.name	  = "PPPOL2TP",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा pppox_sock),
पूर्ण;

अटल पूर्णांक pppol2tp_backlog_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;

	rc = l2tp_udp_encap_recv(sk, skb);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस NET_RX_SUCCESS;
पूर्ण

/* socket() handler. Initialize a new काष्ठा sock.
 */
अटल पूर्णांक pppol2tp_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक kern)
अणु
	पूर्णांक error = -ENOMEM;
	काष्ठा sock *sk;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pppol2tp_sk_proto, kern);
	अगर (!sk)
		जाओ out;

	sock_init_data(sock, sk);

	sock->state  = SS_UNCONNECTED;
	sock->ops    = &pppol2tp_ops;

	sk->sk_backlog_rcv = pppol2tp_backlog_recv;
	sk->sk_protocol	   = PX_PROTO_OL2TP;
	sk->sk_family	   = PF_PPPOX;
	sk->sk_state	   = PPPOX_NONE;
	sk->sk_type	   = SOCK_STREAM;
	sk->sk_deकाष्ठा	   = pppol2tp_session_deकाष्ठा;

	error = 0;

out:
	वापस error;
पूर्ण

अटल व्योम pppol2tp_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा l2tp_session *session = arg;
	काष्ठा sock *sk;

	sk = pppol2tp_session_get_sock(session);
	अगर (sk) अणु
		काष्ठा pppox_sock *po = pppox_sk(sk);

		seq_म_लिखो(m, "   interface %s\n", ppp_dev_name(&po->chan));
		sock_put(sk);
	पूर्ण
पूर्ण

अटल व्योम pppol2tp_session_init(काष्ठा l2tp_session *session)
अणु
	काष्ठा pppol2tp_session *ps;

	session->recv_skb = pppol2tp_recv;
	अगर (IS_ENABLED(CONFIG_L2TP_DEBUGFS))
		session->show = pppol2tp_show;

	ps = l2tp_session_priv(session);
	mutex_init(&ps->sk_lock);
	ps->owner = current->pid;
पूर्ण

काष्ठा l2tp_connect_info अणु
	u8 version;
	पूर्णांक fd;
	u32 tunnel_id;
	u32 peer_tunnel_id;
	u32 session_id;
	u32 peer_session_id;
पूर्ण;

अटल पूर्णांक pppol2tp_sockaddr_get_info(स्थिर व्योम *sa, पूर्णांक sa_len,
				      काष्ठा l2tp_connect_info *info)
अणु
	चयन (sa_len) अणु
	हाल माप(काष्ठा sockaddr_pppol2tp):
	अणु
		स्थिर काष्ठा sockaddr_pppol2tp *sa_v2in4 = sa;

		अगर (sa_v2in4->sa_protocol != PX_PROTO_OL2TP)
			वापस -EINVAL;

		info->version = 2;
		info->fd = sa_v2in4->pppol2tp.fd;
		info->tunnel_id = sa_v2in4->pppol2tp.s_tunnel;
		info->peer_tunnel_id = sa_v2in4->pppol2tp.d_tunnel;
		info->session_id = sa_v2in4->pppol2tp.s_session;
		info->peer_session_id = sa_v2in4->pppol2tp.d_session;

		अवरोध;
	पूर्ण
	हाल माप(काष्ठा sockaddr_pppol2tpv3):
	अणु
		स्थिर काष्ठा sockaddr_pppol2tpv3 *sa_v3in4 = sa;

		अगर (sa_v3in4->sa_protocol != PX_PROTO_OL2TP)
			वापस -EINVAL;

		info->version = 3;
		info->fd = sa_v3in4->pppol2tp.fd;
		info->tunnel_id = sa_v3in4->pppol2tp.s_tunnel;
		info->peer_tunnel_id = sa_v3in4->pppol2tp.d_tunnel;
		info->session_id = sa_v3in4->pppol2tp.s_session;
		info->peer_session_id = sa_v3in4->pppol2tp.d_session;

		अवरोध;
	पूर्ण
	हाल माप(काष्ठा sockaddr_pppol2tpin6):
	अणु
		स्थिर काष्ठा sockaddr_pppol2tpin6 *sa_v2in6 = sa;

		अगर (sa_v2in6->sa_protocol != PX_PROTO_OL2TP)
			वापस -EINVAL;

		info->version = 2;
		info->fd = sa_v2in6->pppol2tp.fd;
		info->tunnel_id = sa_v2in6->pppol2tp.s_tunnel;
		info->peer_tunnel_id = sa_v2in6->pppol2tp.d_tunnel;
		info->session_id = sa_v2in6->pppol2tp.s_session;
		info->peer_session_id = sa_v2in6->pppol2tp.d_session;

		अवरोध;
	पूर्ण
	हाल माप(काष्ठा sockaddr_pppol2tpv3in6):
	अणु
		स्थिर काष्ठा sockaddr_pppol2tpv3in6 *sa_v3in6 = sa;

		अगर (sa_v3in6->sa_protocol != PX_PROTO_OL2TP)
			वापस -EINVAL;

		info->version = 3;
		info->fd = sa_v3in6->pppol2tp.fd;
		info->tunnel_id = sa_v3in6->pppol2tp.s_tunnel;
		info->peer_tunnel_id = sa_v3in6->pppol2tp.d_tunnel;
		info->session_id = sa_v3in6->pppol2tp.s_session;
		info->peer_session_id = sa_v3in6->pppol2tp.d_session;

		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Rough estimation of the maximum payload size a tunnel can transmit without
 * fragmenting at the lower IP layer. Assumes L2TPv2 with sequence
 * numbers and no IP option. Not quite accurate, but the result is mostly
 * unused anyway.
 */
अटल पूर्णांक pppol2tp_tunnel_mtu(स्थिर काष्ठा l2tp_tunnel *tunnel)
अणु
	पूर्णांक mtu;

	mtu = l2tp_tunnel_dst_mtu(tunnel);
	अगर (mtu <= PPPOL2TP_HEADER_OVERHEAD)
		वापस 1500 - PPPOL2TP_HEADER_OVERHEAD;

	वापस mtu - PPPOL2TP_HEADER_OVERHEAD;
पूर्ण

/* connect() handler. Attach a PPPoX socket to a tunnel UDP socket
 */
अटल पूर्णांक pppol2tp_connect(काष्ठा socket *sock, काष्ठा sockaddr *uservaddr,
			    पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा l2tp_session *session = शून्य;
	काष्ठा l2tp_connect_info info;
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा pppol2tp_session *ps;
	काष्ठा l2tp_session_cfg cfg = अणु 0, पूर्ण;
	bool drop_refcnt = false;
	bool drop_tunnel = false;
	bool new_session = false;
	bool new_tunnel = false;
	पूर्णांक error;

	error = pppol2tp_sockaddr_get_info(uservaddr, sockaddr_len, &info);
	अगर (error < 0)
		वापस error;

	lock_sock(sk);

	/* Check क्रम alपढ़ोy bound sockets */
	error = -EBUSY;
	अगर (sk->sk_state & PPPOX_CONNECTED)
		जाओ end;

	/* We करोn't supporting rebinding anyway */
	error = -EALREADY;
	अगर (sk->sk_user_data)
		जाओ end; /* socket is alपढ़ोy attached */

	/* Don't bind अगर tunnel_id is 0 */
	error = -EINVAL;
	अगर (!info.tunnel_id)
		जाओ end;

	tunnel = l2tp_tunnel_get(sock_net(sk), info.tunnel_id);
	अगर (tunnel)
		drop_tunnel = true;

	/* Special हाल: create tunnel context अगर session_id and
	 * peer_session_id is 0. Otherwise look up tunnel using supplied
	 * tunnel id.
	 */
	अगर (!info.session_id && !info.peer_session_id) अणु
		अगर (!tunnel) अणु
			काष्ठा l2tp_tunnel_cfg tcfg = अणु
				.encap = L2TP_ENCAPTYPE_UDP,
			पूर्ण;

			/* Prevent l2tp_tunnel_रेजिस्टर() from trying to set up
			 * a kernel socket.
			 */
			अगर (info.fd < 0) अणु
				error = -EBADF;
				जाओ end;
			पूर्ण

			error = l2tp_tunnel_create(info.fd,
						   info.version,
						   info.tunnel_id,
						   info.peer_tunnel_id, &tcfg,
						   &tunnel);
			अगर (error < 0)
				जाओ end;

			l2tp_tunnel_inc_refcount(tunnel);
			error = l2tp_tunnel_रेजिस्टर(tunnel, sock_net(sk),
						     &tcfg);
			अगर (error < 0) अणु
				kमुक्त(tunnel);
				जाओ end;
			पूर्ण
			drop_tunnel = true;
			new_tunnel = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Error अगर we can't find the tunnel */
		error = -ENOENT;
		अगर (!tunnel)
			जाओ end;

		/* Error अगर socket is not prepped */
		अगर (!tunnel->sock)
			जाओ end;
	पूर्ण

	अगर (tunnel->peer_tunnel_id == 0)
		tunnel->peer_tunnel_id = info.peer_tunnel_id;

	session = l2tp_tunnel_get_session(tunnel, info.session_id);
	अगर (session) अणु
		drop_refcnt = true;

		अगर (session->pwtype != L2TP_PWTYPE_PPP) अणु
			error = -EPROTOTYPE;
			जाओ end;
		पूर्ण

		ps = l2tp_session_priv(session);

		/* Using a pre-existing session is fine as दीर्घ as it hasn't
		 * been connected yet.
		 */
		mutex_lock(&ps->sk_lock);
		अगर (rcu_dereference_रक्षित(ps->sk,
					      lockdep_is_held(&ps->sk_lock)) ||
		    ps->__sk) अणु
			mutex_unlock(&ps->sk_lock);
			error = -EEXIST;
			जाओ end;
		पूर्ण
	पूर्ण अन्यथा अणु
		cfg.pw_type = L2TP_PWTYPE_PPP;

		session = l2tp_session_create(माप(काष्ठा pppol2tp_session),
					      tunnel, info.session_id,
					      info.peer_session_id, &cfg);
		अगर (IS_ERR(session)) अणु
			error = PTR_ERR(session);
			जाओ end;
		पूर्ण

		pppol2tp_session_init(session);
		ps = l2tp_session_priv(session);
		l2tp_session_inc_refcount(session);

		mutex_lock(&ps->sk_lock);
		error = l2tp_session_रेजिस्टर(session, tunnel);
		अगर (error < 0) अणु
			mutex_unlock(&ps->sk_lock);
			kमुक्त(session);
			जाओ end;
		पूर्ण
		drop_refcnt = true;
		new_session = true;
	पूर्ण

	/* Special हाल: अगर source & dest session_id == 0x0000, this
	 * socket is being created to manage the tunnel. Just set up
	 * the पूर्णांकernal context क्रम use by ioctl() and sockopt()
	 * handlers.
	 */
	अगर (session->session_id == 0 && session->peer_session_id == 0) अणु
		error = 0;
		जाओ out_no_ppp;
	पूर्ण

	/* The only header we need to worry about is the L2TP
	 * header. This size is dअगरferent depending on whether
	 * sequence numbers are enabled क्रम the data channel.
	 */
	po->chan.hdrlen = PPPOL2TP_L2TP_HDR_SIZE_NOSEQ;

	po->chan.निजी = sk;
	po->chan.ops	 = &pppol2tp_chan_ops;
	po->chan.mtu	 = pppol2tp_tunnel_mtu(tunnel);

	error = ppp_रेजिस्टर_net_channel(sock_net(sk), &po->chan);
	अगर (error) अणु
		mutex_unlock(&ps->sk_lock);
		जाओ end;
	पूर्ण

out_no_ppp:
	/* This is how we get the session context from the socket. */
	sk->sk_user_data = session;
	rcu_assign_poपूर्णांकer(ps->sk, sk);
	mutex_unlock(&ps->sk_lock);

	/* Keep the reference we've grabbed on the session: sk doesn't expect
	 * the session to disappear. pppol2tp_session_deकाष्ठा() is responsible
	 * क्रम dropping it.
	 */
	drop_refcnt = false;

	sk->sk_state = PPPOX_CONNECTED;

end:
	अगर (error) अणु
		अगर (new_session)
			l2tp_session_delete(session);
		अगर (new_tunnel)
			l2tp_tunnel_delete(tunnel);
	पूर्ण
	अगर (drop_refcnt)
		l2tp_session_dec_refcount(session);
	अगर (drop_tunnel)
		l2tp_tunnel_dec_refcount(tunnel);
	release_sock(sk);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_L2TP_V3

/* Called when creating sessions via the netlink पूर्णांकerface. */
अटल पूर्णांक pppol2tp_session_create(काष्ठा net *net, काष्ठा l2tp_tunnel *tunnel,
				   u32 session_id, u32 peer_session_id,
				   काष्ठा l2tp_session_cfg *cfg)
अणु
	पूर्णांक error;
	काष्ठा l2tp_session *session;

	/* Error अगर tunnel socket is not prepped */
	अगर (!tunnel->sock) अणु
		error = -ENOENT;
		जाओ err;
	पूर्ण

	/* Allocate and initialize a new session context. */
	session = l2tp_session_create(माप(काष्ठा pppol2tp_session),
				      tunnel, session_id,
				      peer_session_id, cfg);
	अगर (IS_ERR(session)) अणु
		error = PTR_ERR(session);
		जाओ err;
	पूर्ण

	pppol2tp_session_init(session);

	error = l2tp_session_रेजिस्टर(session, tunnel);
	अगर (error < 0)
		जाओ err_sess;

	वापस 0;

err_sess:
	kमुक्त(session);
err:
	वापस error;
पूर्ण

#पूर्ण_अगर /* CONFIG_L2TP_V3 */

/* getname() support.
 */
अटल पूर्णांक pppol2tp_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			    पूर्णांक peer)
अणु
	पूर्णांक len = 0;
	पूर्णांक error = 0;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा sock *sk = sock->sk;
	काष्ठा inet_sock *inet;
	काष्ठा pppol2tp_session *pls;

	error = -ENOTCONN;
	अगर (!sk)
		जाओ end;
	अगर (!(sk->sk_state & PPPOX_CONNECTED))
		जाओ end;

	error = -EBADF;
	session = pppol2tp_sock_to_session(sk);
	अगर (!session)
		जाओ end;

	pls = l2tp_session_priv(session);
	tunnel = session->tunnel;

	inet = inet_sk(tunnel->sock);
	अगर (tunnel->version == 2 && tunnel->sock->sk_family == AF_INET) अणु
		काष्ठा sockaddr_pppol2tp sp;

		len = माप(sp);
		स_रखो(&sp, 0, len);
		sp.sa_family	= AF_PPPOX;
		sp.sa_protocol	= PX_PROTO_OL2TP;
		sp.pppol2tp.fd  = tunnel->fd;
		sp.pppol2tp.pid = pls->owner;
		sp.pppol2tp.s_tunnel = tunnel->tunnel_id;
		sp.pppol2tp.d_tunnel = tunnel->peer_tunnel_id;
		sp.pppol2tp.s_session = session->session_id;
		sp.pppol2tp.d_session = session->peer_session_id;
		sp.pppol2tp.addr.sin_family = AF_INET;
		sp.pppol2tp.addr.sin_port = inet->inet_dport;
		sp.pppol2tp.addr.sin_addr.s_addr = inet->inet_daddr;
		स_नकल(uaddr, &sp, len);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (tunnel->version == 2 && tunnel->sock->sk_family == AF_INET6) अणु
		काष्ठा sockaddr_pppol2tpin6 sp;

		len = माप(sp);
		स_रखो(&sp, 0, len);
		sp.sa_family	= AF_PPPOX;
		sp.sa_protocol	= PX_PROTO_OL2TP;
		sp.pppol2tp.fd  = tunnel->fd;
		sp.pppol2tp.pid = pls->owner;
		sp.pppol2tp.s_tunnel = tunnel->tunnel_id;
		sp.pppol2tp.d_tunnel = tunnel->peer_tunnel_id;
		sp.pppol2tp.s_session = session->session_id;
		sp.pppol2tp.d_session = session->peer_session_id;
		sp.pppol2tp.addr.sin6_family = AF_INET6;
		sp.pppol2tp.addr.sin6_port = inet->inet_dport;
		स_नकल(&sp.pppol2tp.addr.sin6_addr, &tunnel->sock->sk_v6_daddr,
		       माप(tunnel->sock->sk_v6_daddr));
		स_नकल(uaddr, &sp, len);
	पूर्ण अन्यथा अगर (tunnel->version == 3 && tunnel->sock->sk_family == AF_INET6) अणु
		काष्ठा sockaddr_pppol2tpv3in6 sp;

		len = माप(sp);
		स_रखो(&sp, 0, len);
		sp.sa_family	= AF_PPPOX;
		sp.sa_protocol	= PX_PROTO_OL2TP;
		sp.pppol2tp.fd  = tunnel->fd;
		sp.pppol2tp.pid = pls->owner;
		sp.pppol2tp.s_tunnel = tunnel->tunnel_id;
		sp.pppol2tp.d_tunnel = tunnel->peer_tunnel_id;
		sp.pppol2tp.s_session = session->session_id;
		sp.pppol2tp.d_session = session->peer_session_id;
		sp.pppol2tp.addr.sin6_family = AF_INET6;
		sp.pppol2tp.addr.sin6_port = inet->inet_dport;
		स_नकल(&sp.pppol2tp.addr.sin6_addr, &tunnel->sock->sk_v6_daddr,
		       माप(tunnel->sock->sk_v6_daddr));
		स_नकल(uaddr, &sp, len);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (tunnel->version == 3) अणु
		काष्ठा sockaddr_pppol2tpv3 sp;

		len = माप(sp);
		स_रखो(&sp, 0, len);
		sp.sa_family	= AF_PPPOX;
		sp.sa_protocol	= PX_PROTO_OL2TP;
		sp.pppol2tp.fd  = tunnel->fd;
		sp.pppol2tp.pid = pls->owner;
		sp.pppol2tp.s_tunnel = tunnel->tunnel_id;
		sp.pppol2tp.d_tunnel = tunnel->peer_tunnel_id;
		sp.pppol2tp.s_session = session->session_id;
		sp.pppol2tp.d_session = session->peer_session_id;
		sp.pppol2tp.addr.sin_family = AF_INET;
		sp.pppol2tp.addr.sin_port = inet->inet_dport;
		sp.pppol2tp.addr.sin_addr.s_addr = inet->inet_daddr;
		स_नकल(uaddr, &sp, len);
	पूर्ण

	error = len;

	sock_put(sk);
end:
	वापस error;
पूर्ण

/****************************************************************************
 * ioctl() handlers.
 *
 * The PPPoX socket is created क्रम L2TP sessions: tunnels have their own UDP
 * sockets. However, in order to control kernel tunnel features, we allow
 * userspace to create a special "tunnel" PPPoX socket which is used क्रम
 * control only.  Tunnel PPPoX sockets have session_id == 0 and simply allow
 * the user application to issue L2TP setsockopt(), माला_लोockopt() and ioctl()
 * calls.
 ****************************************************************************/

अटल व्योम pppol2tp_copy_stats(काष्ठा pppol2tp_ioc_stats *dest,
				स्थिर काष्ठा l2tp_stats *stats)
अणु
	स_रखो(dest, 0, माप(*dest));

	dest->tx_packets = atomic_दीर्घ_पढ़ो(&stats->tx_packets);
	dest->tx_bytes = atomic_दीर्घ_पढ़ो(&stats->tx_bytes);
	dest->tx_errors = atomic_दीर्घ_पढ़ो(&stats->tx_errors);
	dest->rx_packets = atomic_दीर्घ_पढ़ो(&stats->rx_packets);
	dest->rx_bytes = atomic_दीर्घ_पढ़ो(&stats->rx_bytes);
	dest->rx_seq_discards = atomic_दीर्घ_पढ़ो(&stats->rx_seq_discards);
	dest->rx_oos_packets = atomic_दीर्घ_पढ़ो(&stats->rx_oos_packets);
	dest->rx_errors = atomic_दीर्घ_पढ़ो(&stats->rx_errors);
पूर्ण

अटल पूर्णांक pppol2tp_tunnel_copy_stats(काष्ठा pppol2tp_ioc_stats *stats,
				      काष्ठा l2tp_tunnel *tunnel)
अणु
	काष्ठा l2tp_session *session;

	अगर (!stats->session_id) अणु
		pppol2tp_copy_stats(stats, &tunnel->stats);
		वापस 0;
	पूर्ण

	/* If session_id is set, search the corresponding session in the
	 * context of this tunnel and record the session's statistics.
	 */
	session = l2tp_tunnel_get_session(tunnel, stats->session_id);
	अगर (!session)
		वापस -EBADR;

	अगर (session->pwtype != L2TP_PWTYPE_PPP) अणु
		l2tp_session_dec_refcount(session);
		वापस -EBADR;
	पूर्ण

	pppol2tp_copy_stats(stats, &session->stats);
	l2tp_session_dec_refcount(session);

	वापस 0;
पूर्ण

अटल पूर्णांक pppol2tp_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा pppol2tp_ioc_stats stats;
	काष्ठा l2tp_session *session;

	चयन (cmd) अणु
	हाल PPPIOCGMRU:
	हाल PPPIOCGFLAGS:
		session = sock->sk->sk_user_data;
		अगर (!session)
			वापस -ENOTCONN;

		अगर (WARN_ON(session->magic != L2TP_SESSION_MAGIC))
			वापस -EBADF;

		/* Not defined क्रम tunnels */
		अगर (!session->session_id && !session->peer_session_id)
			वापस -ENOSYS;

		अगर (put_user(0, (पूर्णांक __user *)arg))
			वापस -EFAULT;
		अवरोध;

	हाल PPPIOCSMRU:
	हाल PPPIOCSFLAGS:
		session = sock->sk->sk_user_data;
		अगर (!session)
			वापस -ENOTCONN;

		अगर (WARN_ON(session->magic != L2TP_SESSION_MAGIC))
			वापस -EBADF;

		/* Not defined क्रम tunnels */
		अगर (!session->session_id && !session->peer_session_id)
			वापस -ENOSYS;

		अगर (!access_ok((पूर्णांक __user *)arg, माप(पूर्णांक)))
			वापस -EFAULT;
		अवरोध;

	हाल PPPIOCGL2TPSTATS:
		session = sock->sk->sk_user_data;
		अगर (!session)
			वापस -ENOTCONN;

		अगर (WARN_ON(session->magic != L2TP_SESSION_MAGIC))
			वापस -EBADF;

		/* Session 0 represents the parent tunnel */
		अगर (!session->session_id && !session->peer_session_id) अणु
			u32 session_id;
			पूर्णांक err;

			अगर (copy_from_user(&stats, (व्योम __user *)arg,
					   माप(stats)))
				वापस -EFAULT;

			session_id = stats.session_id;
			err = pppol2tp_tunnel_copy_stats(&stats,
							 session->tunnel);
			अगर (err < 0)
				वापस err;

			stats.session_id = session_id;
		पूर्ण अन्यथा अणु
			pppol2tp_copy_stats(&stats, &session->stats);
			stats.session_id = session->session_id;
		पूर्ण
		stats.tunnel_id = session->tunnel->tunnel_id;
		stats.using_ipsec = l2tp_tunnel_uses_xfrm(session->tunnel);

		अगर (copy_to_user((व्योम __user *)arg, &stats, माप(stats)))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

/*****************************************************************************
 * setsockopt() / माला_लोockopt() support.
 *
 * The PPPoX socket is created क्रम L2TP sessions: tunnels have their own UDP
 * sockets. In order to control kernel tunnel features, we allow userspace to
 * create a special "tunnel" PPPoX socket which is used क्रम control only.
 * Tunnel PPPoX sockets have session_id == 0 and simply allow the user
 * application to issue L2TP setsockopt(), माला_लोockopt() and ioctl() calls.
 *****************************************************************************/

/* Tunnel setsockopt() helper.
 */
अटल पूर्णांक pppol2tp_tunnel_setsockopt(काष्ठा sock *sk,
				      काष्ठा l2tp_tunnel *tunnel,
				      पूर्णांक optname, पूर्णांक val)
अणु
	पूर्णांक err = 0;

	चयन (optname) अणु
	हाल PPPOL2TP_SO_DEBUG:
		/* Tunnel debug flags option is deprecated */
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Session setsockopt helper.
 */
अटल पूर्णांक pppol2tp_session_setsockopt(काष्ठा sock *sk,
				       काष्ठा l2tp_session *session,
				       पूर्णांक optname, पूर्णांक val)
अणु
	पूर्णांक err = 0;

	चयन (optname) अणु
	हाल PPPOL2TP_SO_RECVSEQ:
		अगर (val != 0 && val != 1) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		session->recv_seq = !!val;
		अवरोध;

	हाल PPPOL2TP_SO_SENDSEQ:
		अगर (val != 0 && val != 1) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		session->send_seq = !!val;
		अणु
			काष्ठा pppox_sock *po = pppox_sk(sk);

			po->chan.hdrlen = val ? PPPOL2TP_L2TP_HDR_SIZE_SEQ :
				PPPOL2TP_L2TP_HDR_SIZE_NOSEQ;
		पूर्ण
		l2tp_session_set_header_len(session, session->tunnel->version);
		अवरोध;

	हाल PPPOL2TP_SO_LNSMODE:
		अगर (val != 0 && val != 1) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		session->lns_mode = !!val;
		अवरोध;

	हाल PPPOL2TP_SO_DEBUG:
		/* Session debug flags option is deprecated */
		अवरोध;

	हाल PPPOL2TP_SO_REORDERTO:
		session->reorder_समयout = msecs_to_jअगरfies(val);
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Main setsockopt() entry poपूर्णांक.
 * Does API checks, then calls either the tunnel or session setsockopt
 * handler, according to whether the PPPoL2TP socket is a क्रम a regular
 * session or the special tunnel type.
 */
अटल पूर्णांक pppol2tp_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel;
	पूर्णांक val;
	पूर्णांक err;

	अगर (level != SOL_PPPOL2TP)
		वापस -EINVAL;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	err = -ENOTCONN;
	अगर (!sk->sk_user_data)
		जाओ end;

	/* Get session context from the socket */
	err = -EBADF;
	session = pppol2tp_sock_to_session(sk);
	अगर (!session)
		जाओ end;

	/* Special हाल: अगर session_id == 0x0000, treat as operation on tunnel
	 */
	अगर (session->session_id == 0 && session->peer_session_id == 0) अणु
		tunnel = session->tunnel;
		err = pppol2tp_tunnel_setsockopt(sk, tunnel, optname, val);
	पूर्ण अन्यथा अणु
		err = pppol2tp_session_setsockopt(sk, session, optname, val);
	पूर्ण

	sock_put(sk);
end:
	वापस err;
पूर्ण

/* Tunnel माला_लोockopt helper. Called with sock locked.
 */
अटल पूर्णांक pppol2tp_tunnel_माला_लोockopt(काष्ठा sock *sk,
				      काष्ठा l2tp_tunnel *tunnel,
				      पूर्णांक optname, पूर्णांक *val)
अणु
	पूर्णांक err = 0;

	चयन (optname) अणु
	हाल PPPOL2TP_SO_DEBUG:
		/* Tunnel debug flags option is deprecated */
		*val = 0;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Session माला_लोockopt helper. Called with sock locked.
 */
अटल पूर्णांक pppol2tp_session_माला_लोockopt(काष्ठा sock *sk,
				       काष्ठा l2tp_session *session,
				       पूर्णांक optname, पूर्णांक *val)
अणु
	पूर्णांक err = 0;

	चयन (optname) अणु
	हाल PPPOL2TP_SO_RECVSEQ:
		*val = session->recv_seq;
		अवरोध;

	हाल PPPOL2TP_SO_SENDSEQ:
		*val = session->send_seq;
		अवरोध;

	हाल PPPOL2TP_SO_LNSMODE:
		*val = session->lns_mode;
		अवरोध;

	हाल PPPOL2TP_SO_DEBUG:
		/* Session debug flags option is deprecated */
		*val = 0;
		अवरोध;

	हाल PPPOL2TP_SO_REORDERTO:
		*val = (पूर्णांक)jअगरfies_to_msecs(session->reorder_समयout);
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
	पूर्ण

	वापस err;
पूर्ण

/* Main माला_लोockopt() entry poपूर्णांक.
 * Does API checks, then calls either the tunnel or session माला_लोockopt
 * handler, according to whether the PPPoX socket is a क्रम a regular session
 * or the special tunnel type.
 */
अटल पूर्णांक pppol2tp_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel;
	पूर्णांक val, len;
	पूर्णांक err;

	अगर (level != SOL_PPPOL2TP)
		वापस -EINVAL;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	अगर (len < 0)
		वापस -EINVAL;

	err = -ENOTCONN;
	अगर (!sk->sk_user_data)
		जाओ end;

	/* Get the session context */
	err = -EBADF;
	session = pppol2tp_sock_to_session(sk);
	अगर (!session)
		जाओ end;

	/* Special हाल: अगर session_id == 0x0000, treat as operation on tunnel */
	अगर (session->session_id == 0 && session->peer_session_id == 0) अणु
		tunnel = session->tunnel;
		err = pppol2tp_tunnel_माला_लोockopt(sk, tunnel, optname, &val);
		अगर (err)
			जाओ end_put_sess;
	पूर्ण अन्यथा अणु
		err = pppol2tp_session_माला_लोockopt(sk, session, optname, &val);
		अगर (err)
			जाओ end_put_sess;
	पूर्ण

	err = -EFAULT;
	अगर (put_user(len, optlen))
		जाओ end_put_sess;

	अगर (copy_to_user((व्योम __user *)optval, &val, len))
		जाओ end_put_sess;

	err = 0;

end_put_sess:
	sock_put(sk);
end:
	वापस err;
पूर्ण

/*****************************************************************************
 * /proc fileप्रणाली क्रम debug
 * Since the original pppol2tp driver provided /proc/net/pppol2tp क्रम
 * L2TPv2, we dump only L2TPv2 tunnels and sessions here.
 *****************************************************************************/

अटल अचिन्हित पूर्णांक pppol2tp_net_id;

#अगर_घोषित CONFIG_PROC_FS

काष्ठा pppol2tp_seq_data अणु
	काष्ठा seq_net_निजी p;
	पूर्णांक tunnel_idx;			/* current tunnel */
	पूर्णांक session_idx;		/* index of session within current tunnel */
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा l2tp_session *session;	/* शून्य means get next tunnel */
पूर्ण;

अटल व्योम pppol2tp_next_tunnel(काष्ठा net *net, काष्ठा pppol2tp_seq_data *pd)
अणु
	/* Drop reference taken during previous invocation */
	अगर (pd->tunnel)
		l2tp_tunnel_dec_refcount(pd->tunnel);

	क्रम (;;) अणु
		pd->tunnel = l2tp_tunnel_get_nth(net, pd->tunnel_idx);
		pd->tunnel_idx++;

		/* Only accept L2TPv2 tunnels */
		अगर (!pd->tunnel || pd->tunnel->version == 2)
			वापस;

		l2tp_tunnel_dec_refcount(pd->tunnel);
	पूर्ण
पूर्ण

अटल व्योम pppol2tp_next_session(काष्ठा net *net, काष्ठा pppol2tp_seq_data *pd)
अणु
	/* Drop reference taken during previous invocation */
	अगर (pd->session)
		l2tp_session_dec_refcount(pd->session);

	pd->session = l2tp_session_get_nth(pd->tunnel, pd->session_idx);
	pd->session_idx++;

	अगर (!pd->session) अणु
		pd->session_idx = 0;
		pppol2tp_next_tunnel(net, pd);
	पूर्ण
पूर्ण

अटल व्योम *pppol2tp_seq_start(काष्ठा seq_file *m, loff_t *offs)
अणु
	काष्ठा pppol2tp_seq_data *pd = SEQ_START_TOKEN;
	loff_t pos = *offs;
	काष्ठा net *net;

	अगर (!pos)
		जाओ out;

	अगर (WARN_ON(!m->निजी)) अणु
		pd = शून्य;
		जाओ out;
	पूर्ण

	pd = m->निजी;
	net = seq_file_net(m);

	अगर (!pd->tunnel)
		pppol2tp_next_tunnel(net, pd);
	अन्यथा
		pppol2tp_next_session(net, pd);

	/* शून्य tunnel and session indicates end of list */
	अगर (!pd->tunnel && !pd->session)
		pd = शून्य;

out:
	वापस pd;
पूर्ण

अटल व्योम *pppol2tp_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम pppol2tp_seq_stop(काष्ठा seq_file *p, व्योम *v)
अणु
	काष्ठा pppol2tp_seq_data *pd = v;

	अगर (!pd || pd == SEQ_START_TOKEN)
		वापस;

	/* Drop reference taken by last invocation of pppol2tp_next_session()
	 * or pppol2tp_next_tunnel().
	 */
	अगर (pd->session) अणु
		l2tp_session_dec_refcount(pd->session);
		pd->session = शून्य;
	पूर्ण
	अगर (pd->tunnel) अणु
		l2tp_tunnel_dec_refcount(pd->tunnel);
		pd->tunnel = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pppol2tp_seq_tunnel_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा l2tp_tunnel *tunnel = v;

	seq_म_लिखो(m, "\nTUNNEL '%s', %c %d\n",
		   tunnel->name,
		   (tunnel == tunnel->sock->sk_user_data) ? 'Y' : 'N',
		   refcount_पढ़ो(&tunnel->ref_count) - 1);
	seq_म_लिखो(m, " %08x %ld/%ld/%ld %ld/%ld/%ld\n",
		   0,
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_packets),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_bytes),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_errors),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_packets),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_bytes),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_errors));
पूर्ण

अटल व्योम pppol2tp_seq_session_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा l2tp_session *session = v;
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;
	अचिन्हित अक्षर state;
	अक्षर user_data_ok;
	काष्ठा sock *sk;
	u32 ip = 0;
	u16 port = 0;

	अगर (tunnel->sock) अणु
		काष्ठा inet_sock *inet = inet_sk(tunnel->sock);

		ip = ntohl(inet->inet_saddr);
		port = ntohs(inet->inet_sport);
	पूर्ण

	sk = pppol2tp_session_get_sock(session);
	अगर (sk) अणु
		state = sk->sk_state;
		user_data_ok = (session == sk->sk_user_data) ? 'Y' : 'N';
	पूर्ण अन्यथा अणु
		state = 0;
		user_data_ok = 'N';
	पूर्ण

	seq_म_लिखो(m, "  SESSION '%s' %08X/%d %04X/%04X -> %04X/%04X %d %c\n",
		   session->name, ip, port,
		   tunnel->tunnel_id,
		   session->session_id,
		   tunnel->peer_tunnel_id,
		   session->peer_session_id,
		   state, user_data_ok);
	seq_म_लिखो(m, "   0/0/%c/%c/%s %08x %u\n",
		   session->recv_seq ? 'R' : '-',
		   session->send_seq ? 'S' : '-',
		   session->lns_mode ? "LNS" : "LAC",
		   0,
		   jअगरfies_to_msecs(session->reorder_समयout));
	seq_म_लिखो(m, "   %hu/%hu %ld/%ld/%ld %ld/%ld/%ld\n",
		   session->nr, session->ns,
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_packets),
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_bytes),
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_errors),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_packets),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_bytes),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_errors));

	अगर (sk) अणु
		काष्ठा pppox_sock *po = pppox_sk(sk);

		seq_म_लिखो(m, "   interface %s\n", ppp_dev_name(&po->chan));
		sock_put(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक pppol2tp_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pppol2tp_seq_data *pd = v;

	/* display header on line 1 */
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "PPPoL2TP driver info, " PPPOL2TP_DRV_VERSION "\n");
		seq_माला_दो(m, "TUNNEL name, user-data-ok session-count\n");
		seq_माला_दो(m, " debug tx-pkts/bytes/errs rx-pkts/bytes/errs\n");
		seq_माला_दो(m, "  SESSION name, addr/port src-tid/sid dest-tid/sid state user-data-ok\n");
		seq_माला_दो(m, "   mtu/mru/rcvseq/sendseq/lns debug reorderto\n");
		seq_माला_दो(m, "   nr/ns tx-pkts/bytes/errs rx-pkts/bytes/errs\n");
		जाओ out;
	पूर्ण

	अगर (!pd->session)
		pppol2tp_seq_tunnel_show(m, pd->tunnel);
	अन्यथा
		pppol2tp_seq_session_show(m, pd->session);

out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations pppol2tp_seq_ops = अणु
	.start		= pppol2tp_seq_start,
	.next		= pppol2tp_seq_next,
	.stop		= pppol2tp_seq_stop,
	.show		= pppol2tp_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*****************************************************************************
 * Network namespace
 *****************************************************************************/

अटल __net_init पूर्णांक pppol2tp_init_net(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *pde;
	पूर्णांक err = 0;

	pde = proc_create_net("pppol2tp", 0444, net->proc_net,
			      &pppol2tp_seq_ops, माप(काष्ठा pppol2tp_seq_data));
	अगर (!pde) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल __net_निकास व्योम pppol2tp_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("pppol2tp", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations pppol2tp_net_ops = अणु
	.init = pppol2tp_init_net,
	.निकास = pppol2tp_निकास_net,
	.id   = &pppol2tp_net_id,
पूर्ण;

/*****************************************************************************
 * Init and cleanup
 *****************************************************************************/

अटल स्थिर काष्ठा proto_ops pppol2tp_ops = अणु
	.family		= AF_PPPOX,
	.owner		= THIS_MODULE,
	.release	= pppol2tp_release,
	.bind		= sock_no_bind,
	.connect	= pppol2tp_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= pppol2tp_getname,
	.poll		= datagram_poll,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.setsockopt	= pppol2tp_setsockopt,
	.माला_लोockopt	= pppol2tp_माला_लोockopt,
	.sendmsg	= pppol2tp_sendmsg,
	.recvmsg	= pppol2tp_recvmsg,
	.mmap		= sock_no_mmap,
	.ioctl		= pppox_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = pppox_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pppox_proto pppol2tp_proto = अणु
	.create		= pppol2tp_create,
	.ioctl		= pppol2tp_ioctl,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_L2TP_V3

अटल स्थिर काष्ठा l2tp_nl_cmd_ops pppol2tp_nl_cmd_ops = अणु
	.session_create	= pppol2tp_session_create,
	.session_delete	= l2tp_session_delete,
पूर्ण;

#पूर्ण_अगर /* CONFIG_L2TP_V3 */

अटल पूर्णांक __init pppol2tp_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_device(&pppol2tp_net_ops);
	अगर (err)
		जाओ out;

	err = proto_रेजिस्टर(&pppol2tp_sk_proto, 0);
	अगर (err)
		जाओ out_unरेजिस्टर_pppol2tp_pernet;

	err = रेजिस्टर_pppox_proto(PX_PROTO_OL2TP, &pppol2tp_proto);
	अगर (err)
		जाओ out_unरेजिस्टर_pppol2tp_proto;

#अगर_घोषित CONFIG_L2TP_V3
	err = l2tp_nl_रेजिस्टर_ops(L2TP_PWTYPE_PPP, &pppol2tp_nl_cmd_ops);
	अगर (err)
		जाओ out_unरेजिस्टर_pppox;
#पूर्ण_अगर

	pr_info("PPPoL2TP kernel driver, %s\n", PPPOL2TP_DRV_VERSION);

out:
	वापस err;

#अगर_घोषित CONFIG_L2TP_V3
out_unरेजिस्टर_pppox:
	unरेजिस्टर_pppox_proto(PX_PROTO_OL2TP);
#पूर्ण_अगर
out_unरेजिस्टर_pppol2tp_proto:
	proto_unरेजिस्टर(&pppol2tp_sk_proto);
out_unरेजिस्टर_pppol2tp_pernet:
	unरेजिस्टर_pernet_device(&pppol2tp_net_ops);
	जाओ out;
पूर्ण

अटल व्योम __निकास pppol2tp_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_L2TP_V3
	l2tp_nl_unरेजिस्टर_ops(L2TP_PWTYPE_PPP);
#पूर्ण_अगर
	unरेजिस्टर_pppox_proto(PX_PROTO_OL2TP);
	proto_unरेजिस्टर(&pppol2tp_sk_proto);
	unरेजिस्टर_pernet_device(&pppol2tp_net_ops);
पूर्ण

module_init(pppol2tp_init);
module_निकास(pppol2tp_निकास);

MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("PPP over L2TP over UDP");
MODULE_LICENSE("GPL");
MODULE_VERSION(PPPOL2TP_DRV_VERSION);
MODULE_ALIAS_NET_PF_PROTO(PF_PPPOX, PX_PROTO_OL2TP);
MODULE_ALIAS_L2TP_PWTYPE(7);
