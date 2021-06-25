<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "llcp: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "nfc.h"
#समावेश "llcp.h"

अटल पूर्णांक sock_रुको_state(काष्ठा sock *sk, पूर्णांक state, अचिन्हित दीर्घ समयo)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक err = 0;

	pr_debug("sk %p", sk);

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

अटल काष्ठा proto llcp_sock_proto = अणु
	.name     = "NFC_LLCP",
	.owner    = THIS_MODULE,
	.obj_size = माप(काष्ठा nfc_llcp_sock),
पूर्ण;

अटल पूर्णांक llcp_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक alen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	काष्ठा nfc_llcp_local *local;
	काष्ठा nfc_dev *dev;
	काष्ठा sockaddr_nfc_llcp llcp_addr;
	पूर्णांक len, ret = 0;

	अगर (!addr || alen < दुरत्वend(काष्ठा sockaddr, sa_family) ||
	    addr->sa_family != AF_NFC)
		वापस -EINVAL;

	pr_debug("sk %p addr %p family %d\n", sk, addr, addr->sa_family);

	स_रखो(&llcp_addr, 0, माप(llcp_addr));
	len = min_t(अचिन्हित पूर्णांक, माप(llcp_addr), alen);
	स_नकल(&llcp_addr, addr, len);

	/* This is going to be a listening socket, dsap must be 0 */
	अगर (llcp_addr.dsap != 0)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (sk->sk_state != LLCP_CLOSED) अणु
		ret = -EBADFD;
		जाओ error;
	पूर्ण

	dev = nfc_get_device(llcp_addr.dev_idx);
	अगर (dev == शून्य) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		ret = -ENODEV;
		जाओ put_dev;
	पूर्ण

	llcp_sock->dev = dev;
	llcp_sock->local = nfc_llcp_local_get(local);
	llcp_sock->nfc_protocol = llcp_addr.nfc_protocol;
	llcp_sock->service_name_len = min_t(अचिन्हित पूर्णांक,
					    llcp_addr.service_name_len,
					    NFC_LLCP_MAX_SERVICE_NAME);
	llcp_sock->service_name = kmemdup(llcp_addr.service_name,
					  llcp_sock->service_name_len,
					  GFP_KERNEL);
	अगर (!llcp_sock->service_name) अणु
		nfc_llcp_local_put(llcp_sock->local);
		llcp_sock->local = शून्य;
		llcp_sock->dev = शून्य;
		ret = -ENOMEM;
		जाओ put_dev;
	पूर्ण
	llcp_sock->ssap = nfc_llcp_get_sdp_ssap(local, llcp_sock);
	अगर (llcp_sock->ssap == LLCP_SAP_MAX) अणु
		nfc_llcp_local_put(llcp_sock->local);
		llcp_sock->local = शून्य;
		kमुक्त(llcp_sock->service_name);
		llcp_sock->service_name = शून्य;
		llcp_sock->dev = शून्य;
		ret = -EADDRINUSE;
		जाओ put_dev;
	पूर्ण

	llcp_sock->reserved_ssap = llcp_sock->ssap;

	nfc_llcp_sock_link(&local->sockets, sk);

	pr_debug("Socket bound to SAP %d\n", llcp_sock->ssap);

	sk->sk_state = LLCP_BOUND;

put_dev:
	nfc_put_device(dev);

error:
	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक llcp_raw_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			      पूर्णांक alen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	काष्ठा nfc_llcp_local *local;
	काष्ठा nfc_dev *dev;
	काष्ठा sockaddr_nfc_llcp llcp_addr;
	पूर्णांक len, ret = 0;

	अगर (!addr || alen < दुरत्वend(काष्ठा sockaddr, sa_family) ||
	    addr->sa_family != AF_NFC)
		वापस -EINVAL;

	pr_debug("sk %p addr %p family %d\n", sk, addr, addr->sa_family);

	स_रखो(&llcp_addr, 0, माप(llcp_addr));
	len = min_t(अचिन्हित पूर्णांक, माप(llcp_addr), alen);
	स_नकल(&llcp_addr, addr, len);

	lock_sock(sk);

	अगर (sk->sk_state != LLCP_CLOSED) अणु
		ret = -EBADFD;
		जाओ error;
	पूर्ण

	dev = nfc_get_device(llcp_addr.dev_idx);
	अगर (dev == शून्य) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		ret = -ENODEV;
		जाओ put_dev;
	पूर्ण

	llcp_sock->dev = dev;
	llcp_sock->local = nfc_llcp_local_get(local);
	llcp_sock->nfc_protocol = llcp_addr.nfc_protocol;

	nfc_llcp_sock_link(&local->raw_sockets, sk);

	sk->sk_state = LLCP_BOUND;

put_dev:
	nfc_put_device(dev);

error:
	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक llcp_sock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret = 0;

	pr_debug("sk %p backlog %d\n", sk, backlog);

	lock_sock(sk);

	अगर ((sock->type != SOCK_SEQPACKET && sock->type != SOCK_STREAM) ||
	    sk->sk_state != LLCP_BOUND) अणु
		ret = -EBADFD;
		जाओ error;
	पूर्ण

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;

	pr_debug("Socket listening\n");
	sk->sk_state = LLCP_LISTEN;

error:
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक nfc_llcp_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	u32 opt;
	पूर्णांक err = 0;

	pr_debug("%p optname %d\n", sk, optname);

	अगर (level != SOL_NFC)
		वापस -ENOPROTOOPT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल NFC_LLCP_RW:
		अगर (sk->sk_state == LLCP_CONNECTED ||
		    sk->sk_state == LLCP_BOUND ||
		    sk->sk_state == LLCP_LISTEN) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt > LLCP_MAX_RW) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		llcp_sock->rw = (u8) opt;

		अवरोध;

	हाल NFC_LLCP_MIUX:
		अगर (sk->sk_state == LLCP_CONNECTED ||
		    sk->sk_state == LLCP_BOUND ||
		    sk->sk_state == LLCP_LISTEN) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_sockptr(&opt, optval, माप(u32))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt > LLCP_MAX_MIUX) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		llcp_sock->miux = cpu_to_be16((u16) opt);

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);

	pr_debug("%p rw %d miux %d\n", llcp_sock,
		 llcp_sock->rw, llcp_sock->miux);

	वापस err;
पूर्ण

अटल पूर्णांक nfc_llcp_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा nfc_llcp_local *local;
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	पूर्णांक len, err = 0;
	u16 miux, remote_miu;
	u8 rw;

	pr_debug("%p optname %d\n", sk, optname);

	अगर (level != SOL_NFC)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	local = llcp_sock->local;
	अगर (!local)
		वापस -ENODEV;

	len = min_t(u32, len, माप(u32));

	lock_sock(sk);

	चयन (optname) अणु
	हाल NFC_LLCP_RW:
		rw = llcp_sock->rw > LLCP_MAX_RW ? local->rw : llcp_sock->rw;
		अगर (put_user(rw, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल NFC_LLCP_MIUX:
		miux = be16_to_cpu(llcp_sock->miux) > LLCP_MAX_MIUX ?
			be16_to_cpu(local->miux) : be16_to_cpu(llcp_sock->miux);

		अगर (put_user(miux, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल NFC_LLCP_REMOTE_MIU:
		remote_miu = llcp_sock->remote_miu > LLCP_MAX_MIU ?
				local->remote_miu : llcp_sock->remote_miu;

		अगर (put_user(remote_miu, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल NFC_LLCP_REMOTE_LTO:
		अगर (put_user(local->remote_lto / 10, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	हाल NFC_LLCP_REMOTE_RW:
		अगर (put_user(llcp_sock->remote_rw, (u32 __user *) optval))
			err = -EFAULT;

		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस err;
पूर्ण

व्योम nfc_llcp_accept_unlink(काष्ठा sock *sk)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);

	pr_debug("state %d\n", sk->sk_state);

	list_del_init(&llcp_sock->accept_queue);
	sk_acceptq_हटाओd(llcp_sock->parent);
	llcp_sock->parent = शून्य;

	sock_put(sk);
पूर्ण

व्योम nfc_llcp_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	काष्ठा nfc_llcp_sock *llcp_sock_parent = nfc_llcp_sock(parent);

	/* Lock will be मुक्त from unlink */
	sock_hold(sk);

	list_add_tail(&llcp_sock->accept_queue,
		      &llcp_sock_parent->accept_queue);
	llcp_sock->parent = parent;
	sk_acceptq_added(parent);
पूर्ण

काष्ठा sock *nfc_llcp_accept_dequeue(काष्ठा sock *parent,
				     काष्ठा socket *newsock)
अणु
	काष्ठा nfc_llcp_sock *lsk, *n, *llcp_parent;
	काष्ठा sock *sk;

	llcp_parent = nfc_llcp_sock(parent);

	list_क्रम_each_entry_safe(lsk, n, &llcp_parent->accept_queue,
				 accept_queue) अणु
		sk = &lsk->sk;
		lock_sock(sk);

		अगर (sk->sk_state == LLCP_CLOSED) अणु
			release_sock(sk);
			nfc_llcp_accept_unlink(sk);
			जारी;
		पूर्ण

		अगर (sk->sk_state == LLCP_CONNECTED || !newsock) अणु
			list_del_init(&lsk->accept_queue);
			sock_put(sk);

			अगर (newsock)
				sock_graft(sk, newsock);

			release_sock(sk);

			pr_debug("Returning sk state %d\n", sk->sk_state);

			sk_acceptq_हटाओd(parent);

			वापस sk;
		पूर्ण

		release_sock(sk);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक llcp_sock_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			    पूर्णांक flags, bool kern)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा sock *sk = sock->sk, *new_sk;
	दीर्घ समयo;
	पूर्णांक ret = 0;

	pr_debug("parent %p\n", sk);

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	अगर (sk->sk_state != LLCP_LISTEN) अणु
		ret = -EBADFD;
		जाओ error;
	पूर्ण

	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

	/* Wait क्रम an incoming connection. */
	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	जबतक (!(new_sk = nfc_llcp_accept_dequeue(sk, newsock))) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (!समयo) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			ret = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण

		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (ret)
		जाओ error;

	newsock->state = SS_CONNECTED;

	pr_debug("new socket %p\n", new_sk);

error:
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक llcp_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			     पूर्णांक peer)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_nfc_llcp *, llcp_addr, uaddr);

	अगर (llcp_sock == शून्य || llcp_sock->dev == शून्य)
		वापस -EBADFD;

	pr_debug("%p %d %d %d\n", sk, llcp_sock->target_idx,
		 llcp_sock->dsap, llcp_sock->ssap);

	स_रखो(llcp_addr, 0, माप(*llcp_addr));

	lock_sock(sk);
	अगर (!llcp_sock->dev) अणु
		release_sock(sk);
		वापस -EBADFD;
	पूर्ण
	llcp_addr->sa_family = AF_NFC;
	llcp_addr->dev_idx = llcp_sock->dev->idx;
	llcp_addr->target_idx = llcp_sock->target_idx;
	llcp_addr->nfc_protocol = llcp_sock->nfc_protocol;
	llcp_addr->dsap = llcp_sock->dsap;
	llcp_addr->ssap = llcp_sock->ssap;
	llcp_addr->service_name_len = llcp_sock->service_name_len;
	स_नकल(llcp_addr->service_name, llcp_sock->service_name,
	       llcp_addr->service_name_len);
	release_sock(sk);

	वापस माप(काष्ठा sockaddr_nfc_llcp);
पूर्ण

अटल अंतरभूत __poll_t llcp_accept_poll(काष्ठा sock *parent)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock, *parent_sock;
	काष्ठा sock *sk;

	parent_sock = nfc_llcp_sock(parent);

	list_क्रम_each_entry(llcp_sock, &parent_sock->accept_queue,
			    accept_queue) अणु
		sk = &llcp_sock->sk;

		अगर (sk->sk_state == LLCP_CONNECTED)
			वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस 0;
पूर्ण

अटल __poll_t llcp_sock_poll(काष्ठा file *file, काष्ठा socket *sock,
				   poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask = 0;

	pr_debug("%p\n", sk);

	sock_poll_रुको(file, sock, रुको);

	अगर (sk->sk_state == LLCP_LISTEN)
		वापस llcp_accept_poll(sk);

	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);

	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (sk->sk_state == LLCP_CLOSED)
		mask |= EPOLLHUP;

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;

	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	अगर (sock_ग_लिखोable(sk) && sk->sk_state == LLCP_CONNECTED)
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
	अन्यथा
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	pr_debug("mask 0x%x\n", mask);

	वापस mask;
पूर्ण

अटल पूर्णांक llcp_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_local *local;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	पूर्णांक err = 0;

	अगर (!sk)
		वापस 0;

	pr_debug("%p\n", sk);

	local = llcp_sock->local;
	अगर (local == शून्य) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	lock_sock(sk);

	/* Send a DISC */
	अगर (sk->sk_state == LLCP_CONNECTED)
		nfc_llcp_send_disconnect(llcp_sock);

	अगर (sk->sk_state == LLCP_LISTEN) अणु
		काष्ठा nfc_llcp_sock *lsk, *n;
		काष्ठा sock *accept_sk;

		list_क्रम_each_entry_safe(lsk, n, &llcp_sock->accept_queue,
					 accept_queue) अणु
			accept_sk = &lsk->sk;
			lock_sock(accept_sk);

			nfc_llcp_send_disconnect(lsk);
			nfc_llcp_accept_unlink(accept_sk);

			release_sock(accept_sk);
		पूर्ण
	पूर्ण

	अगर (llcp_sock->reserved_ssap < LLCP_SAP_MAX)
		nfc_llcp_put_ssap(llcp_sock->local, llcp_sock->ssap);

	release_sock(sk);

	/* Keep this sock alive and thereक्रमe करो not हटाओ it from the sockets
	 * list until the DISC PDU has been actually sent. Otherwise we would
	 * reply with DM PDUs beक्रमe sending the DISC one.
	 */
	अगर (sk->sk_state == LLCP_DISCONNECTING)
		वापस err;

	अगर (sock->type == SOCK_RAW)
		nfc_llcp_sock_unlink(&local->raw_sockets, sk);
	अन्यथा
		nfc_llcp_sock_unlink(&local->sockets, sk);

out:
	sock_orphan(sk);
	sock_put(sk);

	वापस err;
पूर्ण

अटल पूर्णांक llcp_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *_addr,
			     पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	काष्ठा sockaddr_nfc_llcp *addr = (काष्ठा sockaddr_nfc_llcp *)_addr;
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;
	पूर्णांक ret = 0;

	pr_debug("sock %p sk %p flags 0x%x\n", sock, sk, flags);

	अगर (!addr || len < माप(*addr) || addr->sa_family != AF_NFC)
		वापस -EINVAL;

	अगर (addr->service_name_len == 0 && addr->dsap == 0)
		वापस -EINVAL;

	pr_debug("addr dev_idx=%u target_idx=%u protocol=%u\n", addr->dev_idx,
		 addr->target_idx, addr->nfc_protocol);

	lock_sock(sk);

	अगर (sk->sk_state == LLCP_CONNECTED) अणु
		ret = -EISCONN;
		जाओ error;
	पूर्ण
	अगर (sk->sk_state == LLCP_CONNECTING) अणु
		ret = -EINPROGRESS;
		जाओ error;
	पूर्ण

	dev = nfc_get_device(addr->dev_idx);
	अगर (dev == शून्य) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		ret = -ENODEV;
		जाओ put_dev;
	पूर्ण

	device_lock(&dev->dev);
	अगर (dev->dep_link_up == false) अणु
		ret = -ENOLINK;
		device_unlock(&dev->dev);
		जाओ put_dev;
	पूर्ण
	device_unlock(&dev->dev);

	अगर (local->rf_mode == NFC_RF_INITIATOR &&
	    addr->target_idx != local->target_idx) अणु
		ret = -ENOLINK;
		जाओ put_dev;
	पूर्ण

	llcp_sock->dev = dev;
	llcp_sock->local = nfc_llcp_local_get(local);
	llcp_sock->ssap = nfc_llcp_get_local_ssap(local);
	अगर (llcp_sock->ssap == LLCP_SAP_MAX) अणु
		nfc_llcp_local_put(llcp_sock->local);
		llcp_sock->local = शून्य;
		ret = -ENOMEM;
		जाओ put_dev;
	पूर्ण

	llcp_sock->reserved_ssap = llcp_sock->ssap;

	अगर (addr->service_name_len == 0)
		llcp_sock->dsap = addr->dsap;
	अन्यथा
		llcp_sock->dsap = LLCP_SAP_SDP;
	llcp_sock->nfc_protocol = addr->nfc_protocol;
	llcp_sock->service_name_len = min_t(अचिन्हित पूर्णांक,
					    addr->service_name_len,
					    NFC_LLCP_MAX_SERVICE_NAME);
	llcp_sock->service_name = kmemdup(addr->service_name,
					  llcp_sock->service_name_len,
					  GFP_KERNEL);
	अगर (!llcp_sock->service_name) अणु
		ret = -ENOMEM;
		जाओ sock_llcp_release;
	पूर्ण

	nfc_llcp_sock_link(&local->connecting_sockets, sk);

	ret = nfc_llcp_send_connect(llcp_sock);
	अगर (ret)
		जाओ sock_unlink;

	sk->sk_state = LLCP_CONNECTING;

	ret = sock_रुको_state(sk, LLCP_CONNECTED,
			      sock_sndसमयo(sk, flags & O_NONBLOCK));
	अगर (ret && ret != -EINPROGRESS)
		जाओ sock_unlink;

	release_sock(sk);

	वापस ret;

sock_unlink:
	nfc_llcp_sock_unlink(&local->connecting_sockets, sk);
	kमुक्त(llcp_sock->service_name);
	llcp_sock->service_name = शून्य;

sock_llcp_release:
	nfc_llcp_put_ssap(local, llcp_sock->ssap);
	nfc_llcp_local_put(llcp_sock->local);
	llcp_sock->local = शून्य;

put_dev:
	nfc_put_device(dev);

error:
	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक llcp_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			     माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	पूर्णांक ret;

	pr_debug("sock %p sk %p", sock, sk);

	ret = sock_error(sk);
	अगर (ret)
		वापस ret;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	अगर (sk->sk_type == SOCK_DGRAM) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_nfc_llcp *, addr,
				 msg->msg_name);

		अगर (msg->msg_namelen < माप(*addr)) अणु
			release_sock(sk);
			वापस -EINVAL;
		पूर्ण

		release_sock(sk);

		वापस nfc_llcp_send_ui_frame(llcp_sock, addr->dsap, addr->ssap,
					      msg, len);
	पूर्ण

	अगर (sk->sk_state != LLCP_CONNECTED) अणु
		release_sock(sk);
		वापस -ENOTCONN;
	पूर्ण

	release_sock(sk);

	वापस nfc_llcp_send_i_frame(llcp_sock, msg, len);
पूर्ण

अटल पूर्णांक llcp_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			     माप_प्रकार len, पूर्णांक flags)
अणु
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sock *sk = sock->sk;
	अचिन्हित पूर्णांक copied, rlen;
	काष्ठा sk_buff *skb, *cskb;
	पूर्णांक err = 0;

	pr_debug("%p %zu\n", sk, len);

	lock_sock(sk);

	अगर (sk->sk_state == LLCP_CLOSED &&
	    skb_queue_empty(&sk->sk_receive_queue)) अणु
		release_sock(sk);
		वापस 0;
	पूर्ण

	release_sock(sk);

	अगर (flags & (MSG_OOB))
		वापस -EOPNOTSUPP;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb) अणु
		pr_err("Recv datagram failed state %d %d %d",
		       sk->sk_state, err, sock_error(sk));

		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			वापस 0;

		वापस err;
	पूर्ण

	rlen = skb->len;		/* real length of skb */
	copied = min_t(अचिन्हित पूर्णांक, rlen, len);

	cskb = skb;
	अगर (skb_copy_datagram_msg(cskb, 0, msg, copied)) अणु
		अगर (!(flags & MSG_PEEK))
			skb_queue_head(&sk->sk_receive_queue, skb);
		वापस -EFAULT;
	पूर्ण

	sock_recv_बारtamp(msg, sk, skb);

	अगर (sk->sk_type == SOCK_DGRAM && msg->msg_name) अणु
		काष्ठा nfc_llcp_ui_cb *ui_cb = nfc_llcp_ui_skb_cb(skb);
		DECLARE_SOCKADDR(काष्ठा sockaddr_nfc_llcp *, sockaddr,
				 msg->msg_name);

		msg->msg_namelen = माप(काष्ठा sockaddr_nfc_llcp);

		pr_debug("Datagram socket %d %d\n", ui_cb->dsap, ui_cb->ssap);

		स_रखो(sockaddr, 0, माप(*sockaddr));
		sockaddr->sa_family = AF_NFC;
		sockaddr->nfc_protocol = NFC_PROTO_NFC_DEP;
		sockaddr->dsap = ui_cb->dsap;
		sockaddr->ssap = ui_cb->ssap;
	पूर्ण

	/* Mark पढ़ो part of skb as used */
	अगर (!(flags & MSG_PEEK)) अणु

		/* SOCK_STREAM: re-queue skb अगर it contains unreceived data */
		अगर (sk->sk_type == SOCK_STREAM ||
		    sk->sk_type == SOCK_DGRAM ||
		    sk->sk_type == SOCK_RAW) अणु
			skb_pull(skb, copied);
			अगर (skb->len) अणु
				skb_queue_head(&sk->sk_receive_queue, skb);
				जाओ करोne;
			पूर्ण
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण

	/* XXX Queue backlogged skbs */

करोne:
	/* SOCK_SEQPACKET: वापस real length अगर MSG_TRUNC is set */
	अगर (sk->sk_type == SOCK_SEQPACKET && (flags & MSG_TRUNC))
		copied = rlen;

	वापस copied;
पूर्ण

अटल स्थिर काष्ठा proto_ops llcp_sock_ops = अणु
	.family         = PF_NFC,
	.owner          = THIS_MODULE,
	.bind           = llcp_sock_bind,
	.connect        = llcp_sock_connect,
	.release        = llcp_sock_release,
	.socketpair     = sock_no_socketpair,
	.accept         = llcp_sock_accept,
	.getname        = llcp_sock_getname,
	.poll           = llcp_sock_poll,
	.ioctl          = sock_no_ioctl,
	.listen         = llcp_sock_listen,
	.shutकरोwn       = sock_no_shutकरोwn,
	.setsockopt     = nfc_llcp_setsockopt,
	.माला_लोockopt     = nfc_llcp_माला_लोockopt,
	.sendmsg        = llcp_sock_sendmsg,
	.recvmsg        = llcp_sock_recvmsg,
	.mmap           = sock_no_mmap,
पूर्ण;

अटल स्थिर काष्ठा proto_ops llcp_rawsock_ops = अणु
	.family         = PF_NFC,
	.owner          = THIS_MODULE,
	.bind           = llcp_raw_sock_bind,
	.connect        = sock_no_connect,
	.release        = llcp_sock_release,
	.socketpair     = sock_no_socketpair,
	.accept         = sock_no_accept,
	.getname        = llcp_sock_getname,
	.poll           = llcp_sock_poll,
	.ioctl          = sock_no_ioctl,
	.listen         = sock_no_listen,
	.shutकरोwn       = sock_no_shutकरोwn,
	.sendmsg        = sock_no_sendmsg,
	.recvmsg        = llcp_sock_recvmsg,
	.mmap           = sock_no_mmap,
पूर्ण;

अटल व्योम llcp_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);

	pr_debug("%p\n", sk);

	अगर (sk->sk_state == LLCP_CONNECTED)
		nfc_put_device(llcp_sock->dev);

	skb_queue_purge(&sk->sk_receive_queue);

	nfc_llcp_sock_मुक्त(llcp_sock);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Freeing alive NFC LLCP socket %p\n", sk);
		वापस;
	पूर्ण
पूर्ण

काष्ठा sock *nfc_llcp_sock_alloc(काष्ठा socket *sock, पूर्णांक type, gfp_t gfp, पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा nfc_llcp_sock *llcp_sock;

	sk = sk_alloc(&init_net, PF_NFC, gfp, &llcp_sock_proto, kern);
	अगर (!sk)
		वापस शून्य;

	llcp_sock = nfc_llcp_sock(sk);

	sock_init_data(sock, sk);
	sk->sk_state = LLCP_CLOSED;
	sk->sk_protocol = NFC_SOCKPROTO_LLCP;
	sk->sk_type = type;
	sk->sk_deकाष्ठा = llcp_sock_deकाष्ठा;

	llcp_sock->ssap = 0;
	llcp_sock->dsap = LLCP_SAP_SDP;
	llcp_sock->rw = LLCP_MAX_RW + 1;
	llcp_sock->miux = cpu_to_be16(LLCP_MAX_MIUX + 1);
	llcp_sock->send_n = llcp_sock->send_ack_n = 0;
	llcp_sock->recv_n = llcp_sock->recv_ack_n = 0;
	llcp_sock->remote_पढ़ोy = 1;
	llcp_sock->reserved_ssap = LLCP_SAP_MAX;
	nfc_llcp_socket_remote_param_init(llcp_sock);
	skb_queue_head_init(&llcp_sock->tx_queue);
	skb_queue_head_init(&llcp_sock->tx_pending_queue);
	INIT_LIST_HEAD(&llcp_sock->accept_queue);

	अगर (sock != शून्य)
		sock->state = SS_UNCONNECTED;

	वापस sk;
पूर्ण

व्योम nfc_llcp_sock_मुक्त(काष्ठा nfc_llcp_sock *sock)
अणु
	kमुक्त(sock->service_name);

	skb_queue_purge(&sock->tx_queue);
	skb_queue_purge(&sock->tx_pending_queue);

	list_del_init(&sock->accept_queue);

	sock->parent = शून्य;

	nfc_llcp_local_put(sock->local);
पूर्ण

अटल पूर्णांक llcp_sock_create(काष्ठा net *net, काष्ठा socket *sock,
			    स्थिर काष्ठा nfc_protocol *nfc_proto, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	pr_debug("%p\n", sock);

	अगर (sock->type != SOCK_STREAM &&
	    sock->type != SOCK_DGRAM &&
	    sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	अगर (sock->type == SOCK_RAW) अणु
		अगर (!capable(CAP_NET_RAW))
			वापस -EPERM;
		sock->ops = &llcp_rawsock_ops;
	पूर्ण अन्यथा अणु
		sock->ops = &llcp_sock_ops;
	पूर्ण

	sk = nfc_llcp_sock_alloc(sock, sock->type, GFP_ATOMIC, kern);
	अगर (sk == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nfc_protocol llcp_nfc_proto = अणु
	.id	  = NFC_SOCKPROTO_LLCP,
	.proto    = &llcp_sock_proto,
	.owner    = THIS_MODULE,
	.create   = llcp_sock_create
पूर्ण;

पूर्णांक __init nfc_llcp_sock_init(व्योम)
अणु
	वापस nfc_proto_रेजिस्टर(&llcp_nfc_proto);
पूर्ण

व्योम nfc_llcp_sock_निकास(व्योम)
अणु
	nfc_proto_unरेजिस्टर(&llcp_nfc_proto);
पूर्ण
