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

/* Bluetooth address family and sockets. */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/ioctls.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <linux/proc_fs.h>

#समावेश "leds.h"
#समावेश "selftest.h"

/* Bluetooth sockets */
#घोषणा BT_MAX_PROTO	8
अटल स्थिर काष्ठा net_proto_family *bt_proto[BT_MAX_PROTO];
अटल DEFINE_RWLOCK(bt_proto_lock);

अटल काष्ठा lock_class_key bt_lock_key[BT_MAX_PROTO];
अटल स्थिर अक्षर *स्थिर bt_key_strings[BT_MAX_PROTO] = अणु
	"sk_lock-AF_BLUETOOTH-BTPROTO_L2CAP",
	"sk_lock-AF_BLUETOOTH-BTPROTO_HCI",
	"sk_lock-AF_BLUETOOTH-BTPROTO_SCO",
	"sk_lock-AF_BLUETOOTH-BTPROTO_RFCOMM",
	"sk_lock-AF_BLUETOOTH-BTPROTO_BNEP",
	"sk_lock-AF_BLUETOOTH-BTPROTO_CMTP",
	"sk_lock-AF_BLUETOOTH-BTPROTO_HIDP",
	"sk_lock-AF_BLUETOOTH-BTPROTO_AVDTP",
पूर्ण;

अटल काष्ठा lock_class_key bt_slock_key[BT_MAX_PROTO];
अटल स्थिर अक्षर *स्थिर bt_slock_key_strings[BT_MAX_PROTO] = अणु
	"slock-AF_BLUETOOTH-BTPROTO_L2CAP",
	"slock-AF_BLUETOOTH-BTPROTO_HCI",
	"slock-AF_BLUETOOTH-BTPROTO_SCO",
	"slock-AF_BLUETOOTH-BTPROTO_RFCOMM",
	"slock-AF_BLUETOOTH-BTPROTO_BNEP",
	"slock-AF_BLUETOOTH-BTPROTO_CMTP",
	"slock-AF_BLUETOOTH-BTPROTO_HIDP",
	"slock-AF_BLUETOOTH-BTPROTO_AVDTP",
पूर्ण;

व्योम bt_sock_reclassअगरy_lock(काष्ठा sock *sk, पूर्णांक proto)
अणु
	BUG_ON(!sk);
	BUG_ON(!sock_allow_reclassअगरication(sk));

	sock_lock_init_class_and_name(sk,
				      bt_slock_key_strings[proto], &bt_slock_key[proto],
				      bt_key_strings[proto], &bt_lock_key[proto]);
पूर्ण
EXPORT_SYMBOL(bt_sock_reclassअगरy_lock);

पूर्णांक bt_sock_रेजिस्टर(पूर्णांक proto, स्थिर काष्ठा net_proto_family *ops)
अणु
	पूर्णांक err = 0;

	अगर (proto < 0 || proto >= BT_MAX_PROTO)
		वापस -EINVAL;

	ग_लिखो_lock(&bt_proto_lock);

	अगर (bt_proto[proto])
		err = -EEXIST;
	अन्यथा
		bt_proto[proto] = ops;

	ग_लिखो_unlock(&bt_proto_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(bt_sock_रेजिस्टर);

व्योम bt_sock_unरेजिस्टर(पूर्णांक proto)
अणु
	अगर (proto < 0 || proto >= BT_MAX_PROTO)
		वापस;

	ग_लिखो_lock(&bt_proto_lock);
	bt_proto[proto] = शून्य;
	ग_लिखो_unlock(&bt_proto_lock);
पूर्ण
EXPORT_SYMBOL(bt_sock_unरेजिस्टर);

अटल पूर्णांक bt_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक proto,
			  पूर्णांक kern)
अणु
	पूर्णांक err;

	अगर (net != &init_net)
		वापस -EAFNOSUPPORT;

	अगर (proto < 0 || proto >= BT_MAX_PROTO)
		वापस -EINVAL;

	अगर (!bt_proto[proto])
		request_module("bt-proto-%d", proto);

	err = -EPROTONOSUPPORT;

	पढ़ो_lock(&bt_proto_lock);

	अगर (bt_proto[proto] && try_module_get(bt_proto[proto]->owner)) अणु
		err = bt_proto[proto]->create(net, sock, proto, kern);
		अगर (!err)
			bt_sock_reclassअगरy_lock(sock->sk, proto);
		module_put(bt_proto[proto]->owner);
	पूर्ण

	पढ़ो_unlock(&bt_proto_lock);

	वापस err;
पूर्ण

व्योम bt_sock_link(काष्ठा bt_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_add_node(sk, &l->head);
	ग_लिखो_unlock(&l->lock);
पूर्ण
EXPORT_SYMBOL(bt_sock_link);

व्योम bt_sock_unlink(काष्ठा bt_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock(&l->lock);
पूर्ण
EXPORT_SYMBOL(bt_sock_unlink);

व्योम bt_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk, bool bh)
अणु
	BT_DBG("parent %p, sk %p", parent, sk);

	sock_hold(sk);

	अगर (bh)
		bh_lock_sock_nested(sk);
	अन्यथा
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	list_add_tail(&bt_sk(sk)->accept_q, &bt_sk(parent)->accept_q);
	bt_sk(sk)->parent = parent;

	अगर (bh)
		bh_unlock_sock(sk);
	अन्यथा
		release_sock(sk);

	sk_acceptq_added(parent);
पूर्ण
EXPORT_SYMBOL(bt_accept_enqueue);

/* Calling function must hold the sk lock.
 * bt_sk(sk)->parent must be non-शून्य meaning sk is in the parent list.
 */
व्योम bt_accept_unlink(काष्ठा sock *sk)
अणु
	BT_DBG("sk %p state %d", sk, sk->sk_state);

	list_del_init(&bt_sk(sk)->accept_q);
	sk_acceptq_हटाओd(bt_sk(sk)->parent);
	bt_sk(sk)->parent = शून्य;
	sock_put(sk);
पूर्ण
EXPORT_SYMBOL(bt_accept_unlink);

काष्ठा sock *bt_accept_dequeue(काष्ठा sock *parent, काष्ठा socket *newsock)
अणु
	काष्ठा bt_sock *s, *n;
	काष्ठा sock *sk;

	BT_DBG("parent %p", parent);

restart:
	list_क्रम_each_entry_safe(s, n, &bt_sk(parent)->accept_q, accept_q) अणु
		sk = (काष्ठा sock *)s;

		/* Prevent early मुक्तing of sk due to unlink and sock_समाप्त */
		sock_hold(sk);
		lock_sock(sk);

		/* Check sk has not alपढ़ोy been unlinked via
		 * bt_accept_unlink() due to serialisation caused by sk locking
		 */
		अगर (!bt_sk(sk)->parent) अणु
			BT_DBG("sk %p, already unlinked", sk);
			release_sock(sk);
			sock_put(sk);

			/* Restart the loop as sk is no दीर्घer in the list
			 * and also aव्योम a potential infinite loop because
			 * list_क्रम_each_entry_safe() is not thपढ़ो safe.
			 */
			जाओ restart;
		पूर्ण

		/* sk is safely in the parent list so reduce reference count */
		sock_put(sk);

		/* FIXME: Is this check still needed */
		अगर (sk->sk_state == BT_CLOSED) अणु
			bt_accept_unlink(sk);
			release_sock(sk);
			जारी;
		पूर्ण

		अगर (sk->sk_state == BT_CONNECTED || !newsock ||
		    test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags)) अणु
			bt_accept_unlink(sk);
			अगर (newsock)
				sock_graft(sk, newsock);

			release_sock(sk);
			वापस sk;
		पूर्ण

		release_sock(sk);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bt_accept_dequeue);

पूर्णांक bt_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		    पूर्णांक flags)
अणु
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	माप_प्रकार copied;
	माप_प्रकार skblen;
	पूर्णांक err;

	BT_DBG("sock %p sk %p len %zu", sock, sk, len);

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb) अणु
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			वापस 0;

		वापस err;
	पूर्ण

	skblen = skb->len;
	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	skb_reset_transport_header(skb);
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err == 0) अणु
		sock_recv_ts_and_drops(msg, sk, skb);

		अगर (msg->msg_name && bt_sk(sk)->skb_msg_name)
			bt_sk(sk)->skb_msg_name(skb, msg->msg_name,
						&msg->msg_namelen);

		अगर (bt_sk(sk)->skb_put_cmsg)
			bt_sk(sk)->skb_put_cmsg(skb, msg, sk);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	अगर (flags & MSG_TRUNC)
		copied = skblen;

	वापस err ? : copied;
पूर्ण
EXPORT_SYMBOL(bt_sock_recvmsg);

अटल दीर्घ bt_sock_data_रुको(काष्ठा sock *sk, दीर्घ समयo)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue(sk_sleep(sk), &रुको);
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (!skb_queue_empty(&sk->sk_receive_queue))
			अवरोध;

		अगर (sk->sk_err || (sk->sk_shutकरोwn & RCV_SHUTDOWN))
			अवरोध;

		अगर (संकेत_pending(current) || !समयo)
			अवरोध;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock(sk);
		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	पूर्ण

	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस समयo;
पूर्ण

पूर्णांक bt_sock_stream_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			   माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;
	माप_प्रकार target, copied = 0;
	दीर्घ समयo;

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	BT_DBG("sk %p size %zu", sk, size);

	lock_sock(sk);

	target = sock_rcvlowat(sk, flags & MSG_WAITALL, size);
	समयo  = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	करो अणु
		काष्ठा sk_buff *skb;
		पूर्णांक chunk;

		skb = skb_dequeue(&sk->sk_receive_queue);
		अगर (!skb) अणु
			अगर (copied >= target)
				अवरोध;

			err = sock_error(sk);
			अगर (err)
				अवरोध;
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;

			err = -EAGAIN;
			अगर (!समयo)
				अवरोध;

			समयo = bt_sock_data_रुको(sk, समयo);

			अगर (संकेत_pending(current)) अणु
				err = sock_पूर्णांकr_त्रुटि_सं(समयo);
				जाओ out;
			पूर्ण
			जारी;
		पूर्ण

		chunk = min_t(अचिन्हित पूर्णांक, skb->len, size);
		अगर (skb_copy_datagram_msg(skb, 0, msg, chunk)) अणु
			skb_queue_head(&sk->sk_receive_queue, skb);
			अगर (!copied)
				copied = -EFAULT;
			अवरोध;
		पूर्ण
		copied += chunk;
		size   -= chunk;

		sock_recv_ts_and_drops(msg, sk, skb);

		अगर (!(flags & MSG_PEEK)) अणु
			पूर्णांक skb_len = skb_headlen(skb);

			अगर (chunk <= skb_len) अणु
				__skb_pull(skb, chunk);
			पूर्ण अन्यथा अणु
				काष्ठा sk_buff *frag;

				__skb_pull(skb, skb_len);
				chunk -= skb_len;

				skb_walk_frags(skb, frag) अणु
					अगर (chunk <= frag->len) अणु
						/* Pulling partial data */
						skb->len -= chunk;
						skb->data_len -= chunk;
						__skb_pull(frag, chunk);
						अवरोध;
					पूर्ण अन्यथा अगर (frag->len) अणु
						/* Pulling all frag data */
						chunk -= frag->len;
						skb->len -= frag->len;
						skb->data_len -= frag->len;
						__skb_pull(frag, frag->len);
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (skb->len) अणु
				skb_queue_head(&sk->sk_receive_queue, skb);
				अवरोध;
			पूर्ण
			kमुक्त_skb(skb);

		पूर्ण अन्यथा अणु
			/* put message back and वापस */
			skb_queue_head(&sk->sk_receive_queue, skb);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (size);

out:
	release_sock(sk);
	वापस copied ? : err;
पूर्ण
EXPORT_SYMBOL(bt_sock_stream_recvmsg);

अटल अंतरभूत __poll_t bt_accept_poll(काष्ठा sock *parent)
अणु
	काष्ठा bt_sock *s, *n;
	काष्ठा sock *sk;

	list_क्रम_each_entry_safe(s, n, &bt_sk(parent)->accept_q, accept_q) अणु
		sk = (काष्ठा sock *)s;
		अगर (sk->sk_state == BT_CONNECTED ||
		    (test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags) &&
		     sk->sk_state == BT_CONNECT2))
			वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस 0;
पूर्ण

__poll_t bt_sock_poll(काष्ठा file *file, काष्ठा socket *sock,
		      poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask = 0;

	poll_रुको(file, sk_sleep(sk), रुको);

	अगर (sk->sk_state == BT_LISTEN)
		वापस bt_accept_poll(sk);

	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;

	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (sk->sk_state == BT_CLOSED)
		mask |= EPOLLHUP;

	अगर (sk->sk_state == BT_CONNECT ||
	    sk->sk_state == BT_CONNECT2 ||
	    sk->sk_state == BT_CONFIG)
		वापस mask;

	अगर (!test_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags) && sock_ग_लिखोable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
	अन्यथा
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	वापस mask;
पूर्ण
EXPORT_SYMBOL(bt_sock_poll);

पूर्णांक bt_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	दीर्घ amount;
	पूर्णांक err;

	BT_DBG("sk %p cmd %x arg %lx", sk, cmd, arg);

	चयन (cmd) अणु
	हाल TIOCOUTQ:
		अगर (sk->sk_state == BT_LISTEN)
			वापस -EINVAL;

		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;

	हाल TIOCINQ:
		अगर (sk->sk_state == BT_LISTEN)
			वापस -EINVAL;

		lock_sock(sk);
		skb = skb_peek(&sk->sk_receive_queue);
		amount = skb ? skb->len : 0;
		release_sock(sk);
		err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;

	शेष:
		err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(bt_sock_ioctl);

/* This function expects the sk lock to be held when called */
पूर्णांक bt_sock_रुको_state(काष्ठा sock *sk, पूर्णांक state, अचिन्हित दीर्घ समयo)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक err = 0;

	BT_DBG("sk %p", sk);

	add_रुको_queue(sk_sleep(sk), &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (sk->sk_state != state) अणु
		अगर (!समयo) अणु
			err = -EINPROGRESS;
			अवरोध;
		पूर्ण

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
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस err;
पूर्ण
EXPORT_SYMBOL(bt_sock_रुको_state);

/* This function expects the sk lock to be held when called */
पूर्णांक bt_sock_रुको_पढ़ोy(काष्ठा sock *sk, अचिन्हित दीर्घ flags)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ समयo;
	पूर्णांक err = 0;

	BT_DBG("sk %p", sk);

	समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

	add_रुको_queue(sk_sleep(sk), &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (test_bit(BT_SK_SUSPEND, &bt_sk(sk)->flags)) अणु
		अगर (!समयo) अणु
			err = -EAGAIN;
			अवरोध;
		पूर्ण

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
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	वापस err;
पूर्ण
EXPORT_SYMBOL(bt_sock_रुको_पढ़ोy);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *bt_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(seq->निजी->l->lock)
अणु
	काष्ठा bt_sock_list *l = PDE_DATA(file_inode(seq->file));

	पढ़ो_lock(&l->lock);
	वापस seq_hlist_start_head(&l->head, *pos);
पूर्ण

अटल व्योम *bt_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bt_sock_list *l = PDE_DATA(file_inode(seq->file));

	वापस seq_hlist_next(v, &l->head, pos);
पूर्ण

अटल व्योम bt_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(seq->निजी->l->lock)
अणु
	काष्ठा bt_sock_list *l = PDE_DATA(file_inode(seq->file));

	पढ़ो_unlock(&l->lock);
पूर्ण

अटल पूर्णांक bt_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bt_sock_list *l = PDE_DATA(file_inode(seq->file));

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "sk               RefCnt Rmem   Wmem   User   Inode  Parent");

		अगर (l->custom_seq_show) अणु
			seq_अ_दो(seq, ' ');
			l->custom_seq_show(seq, v);
		पूर्ण

		seq_अ_दो(seq, '\n');
	पूर्ण अन्यथा अणु
		काष्ठा sock *sk = sk_entry(v);
		काष्ठा bt_sock *bt = bt_sk(sk);

		seq_म_लिखो(seq,
			   "%pK %-6d %-6u %-6u %-6u %-6lu %-6lu",
			   sk,
			   refcount_पढ़ो(&sk->sk_refcnt),
			   sk_rmem_alloc_get(sk),
			   sk_wmem_alloc_get(sk),
			   from_kuid(seq_user_ns(seq), sock_i_uid(sk)),
			   sock_i_ino(sk),
			   bt->parent ? sock_i_ino(bt->parent) : 0LU);

		अगर (l->custom_seq_show) अणु
			seq_अ_दो(seq, ' ');
			l->custom_seq_show(seq, v);
		पूर्ण

		seq_अ_दो(seq, '\n');
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations bt_seq_ops = अणु
	.start = bt_seq_start,
	.next  = bt_seq_next,
	.stop  = bt_seq_stop,
	.show  = bt_seq_show,
पूर्ण;

पूर्णांक bt_procfs_init(काष्ठा net *net, स्थिर अक्षर *name,
		   काष्ठा bt_sock_list *sk_list,
		   पूर्णांक (*seq_show)(काष्ठा seq_file *, व्योम *))
अणु
	sk_list->custom_seq_show = seq_show;

	अगर (!proc_create_seq_data(name, 0, net->proc_net, &bt_seq_ops, sk_list))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम bt_procfs_cleanup(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	हटाओ_proc_entry(name, net->proc_net);
पूर्ण
#अन्यथा
पूर्णांक bt_procfs_init(काष्ठा net *net, स्थिर अक्षर *name,
		   काष्ठा bt_sock_list *sk_list,
		   पूर्णांक (*seq_show)(काष्ठा seq_file *, व्योम *))
अणु
	वापस 0;
पूर्ण

व्योम bt_procfs_cleanup(काष्ठा net *net, स्थिर अक्षर *name)
अणु
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(bt_procfs_init);
EXPORT_SYMBOL(bt_procfs_cleanup);

अटल स्थिर काष्ठा net_proto_family bt_sock_family_ops = अणु
	.owner	= THIS_MODULE,
	.family	= PF_BLUETOOTH,
	.create	= bt_sock_create,
पूर्ण;

काष्ठा dentry *bt_debugfs;
EXPORT_SYMBOL_GPL(bt_debugfs);

#घोषणा VERSION __stringअगरy(BT_SUBSYS_VERSION) "." \
		__stringअगरy(BT_SUBSYS_REVISION)

अटल पूर्णांक __init bt_init(व्योम)
अणु
	पूर्णांक err;

	sock_skb_cb_check_size(माप(काष्ठा bt_skb_cb));

	BT_INFO("Core ver %s", VERSION);

	err = bt_selftest();
	अगर (err < 0)
		वापस err;

	bt_debugfs = debugfs_create_dir("bluetooth", शून्य);

	bt_leds_init();

	err = bt_sysfs_init();
	अगर (err < 0)
		वापस err;

	err = sock_रेजिस्टर(&bt_sock_family_ops);
	अगर (err)
		जाओ cleanup_sysfs;

	BT_INFO("HCI device and connection manager initialized");

	err = hci_sock_init();
	अगर (err)
		जाओ unरेजिस्टर_socket;

	err = l2cap_init();
	अगर (err)
		जाओ cleanup_socket;

	err = sco_init();
	अगर (err)
		जाओ cleanup_cap;

	err = mgmt_init();
	अगर (err)
		जाओ cleanup_sco;

	वापस 0;

cleanup_sco:
	sco_निकास();
cleanup_cap:
	l2cap_निकास();
cleanup_socket:
	hci_sock_cleanup();
unरेजिस्टर_socket:
	sock_unरेजिस्टर(PF_BLUETOOTH);
cleanup_sysfs:
	bt_sysfs_cleanup();
	वापस err;
पूर्ण

अटल व्योम __निकास bt_निकास(व्योम)
अणु
	mgmt_निकास();

	sco_निकास();

	l2cap_निकास();

	hci_sock_cleanup();

	sock_unरेजिस्टर(PF_BLUETOOTH);

	bt_sysfs_cleanup();

	bt_leds_cleanup();

	debugfs_हटाओ_recursive(bt_debugfs);
पूर्ण

subsys_initcall(bt_init);
module_निकास(bt_निकास);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth Core ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_BLUETOOTH);
