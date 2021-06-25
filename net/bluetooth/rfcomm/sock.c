<शैली गुरु>
/*
   RFCOMM implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>
   Copyright (C) 2002 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

/*
 * RFCOMM sockets.
 */
#समावेश <linux/compat.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/rfcomm.h>

अटल स्थिर काष्ठा proto_ops rfcomm_sock_ops;

अटल काष्ठा bt_sock_list rfcomm_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(rfcomm_sk_list.lock)
पूर्ण;

अटल व्योम rfcomm_sock_बंद(काष्ठा sock *sk);
अटल व्योम rfcomm_sock_समाप्त(काष्ठा sock *sk);

/* ---- DLC callbacks ----
 *
 * called under rfcomm_dlc_lock()
 */
अटल व्योम rfcomm_sk_data_पढ़ोy(काष्ठा rfcomm_dlc *d, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = d->owner;
	अगर (!sk)
		वापस;

	atomic_add(skb->len, &sk->sk_rmem_alloc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		rfcomm_dlc_throttle(d);
पूर्ण

अटल व्योम rfcomm_sk_state_change(काष्ठा rfcomm_dlc *d, पूर्णांक err)
अणु
	काष्ठा sock *sk = d->owner, *parent;

	अगर (!sk)
		वापस;

	BT_DBG("dlc %p state %ld err %d", d, d->state, err);

	spin_lock_bh(&sk->sk_lock.slock);

	अगर (err)
		sk->sk_err = err;

	sk->sk_state = d->state;

	parent = bt_sk(sk)->parent;
	अगर (parent) अणु
		अगर (d->state == BT_CLOSED) अणु
			sock_set_flag(sk, SOCK_ZAPPED);
			bt_accept_unlink(sk);
		पूर्ण
		parent->sk_data_पढ़ोy(parent);
	पूर्ण अन्यथा अणु
		अगर (d->state == BT_CONNECTED)
			rfcomm_session_getaddr(d->session,
					       &rfcomm_pi(sk)->src, शून्य);
		sk->sk_state_change(sk);
	पूर्ण

	spin_unlock_bh(&sk->sk_lock.slock);

	अगर (parent && sock_flag(sk, SOCK_ZAPPED)) अणु
		/* We have to drop DLC lock here, otherwise
		 * rfcomm_sock_deकाष्ठा() will dead lock. */
		rfcomm_dlc_unlock(d);
		rfcomm_sock_समाप्त(sk);
		rfcomm_dlc_lock(d);
	पूर्ण
पूर्ण

/* ---- Socket functions ---- */
अटल काष्ठा sock *__rfcomm_get_listen_sock_by_addr(u8 channel, bdaddr_t *src)
अणु
	काष्ठा sock *sk = शून्य;

	sk_क्रम_each(sk, &rfcomm_sk_list.head) अणु
		अगर (rfcomm_pi(sk)->channel != channel)
			जारी;

		अगर (bacmp(&rfcomm_pi(sk)->src, src))
			जारी;

		अगर (sk->sk_state == BT_BOUND || sk->sk_state == BT_LISTEN)
			अवरोध;
	पूर्ण

	वापस sk ? sk : शून्य;
पूर्ण

/* Find socket with channel and source bdaddr.
 * Returns बंदst match.
 */
अटल काष्ठा sock *rfcomm_get_sock_by_channel(पूर्णांक state, u8 channel, bdaddr_t *src)
अणु
	काष्ठा sock *sk = शून्य, *sk1 = शून्य;

	पढ़ो_lock(&rfcomm_sk_list.lock);

	sk_क्रम_each(sk, &rfcomm_sk_list.head) अणु
		अगर (state && sk->sk_state != state)
			जारी;

		अगर (rfcomm_pi(sk)->channel == channel) अणु
			/* Exact match. */
			अगर (!bacmp(&rfcomm_pi(sk)->src, src))
				अवरोध;

			/* Closest match */
			अगर (!bacmp(&rfcomm_pi(sk)->src, BDADDR_ANY))
				sk1 = sk;
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&rfcomm_sk_list.lock);

	वापस sk ? sk : sk1;
पूर्ण

अटल व्योम rfcomm_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा rfcomm_dlc *d = rfcomm_pi(sk)->dlc;

	BT_DBG("sk %p dlc %p", sk, d);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);

	rfcomm_dlc_lock(d);
	rfcomm_pi(sk)->dlc = शून्य;

	/* Detach DLC अगर it's owned by this socket */
	अगर (d->owner == sk)
		d->owner = शून्य;
	rfcomm_dlc_unlock(d);

	rfcomm_dlc_put(d);
पूर्ण

अटल व्योम rfcomm_sock_cleanup_listen(काष्ठा sock *parent)
अणु
	काष्ठा sock *sk;

	BT_DBG("parent %p", parent);

	/* Close not yet accepted dlcs */
	जबतक ((sk = bt_accept_dequeue(parent, शून्य))) अणु
		rfcomm_sock_बंद(sk);
		rfcomm_sock_समाप्त(sk);
	पूर्ण

	parent->sk_state  = BT_CLOSED;
	sock_set_flag(parent, SOCK_ZAPPED);
पूर्ण

/* Kill socket (only अगर zapped and orphan)
 * Must be called on unlocked socket.
 */
अटल व्योम rfcomm_sock_समाप्त(काष्ठा sock *sk)
अणु
	अगर (!sock_flag(sk, SOCK_ZAPPED) || sk->sk_socket)
		वापस;

	BT_DBG("sk %p state %d refcnt %d", sk, sk->sk_state, refcount_पढ़ो(&sk->sk_refcnt));

	/* Kill poor orphan */
	bt_sock_unlink(&rfcomm_sk_list, sk);
	sock_set_flag(sk, SOCK_DEAD);
	sock_put(sk);
पूर्ण

अटल व्योम __rfcomm_sock_बंद(काष्ठा sock *sk)
अणु
	काष्ठा rfcomm_dlc *d = rfcomm_pi(sk)->dlc;

	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	चयन (sk->sk_state) अणु
	हाल BT_LISTEN:
		rfcomm_sock_cleanup_listen(sk);
		अवरोध;

	हाल BT_CONNECT:
	हाल BT_CONNECT2:
	हाल BT_CONFIG:
	हाल BT_CONNECTED:
		rfcomm_dlc_बंद(d, 0);
		fallthrough;

	शेष:
		sock_set_flag(sk, SOCK_ZAPPED);
		अवरोध;
	पूर्ण
पूर्ण

/* Close socket.
 * Must be called on unlocked socket.
 */
अटल व्योम rfcomm_sock_बंद(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	__rfcomm_sock_बंद(sk);
	release_sock(sk);
पूर्ण

अटल व्योम rfcomm_sock_init(काष्ठा sock *sk, काष्ठा sock *parent)
अणु
	काष्ठा rfcomm_pinfo *pi = rfcomm_pi(sk);

	BT_DBG("sk %p", sk);

	अगर (parent) अणु
		sk->sk_type = parent->sk_type;
		pi->dlc->defer_setup = test_bit(BT_SK_DEFER_SETUP,
						&bt_sk(parent)->flags);

		pi->sec_level = rfcomm_pi(parent)->sec_level;
		pi->role_चयन = rfcomm_pi(parent)->role_चयन;

		security_sk_clone(parent, sk);
	पूर्ण अन्यथा अणु
		pi->dlc->defer_setup = 0;

		pi->sec_level = BT_SECURITY_LOW;
		pi->role_चयन = 0;
	पूर्ण

	pi->dlc->sec_level = pi->sec_level;
	pi->dlc->role_चयन = pi->role_चयन;
पूर्ण

अटल काष्ठा proto rfcomm_proto = अणु
	.name		= "RFCOMM",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा rfcomm_pinfo)
पूर्ण;

अटल काष्ठा sock *rfcomm_sock_alloc(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक proto, gfp_t prio, पूर्णांक kern)
अणु
	काष्ठा rfcomm_dlc *d;
	काष्ठा sock *sk;

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &rfcomm_proto, kern);
	अगर (!sk)
		वापस शून्य;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	d = rfcomm_dlc_alloc(prio);
	अगर (!d) अणु
		sk_मुक्त(sk);
		वापस शून्य;
	पूर्ण

	d->data_पढ़ोy   = rfcomm_sk_data_पढ़ोy;
	d->state_change = rfcomm_sk_state_change;

	rfcomm_pi(sk)->dlc = d;
	d->owner = sk;

	sk->sk_deकाष्ठा = rfcomm_sock_deकाष्ठा;
	sk->sk_sndसमयo = RFCOMM_CONN_TIMEOUT;

	sk->sk_sndbuf = RFCOMM_MAX_CREDITS * RFCOMM_DEFAULT_MTU * 10;
	sk->sk_rcvbuf = RFCOMM_MAX_CREDITS * RFCOMM_DEFAULT_MTU * 10;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state    = BT_OPEN;

	bt_sock_link(&rfcomm_sk_list, sk);

	BT_DBG("sk %p", sk);
	वापस sk;
पूर्ण

अटल पूर्णांक rfcomm_sock_create(काष्ठा net *net, काष्ठा socket *sock,
			      पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	अगर (sock->type != SOCK_STREAM && sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	sock->ops = &rfcomm_sock_ops;

	sk = rfcomm_sock_alloc(net, sock, protocol, GFP_ATOMIC, kern);
	अगर (!sk)
		वापस -ENOMEM;

	rfcomm_sock_init(sk, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक rfcomm_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_rc sa;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक len, err = 0;

	अगर (!addr || addr_len < दुरत्वend(काष्ठा sockaddr, sa_family) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	स_रखो(&sa, 0, माप(sa));
	len = min_t(अचिन्हित पूर्णांक, माप(sa), addr_len);
	स_नकल(&sa, addr, len);

	BT_DBG("sk %p %pMR", sk, &sa.rc_bdaddr);

	lock_sock(sk);

	अगर (sk->sk_state != BT_OPEN) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_STREAM) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	ग_लिखो_lock(&rfcomm_sk_list.lock);

	अगर (sa.rc_channel &&
	    __rfcomm_get_listen_sock_by_addr(sa.rc_channel, &sa.rc_bdaddr)) अणु
		err = -EADDRINUSE;
	पूर्ण अन्यथा अणु
		/* Save source address */
		bacpy(&rfcomm_pi(sk)->src, &sa.rc_bdaddr);
		rfcomm_pi(sk)->channel = sa.rc_channel;
		sk->sk_state = BT_BOUND;
	पूर्ण

	ग_लिखो_unlock(&rfcomm_sk_list.lock);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक alen, पूर्णांक flags)
अणु
	काष्ठा sockaddr_rc *sa = (काष्ठा sockaddr_rc *) addr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा rfcomm_dlc *d = rfcomm_pi(sk)->dlc;
	पूर्णांक err = 0;

	BT_DBG("sk %p", sk);

	अगर (alen < माप(काष्ठा sockaddr_rc) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (sk->sk_state != BT_OPEN && sk->sk_state != BT_BOUND) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_STREAM) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	sk->sk_state = BT_CONNECT;
	bacpy(&rfcomm_pi(sk)->dst, &sa->rc_bdaddr);
	rfcomm_pi(sk)->channel = sa->rc_channel;

	d->sec_level = rfcomm_pi(sk)->sec_level;
	d->role_चयन = rfcomm_pi(sk)->role_चयन;

	err = rfcomm_dlc_खोलो(d, &rfcomm_pi(sk)->src, &sa->rc_bdaddr,
			      sa->rc_channel);
	अगर (!err)
		err = bt_sock_रुको_state(sk, BT_CONNECTED,
				sock_sndसमयo(sk, flags & O_NONBLOCK));

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	अगर (sk->sk_state != BT_BOUND) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_STREAM) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (!rfcomm_pi(sk)->channel) अणु
		bdaddr_t *src = &rfcomm_pi(sk)->src;
		u8 channel;

		err = -EINVAL;

		ग_लिखो_lock(&rfcomm_sk_list.lock);

		क्रम (channel = 1; channel < 31; channel++)
			अगर (!__rfcomm_get_listen_sock_by_addr(channel, src)) अणु
				rfcomm_pi(sk)->channel = channel;
				err = 0;
				अवरोध;
			पूर्ण

		ग_लिखो_unlock(&rfcomm_sk_list.lock);

		अगर (err < 0)
			जाओ करोne;
	पूर्ण

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
	sk->sk_state = BT_LISTEN;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
			      bool kern)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा sock *sk = sock->sk, *nsk;
	दीर्घ समयo;
	पूर्णांक err = 0;

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	अगर (sk->sk_type != SOCK_STREAM) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

	BT_DBG("sk %p timeo %ld", sk, समयo);

	/* Wait क्रम an incoming connection. (wake-one). */
	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (sk->sk_state != BT_LISTEN) अणु
			err = -EBADFD;
			अवरोध;
		पूर्ण

		nsk = bt_accept_dequeue(sk, newsock);
		अगर (nsk)
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

		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (err)
		जाओ करोne;

	newsock->state = SS_CONNECTED;

	BT_DBG("new socket %p", nsk);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक peer)
अणु
	काष्ठा sockaddr_rc *sa = (काष्ठा sockaddr_rc *) addr;
	काष्ठा sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (peer && sk->sk_state != BT_CONNECTED &&
	    sk->sk_state != BT_CONNECT && sk->sk_state != BT_CONNECT2)
		वापस -ENOTCONN;

	स_रखो(sa, 0, माप(*sa));
	sa->rc_family  = AF_BLUETOOTH;
	sa->rc_channel = rfcomm_pi(sk)->channel;
	अगर (peer)
		bacpy(&sa->rc_bdaddr, &rfcomm_pi(sk)->dst);
	अन्यथा
		bacpy(&sa->rc_bdaddr, &rfcomm_pi(sk)->src);

	वापस माप(काष्ठा sockaddr_rc);
पूर्ण

अटल पूर्णांक rfcomm_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rfcomm_dlc *d = rfcomm_pi(sk)->dlc;
	काष्ठा sk_buff *skb;
	पूर्णांक sent;

	अगर (test_bit(RFCOMM_DEFER_SETUP, &d->flags))
		वापस -ENOTCONN;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN)
		वापस -EPIPE;

	BT_DBG("sock %p, sk %p", sock, sk);

	lock_sock(sk);

	sent = bt_sock_रुको_पढ़ोy(sk, msg->msg_flags);
	अगर (sent)
		जाओ करोne;

	जबतक (len) अणु
		माप_प्रकार size = min_t(माप_प्रकार, len, d->mtu);
		पूर्णांक err;

		skb = sock_alloc_send_skb(sk, size + RFCOMM_SKB_RESERVE,
				msg->msg_flags & MSG_DONTWAIT, &err);
		अगर (!skb) अणु
			अगर (sent == 0)
				sent = err;
			अवरोध;
		पूर्ण
		skb_reserve(skb, RFCOMM_SKB_HEAD_RESERVE);

		err = स_नकल_from_msg(skb_put(skb, size), msg, size);
		अगर (err) अणु
			kमुक्त_skb(skb);
			अगर (sent == 0)
				sent = err;
			अवरोध;
		पूर्ण

		skb->priority = sk->sk_priority;

		err = rfcomm_dlc_send(d, skb);
		अगर (err < 0) अणु
			kमुक्त_skb(skb);
			अगर (sent == 0)
				sent = err;
			अवरोध;
		पूर्ण

		sent += size;
		len  -= size;
	पूर्ण

करोne:
	release_sock(sk);

	वापस sent;
पूर्ण

अटल पूर्णांक rfcomm_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rfcomm_dlc *d = rfcomm_pi(sk)->dlc;
	पूर्णांक len;

	अगर (test_and_clear_bit(RFCOMM_DEFER_SETUP, &d->flags)) अणु
		rfcomm_dlc_accept(d);
		वापस 0;
	पूर्ण

	len = bt_sock_stream_recvmsg(sock, msg, size, flags);

	lock_sock(sk);
	अगर (!(flags & MSG_PEEK) && len > 0)
		atomic_sub(len, &sk->sk_rmem_alloc);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= (sk->sk_rcvbuf >> 2))
		rfcomm_dlc_unthrottle(rfcomm_pi(sk)->dlc);
	release_sock(sk);

	वापस len;
पूर्ण

अटल पूर्णांक rfcomm_sock_setsockopt_old(काष्ठा socket *sock, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	lock_sock(sk);

	चयन (optname) अणु
	हाल RFCOMM_LM:
		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt & RFCOMM_LM_FIPS) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (opt & RFCOMM_LM_AUTH)
			rfcomm_pi(sk)->sec_level = BT_SECURITY_LOW;
		अगर (opt & RFCOMM_LM_ENCRYPT)
			rfcomm_pi(sk)->sec_level = BT_SECURITY_MEDIUM;
		अगर (opt & RFCOMM_LM_SECURE)
			rfcomm_pi(sk)->sec_level = BT_SECURITY_HIGH;

		rfcomm_pi(sk)->role_चयन = (opt & RFCOMM_LM_MASTER);
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा bt_security sec;
	पूर्णांक err = 0;
	माप_प्रकार len;
	u32 opt;

	BT_DBG("sk %p", sk);

	अगर (level == SOL_RFCOMM)
		वापस rfcomm_sock_setsockopt_old(sock, optname, optval, optlen);

	अगर (level != SOL_BLUETOOTH)
		वापस -ENOPROTOOPT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल BT_SECURITY:
		अगर (sk->sk_type != SOCK_STREAM) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		sec.level = BT_SECURITY_LOW;

		len = min_t(अचिन्हित पूर्णांक, माप(sec), optlen);
		अगर (copy_from_sockptr(&sec, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (sec.level > BT_SECURITY_HIGH) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		rfcomm_pi(sk)->sec_level = sec.level;
		अवरोध;

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

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_माला_लोockopt_old(काष्ठा socket *sock, पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *l2cap_sk;
	काष्ठा l2cap_conn *conn;
	काष्ठा rfcomm_conninfo cinfo;
	पूर्णांक len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल RFCOMM_LM:
		चयन (rfcomm_pi(sk)->sec_level) अणु
		हाल BT_SECURITY_LOW:
			opt = RFCOMM_LM_AUTH;
			अवरोध;
		हाल BT_SECURITY_MEDIUM:
			opt = RFCOMM_LM_AUTH | RFCOMM_LM_ENCRYPT;
			अवरोध;
		हाल BT_SECURITY_HIGH:
			opt = RFCOMM_LM_AUTH | RFCOMM_LM_ENCRYPT |
			      RFCOMM_LM_SECURE;
			अवरोध;
		हाल BT_SECURITY_FIPS:
			opt = RFCOMM_LM_AUTH | RFCOMM_LM_ENCRYPT |
			      RFCOMM_LM_SECURE | RFCOMM_LM_FIPS;
			अवरोध;
		शेष:
			opt = 0;
			अवरोध;
		पूर्ण

		अगर (rfcomm_pi(sk)->role_चयन)
			opt |= RFCOMM_LM_MASTER;

		अगर (put_user(opt, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल RFCOMM_CONNINFO:
		अगर (sk->sk_state != BT_CONNECTED &&
					!rfcomm_pi(sk)->dlc->defer_setup) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		l2cap_sk = rfcomm_pi(sk)->dlc->session->sock->sk;
		conn = l2cap_pi(l2cap_sk)->chan->conn;

		स_रखो(&cinfo, 0, माप(cinfo));
		cinfo.hci_handle = conn->hcon->handle;
		स_नकल(cinfo.dev_class, conn->hcon->dev_class, 3);

		len = min_t(अचिन्हित पूर्णांक, len, माप(cinfo));
		अगर (copy_to_user(optval, (अक्षर *) &cinfo, len))
			err = -EFAULT;

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा bt_security sec;
	पूर्णांक len, err = 0;

	BT_DBG("sk %p", sk);

	अगर (level == SOL_RFCOMM)
		वापस rfcomm_sock_माला_लोockopt_old(sock, optname, optval, optlen);

	अगर (level != SOL_BLUETOOTH)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल BT_SECURITY:
		अगर (sk->sk_type != SOCK_STREAM) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		sec.level = rfcomm_pi(sk)->sec_level;
		sec.key_size = 0;

		len = min_t(अचिन्हित पूर्णांक, len, माप(sec));
		अगर (copy_to_user(optval, (अक्षर *) &sec, len))
			err = -EFAULT;

		अवरोध;

	हाल BT_DEFER_SETUP:
		अगर (sk->sk_state != BT_BOUND && sk->sk_state != BT_LISTEN) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (put_user(test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags),
			     (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk __maybe_unused = sock->sk;
	पूर्णांक err;

	BT_DBG("sk %p cmd %x arg %lx", sk, cmd, arg);

	err = bt_sock_ioctl(sock, cmd, arg);

	अगर (err == -ENOIOCTLCMD) अणु
#अगर_घोषित CONFIG_BT_RFCOMM_TTY
		lock_sock(sk);
		err = rfcomm_dev_ioctl(sk, cmd, (व्योम __user *) arg);
		release_sock(sk);
#अन्यथा
		err = -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक rfcomm_sock_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस rfcomm_sock_ioctl(sock, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rfcomm_sock_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	lock_sock(sk);
	अगर (!sk->sk_shutकरोwn) अणु
		sk->sk_shutकरोwn = SHUTDOWN_MASK;
		__rfcomm_sock_बंद(sk);

		अगर (sock_flag(sk, SOCK_LINGER) && sk->sk_lingerसमय &&
		    !(current->flags & PF_EXITING))
			err = bt_sock_रुको_state(sk, BT_CLOSED, sk->sk_lingerसमय);
	पूर्ण
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक rfcomm_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	err = rfcomm_sock_shutकरोwn(sock, 2);

	sock_orphan(sk);
	rfcomm_sock_समाप्त(sk);
	वापस err;
पूर्ण

/* ---- RFCOMM core layer callbacks ----
 *
 * called under rfcomm_lock()
 */
पूर्णांक rfcomm_connect_ind(काष्ठा rfcomm_session *s, u8 channel, काष्ठा rfcomm_dlc **d)
अणु
	काष्ठा sock *sk, *parent;
	bdaddr_t src, dst;
	पूर्णांक result = 0;

	BT_DBG("session %p channel %d", s, channel);

	rfcomm_session_getaddr(s, &src, &dst);

	/* Check अगर we have socket listening on channel */
	parent = rfcomm_get_sock_by_channel(BT_LISTEN, channel, &src);
	अगर (!parent)
		वापस 0;

	bh_lock_sock(parent);

	/* Check क्रम backlog size */
	अगर (sk_acceptq_is_full(parent)) अणु
		BT_DBG("backlog full %d", parent->sk_ack_backlog);
		जाओ करोne;
	पूर्ण

	sk = rfcomm_sock_alloc(sock_net(parent), शून्य, BTPROTO_RFCOMM, GFP_ATOMIC, 0);
	अगर (!sk)
		जाओ करोne;

	bt_sock_reclassअगरy_lock(sk, BTPROTO_RFCOMM);

	rfcomm_sock_init(sk, parent);
	bacpy(&rfcomm_pi(sk)->src, &src);
	bacpy(&rfcomm_pi(sk)->dst, &dst);
	rfcomm_pi(sk)->channel = channel;

	sk->sk_state = BT_CONFIG;
	bt_accept_enqueue(parent, sk, true);

	/* Accept connection and वापस socket DLC */
	*d = rfcomm_pi(sk)->dlc;
	result = 1;

करोne:
	bh_unlock_sock(parent);

	अगर (test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags))
		parent->sk_state_change(parent);

	वापस result;
पूर्ण

अटल पूर्णांक rfcomm_sock_debugfs_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा sock *sk;

	पढ़ो_lock(&rfcomm_sk_list.lock);

	sk_क्रम_each(sk, &rfcomm_sk_list.head) अणु
		seq_म_लिखो(f, "%pMR %pMR %d %d\n",
			   &rfcomm_pi(sk)->src, &rfcomm_pi(sk)->dst,
			   sk->sk_state, rfcomm_pi(sk)->channel);
	पूर्ण

	पढ़ो_unlock(&rfcomm_sk_list.lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rfcomm_sock_debugfs);

अटल काष्ठा dentry *rfcomm_sock_debugfs;

अटल स्थिर काष्ठा proto_ops rfcomm_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= rfcomm_sock_release,
	.bind		= rfcomm_sock_bind,
	.connect	= rfcomm_sock_connect,
	.listen		= rfcomm_sock_listen,
	.accept		= rfcomm_sock_accept,
	.getname	= rfcomm_sock_getname,
	.sendmsg	= rfcomm_sock_sendmsg,
	.recvmsg	= rfcomm_sock_recvmsg,
	.shutकरोwn	= rfcomm_sock_shutकरोwn,
	.setsockopt	= rfcomm_sock_setsockopt,
	.माला_लोockopt	= rfcomm_sock_माला_लोockopt,
	.ioctl		= rfcomm_sock_ioctl,
	.gettstamp	= sock_gettstamp,
	.poll		= bt_sock_poll,
	.socketpair	= sock_no_socketpair,
	.mmap		= sock_no_mmap,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= rfcomm_sock_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_proto_family rfcomm_sock_family_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.create		= rfcomm_sock_create
पूर्ण;

पूर्णांक __init rfcomm_init_sockets(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा sockaddr_rc) > माप(काष्ठा sockaddr));

	err = proto_रेजिस्टर(&rfcomm_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_RFCOMM, &rfcomm_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("RFCOMM socket layer registration failed");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "rfcomm", &rfcomm_sk_list, शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create RFCOMM proc file");
		bt_sock_unरेजिस्टर(BTPROTO_RFCOMM);
		जाओ error;
	पूर्ण

	BT_INFO("RFCOMM socket layer initialized");

	अगर (IS_ERR_OR_शून्य(bt_debugfs))
		वापस 0;

	rfcomm_sock_debugfs = debugfs_create_file("rfcomm", 0444,
						  bt_debugfs, शून्य,
						  &rfcomm_sock_debugfs_fops);

	वापस 0;

error:
	proto_unरेजिस्टर(&rfcomm_proto);
	वापस err;
पूर्ण

व्योम __निकास rfcomm_cleanup_sockets(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "rfcomm");

	debugfs_हटाओ(rfcomm_sock_debugfs);

	bt_sock_unरेजिस्टर(BTPROTO_RFCOMM);

	proto_unरेजिस्टर(&rfcomm_proto);
पूर्ण
