<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated
   Copyright (C) 2009-2010 Gustavo F. Paकरोvan <gustavo@paकरोvan.org>
   Copyright (C) 2010 Google Inc.
   Copyright (C) 2011 ProFUSION Embedded Systems

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

/* Bluetooth L2CAP sockets. */

#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "smp.h"

अटल काष्ठा bt_sock_list l2cap_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(l2cap_sk_list.lock)
पूर्ण;

अटल स्थिर काष्ठा proto_ops l2cap_sock_ops;
अटल व्योम l2cap_sock_init(काष्ठा sock *sk, काष्ठा sock *parent);
अटल काष्ठा sock *l2cap_sock_alloc(काष्ठा net *net, काष्ठा socket *sock,
				     पूर्णांक proto, gfp_t prio, पूर्णांक kern);

bool l2cap_is_socket(काष्ठा socket *sock)
अणु
	वापस sock && sock->ops == &l2cap_sock_ops;
पूर्ण
EXPORT_SYMBOL(l2cap_is_socket);

अटल पूर्णांक l2cap_validate_bredr_psm(u16 psm)
अणु
	/* PSM must be odd and lsb of upper byte must be 0 */
	अगर ((psm & 0x0101) != 0x0001)
		वापस -EINVAL;

	/* Restrict usage of well-known PSMs */
	अगर (psm < L2CAP_PSM_DYN_START && !capable(CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_validate_le_psm(u16 psm)
अणु
	/* Valid LE_PSM ranges are defined only until 0x00ff */
	अगर (psm > L2CAP_PSM_LE_DYN_END)
		वापस -EINVAL;

	/* Restrict fixed, SIG asचिन्हित PSM values to CAP_NET_BIND_SERVICE */
	अगर (psm < L2CAP_PSM_LE_DYN_START && !capable(CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक alen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा sockaddr_l2 la;
	पूर्णांक len, err = 0;

	BT_DBG("sk %p", sk);

	अगर (!addr || alen < दुरत्वend(काष्ठा sockaddr, sa_family) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	स_रखो(&la, 0, माप(la));
	len = min_t(अचिन्हित पूर्णांक, माप(la), alen);
	स_नकल(&la, addr, len);

	अगर (la.l2_cid && la.l2_psm)
		वापस -EINVAL;

	अगर (!bdaddr_type_is_valid(la.l2_bdaddr_type))
		वापस -EINVAL;

	अगर (bdaddr_type_is_le(la.l2_bdaddr_type)) अणु
		/* We only allow ATT user space socket */
		अगर (la.l2_cid &&
		    la.l2_cid != cpu_to_le16(L2CAP_CID_ATT))
			वापस -EINVAL;
	पूर्ण

	lock_sock(sk);

	अगर (sk->sk_state != BT_OPEN) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (la.l2_psm) अणु
		__u16 psm = __le16_to_cpu(la.l2_psm);

		अगर (la.l2_bdaddr_type == BDADDR_BREDR)
			err = l2cap_validate_bredr_psm(psm);
		अन्यथा
			err = l2cap_validate_le_psm(psm);

		अगर (err)
			जाओ करोne;
	पूर्ण

	bacpy(&chan->src, &la.l2_bdaddr);
	chan->src_type = la.l2_bdaddr_type;

	अगर (la.l2_cid)
		err = l2cap_add_scid(chan, __le16_to_cpu(la.l2_cid));
	अन्यथा
		err = l2cap_add_psm(chan, &la.l2_bdaddr, la.l2_psm);

	अगर (err < 0)
		जाओ करोne;

	चयन (chan->chan_type) अणु
	हाल L2CAP_CHAN_CONN_LESS:
		अगर (__le16_to_cpu(la.l2_psm) == L2CAP_PSM_3DSP)
			chan->sec_level = BT_SECURITY_SDP;
		अवरोध;
	हाल L2CAP_CHAN_CONN_ORIENTED:
		अगर (__le16_to_cpu(la.l2_psm) == L2CAP_PSM_SDP ||
		    __le16_to_cpu(la.l2_psm) == L2CAP_PSM_RFCOMM)
			chan->sec_level = BT_SECURITY_SDP;
		अवरोध;
	हाल L2CAP_CHAN_RAW:
		chan->sec_level = BT_SECURITY_SDP;
		अवरोध;
	हाल L2CAP_CHAN_FIXED:
		/* Fixed channels शेष to the L2CAP core not holding a
		 * hci_conn reference क्रम them. For fixed channels mapping to
		 * L2CAP sockets we करो want to hold a reference so set the
		 * appropriate flag to request it.
		 */
		set_bit(FLAG_HOLD_HCI_CONN, &chan->flags);
		अवरोध;
	पूर्ण

	अगर (chan->psm && bdaddr_type_is_le(chan->src_type))
		chan->mode = L2CAP_MODE_LE_FLOWCTL;

	chan->state = BT_BOUND;
	sk->sk_state = BT_BOUND;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			      पूर्णांक alen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा sockaddr_l2 la;
	पूर्णांक len, err = 0;
	bool zapped;

	BT_DBG("sk %p", sk);

	lock_sock(sk);
	zapped = sock_flag(sk, SOCK_ZAPPED);
	release_sock(sk);

	अगर (zapped)
		वापस -EINVAL;

	अगर (!addr || alen < दुरत्वend(काष्ठा sockaddr, sa_family) ||
	    addr->sa_family != AF_BLUETOOTH)
		वापस -EINVAL;

	स_रखो(&la, 0, माप(la));
	len = min_t(अचिन्हित पूर्णांक, माप(la), alen);
	स_नकल(&la, addr, len);

	अगर (la.l2_cid && la.l2_psm)
		वापस -EINVAL;

	अगर (!bdaddr_type_is_valid(la.l2_bdaddr_type))
		वापस -EINVAL;

	/* Check that the socket wasn't bound to something that
	 * conflicts with the address given to connect(). If chan->src
	 * is BDADDR_ANY it means bind() was never used, in which हाल
	 * chan->src_type and la.l2_bdaddr_type करो not need to match.
	 */
	अगर (chan->src_type == BDADDR_BREDR && bacmp(&chan->src, BDADDR_ANY) &&
	    bdaddr_type_is_le(la.l2_bdaddr_type)) अणु
		/* Old user space versions will try to incorrectly bind
		 * the ATT socket using BDADDR_BREDR. We need to accept
		 * this and fix up the source address type only when
		 * both the source CID and destination CID indicate
		 * ATT. Anything अन्यथा is an invalid combination.
		 */
		अगर (chan->scid != L2CAP_CID_ATT ||
		    la.l2_cid != cpu_to_le16(L2CAP_CID_ATT))
			वापस -EINVAL;

		/* We करोn't have the hdev available here to make a
		 * better decision on अक्रमom vs खुला, but since all
		 * user space versions that exhibit this issue anyway करो
		 * not support अक्रमom local addresses assuming खुला
		 * here is good enough.
		 */
		chan->src_type = BDADDR_LE_PUBLIC;
	पूर्ण

	अगर (chan->src_type != BDADDR_BREDR && la.l2_bdaddr_type == BDADDR_BREDR)
		वापस -EINVAL;

	अगर (bdaddr_type_is_le(la.l2_bdaddr_type)) अणु
		/* We only allow ATT user space socket */
		अगर (la.l2_cid &&
		    la.l2_cid != cpu_to_le16(L2CAP_CID_ATT))
			वापस -EINVAL;
	पूर्ण

	अगर (chan->psm && bdaddr_type_is_le(chan->src_type) && !chan->mode)
		chan->mode = L2CAP_MODE_LE_FLOWCTL;

	err = l2cap_chan_connect(chan, la.l2_psm, __le16_to_cpu(la.l2_cid),
				 &la.l2_bdaddr, la.l2_bdaddr_type);
	अगर (err)
		वापस err;

	lock_sock(sk);

	err = bt_sock_रुको_state(sk, BT_CONNECTED,
				 sock_sndसमयo(sk, flags & O_NONBLOCK));

	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	पूर्णांक err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	अगर (sk->sk_state != BT_BOUND) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_BASIC:
	हाल L2CAP_MODE_LE_FLOWCTL:
		अवरोध;
	हाल L2CAP_MODE_EXT_FLOWCTL:
		अगर (!enable_ecred) अणु
			err = -EOPNOTSUPP;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल L2CAP_MODE_ERTM:
	हाल L2CAP_MODE_STREAMING:
		अगर (!disable_erपंचांग)
			अवरोध;
		fallthrough;
	शेष:
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;

	/* Listening channels need to use nested locking in order not to
	 * cause lockdep warnings when the created child channels end up
	 * being locked in the same thपढ़ो as the parent channel.
	 */
	atomic_set(&chan->nesting, L2CAP_NESTING_PARENT);

	chan->state = BT_LISTEN;
	sk->sk_state = BT_LISTEN;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			     पूर्णांक flags, bool kern)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा sock *sk = sock->sk, *nsk;
	दीर्घ समयo;
	पूर्णांक err = 0;

	lock_sock_nested(sk, L2CAP_NESTING_PARENT);

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

		lock_sock_nested(sk, L2CAP_NESTING_PARENT);
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

अटल पूर्णांक l2cap_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			      पूर्णांक peer)
अणु
	काष्ठा sockaddr_l2 *la = (काष्ठा sockaddr_l2 *) addr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (peer && sk->sk_state != BT_CONNECTED &&
	    sk->sk_state != BT_CONNECT && sk->sk_state != BT_CONNECT2 &&
	    sk->sk_state != BT_CONFIG)
		वापस -ENOTCONN;

	स_रखो(la, 0, माप(काष्ठा sockaddr_l2));
	addr->sa_family = AF_BLUETOOTH;

	la->l2_psm = chan->psm;

	अगर (peer) अणु
		bacpy(&la->l2_bdaddr, &chan->dst);
		la->l2_cid = cpu_to_le16(chan->dcid);
		la->l2_bdaddr_type = chan->dst_type;
	पूर्ण अन्यथा अणु
		bacpy(&la->l2_bdaddr, &chan->src);
		la->l2_cid = cpu_to_le16(chan->scid);
		la->l2_bdaddr_type = chan->src_type;
	पूर्ण

	वापस माप(काष्ठा sockaddr_l2);
पूर्ण

अटल पूर्णांक l2cap_get_mode(काष्ठा l2cap_chan *chan)
अणु
	चयन (chan->mode) अणु
	हाल L2CAP_MODE_BASIC:
		वापस BT_MODE_BASIC;
	हाल L2CAP_MODE_ERTM:
		वापस BT_MODE_ERTM;
	हाल L2CAP_MODE_STREAMING:
		वापस BT_MODE_STREAMING;
	हाल L2CAP_MODE_LE_FLOWCTL:
		वापस BT_MODE_LE_FLOWCTL;
	हाल L2CAP_MODE_EXT_FLOWCTL:
		वापस BT_MODE_EXT_FLOWCTL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक l2cap_sock_माला_लोockopt_old(काष्ठा socket *sock, पूर्णांक optname,
				     अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा l2cap_options opts;
	काष्ठा l2cap_conninfo cinfo;
	पूर्णांक len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल L2CAP_OPTIONS:
		/* LE sockets should use BT_SNDMTU/BT_RCVMTU, but since
		 * legacy ATT code depends on माला_लोockopt क्रम
		 * L2CAP_OPTIONS we need to let this pass.
		 */
		अगर (bdaddr_type_is_le(chan->src_type) &&
		    chan->scid != L2CAP_CID_ATT) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/* Only BR/EDR modes are supported here */
		चयन (chan->mode) अणु
		हाल L2CAP_MODE_BASIC:
		हाल L2CAP_MODE_ERTM:
		हाल L2CAP_MODE_STREAMING:
			अवरोध;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (err < 0)
			अवरोध;

		स_रखो(&opts, 0, माप(opts));
		opts.imtu     = chan->imtu;
		opts.omtu     = chan->omtu;
		opts.flush_to = chan->flush_to;
		opts.mode     = chan->mode;
		opts.fcs      = chan->fcs;
		opts.max_tx   = chan->max_tx;
		opts.txwin_size = chan->tx_win;

		BT_DBG("mode 0x%2.2x", chan->mode);

		len = min_t(अचिन्हित पूर्णांक, len, माप(opts));
		अगर (copy_to_user(optval, (अक्षर *) &opts, len))
			err = -EFAULT;

		अवरोध;

	हाल L2CAP_LM:
		चयन (chan->sec_level) अणु
		हाल BT_SECURITY_LOW:
			opt = L2CAP_LM_AUTH;
			अवरोध;
		हाल BT_SECURITY_MEDIUM:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT;
			अवरोध;
		हाल BT_SECURITY_HIGH:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT |
			      L2CAP_LM_SECURE;
			अवरोध;
		हाल BT_SECURITY_FIPS:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT |
			      L2CAP_LM_SECURE | L2CAP_LM_FIPS;
			अवरोध;
		शेष:
			opt = 0;
			अवरोध;
		पूर्ण

		अगर (test_bit(FLAG_ROLE_SWITCH, &chan->flags))
			opt |= L2CAP_LM_MASTER;

		अगर (test_bit(FLAG_FORCE_RELIABLE, &chan->flags))
			opt |= L2CAP_LM_RELIABLE;

		अगर (put_user(opt, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल L2CAP_CONNINFO:
		अगर (sk->sk_state != BT_CONNECTED &&
		    !(sk->sk_state == BT_CONNECT2 &&
		      test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags))) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		स_रखो(&cinfo, 0, माप(cinfo));
		cinfo.hci_handle = chan->conn->hcon->handle;
		स_नकल(cinfo.dev_class, chan->conn->hcon->dev_class, 3);

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

अटल पूर्णांक l2cap_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				 अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा bt_security sec;
	काष्ठा bt_घातer pwr;
	u32 phys;
	पूर्णांक len, mode, err = 0;

	BT_DBG("sk %p", sk);

	अगर (level == SOL_L2CAP)
		वापस l2cap_sock_माला_लोockopt_old(sock, optname, optval, optlen);

	अगर (level != SOL_BLUETOOTH)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल BT_SECURITY:
		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
		    chan->chan_type != L2CAP_CHAN_FIXED &&
		    chan->chan_type != L2CAP_CHAN_RAW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		स_रखो(&sec, 0, माप(sec));
		अगर (chan->conn) अणु
			sec.level = chan->conn->hcon->sec_level;

			अगर (sk->sk_state == BT_CONNECTED)
				sec.key_size = chan->conn->hcon->enc_key_size;
		पूर्ण अन्यथा अणु
			sec.level = chan->sec_level;
		पूर्ण

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

	हाल BT_FLUSHABLE:
		अगर (put_user(test_bit(FLAG_FLUSHABLE, &chan->flags),
			     (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल BT_POWER:
		अगर (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
		    && sk->sk_type != SOCK_RAW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		pwr.क्रमce_active = test_bit(FLAG_FORCE_ACTIVE, &chan->flags);

		len = min_t(अचिन्हित पूर्णांक, len, माप(pwr));
		अगर (copy_to_user(optval, (अक्षर *) &pwr, len))
			err = -EFAULT;

		अवरोध;

	हाल BT_CHANNEL_POLICY:
		अगर (put_user(chan->chan_policy, (u32 __user *) optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_SNDMTU:
		अगर (!bdaddr_type_is_le(chan->src_type)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (sk->sk_state != BT_CONNECTED) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		अगर (put_user(chan->omtu, (u16 __user *) optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_RCVMTU:
		अगर (!bdaddr_type_is_le(chan->src_type)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (put_user(chan->imtu, (u16 __user *) optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_PHY:
		अगर (sk->sk_state != BT_CONNECTED) अणु
			err = -ENOTCONN;
			अवरोध;
		पूर्ण

		phys = hci_conn_get_phy(chan->conn->hcon);

		अगर (put_user(phys, (u32 __user *) optval))
			err = -EFAULT;
		अवरोध;

	हाल BT_MODE:
		अगर (!enable_ecred) अणु
			err = -ENOPROTOOPT;
			अवरोध;
		पूर्ण

		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		mode = l2cap_get_mode(chan);
		अगर (mode < 0) अणु
			err = mode;
			अवरोध;
		पूर्ण

		अगर (put_user(mode, (u8 __user *) optval))
			err = -EFAULT;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल bool l2cap_valid_mtu(काष्ठा l2cap_chan *chan, u16 mtu)
अणु
	चयन (chan->scid) अणु
	हाल L2CAP_CID_ATT:
		अगर (mtu < L2CAP_LE_MIN_MTU)
			वापस false;
		अवरोध;

	शेष:
		अगर (mtu < L2CAP_DEFAULT_MIN_MTU)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक l2cap_sock_setsockopt_old(काष्ठा socket *sock, पूर्णांक optname,
				     sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा l2cap_options opts;
	पूर्णांक len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	lock_sock(sk);

	चयन (optname) अणु
	हाल L2CAP_OPTIONS:
		अगर (bdaddr_type_is_le(chan->src_type)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (sk->sk_state == BT_CONNECTED) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		opts.imtu     = chan->imtu;
		opts.omtu     = chan->omtu;
		opts.flush_to = chan->flush_to;
		opts.mode     = chan->mode;
		opts.fcs      = chan->fcs;
		opts.max_tx   = chan->max_tx;
		opts.txwin_size = chan->tx_win;

		len = min_t(अचिन्हित पूर्णांक, माप(opts), optlen);
		अगर (copy_from_sockptr(&opts, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opts.txwin_size > L2CAP_DEFAULT_EXT_WINDOW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!l2cap_valid_mtu(chan, opts.imtu)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/* Only BR/EDR modes are supported here */
		चयन (opts.mode) अणु
		हाल L2CAP_MODE_BASIC:
			clear_bit(CONF_STATE2_DEVICE, &chan->conf_state);
			अवरोध;
		हाल L2CAP_MODE_ERTM:
		हाल L2CAP_MODE_STREAMING:
			अगर (!disable_erपंचांग)
				अवरोध;
			fallthrough;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (err < 0)
			अवरोध;

		chan->mode = opts.mode;

		BT_DBG("mode 0x%2.2x", chan->mode);

		chan->imtu = opts.imtu;
		chan->omtu = opts.omtu;
		chan->fcs  = opts.fcs;
		chan->max_tx = opts.max_tx;
		chan->tx_win = opts.txwin_size;
		chan->flush_to = opts.flush_to;
		अवरोध;

	हाल L2CAP_LM:
		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt & L2CAP_LM_FIPS) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (opt & L2CAP_LM_AUTH)
			chan->sec_level = BT_SECURITY_LOW;
		अगर (opt & L2CAP_LM_ENCRYPT)
			chan->sec_level = BT_SECURITY_MEDIUM;
		अगर (opt & L2CAP_LM_SECURE)
			chan->sec_level = BT_SECURITY_HIGH;

		अगर (opt & L2CAP_LM_MASTER)
			set_bit(FLAG_ROLE_SWITCH, &chan->flags);
		अन्यथा
			clear_bit(FLAG_ROLE_SWITCH, &chan->flags);

		अगर (opt & L2CAP_LM_RELIABLE)
			set_bit(FLAG_FORCE_RELIABLE, &chan->flags);
		अन्यथा
			clear_bit(FLAG_FORCE_RELIABLE, &chan->flags);
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक l2cap_set_mode(काष्ठा l2cap_chan *chan, u8 mode)
अणु
	चयन (mode) अणु
	हाल BT_MODE_BASIC:
		अगर (bdaddr_type_is_le(chan->src_type))
			वापस -EINVAL;
		mode = L2CAP_MODE_BASIC;
		clear_bit(CONF_STATE2_DEVICE, &chan->conf_state);
		अवरोध;
	हाल BT_MODE_ERTM:
		अगर (!disable_erपंचांग || bdaddr_type_is_le(chan->src_type))
			वापस -EINVAL;
		mode = L2CAP_MODE_ERTM;
		अवरोध;
	हाल BT_MODE_STREAMING:
		अगर (!disable_erपंचांग || bdaddr_type_is_le(chan->src_type))
			वापस -EINVAL;
		mode = L2CAP_MODE_STREAMING;
		अवरोध;
	हाल BT_MODE_LE_FLOWCTL:
		अगर (!bdaddr_type_is_le(chan->src_type))
			वापस -EINVAL;
		mode = L2CAP_MODE_LE_FLOWCTL;
		अवरोध;
	हाल BT_MODE_EXT_FLOWCTL:
		/* TODO: Add support क्रम ECRED PDUs to BR/EDR */
		अगर (!bdaddr_type_is_le(chan->src_type))
			वापस -EINVAL;
		mode = L2CAP_MODE_EXT_FLOWCTL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	chan->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक l2cap_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				 sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	काष्ठा bt_security sec;
	काष्ठा bt_घातer pwr;
	काष्ठा l2cap_conn *conn;
	पूर्णांक len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	अगर (level == SOL_L2CAP)
		वापस l2cap_sock_setsockopt_old(sock, optname, optval, optlen);

	अगर (level != SOL_BLUETOOTH)
		वापस -ENOPROTOOPT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल BT_SECURITY:
		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
		    chan->chan_type != L2CAP_CHAN_FIXED &&
		    chan->chan_type != L2CAP_CHAN_RAW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		sec.level = BT_SECURITY_LOW;

		len = min_t(अचिन्हित पूर्णांक, माप(sec), optlen);
		अगर (copy_from_sockptr(&sec, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (sec.level < BT_SECURITY_LOW ||
		    sec.level > BT_SECURITY_FIPS) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		chan->sec_level = sec.level;

		अगर (!chan->conn)
			अवरोध;

		conn = chan->conn;

		/* change security क्रम LE channels */
		अगर (chan->scid == L2CAP_CID_ATT) अणु
			अगर (smp_conn_security(conn->hcon, sec.level)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण

			set_bit(FLAG_PENDING_SECURITY, &chan->flags);
			sk->sk_state = BT_CONFIG;
			chan->state = BT_CONFIG;

		/* or क्रम ACL link */
		पूर्ण अन्यथा अगर ((sk->sk_state == BT_CONNECT2 &&
			    test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags)) ||
			   sk->sk_state == BT_CONNECTED) अणु
			अगर (!l2cap_chan_check_security(chan, true))
				set_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags);
			अन्यथा
				sk->sk_state_change(sk);
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
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

		अगर (opt) अणु
			set_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags);
			set_bit(FLAG_DEFER_SETUP, &chan->flags);
		पूर्ण अन्यथा अणु
			clear_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags);
			clear_bit(FLAG_DEFER_SETUP, &chan->flags);
		पूर्ण
		अवरोध;

	हाल BT_FLUSHABLE:
		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt > BT_FLUSHABLE_ON) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (opt == BT_FLUSHABLE_OFF) अणु
			conn = chan->conn;
			/* proceed further only when we have l2cap_conn and
			   No Flush support in the LM */
			अगर (!conn || !lmp_no_flush_capable(conn->hcon->hdev)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (opt)
			set_bit(FLAG_FLUSHABLE, &chan->flags);
		अन्यथा
			clear_bit(FLAG_FLUSHABLE, &chan->flags);
		अवरोध;

	हाल BT_POWER:
		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
		    chan->chan_type != L2CAP_CHAN_RAW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		pwr.क्रमce_active = BT_POWER_FORCE_ACTIVE_ON;

		len = min_t(अचिन्हित पूर्णांक, माप(pwr), optlen);
		अगर (copy_from_sockptr(&pwr, optval, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (pwr.क्रमce_active)
			set_bit(FLAG_FORCE_ACTIVE, &chan->flags);
		अन्यथा
			clear_bit(FLAG_FORCE_ACTIVE, &chan->flags);
		अवरोध;

	हाल BT_CHANNEL_POLICY:
		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt > BT_CHANNEL_POLICY_AMP_PREFERRED) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (chan->mode != L2CAP_MODE_ERTM &&
		    chan->mode != L2CAP_MODE_STREAMING) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		chan->chan_policy = (u8) opt;

		अगर (sk->sk_state == BT_CONNECTED &&
		    chan->move_role == L2CAP_MOVE_ROLE_NONE)
			l2cap_move_start(chan);

		अवरोध;

	हाल BT_SNDMTU:
		अगर (!bdaddr_type_is_le(chan->src_type)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/* Setting is not supported as it's the remote side that
		 * decides this.
		 */
		err = -EPERM;
		अवरोध;

	हाल BT_RCVMTU:
		अगर (!bdaddr_type_is_le(chan->src_type)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (chan->mode == L2CAP_MODE_LE_FLOWCTL &&
		    sk->sk_state == BT_CONNECTED) अणु
			err = -EISCONN;
			अवरोध;
		पूर्ण

		अगर (copy_from_sockptr(&opt, optval, माप(u16))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (chan->mode == L2CAP_MODE_EXT_FLOWCTL &&
		    sk->sk_state == BT_CONNECTED)
			err = l2cap_chan_reconfigure(chan, opt);
		अन्यथा
			chan->imtu = opt;

		अवरोध;

	हाल BT_MODE:
		अगर (!enable_ecred) अणु
			err = -ENOPROTOOPT;
			अवरोध;
		पूर्ण

		BT_DBG("sk->sk_state %u", sk->sk_state);

		अगर (sk->sk_state != BT_BOUND) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_sockptr(&opt, optval, माप(u8))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		BT_DBG("opt %u", opt);

		err = l2cap_set_mode(chan, opt);
		अगर (err)
			अवरोध;

		BT_DBG("mode 0x%2.2x", chan->mode);

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;
	पूर्णांक err;

	BT_DBG("sock %p, sk %p", sock, sk);

	err = sock_error(sk);
	अगर (err)
		वापस err;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (sk->sk_state != BT_CONNECTED)
		वापस -ENOTCONN;

	lock_sock(sk);
	err = bt_sock_रुको_पढ़ोy(sk, msg->msg_flags);
	release_sock(sk);
	अगर (err)
		वापस err;

	l2cap_chan_lock(chan);
	err = l2cap_chan_send(chan, msg, len);
	l2cap_chan_unlock(chan);

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_pinfo *pi = l2cap_pi(sk);
	पूर्णांक err;

	lock_sock(sk);

	अगर (sk->sk_state == BT_CONNECT2 && test_bit(BT_SK_DEFER_SETUP,
						    &bt_sk(sk)->flags)) अणु
		अगर (pi->chan->mode == L2CAP_MODE_EXT_FLOWCTL) अणु
			sk->sk_state = BT_CONNECTED;
			pi->chan->state = BT_CONNECTED;
			__l2cap_ecred_conn_rsp_defer(pi->chan);
		पूर्ण अन्यथा अगर (bdaddr_type_is_le(pi->chan->src_type)) अणु
			sk->sk_state = BT_CONNECTED;
			pi->chan->state = BT_CONNECTED;
			__l2cap_le_connect_rsp_defer(pi->chan);
		पूर्ण अन्यथा अणु
			sk->sk_state = BT_CONFIG;
			pi->chan->state = BT_CONFIG;
			__l2cap_connect_rsp_defer(pi->chan);
		पूर्ण

		err = 0;
		जाओ करोne;
	पूर्ण

	release_sock(sk);

	अगर (sock->type == SOCK_STREAM)
		err = bt_sock_stream_recvmsg(sock, msg, len, flags);
	अन्यथा
		err = bt_sock_recvmsg(sock, msg, len, flags);

	अगर (pi->chan->mode != L2CAP_MODE_ERTM)
		वापस err;

	/* Attempt to put pending rx data in the socket buffer */

	lock_sock(sk);

	अगर (!test_bit(CONN_LOCAL_BUSY, &pi->chan->conn_state))
		जाओ करोne;

	अगर (pi->rx_busy_skb) अणु
		अगर (!__sock_queue_rcv_skb(sk, pi->rx_busy_skb))
			pi->rx_busy_skb = शून्य;
		अन्यथा
			जाओ करोne;
	पूर्ण

	/* Restore data flow when half of the receive buffer is
	 * available.  This aव्योमs resending large numbers of
	 * frames.
	 */
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf >> 1)
		l2cap_chan_busy(pi->chan, 0);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

/* Kill socket (only अगर zapped and orphan)
 * Must be called on unlocked socket, with l2cap channel lock.
 */
अटल व्योम l2cap_sock_समाप्त(काष्ठा sock *sk)
अणु
	अगर (!sock_flag(sk, SOCK_ZAPPED) || sk->sk_socket)
		वापस;

	BT_DBG("sk %p state %s", sk, state_to_string(sk->sk_state));

	/* Kill poor orphan */

	l2cap_chan_put(l2cap_pi(sk)->chan);
	sock_set_flag(sk, SOCK_DEAD);
	sock_put(sk);
पूर्ण

अटल पूर्णांक __l2cap_रुको_ack(काष्ठा sock *sk, काष्ठा l2cap_chan *chan)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक err = 0;
	पूर्णांक समयo = L2CAP_WAIT_ACK_POLL_PERIOD;
	/* Timeout to prevent infinite loop */
	अचिन्हित दीर्घ समयout = jअगरfies + L2CAP_WAIT_ACK_TIMEOUT;

	add_रुको_queue(sk_sleep(sk), &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	करो अणु
		BT_DBG("Waiting for %d ACKs, timeout %04d ms",
		       chan->unacked_frames, समय_after(jअगरfies, समयout) ? 0 :
		       jअगरfies_to_msecs(समयout - jअगरfies));

		अगर (!समयo)
			समयo = L2CAP_WAIT_ACK_POLL_PERIOD;

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण

		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock(sk);
		set_current_state(TASK_INTERRUPTIBLE);

		err = sock_error(sk);
		अगर (err)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			err = -ENOLINK;
			अवरोध;
		पूर्ण

	पूर्ण जबतक (chan->unacked_frames > 0 &&
		 chan->state == BT_CONNECTED);

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा l2cap_chan *chan;
	काष्ठा l2cap_conn *conn;
	पूर्णांक err = 0;

	BT_DBG("sock %p, sk %p, how %d", sock, sk, how);

	/* 'how' parameter is mapped to sk_shutकरोwn as follows:
	 * SHUT_RD   (0) --> RCV_SHUTDOWN  (1)
	 * SHUT_WR   (1) --> SEND_SHUTDOWN (2)
	 * SHUT_RDWR (2) --> SHUTDOWN_MASK (3)
	 */
	how++;

	अगर (!sk)
		वापस 0;

	lock_sock(sk);

	अगर ((sk->sk_shutकरोwn & how) == how)
		जाओ shutकरोwn_alपढ़ोy;

	BT_DBG("Handling sock shutdown");

	/* prevent sk काष्ठाure from being मुक्तd whilst unlocked */
	sock_hold(sk);

	chan = l2cap_pi(sk)->chan;
	/* prevent chan काष्ठाure from being मुक्तd whilst unlocked */
	l2cap_chan_hold(chan);

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	अगर (chan->mode == L2CAP_MODE_ERTM &&
	    chan->unacked_frames > 0 &&
	    chan->state == BT_CONNECTED) अणु
		err = __l2cap_रुको_ack(sk, chan);

		/* After रुकोing क्रम ACKs, check whether shutकरोwn
		 * has alपढ़ोy been actioned to बंद the L2CAP
		 * link such as by l2cap_disconnection_req().
		 */
		अगर ((sk->sk_shutकरोwn & how) == how)
			जाओ shutकरोwn_matched;
	पूर्ण

	/* Try setting the RCV_SHUTDOWN bit, वापस early अगर SEND_SHUTDOWN
	 * is alपढ़ोy set
	 */
	अगर ((how & RCV_SHUTDOWN) && !(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		sk->sk_shutकरोwn |= RCV_SHUTDOWN;
		अगर ((sk->sk_shutकरोwn & how) == how)
			जाओ shutकरोwn_matched;
	पूर्ण

	sk->sk_shutकरोwn |= SEND_SHUTDOWN;
	release_sock(sk);

	l2cap_chan_lock(chan);
	conn = chan->conn;
	अगर (conn)
		/* prevent conn काष्ठाure from being मुक्तd */
		l2cap_conn_get(conn);
	l2cap_chan_unlock(chan);

	अगर (conn)
		/* mutex lock must be taken beक्रमe l2cap_chan_lock() */
		mutex_lock(&conn->chan_lock);

	l2cap_chan_lock(chan);
	l2cap_chan_बंद(chan, 0);
	l2cap_chan_unlock(chan);

	अगर (conn) अणु
		mutex_unlock(&conn->chan_lock);
		l2cap_conn_put(conn);
	पूर्ण

	lock_sock(sk);

	अगर (sock_flag(sk, SOCK_LINGER) && sk->sk_lingerसमय &&
	    !(current->flags & PF_EXITING))
		err = bt_sock_रुको_state(sk, BT_CLOSED,
					 sk->sk_lingerसमय);

shutकरोwn_matched:
	l2cap_chan_put(chan);
	sock_put(sk);

shutकरोwn_alपढ़ोy:
	अगर (!err && sk->sk_err)
		err = -sk->sk_err;

	release_sock(sk);

	BT_DBG("Sock shutdown complete err: %d", err);

	वापस err;
पूर्ण

अटल पूर्णांक l2cap_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;
	काष्ठा l2cap_chan *chan;

	BT_DBG("sock %p, sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	bt_sock_unlink(&l2cap_sk_list, sk);

	err = l2cap_sock_shutकरोwn(sock, SHUT_RDWR);
	chan = l2cap_pi(sk)->chan;

	l2cap_chan_hold(chan);
	l2cap_chan_lock(chan);

	sock_orphan(sk);
	l2cap_sock_समाप्त(sk);

	l2cap_chan_unlock(chan);
	l2cap_chan_put(chan);

	वापस err;
पूर्ण

अटल व्योम l2cap_sock_cleanup_listen(काष्ठा sock *parent)
अणु
	काष्ठा sock *sk;

	BT_DBG("parent %p state %s", parent,
	       state_to_string(parent->sk_state));

	/* Close not yet accepted channels */
	जबतक ((sk = bt_accept_dequeue(parent, शून्य))) अणु
		काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;

		BT_DBG("child chan %p state %s", chan,
		       state_to_string(chan->state));

		l2cap_chan_hold(chan);
		l2cap_chan_lock(chan);

		__clear_chan_समयr(chan);
		l2cap_chan_बंद(chan, ECONNRESET);
		l2cap_sock_समाप्त(sk);

		l2cap_chan_unlock(chan);
		l2cap_chan_put(chan);
	पूर्ण
पूर्ण

अटल काष्ठा l2cap_chan *l2cap_sock_new_connection_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk, *parent = chan->data;

	lock_sock(parent);

	/* Check क्रम backlog size */
	अगर (sk_acceptq_is_full(parent)) अणु
		BT_DBG("backlog full %d", parent->sk_ack_backlog);
		release_sock(parent);
		वापस शून्य;
	पूर्ण

	sk = l2cap_sock_alloc(sock_net(parent), शून्य, BTPROTO_L2CAP,
			      GFP_ATOMIC, 0);
	अगर (!sk) अणु
		release_sock(parent);
		वापस शून्य;
        पूर्ण

	bt_sock_reclassअगरy_lock(sk, BTPROTO_L2CAP);

	l2cap_sock_init(sk, parent);

	bt_accept_enqueue(parent, sk, false);

	release_sock(parent);

	वापस l2cap_pi(sk)->chan;
पूर्ण

अटल पूर्णांक l2cap_sock_recv_cb(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = chan->data;
	पूर्णांक err;

	lock_sock(sk);

	अगर (l2cap_pi(sk)->rx_busy_skb) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर (chan->mode != L2CAP_MODE_ERTM &&
	    chan->mode != L2CAP_MODE_STREAMING) अणु
		/* Even अगर no filter is attached, we could potentially
		 * get errors from security modules, etc.
		 */
		err = sk_filter(sk, skb);
		अगर (err)
			जाओ करोne;
	पूर्ण

	err = __sock_queue_rcv_skb(sk, skb);

	/* For ERTM, handle one skb that करोesn't fit पूर्णांकo the recv
	 * buffer.  This is important to करो because the data frames
	 * have alपढ़ोy been acked, so the skb cannot be discarded.
	 *
	 * Notअगरy the l2cap core that the buffer is full, so the
	 * LOCAL_BUSY state is entered and no more frames are
	 * acked and reassembled until there is buffer space
	 * available.
	 */
	अगर (err < 0 && chan->mode == L2CAP_MODE_ERTM) अणु
		l2cap_pi(sk)->rx_busy_skb = skb;
		l2cap_chan_busy(chan, 1);
		err = 0;
	पूर्ण

करोne:
	release_sock(sk);

	वापस err;
पूर्ण

अटल व्योम l2cap_sock_बंद_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	l2cap_sock_समाप्त(sk);
पूर्ण

अटल व्योम l2cap_sock_tearकरोwn_cb(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
	काष्ठा sock *sk = chan->data;
	काष्ठा sock *parent;

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	/* This callback can be called both क्रम server (BT_LISTEN)
	 * sockets as well as "normal" ones. To aव्योम lockdep warnings
	 * with child socket locking (through l2cap_sock_cleanup_listen)
	 * we need separation पूर्णांकo separate nesting levels. The simplest
	 * way to accomplish this is to inherit the nesting level used
	 * क्रम the channel.
	 */
	lock_sock_nested(sk, atomic_पढ़ो(&chan->nesting));

	parent = bt_sk(sk)->parent;

	चयन (chan->state) अणु
	हाल BT_OPEN:
	हाल BT_BOUND:
	हाल BT_CLOSED:
		अवरोध;
	हाल BT_LISTEN:
		l2cap_sock_cleanup_listen(sk);
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		अवरोध;
	शेष:
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		sk->sk_err = err;

		अगर (parent) अणु
			bt_accept_unlink(sk);
			parent->sk_data_पढ़ोy(parent);
		पूर्ण अन्यथा अणु
			sk->sk_state_change(sk);
		पूर्ण

		अवरोध;
	पूर्ण
	release_sock(sk);

	/* Only zap after cleanup to aव्योम use after मुक्त race */
	sock_set_flag(sk, SOCK_ZAPPED);

पूर्ण

अटल व्योम l2cap_sock_state_change_cb(काष्ठा l2cap_chan *chan, पूर्णांक state,
				       पूर्णांक err)
अणु
	काष्ठा sock *sk = chan->data;

	sk->sk_state = state;

	अगर (err)
		sk->sk_err = err;
पूर्ण

अटल काष्ठा sk_buff *l2cap_sock_alloc_skb_cb(काष्ठा l2cap_chan *chan,
					       अचिन्हित दीर्घ hdr_len,
					       अचिन्हित दीर्घ len, पूर्णांक nb)
अणु
	काष्ठा sock *sk = chan->data;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	l2cap_chan_unlock(chan);
	skb = bt_skb_send_alloc(sk, hdr_len + len, nb, &err);
	l2cap_chan_lock(chan);

	अगर (!skb)
		वापस ERR_PTR(err);

	skb->priority = sk->sk_priority;

	bt_cb(skb)->l2cap.chan = chan;

	वापस skb;
पूर्ण

अटल व्योम l2cap_sock_पढ़ोy_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;
	काष्ठा sock *parent;

	lock_sock(sk);

	parent = bt_sk(sk)->parent;

	BT_DBG("sk %p, parent %p", sk, parent);

	sk->sk_state = BT_CONNECTED;
	sk->sk_state_change(sk);

	अगर (parent)
		parent->sk_data_पढ़ोy(parent);

	release_sock(sk);
पूर्ण

अटल व्योम l2cap_sock_defer_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *parent, *sk = chan->data;

	lock_sock(sk);

	parent = bt_sk(sk)->parent;
	अगर (parent)
		parent->sk_data_पढ़ोy(parent);

	release_sock(sk);
पूर्ण

अटल व्योम l2cap_sock_resume_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	अगर (test_and_clear_bit(FLAG_PENDING_SECURITY, &chan->flags)) अणु
		sk->sk_state = BT_CONNECTED;
		chan->state = BT_CONNECTED;
	पूर्ण

	clear_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags);
	sk->sk_state_change(sk);
पूर्ण

अटल व्योम l2cap_sock_set_shutकरोwn_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	lock_sock(sk);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	release_sock(sk);
पूर्ण

अटल दीर्घ l2cap_sock_get_sndसमयo_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	वापस sk->sk_sndसमयo;
पूर्ण

अटल काष्ठा pid *l2cap_sock_get_peer_pid_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	वापस sk->sk_peer_pid;
पूर्ण

अटल व्योम l2cap_sock_suspend_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा sock *sk = chan->data;

	set_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags);
	sk->sk_state_change(sk);
पूर्ण

अटल पूर्णांक l2cap_sock_filter(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = chan->data;

	चयन (chan->mode) अणु
	हाल L2CAP_MODE_ERTM:
	हाल L2CAP_MODE_STREAMING:
		वापस sk_filter(sk, skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा l2cap_ops l2cap_chan_ops = अणु
	.name			= "L2CAP Socket Interface",
	.new_connection		= l2cap_sock_new_connection_cb,
	.recv			= l2cap_sock_recv_cb,
	.बंद			= l2cap_sock_बंद_cb,
	.tearकरोwn		= l2cap_sock_tearकरोwn_cb,
	.state_change		= l2cap_sock_state_change_cb,
	.पढ़ोy			= l2cap_sock_पढ़ोy_cb,
	.defer			= l2cap_sock_defer_cb,
	.resume			= l2cap_sock_resume_cb,
	.suspend		= l2cap_sock_suspend_cb,
	.set_shutकरोwn		= l2cap_sock_set_shutकरोwn_cb,
	.get_sndसमयo		= l2cap_sock_get_sndसमयo_cb,
	.get_peer_pid		= l2cap_sock_get_peer_pid_cb,
	.alloc_skb		= l2cap_sock_alloc_skb_cb,
	.filter			= l2cap_sock_filter,
पूर्ण;

अटल व्योम l2cap_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	BT_DBG("sk %p", sk);

	अगर (l2cap_pi(sk)->chan)
		l2cap_chan_put(l2cap_pi(sk)->chan);

	अगर (l2cap_pi(sk)->rx_busy_skb) अणु
		kमुक्त_skb(l2cap_pi(sk)->rx_busy_skb);
		l2cap_pi(sk)->rx_busy_skb = शून्य;
	पूर्ण

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_ग_लिखो_queue);
पूर्ण

अटल व्योम l2cap_skb_msg_name(काष्ठा sk_buff *skb, व्योम *msg_name,
			       पूर्णांक *msg_namelen)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_l2 *, la, msg_name);

	स_रखो(la, 0, माप(काष्ठा sockaddr_l2));
	la->l2_family = AF_BLUETOOTH;
	la->l2_psm = bt_cb(skb)->l2cap.psm;
	bacpy(&la->l2_bdaddr, &bt_cb(skb)->l2cap.bdaddr);

	*msg_namelen = माप(काष्ठा sockaddr_l2);
पूर्ण

अटल व्योम l2cap_sock_init(काष्ठा sock *sk, काष्ठा sock *parent)
अणु
	काष्ठा l2cap_chan *chan = l2cap_pi(sk)->chan;

	BT_DBG("sk %p", sk);

	अगर (parent) अणु
		काष्ठा l2cap_chan *pchan = l2cap_pi(parent)->chan;

		sk->sk_type = parent->sk_type;
		bt_sk(sk)->flags = bt_sk(parent)->flags;

		chan->chan_type = pchan->chan_type;
		chan->imtu = pchan->imtu;
		chan->omtu = pchan->omtu;
		chan->conf_state = pchan->conf_state;
		chan->mode = pchan->mode;
		chan->fcs  = pchan->fcs;
		chan->max_tx = pchan->max_tx;
		chan->tx_win = pchan->tx_win;
		chan->tx_win_max = pchan->tx_win_max;
		chan->sec_level = pchan->sec_level;
		chan->flags = pchan->flags;
		chan->tx_credits = pchan->tx_credits;
		chan->rx_credits = pchan->rx_credits;

		अगर (chan->chan_type == L2CAP_CHAN_FIXED) अणु
			chan->scid = pchan->scid;
			chan->dcid = pchan->scid;
		पूर्ण

		security_sk_clone(parent, sk);
	पूर्ण अन्यथा अणु
		चयन (sk->sk_type) अणु
		हाल SOCK_RAW:
			chan->chan_type = L2CAP_CHAN_RAW;
			अवरोध;
		हाल SOCK_DGRAM:
			chan->chan_type = L2CAP_CHAN_CONN_LESS;
			bt_sk(sk)->skb_msg_name = l2cap_skb_msg_name;
			अवरोध;
		हाल SOCK_SEQPACKET:
		हाल SOCK_STREAM:
			chan->chan_type = L2CAP_CHAN_CONN_ORIENTED;
			अवरोध;
		पूर्ण

		chan->imtu = L2CAP_DEFAULT_MTU;
		chan->omtu = 0;
		अगर (!disable_erपंचांग && sk->sk_type == SOCK_STREAM) अणु
			chan->mode = L2CAP_MODE_ERTM;
			set_bit(CONF_STATE2_DEVICE, &chan->conf_state);
		पूर्ण अन्यथा अणु
			chan->mode = L2CAP_MODE_BASIC;
		पूर्ण

		l2cap_chan_set_शेषs(chan);
	पूर्ण

	/* Default config options */
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;

	chan->data = sk;
	chan->ops = &l2cap_chan_ops;
पूर्ण

अटल काष्ठा proto l2cap_proto = अणु
	.name		= "L2CAP",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा l2cap_pinfo)
पूर्ण;

अटल काष्ठा sock *l2cap_sock_alloc(काष्ठा net *net, काष्ठा socket *sock,
				     पूर्णांक proto, gfp_t prio, पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा l2cap_chan *chan;

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &l2cap_proto, kern);
	अगर (!sk)
		वापस शून्य;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	sk->sk_deकाष्ठा = l2cap_sock_deकाष्ठा;
	sk->sk_sndसमयo = L2CAP_CONN_TIMEOUT;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state = BT_OPEN;

	chan = l2cap_chan_create();
	अगर (!chan) अणु
		sk_मुक्त(sk);
		वापस शून्य;
	पूर्ण

	l2cap_chan_hold(chan);

	l2cap_pi(sk)->chan = chan;

	वापस sk;
पूर्ण

अटल पूर्णांक l2cap_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			     पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	अगर (sock->type != SOCK_SEQPACKET && sock->type != SOCK_STREAM &&
	    sock->type != SOCK_DGRAM && sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	अगर (sock->type == SOCK_RAW && !kern && !capable(CAP_NET_RAW))
		वापस -EPERM;

	sock->ops = &l2cap_sock_ops;

	sk = l2cap_sock_alloc(net, sock, protocol, GFP_ATOMIC, kern);
	अगर (!sk)
		वापस -ENOMEM;

	l2cap_sock_init(sk, शून्य);
	bt_sock_link(&l2cap_sk_list, sk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proto_ops l2cap_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= l2cap_sock_release,
	.bind		= l2cap_sock_bind,
	.connect	= l2cap_sock_connect,
	.listen		= l2cap_sock_listen,
	.accept		= l2cap_sock_accept,
	.getname	= l2cap_sock_getname,
	.sendmsg	= l2cap_sock_sendmsg,
	.recvmsg	= l2cap_sock_recvmsg,
	.poll		= bt_sock_poll,
	.ioctl		= bt_sock_ioctl,
	.gettstamp	= sock_gettstamp,
	.mmap		= sock_no_mmap,
	.socketpair	= sock_no_socketpair,
	.shutकरोwn	= l2cap_sock_shutकरोwn,
	.setsockopt	= l2cap_sock_setsockopt,
	.माला_लोockopt	= l2cap_sock_माला_लोockopt
पूर्ण;

अटल स्थिर काष्ठा net_proto_family l2cap_sock_family_ops = अणु
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= l2cap_sock_create,
पूर्ण;

पूर्णांक __init l2cap_init_sockets(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा sockaddr_l2) > माप(काष्ठा sockaddr));

	err = proto_रेजिस्टर(&l2cap_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_L2CAP, &l2cap_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("L2CAP socket registration failed");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "l2cap", &l2cap_sk_list,
			     शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create L2CAP proc file");
		bt_sock_unरेजिस्टर(BTPROTO_L2CAP);
		जाओ error;
	पूर्ण

	BT_INFO("L2CAP socket layer initialized");

	वापस 0;

error:
	proto_unरेजिस्टर(&l2cap_proto);
	वापस err;
पूर्ण

व्योम l2cap_cleanup_sockets(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "l2cap");
	bt_sock_unरेजिस्टर(BTPROTO_L2CAP);
	proto_unरेजिस्टर(&l2cap_proto);
पूर्ण
