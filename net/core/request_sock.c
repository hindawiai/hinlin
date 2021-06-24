<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET		Generic infraकाष्ठाure क्रम Network protocols.
 *
 * Authors:	Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * 		From code originally in include/net/tcp.h
 */

#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tcp.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <net/request_sock.h>

/*
 * Maximum number of SYN_RECV sockets in queue per LISTEN socket.
 * One SYN_RECV socket costs about 80bytes on a 32bit machine.
 * It would be better to replace it with a global counter क्रम all sockets
 * but then some measure against one socket starving all other sockets
 * would be needed.
 *
 * The minimum value of it is 128. Experiments with real servers show that
 * it is असलolutely not enough even at 100conn/sec. 256 cures most
 * of problems.
 * This value is adjusted to 128 क्रम low memory machines,
 * and it will increase in proportion to the memory of machine.
 * Note : Dont क्रमget somaxconn that may limit backlog too.
 */

व्योम reqsk_queue_alloc(काष्ठा request_sock_queue *queue)
अणु
	spin_lock_init(&queue->rskq_lock);

	spin_lock_init(&queue->fastखोलोq.lock);
	queue->fastखोलोq.rskq_rst_head = शून्य;
	queue->fastखोलोq.rskq_rst_tail = शून्य;
	queue->fastखोलोq.qlen = 0;

	queue->rskq_accept_head = शून्य;
पूर्ण

/*
 * This function is called to set a Fast Open socket's "fastopen_rsk" field
 * to शून्य when a TFO socket no दीर्घer needs to access the request_sock.
 * This happens only after 3WHS has been either completed or पातed (e.g.,
 * RST is received).
 *
 * Beक्रमe TFO, a child socket is created only after 3WHS is completed,
 * hence it never needs to access the request_sock. things get a lot more
 * complex with TFO. A child socket, accepted or not, has to access its
 * request_sock क्रम 3WHS processing, e.g., to retransmit SYN-ACK pkts,
 * until 3WHS is either completed or पातed. Afterwards the req will stay
 * until either the child socket is accepted, or in the rare हाल when the
 * listener is बंदd beक्रमe the child is accepted.
 *
 * In लघु, a request socket is only मुक्तd after BOTH 3WHS has completed
 * (or पातed) and the child socket has been accepted (or listener बंदd).
 * When a child socket is accepted, its corresponding req->sk is set to
 * शून्य since it's no दीर्घer needed. More importantly, "req->sk == NULL"
 * will be used by the code below to determine अगर a child socket has been
 * accepted or not, and the check is रक्षित by the fastखोलोq->lock
 * described below.
 *
 * Note that fastखोलो_rsk is only accessed from the child socket's context
 * with its socket lock held. But a request_sock (req) can be accessed by
 * both its child socket through fastखोलो_rsk, and a listener socket through
 * icsk_accept_queue.rskq_accept_head. To protect the access a simple spin
 * lock per listener "icsk->icsk_accept_queue.fastopenq->lock" is created.
 * only in the rare हाल when both the listener and the child locks are held,
 * e.g., in inet_csk_listen_stop() करो we not need to acquire the lock.
 * The lock also protects other fields such as fastखोलोq->qlen, which is
 * decremented by this function when fastखोलो_rsk is no दीर्घer needed.
 *
 * Note that another solution was to simply use the existing socket lock
 * from the listener. But first socket lock is dअगरficult to use. It is not
 * a simple spin lock - one must consider sock_owned_by_user() and arrange
 * to use sk_add_backlog() stuff. But what really makes it infeasible is the
 * locking hierarchy violation. E.g., inet_csk_listen_stop() may try to
 * acquire a child's lock while holding listener's socket lock. A corner
 * हाल might also exist in tcp_v4_hnd_req() that will trigger this locking
 * order.
 *
 * This function also sets "treq->tfo_listener" to false.
 * treq->tfo_listener is used by the listener so it is रक्षित by the
 * fastखोलोq->lock in this function.
 */
व्योम reqsk_fastखोलो_हटाओ(काष्ठा sock *sk, काष्ठा request_sock *req,
			   bool reset)
अणु
	काष्ठा sock *lsk = req->rsk_listener;
	काष्ठा fastखोलो_queue *fastखोलोq;

	fastखोलोq = &inet_csk(lsk)->icsk_accept_queue.fastखोलोq;

	RCU_INIT_POINTER(tcp_sk(sk)->fastखोलो_rsk, शून्य);
	spin_lock_bh(&fastखोलोq->lock);
	fastखोलोq->qlen--;
	tcp_rsk(req)->tfo_listener = false;
	अगर (req->sk)	/* the child socket hasn't been accepted yet */
		जाओ out;

	अगर (!reset || lsk->sk_state != TCP_LISTEN) अणु
		/* If the listener has been बंदd करोn't bother with the
		 * special RST handling below.
		 */
		spin_unlock_bh(&fastखोलोq->lock);
		reqsk_put(req);
		वापस;
	पूर्ण
	/* Wait क्रम 60secs beक्रमe removing a req that has triggered RST.
	 * This is a simple defense against TFO spoofing attack - by
	 * counting the req against fastखोलो.max_qlen, and disabling
	 * TFO when the qlen exceeds max_qlen.
	 *
	 * For more details see CoNext'11 "TCP Fast Open" paper.
	 */
	req->rsk_समयr.expires = jअगरfies + 60*HZ;
	अगर (fastखोलोq->rskq_rst_head == शून्य)
		fastखोलोq->rskq_rst_head = req;
	अन्यथा
		fastखोलोq->rskq_rst_tail->dl_next = req;

	req->dl_next = शून्य;
	fastखोलोq->rskq_rst_tail = req;
	fastखोलोq->qlen++;
out:
	spin_unlock_bh(&fastखोलोq->lock);
पूर्ण
