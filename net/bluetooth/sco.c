<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/* Bluetooth SCO sockets. */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/sco.h>

अटल bool disable_esco;

अटल स्थिर काष्ठा proto_ops sco_sock_ops;

अटल काष्ठा bt_sock_list sco_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(sco_sk_list.lock)
पूर्ण;

/* ---- SCO connections ---- */
काष्ठा sco_conn अणु
	काष्ठा hci_conn	*hcon;

	spinlock_t	lock;
	काष्ठा sock	*sk;

	अचिन्हित पूर्णांक    mtu;
पूर्ण;

#घोषणा sco_conn_lock(c)	spin_lock(&c->lock)
#घोषणा sco_conn_unlock(c)	spin_unlock(&c->lock)

अटल व्योम sco_sock_बंद(काष्ठा sock *sk);
अटल व्योम sco_sock_समाप्त(काष्ठा sock *sk);

/* ----- SCO socket info ----- */
#घोषणा sco_pi(sk) ((काष्ठा sco_pinfo *) sk)

काष्ठा sco_pinfo अणु
	काष्ठा bt_sock	bt;
	bdaddr_t	src;
	bdaddr_t	dst;
	__u32		flags;
	__u16		setting;
	__u8		cmsg_mask;
	काष्ठा sco_conn	*conn;
पूर्ण;

/* ---- SCO समयrs ---- */
#घोषणा SCO_CONN_TIMEOUT	(HZ * 40)
#घोषणा SCO_DISCONN_TIMEOUT	(HZ * 2)

अटल व्योम sco_sock_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	BT_DBG("sock %p state %d", sk, sk->sk_state);

	bh_lock_sock(sk);
	sk->sk_err = ETIMEDOUT;
	sk->sk_state_change(sk);
	bh_unlock_sock(sk);

	sco_sock_समाप्त(sk);
	sock_put(sk);
पूर्ण

अटल व्योम sco_sock_set_समयr(काष्ठा sock *sk, दीर्घ समयout)
अणु
	BT_DBG("sock %p state %d timeout %ld", sk, sk->sk_state, समयout);
	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + समयout);
पूर्ण

अटल व्योम sco_sock_clear_समयr(काष्ठा sock *sk)
अणु
	BT_DBG("sock %p state %d", sk, sk->sk_state);
	sk_stop_समयr(sk, &sk->sk_समयr);
पूर्ण

/* ---- SCO connections ---- */
अटल काष्ठा sco_conn *sco_conn_add(काष्ठा hci_conn *hcon)
अणु
	काष्ठा hci_dev *hdev = hcon->hdev;
	काष्ठा sco_conn *conn = hcon->sco_data;

	अगर (conn)
		वापस conn;

	conn = kzalloc(माप(काष्ठा sco_conn), GFP_KERNEL);
	अगर (!conn)
		वापस शून्य;

	spin_lock_init(&conn->lock);

	hcon->sco_data = conn;
	conn->hcon = hcon;

	अगर (hdev->sco_mtu > 0)
		conn->mtu = hdev->sco_mtu;
	अन्यथा
		conn->mtu = 60;

	BT_DBG("hcon %p conn %p", hcon, conn);

	वापस conn;
पूर्ण

/* Delete channel.
 * Must be called on the locked socket. */
अटल व्योम sco_chan_del(काष्ठा sock *sk, पूर्णांक err)
अणु
	काष्ठा sco_conn *conn;

	conn = sco_pi(sk)->conn;

	BT_DBG("sk %p, conn %p, err %d", sk, conn, err);

	अगर (conn) अणु
		sco_conn_lock(conn);
		conn->sk = शून्य;
		sco_pi(sk)->conn = शून्य;
		sco_conn_unlock(conn);

		अगर (conn->hcon)
			hci_conn_drop(conn->hcon);
	पूर्ण

	sk->sk_state = BT_CLOSED;
	sk->sk_err   = err;
	sk->sk_state_change(sk);

	sock_set_flag(sk, SOCK_ZAPPED);
पूर्ण

अटल व्योम sco_conn_del(काष्ठा hci_conn *hcon, पूर्णांक err)
अणु
	काष्ठा sco_conn *conn = hcon->sco_data;
	काष्ठा sock *sk;

	अगर (!conn)
		वापस;

	BT_DBG("hcon %p conn %p, err %d", hcon, conn, err);

	/* Kill socket */
	sco_conn_lock(conn);
	sk = conn->sk;
	sco_conn_unlock(conn);

	अगर (sk) अणु
		sock_hold(sk);
		bh_lock_sock(sk);
		sco_sock_clear_समयr(sk);
		sco_chan_del(sk, err);
		bh_unlock_sock(sk);
		sco_sock_समाप्त(sk);
		sock_put(sk);
	पूर्ण

	hcon->sco_data = शून्य;
	kमुक्त(conn);
पूर्ण

अटल व्योम __sco_chan_add(काष्ठा sco_conn *conn, काष्ठा sock *sk,
			   काष्ठा sock *parent)
अणु
	BT_DBG("conn %p", conn);

	sco_pi(sk)->conn = conn;
	conn->sk = sk;

	अगर (parent)
		bt_accept_enqueue(parent, sk, true);
पूर्ण

अटल पूर्णांक sco_chan_add(काष्ठा sco_conn *conn, काष्ठा sock *sk,
			काष्ठा sock *parent)
अणु
	पूर्णांक err = 0;

	sco_conn_lock(conn);
	अगर (conn->sk)
		err = -EBUSY;
	अन्यथा
		__sco_chan_add(conn, sk, parent);

	sco_conn_unlock(conn);
	वापस err;
पूर्ण

अटल पूर्णांक sco_connect(काष्ठा sock *sk)
अणु
	काष्ठा sco_conn *conn;
	काष्ठा hci_conn *hcon;
	काष्ठा hci_dev  *hdev;
	पूर्णांक err, type;

	BT_DBG("%pMR -> %pMR", &sco_pi(sk)->src, &sco_pi(sk)->dst);

	hdev = hci_get_route(&sco_pi(sk)->dst, &sco_pi(sk)->src, BDADDR_BREDR);
	अगर (!hdev)
		वापस -EHOSTUNREACH;

	hci_dev_lock(hdev);

	अगर (lmp_esco_capable(hdev) && !disable_esco)
		type = ESCO_LINK;
	अन्यथा
		type = SCO_LINK;

	अगर (sco_pi(sk)->setting == BT_VOICE_TRANSPARENT &&
	    (!lmp_transp_capable(hdev) || !lmp_esco_capable(hdev))) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	hcon = hci_connect_sco(hdev, type, &sco_pi(sk)->dst,
			       sco_pi(sk)->setting);
	अगर (IS_ERR(hcon)) अणु
		err = PTR_ERR(hcon);
		जाओ करोne;
	पूर्ण

	conn = sco_conn_add(hcon);
	अगर (!conn) अणु
		hci_conn_drop(hcon);
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Update source addr of the socket */
	bacpy(&sco_pi(sk)->src, &hcon->src);

	err = sco_chan_add(conn, sk, शून्य);
	अगर (err)
		जाओ करोne;

	अगर (hcon->state == BT_CONNECTED) अणु
		sco_sock_clear_समयr(sk);
		sk->sk_state = BT_CONNECTED;
	पूर्ण अन्यथा अणु
		sk->sk_state = BT_CONNECT;
		sco_sock_set_समयr(sk, sk->sk_sndसमयo);
	पूर्ण

करोne:
	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
	वापस err;
पूर्ण

अटल पूर्णांक sco_send_frame(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len)
अणु
	काष्ठा sco_conn *conn = sco_pi(sk)->conn;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	/* Check outgoing MTU */
	अगर (len > conn->mtu)
		वापस -EINVAL;

	BT_DBG("sk %p len %d", sk, len);

	skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		वापस err;

	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	hci_send_sco(conn->hcon, skb);

	वापस len;
पूर्ण

अटल व्योम sco_recv_frame(काष्ठा sco_conn *conn, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;

	sco_conn_lock(conn);
	sk = conn->sk;
	sco_conn_unlock(conn);

	अगर (!sk)
		जाओ drop;

	BT_DBG("sk %p len %d", sk, skb->len);

	अगर (sk->sk_state != BT_CONNECTED)
		जाओ drop;

	अगर (!sock_queue_rcv_skb(sk, skb))
		वापस;

drop:
	kमुक्त_skb(skb);
पूर्ण

/* -------- Socket पूर्णांकerface ---------- */
अटल काष्ठा sock *__sco_get_sock_listen_by_addr(bdaddr_t *ba)
अणु
	काष्ठा sock *sk;

	sk_क्रम_each(sk, &sco_sk_list.head) अणु
		अगर (sk->sk_state != BT_LISTEN)
			जारी;

		अगर (!bacmp(&sco_pi(sk)->src, ba))
			वापस sk;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Find socket listening on source bdaddr.
 * Returns बंदst match.
 */
अटल काष्ठा sock *sco_get_sock_listen(bdaddr_t *src)
अणु
	काष्ठा sock *sk = शून्य, *sk1 = शून्य;

	पढ़ो_lock(&sco_sk_list.lock);

	sk_क्रम_each(sk, &sco_sk_list.head) अणु
		अगर (sk->sk_state != BT_LISTEN)
			जारी;

		/* Exact match. */
		अगर (!bacmp(&sco_pi(sk)->src, src))
			अवरोध;

		/* Closest match */
		अगर (!bacmp(&sco_pi(sk)->src, BDADDR_ANY))
			sk1 = sk;
	पूर्ण

	पढ़ो_unlock(&sco_sk_list.lock);

	वापस sk ? sk : sk1;
पूर्ण

अटल व्योम sco_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	BT_DBG("sk %p", sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);
पूर्ण

अटल व्योम sco_sock_cleanup_listen(काष्ठा sock *parent)
अणु
	काष्ठा sock *sk;

	BT_DBG("parent %p", parent);

	/* Close not yet accepted channels */
	जबतक ((sk = bt_accept_dequeue(parent, शून्य))) अणु
		sco_sock_बंद(sk);
		sco_sock_समाप्त(sk);
	पूर्ण

	parent->sk_state  = BT_CLOSED;
	sock_set_flag(parent, SOCK_ZAPPED);
पूर्ण

/* Kill socket (only अगर zapped and orphan)
 * Must be called on unlocked socket.
 */
अटल व्योम sco_sock_समाप्त(काष्ठा sock *sk)
अणु
	अगर (!sock_flag(sk, SOCK_ZAPPED) || sk->sk_socket ||
	    sock_flag(sk, SOCK_DEAD))
		वापस;

	BT_DBG("sk %p state %d", sk, sk->sk_state);

	/* Kill poor orphan */
	bt_sock_unlink(&sco_sk_list, sk);
	sock_set_flag(sk, SOCK_DEAD);
	sock_put(sk);
पूर्ण

अटल व्योम __sco_sock_बंद(काष्ठा sock *sk)
अणु
	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	चयन (sk->sk_state) अणु
	हाल BT_LISTEN:
		sco_sock_cleanup_listen(sk);
		अवरोध;

	हाल BT_CONNECTED:
	हाल BT_CONFIG:
		अगर (sco_pi(sk)->conn->hcon) अणु
			sk->sk_state = BT_DISCONN;
			sco_sock_set_समयr(sk, SCO_DISCONN_TIMEOUT);
			sco_conn_lock(sco_pi(sk)->conn);
			hci_conn_drop(sco_pi(sk)->conn->hcon);
			sco_pi(sk)->conn->hcon = शून्य;
			sco_conn_unlock(sco_pi(sk)->conn);
		पूर्ण अन्यथा
			sco_chan_del(sk, ECONNRESET);
		अवरोध;

	हाल BT_CONNECT2:
	हाल BT_CONNECT:
	हाल BT_DISCONN:
		sco_chan_del(sk, ECONNRESET);
		अवरोध;

	शेष:
		sock_set_flag(sk, SOCK_ZAPPED);
		अवरोध;
	पूर्ण
पूर्ण

/* Must be called on unlocked socket. */
अटल व्योम sco_sock_बंद(काष्ठा sock *sk)
अणु
	sco_sock_clear_समयr(sk);
	lock_sock(sk);
	__sco_sock_बंद(sk);
	release_sock(sk);
	sco_sock_समाप्त(sk);
पूर्ण

अटल व्योम sco_skb_put_cmsg(काष्ठा sk_buff *skb, काष्ठा msghdr *msg,
			     काष्ठा sock *sk)
अणु
	अगर (sco_pi(sk)->cmsg_mask & SCO_CMSG_PKT_STATUS)
		put_cmsg(msg, SOL_BLUETOOTH, BT_SCM_PKT_STATUS,
			 माप(bt_cb(skb)->sco.pkt_status),
			 &bt_cb(skb)->sco.pkt_status);
पूर्ण

अटल व्योम sco_sock_init(काष्ठा sock *sk, काष्ठा sock *parent)
अणु
	BT_DBG("sk %p", sk);

	अगर (parent) अणु
		sk->sk_type = parent->sk_type;
		bt_sk(sk)->flags = bt_sk(parent)->flags;
		security_sk_clone(parent, sk);
	पूर्ण अन्यथा अणु
		bt_sk(sk)->skb_put_cmsg = sco_skb_put_cmsg;
	पूर्ण
पूर्ण

अटल काष्ठा proto sco_proto = अणु
	.name		= "SCO",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा sco_pinfo)
पूर्ण;

अटल काष्ठा sock *sco_sock_alloc(काष्ठा net *net, काष्ठा socket *sock,
				   पूर्णांक proto, gfp_t prio, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &sco_proto, kern);
	अगर (!sk)
		वापस शून्य;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	sk->sk_deकाष्ठा = sco_sock_deकाष्ठा;
	sk->sk_sndसमयo = SCO_CONN_TIMEOUT;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state    = BT_OPEN;

	sco_pi(sk)->setting = BT_VOICE_CVSD_16BIT;

	समयr_setup(&sk->sk_समयr, sco_sock_समयout, 0);

	bt_sock_link(&sco_sk_list, sk);
	वापस sk;
पूर्ण

अटल पूर्णांक sco_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			   पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	अगर (sock->type != SOCK_SEQPACKET)
		वापस -ESOCKTNOSUPPORT;

	sock->ops = &sco_sock_ops;

	sk = sco_sock_alloc(net, sock, protocol, GFP_ATOMIC, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sco_sock_init(sk, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक sco_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			 पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_sco *sa = (काष्ठा sockaddr_sco *) addr;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	अगर (!addr || addr_len < माप(काष्ठा sockaddr_sco) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	BT_DBG("sk %p %pMR", sk, &sa->sco_bdaddr);

	lock_sock(sk);

	अगर (sk->sk_state != BT_OPEN) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	bacpy(&sco_pi(sk)->src, &sa->sco_bdaddr);

	sk->sk_state = BT_BOUND;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक alen, पूर्णांक flags)
अणु
	काष्ठा sockaddr_sco *sa = (काष्ठा sockaddr_sco *) addr;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	BT_DBG("sk %p", sk);

	अगर (alen < माप(काष्ठा sockaddr_sco) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	अगर (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND)
		वापस -EBADFD;

	अगर (sk->sk_type != SOCK_SEQPACKET)
		वापस -EINVAL;

	lock_sock(sk);

	/* Set destination address and psm */
	bacpy(&sco_pi(sk)->dst, &sa->sco_bdaddr);

	err = sco_connect(sk);
	अगर (err)
		जाओ करोne;

	err = bt_sock_रुको_state(sk, BT_CONNECTED,
				 sock_sndसमयo(sk, flags & O_NONBLOCK));

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	bdaddr_t *src = &sco_pi(sk)->src;
	पूर्णांक err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	अगर (sk->sk_state != BT_BOUND) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	ग_लिखो_lock(&sco_sk_list.lock);

	अगर (__sco_get_sock_listen_by_addr(src)) अणु
		err = -EADDRINUSE;
		जाओ unlock;
	पूर्ण

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;

	sk->sk_state = BT_LISTEN;

unlock:
	ग_लिखो_unlock(&sco_sk_list.lock);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			   पूर्णांक flags, bool kern)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा sock *sk = sock->sk, *ch;
	दीर्घ समयo;
	पूर्णांक err = 0;

	lock_sock(sk);

	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

	BT_DBG("sk %p timeo %ld", sk, समयo);

	/* Wait क्रम an incoming connection. (wake-one). */
	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (sk->sk_state != BT_LISTEN) अणु
			err = -EBADFD;
			अवरोध;
		पूर्ण

		ch = bt_accept_dequeue(sk, newsock);
		अगर (ch)
			अवरोध;

		अगर (!समयo) अणु
			err = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण

		release_sock(sk);

		समयo = रुको_woken(&रुको, TASK_INTERRUPTIBLE, समयo);
		lock_sock(sk);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (err)
		जाओ करोne;

	newsock->state = SS_CONNECTED;

	BT_DBG("new socket %p", ch);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			    पूर्णांक peer)
अणु
	काष्ठा sockaddr_sco *sa = (काष्ठा sockaddr_sco *) addr;
	काष्ठा sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	addr->sa_family = AF_BLUETOOTH;

	अगर (peer)
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->dst);
	अन्यथा
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->src);

	वापस माप(काष्ठा sockaddr_sco);
पूर्ण

अटल पूर्णांक sco_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	BT_DBG("sock %p, sk %p", sock, sk);

	err = sock_error(sk);
	अगर (err)
		वापस err;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	अगर (sk->sk_state == BT_CONNECTED)
		err = sco_send_frame(sk, msg, len);
	अन्यथा
		err = -ENOTCONN;

	release_sock(sk);
	वापस err;
पूर्ण

अटल व्योम sco_conn_defer_accept(काष्ठा hci_conn *conn, u16 setting)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p", conn);

	conn->state = BT_CONFIG;

	अगर (!lmp_esco_capable(hdev)) अणु
		काष्ठा hci_cp_accept_conn_req cp;

		bacpy(&cp.bdaddr, &conn->dst);
		cp.role = 0x00; /* Ignored */

		hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_REQ, माप(cp), &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_accept_sync_conn_req cp;

		bacpy(&cp.bdaddr, &conn->dst);
		cp.pkt_type = cpu_to_le16(conn->pkt_type);

		cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
		cp.content_क्रमmat = cpu_to_le16(setting);

		चयन (setting & SCO_AIRMODE_MASK) अणु
		हाल SCO_AIRMODE_TRANSP:
			अगर (conn->pkt_type & ESCO_2EV3)
				cp.max_latency = cpu_to_le16(0x0008);
			अन्यथा
				cp.max_latency = cpu_to_le16(0x000D);
			cp.retrans_efक्रमt = 0x02;
			अवरोध;
		हाल SCO_AIRMODE_CVSD:
			cp.max_latency = cpu_to_le16(0xffff);
			cp.retrans_efक्रमt = 0xff;
			अवरोध;
		पूर्ण

		hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_REQ,
			     माप(cp), &cp);
	पूर्ण
पूर्ण

अटल पूर्णांक sco_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sco_pinfo *pi = sco_pi(sk);

	lock_sock(sk);

	अगर (sk->sk_state == BT_CONNECT2 &&
	    test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags)) अणु
		sco_conn_defer_accept(pi->conn->hcon, pi->setting);
		sk->sk_state = BT_CONFIG;

		release_sock(sk);
		वापस 0;
	पूर्ण

	release_sock(sk);

	वापस bt_sock_recvmsg(sock, msg, len, flags);
पूर्ण

अटल पूर्णांक sco_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक len, err = 0;
	काष्ठा bt_voice voice;
	u32 opt;

	BT_DBG("sk %p", sk);

	lock_sock(sk);

	चयन (optname) अणु

	हाल BT_DEFER_SETUP:
		अगर (sk->sk_state != BT_BOUND && sk->sk_state != BT_LISTEN) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt)
			set_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags);
		अन्यथा
			clear_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags);
		अवरोध;

	हाल BT_VOICE:
		अगर (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND &&
		    sk->sk_state != BT_CONNECT2) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		voice.setting = sco_pi(sk)->setting;

		len = min_t(अचिन्हित पूर्णांक, माप(voice), optlen);
		अगर (copy_from_sockptr(&voice, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		/* Explicitly check क्रम these values */
		अगर (voice.setting != BT_VOICE_TRANSPARENT &&
		    voice.setting != BT_VOICE_CVSD_16BIT) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		sco_pi(sk)->setting = voice.setting;
		अवरोध;

	हाल BT_PKT_STATUS:
		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt)
			sco_pi(sk)->cmsg_mask |= SCO_CMSG_PKT_STATUS;
		अन्यथा
			sco_pi(sk)->cmsg_mask &= SCO_CMSG_PKT_STATUS;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_माला_लोockopt_old(काष्ठा socket *sock, पूर्णांक optname,
				   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sco_options opts;
	काष्ठा sco_conninfo cinfo;
	पूर्णांक len, err = 0;

	BT_DBG("sk %p", sk);

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल SCO_OPTIONS:
		अगर (sk->sk_state != BT_CONNECTED &&
		    !(sk->sk_state == BT_CONNECT2 &&
		      test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags))) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		opts.mtu = sco_pi(sk)->conn->mtu;

		BT_DBG("mtu %d", opts.mtu);

		len = min_t(अचिन्हित पूर्णांक, len, माप(opts));
		अगर (copy_to_user(optval, (अक्षर *)&opts, len))
			err = -EFAULT;

		अवरोध;

	हाल SCO_CONNINFO:
		अगर (sk->sk_state != BT_CONNECTED &&
		    !(sk->sk_state == BT_CONNECT2 &&
		      test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags))) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		स_रखो(&cinfo, 0, माप(cinfo));
		cinfo.hci_handle = sco_pi(sk)->conn->hcon->handle;
		स_नकल(cinfo.dev_class, sco_pi(sk)->conn->hcon->dev_class, 3);

		len = min_t(अचिन्हित पूर्णांक, len, माप(cinfo));
		अगर (copy_to_user(optval, (अक्षर *)&cinfo, len))
			err = -EFAULT;

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक len, err = 0;
	काष्ठा bt_voice voice;
	u32 phys;
	पूर्णांक pkt_status;

	BT_DBG("sk %p", sk);

	अगर (level == SOL_SCO)
		वापस sco_sock_माला_लोockopt_old(sock, optname, optval, optlen);

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु

	हाल BT_DEFER_SETUP:
		अगर (sk->sk_state != BT_BOUND && sk->sk_state != BT_LISTEN) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (put_user(test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags),
			     (u32 __user *)optval))
			err = -EFAULT;

		अवरोध;

	हाल BT_VOICE:
		voice.setting = sco_pi(sk)->setting;

		len = min_t(अचिन्हित पूर्णांक, len, माप(voice));
		अगर (copy_to_user(optval, (अक्षर *)&voice, len))
			err = -EFAULT;

		अवरोध;

	हाल BT_PHY:
		अगर (sk->sk_state != BT_CONNECTED) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		phys = hci_conn_get_phy(sco_pi(sk)->conn->hcon);

		अगर (put_user(phys, (u32 __user *) optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_PKT_STATUS:
		pkt_status = (sco_pi(sk)->cmsg_mask & SCO_CMSG_PKT_STATUS);

		अगर (put_user(pkt_status, (पूर्णांक __user *)optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_SNDMTU:
	हाल BT_RCVMTU:
		अगर (sk->sk_state != BT_CONNECTED) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		अगर (put_user(sco_pi(sk)->conn->mtu, (u32 __user *)optval))
			err = -EFAULT;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	sock_hold(sk);
	lock_sock(sk);

	अगर (!sk->sk_shutकरोwn) अणु
		sk->sk_shutकरोwn = SHUTDOWN_MASK;
		sco_sock_clear_समयr(sk);
		__sco_sock_बंद(sk);

		अगर (sock_flag(sk, SOCK_LINGER) && sk->sk_lingerसमय &&
		    !(current->flags & PF_EXITING))
			err = bt_sock_रुको_state(sk, BT_CLOSED,
						 sk->sk_lingerसमय);
	पूर्ण

	release_sock(sk);
	sock_put(sk);

	वापस err;
पूर्ण

अटल पूर्णांक sco_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	sco_sock_बंद(sk);

	अगर (sock_flag(sk, SOCK_LINGER) && sk->sk_lingerसमय &&
	    !(current->flags & PF_EXITING)) अणु
		lock_sock(sk);
		err = bt_sock_रुको_state(sk, BT_CLOSED, sk->sk_lingerसमय);
		release_sock(sk);
	पूर्ण

	sock_orphan(sk);
	sco_sock_समाप्त(sk);
	वापस err;
पूर्ण

अटल व्योम sco_conn_पढ़ोy(काष्ठा sco_conn *conn)
अणु
	काष्ठा sock *parent;
	काष्ठा sock *sk = conn->sk;

	BT_DBG("conn %p", conn);

	अगर (sk) अणु
		sco_sock_clear_समयr(sk);
		bh_lock_sock(sk);
		sk->sk_state = BT_CONNECTED;
		sk->sk_state_change(sk);
		bh_unlock_sock(sk);
	पूर्ण अन्यथा अणु
		sco_conn_lock(conn);

		अगर (!conn->hcon) अणु
			sco_conn_unlock(conn);
			वापस;
		पूर्ण

		parent = sco_get_sock_listen(&conn->hcon->src);
		अगर (!parent) अणु
			sco_conn_unlock(conn);
			वापस;
		पूर्ण

		bh_lock_sock(parent);

		sk = sco_sock_alloc(sock_net(parent), शून्य,
				    BTPROTO_SCO, GFP_ATOMIC, 0);
		अगर (!sk) अणु
			bh_unlock_sock(parent);
			sco_conn_unlock(conn);
			वापस;
		पूर्ण

		sco_sock_init(sk, parent);

		bacpy(&sco_pi(sk)->src, &conn->hcon->src);
		bacpy(&sco_pi(sk)->dst, &conn->hcon->dst);

		hci_conn_hold(conn->hcon);
		__sco_chan_add(conn, sk, parent);

		अगर (test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags))
			sk->sk_state = BT_CONNECT2;
		अन्यथा
			sk->sk_state = BT_CONNECTED;

		/* Wake up parent */
		parent->sk_data_पढ़ोy(parent);

		bh_unlock_sock(parent);

		sco_conn_unlock(conn);
	पूर्ण
पूर्ण

/* ----- SCO पूर्णांकerface with lower layer (HCI) ----- */
पूर्णांक sco_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, __u8 *flags)
अणु
	काष्ठा sock *sk;
	पूर्णांक lm = 0;

	BT_DBG("hdev %s, bdaddr %pMR", hdev->name, bdaddr);

	/* Find listening sockets */
	पढ़ो_lock(&sco_sk_list.lock);
	sk_क्रम_each(sk, &sco_sk_list.head) अणु
		अगर (sk->sk_state != BT_LISTEN)
			जारी;

		अगर (!bacmp(&sco_pi(sk)->src, &hdev->bdaddr) ||
		    !bacmp(&sco_pi(sk)->src, BDADDR_ANY)) अणु
			lm |= HCI_LM_ACCEPT;

			अगर (test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags))
				*flags |= HCI_PROTO_DEFER;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&sco_sk_list.lock);

	वापस lm;
पूर्ण

अटल व्योम sco_connect_cfm(काष्ठा hci_conn *hcon, __u8 status)
अणु
	अगर (hcon->type != SCO_LINK && hcon->type != ESCO_LINK)
		वापस;

	BT_DBG("hcon %p bdaddr %pMR status %d", hcon, &hcon->dst, status);

	अगर (!status) अणु
		काष्ठा sco_conn *conn;

		conn = sco_conn_add(hcon);
		अगर (conn)
			sco_conn_पढ़ोy(conn);
	पूर्ण अन्यथा
		sco_conn_del(hcon, bt_to_त्रुटि_सं(status));
पूर्ण

अटल व्योम sco_disconn_cfm(काष्ठा hci_conn *hcon, __u8 reason)
अणु
	अगर (hcon->type != SCO_LINK && hcon->type != ESCO_LINK)
		वापस;

	BT_DBG("hcon %p reason %d", hcon, reason);

	sco_conn_del(hcon, bt_to_त्रुटि_सं(reason));
पूर्ण

व्योम sco_recv_scodata(काष्ठा hci_conn *hcon, काष्ठा sk_buff *skb)
अणु
	काष्ठा sco_conn *conn = hcon->sco_data;

	अगर (!conn)
		जाओ drop;

	BT_DBG("conn %p len %d", conn, skb->len);

	अगर (skb->len) अणु
		sco_recv_frame(conn, skb);
		वापस;
	पूर्ण

drop:
	kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा hci_cb sco_cb = अणु
	.name		= "SCO",
	.connect_cfm	= sco_connect_cfm,
	.disconn_cfm	= sco_disconn_cfm,
पूर्ण;

अटल पूर्णांक sco_debugfs_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा sock *sk;

	पढ़ो_lock(&sco_sk_list.lock);

	sk_क्रम_each(sk, &sco_sk_list.head) अणु
		seq_म_लिखो(f, "%pMR %pMR %d\n", &sco_pi(sk)->src,
			   &sco_pi(sk)->dst, sk->sk_state);
	पूर्ण

	पढ़ो_unlock(&sco_sk_list.lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(sco_debugfs);

अटल काष्ठा dentry *sco_debugfs;

अटल स्थिर काष्ठा proto_ops sco_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= sco_sock_release,
	.bind		= sco_sock_bind,
	.connect	= sco_sock_connect,
	.listen		= sco_sock_listen,
	.accept		= sco_sock_accept,
	.getname	= sco_sock_getname,
	.sendmsg	= sco_sock_sendmsg,
	.recvmsg	= sco_sock_recvmsg,
	.poll		= bt_sock_poll,
	.ioctl		= bt_sock_ioctl,
	.gettstamp	= sock_gettstamp,
	.mmap		= sock_no_mmap,
	.socketpair	= sock_no_socketpair,
	.shutकरोwn	= sco_sock_shutकरोwn,
	.setsockopt	= sco_sock_setsockopt,
	.माला_लोockopt	= sco_sock_माला_लोockopt
पूर्ण;

अटल स्थिर काष्ठा net_proto_family sco_sock_family_ops = अणु
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= sco_sock_create,
पूर्ण;

पूर्णांक __init sco_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा sockaddr_sco) > माप(काष्ठा sockaddr));

	err = proto_रेजिस्टर(&sco_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_SCO, &sco_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("SCO socket registration failed");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "sco", &sco_sk_list, शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create SCO proc file");
		bt_sock_unरेजिस्टर(BTPROTO_SCO);
		जाओ error;
	पूर्ण

	BT_INFO("SCO socket layer initialized");

	hci_रेजिस्टर_cb(&sco_cb);

	अगर (IS_ERR_OR_शून्य(bt_debugfs))
		वापस 0;

	sco_debugfs = debugfs_create_file("sco", 0444, bt_debugfs,
					  शून्य, &sco_debugfs_fops);

	वापस 0;

error:
	proto_unरेजिस्टर(&sco_proto);
	वापस err;
पूर्ण

व्योम sco_निकास(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "sco");

	debugfs_हटाओ(sco_debugfs);

	hci_unरेजिस्टर_cb(&sco_cb);

	bt_sock_unरेजिस्टर(BTPROTO_SCO);

	proto_unरेजिस्टर(&sco_proto);
पूर्ण

module_param(disable_esco, bool, 0644);
MODULE_PARM_DESC(disable_esco, "Disable eSCO connection creation");
