<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *     SUCS NET3:
 *
 *     Generic stream handling routines. These are generic क्रम most
 *     protocols. Even IP. Tonight 8-).
 *     This is used because TCP, LLC (others too) layer all have mostly
 *     identical sendmsg() and recvmsg() code.
 *     So we (will) share it here.
 *
 *     Authors:        Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *                     (from old tcp.c code)
 *                     Alan Cox <alan@lxorguk.ukuu.org.uk> (Borrowed comments 8-))
 */

#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/net.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/tcp.h>
#समावेश <linux/रुको.h>
#समावेश <net/sock.h>

/**
 * sk_stream_ग_लिखो_space - stream socket ग_लिखो_space callback.
 * @sk: socket
 *
 * FIXME: ग_लिखो proper description
 */
व्योम sk_stream_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket *sock = sk->sk_socket;
	काष्ठा socket_wq *wq;

	अगर (__sk_stream_is_ग_लिखोable(sk, 1) && sock) अणु
		clear_bit(SOCK_NOSPACE, &sock->flags);

		rcu_पढ़ो_lock();
		wq = rcu_dereference(sk->sk_wq);
		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible_poll(&wq->रुको, EPOLLOUT |
						EPOLLWRNORM | EPOLLWRBAND);
		अगर (wq && wq->fasync_list && !(sk->sk_shutकरोwn & SEND_SHUTDOWN))
			sock_wake_async(wq, SOCK_WAKE_SPACE, POLL_OUT);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * sk_stream_रुको_connect - Wait क्रम a socket to get पूर्णांकo the connected state
 * @sk: sock to रुको on
 * @समयo_p: क्रम how दीर्घ to रुको
 *
 * Must be called with the socket locked.
 */
पूर्णांक sk_stream_रुको_connect(काष्ठा sock *sk, दीर्घ *समयo_p)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक करोne;

	करो अणु
		पूर्णांक err = sock_error(sk);
		अगर (err)
			वापस err;
		अगर ((1 << sk->sk_state) & ~(TCPF_SYN_SENT | TCPF_SYN_RECV))
			वापस -EPIPE;
		अगर (!*समयo_p)
			वापस -EAGAIN;
		अगर (संकेत_pending(tsk))
			वापस sock_पूर्णांकr_त्रुटि_सं(*समयo_p);

		add_रुको_queue(sk_sleep(sk), &रुको);
		sk->sk_ग_लिखो_pending++;
		करोne = sk_रुको_event(sk, समयo_p,
				     !sk->sk_err &&
				     !((1 << sk->sk_state) &
				       ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)), &रुको);
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);
		sk->sk_ग_लिखो_pending--;
	पूर्ण जबतक (!करोne);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sk_stream_रुको_connect);

/**
 * sk_stream_closing - Return 1 अगर we still have things to send in our buffers.
 * @sk: socket to verअगरy
 */
अटल अंतरभूत पूर्णांक sk_stream_closing(काष्ठा sock *sk)
अणु
	वापस (1 << sk->sk_state) &
	       (TCPF_FIN_WAIT1 | TCPF_CLOSING | TCPF_LAST_ACK);
पूर्ण

व्योम sk_stream_रुको_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	अगर (समयout) अणु
		DEFINE_WAIT_FUNC(रुको, woken_wake_function);

		add_रुको_queue(sk_sleep(sk), &रुको);

		करो अणु
			अगर (sk_रुको_event(sk, &समयout, !sk_stream_closing(sk), &रुको))
				अवरोध;
		पूर्ण जबतक (!संकेत_pending(current) && समयout);

		हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sk_stream_रुको_बंद);

/**
 * sk_stream_रुको_memory - Wait क्रम more memory क्रम a socket
 * @sk: socket to रुको क्रम memory
 * @समयo_p: क्रम how दीर्घ
 */
पूर्णांक sk_stream_रुको_memory(काष्ठा sock *sk, दीर्घ *समयo_p)
अणु
	पूर्णांक err = 0;
	दीर्घ vm_रुको = 0;
	दीर्घ current_समयo = *समयo_p;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	अगर (sk_stream_memory_मुक्त(sk))
		current_समयo = vm_रुको = (pअक्रमom_u32() % (HZ / 5)) + 2;

	add_रुको_queue(sk_sleep(sk), &रुको);

	जबतक (1) अणु
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

		अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN))
			जाओ करो_error;
		अगर (!*समयo_p)
			जाओ करो_eagain;
		अगर (संकेत_pending(current))
			जाओ करो_पूर्णांकerrupted;
		sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		अगर (sk_stream_memory_मुक्त(sk) && !vm_रुको)
			अवरोध;

		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk->sk_ग_लिखो_pending++;
		sk_रुको_event(sk, &current_समयo, sk->sk_err ||
						  (sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
						  (sk_stream_memory_मुक्त(sk) &&
						  !vm_रुको), &रुको);
		sk->sk_ग_लिखो_pending--;

		अगर (vm_रुको) अणु
			vm_रुको -= current_समयo;
			current_समयo = *समयo_p;
			अगर (current_समयo != MAX_SCHEDULE_TIMEOUT &&
			    (current_समयo -= vm_रुको) < 0)
				current_समयo = 0;
			vm_रुको = 0;
		पूर्ण
		*समयo_p = current_समयo;
	पूर्ण
out:
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस err;

करो_error:
	err = -EPIPE;
	जाओ out;
करो_eagain:
	/* Make sure that whenever EAGAIN is वापसed, EPOLLOUT event can
	 * be generated later.
	 * When TCP receives ACK packets that make room, tcp_check_space()
	 * only calls tcp_new_space() अगर SOCK_NOSPACE is set.
	 */
	set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
	err = -EAGAIN;
	जाओ out;
करो_पूर्णांकerrupted:
	err = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(sk_stream_रुको_memory);

पूर्णांक sk_stream_error(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक err)
अणु
	अगर (err == -EPIPE)
		err = sock_error(sk) ? : -EPIPE;
	अगर (err == -EPIPE && !(flags & MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	वापस err;
पूर्ण
EXPORT_SYMBOL(sk_stream_error);

व्योम sk_stream_समाप्त_queues(काष्ठा sock *sk)
अणु
	/* First the पढ़ो buffer. */
	__skb_queue_purge(&sk->sk_receive_queue);

	/* Next, the error queue. */
	__skb_queue_purge(&sk->sk_error_queue);

	/* Next, the ग_लिखो queue. */
	WARN_ON(!skb_queue_empty(&sk->sk_ग_लिखो_queue));

	/* Account क्रम वापसed memory. */
	sk_mem_reclaim(sk);

	WARN_ON(sk->sk_wmem_queued);
	WARN_ON(sk->sk_क्रमward_alloc);

	/* It is _impossible_ क्रम the backlog to contain anything
	 * when we get here.  All user references to this socket
	 * have gone away, only the net layer knows can touch it.
	 */
पूर्ण
EXPORT_SYMBOL(sk_stream_समाप्त_queues);
