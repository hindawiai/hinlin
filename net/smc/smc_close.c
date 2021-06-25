<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Socket Closing - normal and abnormal
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/workqueue.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/tcp.h>

#समावेश "smc.h"
#समावेश "smc_tx.h"
#समावेश "smc_cdc.h"
#समावेश "smc_close.h"

/* release the clcsock that is asचिन्हित to the smc_sock */
व्योम smc_clcsock_release(काष्ठा smc_sock *smc)
अणु
	काष्ठा socket *tcp;

	अगर (smc->listen_smc && current_work() != &smc->smc_listen_work)
		cancel_work_sync(&smc->smc_listen_work);
	mutex_lock(&smc->clcsock_release_lock);
	अगर (smc->clcsock) अणु
		tcp = smc->clcsock;
		smc->clcsock = शून्य;
		sock_release(tcp);
	पूर्ण
	mutex_unlock(&smc->clcsock_release_lock);
पूर्ण

अटल व्योम smc_बंद_cleanup_listen(काष्ठा sock *parent)
अणु
	काष्ठा sock *sk;

	/* Close non-accepted connections */
	जबतक ((sk = smc_accept_dequeue(parent, शून्य)))
		smc_बंद_non_accepted(sk);
पूर्ण

/* रुको क्रम sndbuf data being transmitted */
अटल व्योम smc_बंद_stream_रुको(काष्ठा smc_sock *smc, दीर्घ समयout)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा sock *sk = &smc->sk;

	अगर (!समयout)
		वापस;

	अगर (!smc_tx_prepared_sends(&smc->conn))
		वापस;

	smc->रुको_बंद_tx_prepared = 1;
	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (!संकेत_pending(current) && समयout) अणु
		पूर्णांक rc;

		rc = sk_रुको_event(sk, &समयout,
				   !smc_tx_prepared_sends(&smc->conn) ||
				   sk->sk_err == ECONNABORTED ||
				   sk->sk_err == ECONNRESET ||
				   smc->conn.समाप्तed,
				   &रुको);
		अगर (rc)
			अवरोध;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	smc->रुको_बंद_tx_prepared = 0;
पूर्ण

व्योम smc_बंद_wake_tx_prepared(काष्ठा smc_sock *smc)
अणु
	अगर (smc->रुको_बंद_tx_prepared)
		/* wake up socket closing */
		smc->sk.sk_state_change(&smc->sk);
पूर्ण

अटल पूर्णांक smc_बंद_wr(काष्ठा smc_connection *conn)
अणु
	conn->local_tx_ctrl.conn_state_flags.peer_करोne_writing = 1;

	वापस smc_cdc_get_slot_and_msg_send(conn);
पूर्ण

अटल पूर्णांक smc_बंद_final(काष्ठा smc_connection *conn)
अणु
	अगर (atomic_पढ़ो(&conn->bytes_to_rcv))
		conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;
	अन्यथा
		conn->local_tx_ctrl.conn_state_flags.peer_conn_बंदd = 1;
	अगर (conn->समाप्तed)
		वापस -EPIPE;

	वापस smc_cdc_get_slot_and_msg_send(conn);
पूर्ण

पूर्णांक smc_बंद_पात(काष्ठा smc_connection *conn)
अणु
	conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;

	वापस smc_cdc_get_slot_and_msg_send(conn);
पूर्ण

अटल व्योम smc_बंद_cancel_work(काष्ठा smc_sock *smc)
अणु
	काष्ठा sock *sk = &smc->sk;

	release_sock(sk);
	cancel_work_sync(&smc->conn.बंद_work);
	cancel_delayed_work_sync(&smc->conn.tx_work);
	lock_sock(sk);
पूर्ण

/* terminate smc socket abnormally - active पात
 * link group is terminated, i.e. RDMA communication no दीर्घer possible
 */
व्योम smc_बंद_active_पात(काष्ठा smc_sock *smc)
अणु
	काष्ठा sock *sk = &smc->sk;
	bool release_clcsock = false;

	अगर (sk->sk_state != SMC_INIT && smc->clcsock && smc->clcsock->sk) अणु
		sk->sk_err = ECONNABORTED;
		अगर (smc->clcsock && smc->clcsock->sk)
			tcp_पात(smc->clcsock->sk, ECONNABORTED);
	पूर्ण
	चयन (sk->sk_state) अणु
	हाल SMC_ACTIVE:
	हाल SMC_APPCLOSEWAIT1:
	हाल SMC_APPCLOSEWAIT2:
		sk->sk_state = SMC_PEERABORTWAIT;
		smc_बंद_cancel_work(smc);
		अगर (sk->sk_state != SMC_PEERABORTWAIT)
			अवरोध;
		sk->sk_state = SMC_CLOSED;
		sock_put(sk); /* (postponed) passive closing */
		अवरोध;
	हाल SMC_PEERCLOSEWAIT1:
	हाल SMC_PEERCLOSEWAIT2:
	हाल SMC_PEERFINCLOSEWAIT:
		sk->sk_state = SMC_PEERABORTWAIT;
		smc_बंद_cancel_work(smc);
		अगर (sk->sk_state != SMC_PEERABORTWAIT)
			अवरोध;
		sk->sk_state = SMC_CLOSED;
		smc_conn_मुक्त(&smc->conn);
		release_clcsock = true;
		sock_put(sk); /* passive closing */
		अवरोध;
	हाल SMC_PROCESSABORT:
	हाल SMC_APPFINCLOSEWAIT:
		sk->sk_state = SMC_PEERABORTWAIT;
		smc_बंद_cancel_work(smc);
		अगर (sk->sk_state != SMC_PEERABORTWAIT)
			अवरोध;
		sk->sk_state = SMC_CLOSED;
		smc_conn_मुक्त(&smc->conn);
		release_clcsock = true;
		अवरोध;
	हाल SMC_INIT:
	हाल SMC_PEERABORTWAIT:
	हाल SMC_CLOSED:
		अवरोध;
	पूर्ण

	sock_set_flag(sk, SOCK_DEAD);
	sk->sk_state_change(sk);

	अगर (release_clcsock) अणु
		release_sock(sk);
		smc_clcsock_release(smc);
		lock_sock(sk);
	पूर्ण
पूर्ण

अटल अंतरभूत bool smc_बंद_sent_any_बंद(काष्ठा smc_connection *conn)
अणु
	वापस conn->local_tx_ctrl.conn_state_flags.peer_conn_पात ||
	       conn->local_tx_ctrl.conn_state_flags.peer_conn_बंदd;
पूर्ण

पूर्णांक smc_बंद_active(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_cdc_conn_state_flags *txflags =
		&smc->conn.local_tx_ctrl.conn_state_flags;
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक old_state;
	दीर्घ समयout;
	पूर्णांक rc = 0;

	समयout = current->flags & PF_EXITING ?
		  0 : sock_flag(sk, SOCK_LINGER) ?
		      sk->sk_lingerसमय : SMC_MAX_STREAM_WAIT_TIMEOUT;

	old_state = sk->sk_state;
again:
	चयन (sk->sk_state) अणु
	हाल SMC_INIT:
		sk->sk_state = SMC_CLOSED;
		अवरोध;
	हाल SMC_LISTEN:
		sk->sk_state = SMC_CLOSED;
		sk->sk_state_change(sk); /* wake up accept */
		अगर (smc->clcsock && smc->clcsock->sk) अणु
			smc->clcsock->sk->sk_data_पढ़ोy = smc->clcsk_data_पढ़ोy;
			smc->clcsock->sk->sk_user_data = शून्य;
			rc = kernel_sock_shutकरोwn(smc->clcsock, SHUT_RDWR);
		पूर्ण
		smc_बंद_cleanup_listen(sk);
		release_sock(sk);
		flush_work(&smc->tcp_listen_work);
		lock_sock(sk);
		अवरोध;
	हाल SMC_ACTIVE:
		smc_बंद_stream_रुको(smc, समयout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		अगर (sk->sk_state == SMC_ACTIVE) अणु
			/* send बंद request */
			rc = smc_बंद_final(conn);
			sk->sk_state = SMC_PEERCLOSEWAIT1;
		पूर्ण अन्यथा अणु
			/* peer event has changed the state */
			जाओ again;
		पूर्ण
		अवरोध;
	हाल SMC_APPFINCLOSEWAIT:
		/* socket alपढ़ोy shutकरोwn wr or both (active बंद) */
		अगर (txflags->peer_करोne_writing &&
		    !smc_बंद_sent_any_बंद(conn)) अणु
			/* just shutकरोwn wr करोne, send बंद request */
			rc = smc_बंद_final(conn);
		पूर्ण
		sk->sk_state = SMC_CLOSED;
		अवरोध;
	हाल SMC_APPCLOSEWAIT1:
	हाल SMC_APPCLOSEWAIT2:
		अगर (!smc_cdc_rxed_any_बंद(conn))
			smc_बंद_stream_रुको(smc, समयout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		अगर (sk->sk_state != SMC_APPCLOSEWAIT1 &&
		    sk->sk_state != SMC_APPCLOSEWAIT2)
			जाओ again;
		/* confirm बंद from peer */
		rc = smc_बंद_final(conn);
		अगर (smc_cdc_rxed_any_बंद(conn)) अणु
			/* peer has बंदd the socket alपढ़ोy */
			sk->sk_state = SMC_CLOSED;
			sock_put(sk); /* postponed passive closing */
		पूर्ण अन्यथा अणु
			/* peer has just issued a shutकरोwn ग_लिखो */
			sk->sk_state = SMC_PEERFINCLOSEWAIT;
		पूर्ण
		अवरोध;
	हाल SMC_PEERCLOSEWAIT1:
	हाल SMC_PEERCLOSEWAIT2:
		अगर (txflags->peer_करोne_writing &&
		    !smc_बंद_sent_any_बंद(conn)) अणु
			/* just shutकरोwn wr करोne, send बंद request */
			rc = smc_बंद_final(conn);
		पूर्ण
		/* peer sending PeerConnectionClosed will cause transition */
		अवरोध;
	हाल SMC_PEERFINCLOSEWAIT:
		/* peer sending PeerConnectionClosed will cause transition */
		अवरोध;
	हाल SMC_PROCESSABORT:
		rc = smc_बंद_पात(conn);
		sk->sk_state = SMC_CLOSED;
		अवरोध;
	हाल SMC_PEERABORTWAIT:
		sk->sk_state = SMC_CLOSED;
		अवरोध;
	हाल SMC_CLOSED:
		/* nothing to करो, add tracing in future patch */
		अवरोध;
	पूर्ण

	अगर (old_state != sk->sk_state)
		sk->sk_state_change(sk);
	वापस rc;
पूर्ण

अटल व्योम smc_बंद_passive_पात_received(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_cdc_conn_state_flags *txflags =
		&smc->conn.local_tx_ctrl.conn_state_flags;
	काष्ठा sock *sk = &smc->sk;

	चयन (sk->sk_state) अणु
	हाल SMC_INIT:
	हाल SMC_ACTIVE:
	हाल SMC_APPCLOSEWAIT1:
		sk->sk_state = SMC_PROCESSABORT;
		sock_put(sk); /* passive closing */
		अवरोध;
	हाल SMC_APPFINCLOSEWAIT:
		sk->sk_state = SMC_PROCESSABORT;
		अवरोध;
	हाल SMC_PEERCLOSEWAIT1:
	हाल SMC_PEERCLOSEWAIT2:
		अगर (txflags->peer_करोne_writing &&
		    !smc_बंद_sent_any_बंद(&smc->conn))
			/* just shutकरोwn, but not yet बंदd locally */
			sk->sk_state = SMC_PROCESSABORT;
		अन्यथा
			sk->sk_state = SMC_CLOSED;
		sock_put(sk); /* passive closing */
		अवरोध;
	हाल SMC_APPCLOSEWAIT2:
	हाल SMC_PEERFINCLOSEWAIT:
		sk->sk_state = SMC_CLOSED;
		sock_put(sk); /* passive closing */
		अवरोध;
	हाल SMC_PEERABORTWAIT:
		sk->sk_state = SMC_CLOSED;
		अवरोध;
	हाल SMC_PROCESSABORT:
	/* nothing to करो, add tracing in future patch */
		अवरोध;
	पूर्ण
पूर्ण

/* Either some kind of closing has been received: peer_conn_बंदd,
 * peer_conn_पात, or peer_करोne_writing
 * or the link group of the connection terminates abnormally.
 */
अटल व्योम smc_बंद_passive_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_connection *conn = container_of(work,
						   काष्ठा smc_connection,
						   बंद_work);
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);
	काष्ठा smc_cdc_conn_state_flags *rxflags;
	bool release_clcsock = false;
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक old_state;

	lock_sock(sk);
	old_state = sk->sk_state;

	rxflags = &conn->local_rx_ctrl.conn_state_flags;
	अगर (rxflags->peer_conn_पात) अणु
		/* peer has not received all data */
		smc_बंद_passive_पात_received(smc);
		release_sock(&smc->sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(&smc->sk);
		जाओ wakeup;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल SMC_INIT:
		sk->sk_state = SMC_APPCLOSEWAIT1;
		अवरोध;
	हाल SMC_ACTIVE:
		sk->sk_state = SMC_APPCLOSEWAIT1;
		/* postpone sock_put() क्रम passive closing to cover
		 * received SEND_SHUTDOWN as well
		 */
		अवरोध;
	हाल SMC_PEERCLOSEWAIT1:
		अगर (rxflags->peer_करोne_writing)
			sk->sk_state = SMC_PEERCLOSEWAIT2;
		fallthrough;
		/* to check क्रम closing */
	हाल SMC_PEERCLOSEWAIT2:
		अगर (!smc_cdc_rxed_any_बंद(conn))
			अवरोध;
		अगर (sock_flag(sk, SOCK_DEAD) &&
		    smc_बंद_sent_any_बंद(conn)) अणु
			/* smc_release has alपढ़ोy been called locally */
			sk->sk_state = SMC_CLOSED;
		पूर्ण अन्यथा अणु
			/* just shutकरोwn, but not yet बंदd locally */
			sk->sk_state = SMC_APPFINCLOSEWAIT;
		पूर्ण
		sock_put(sk); /* passive closing */
		अवरोध;
	हाल SMC_PEERFINCLOSEWAIT:
		अगर (smc_cdc_rxed_any_बंद(conn)) अणु
			sk->sk_state = SMC_CLOSED;
			sock_put(sk); /* passive closing */
		पूर्ण
		अवरोध;
	हाल SMC_APPCLOSEWAIT1:
	हाल SMC_APPCLOSEWAIT2:
		/* postpone sock_put() क्रम passive closing to cover
		 * received SEND_SHUTDOWN as well
		 */
		अवरोध;
	हाल SMC_APPFINCLOSEWAIT:
	हाल SMC_PEERABORTWAIT:
	हाल SMC_PROCESSABORT:
	हाल SMC_CLOSED:
		/* nothing to करो, add tracing in future patch */
		अवरोध;
	पूर्ण

wakeup:
	sk->sk_data_पढ़ोy(sk); /* wakeup blocked rcvbuf consumers */
	sk->sk_ग_लिखो_space(sk); /* wakeup blocked sndbuf producers */

	अगर (old_state != sk->sk_state) अणु
		sk->sk_state_change(sk);
		अगर ((sk->sk_state == SMC_CLOSED) &&
		    (sock_flag(sk, SOCK_DEAD) || !sk->sk_socket)) अणु
			smc_conn_मुक्त(conn);
			अगर (smc->clcsock)
				release_clcsock = true;
		पूर्ण
	पूर्ण
	release_sock(sk);
	अगर (release_clcsock)
		smc_clcsock_release(smc);
	sock_put(sk); /* sock_hold करोne by schedulers of बंद_work */
पूर्ण

पूर्णांक smc_बंद_shutकरोwn_ग_लिखो(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक old_state;
	दीर्घ समयout;
	पूर्णांक rc = 0;

	समयout = current->flags & PF_EXITING ?
		  0 : sock_flag(sk, SOCK_LINGER) ?
		      sk->sk_lingerसमय : SMC_MAX_STREAM_WAIT_TIMEOUT;

	old_state = sk->sk_state;
again:
	चयन (sk->sk_state) अणु
	हाल SMC_ACTIVE:
		smc_बंद_stream_रुको(smc, समयout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		अगर (sk->sk_state != SMC_ACTIVE)
			जाओ again;
		/* send बंद wr request */
		rc = smc_बंद_wr(conn);
		sk->sk_state = SMC_PEERCLOSEWAIT1;
		अवरोध;
	हाल SMC_APPCLOSEWAIT1:
		/* passive बंद */
		अगर (!smc_cdc_rxed_any_बंद(conn))
			smc_बंद_stream_रुको(smc, समयout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		अगर (sk->sk_state != SMC_APPCLOSEWAIT1)
			जाओ again;
		/* confirm बंद from peer */
		rc = smc_बंद_wr(conn);
		sk->sk_state = SMC_APPCLOSEWAIT2;
		अवरोध;
	हाल SMC_APPCLOSEWAIT2:
	हाल SMC_PEERFINCLOSEWAIT:
	हाल SMC_PEERCLOSEWAIT1:
	हाल SMC_PEERCLOSEWAIT2:
	हाल SMC_APPFINCLOSEWAIT:
	हाल SMC_PROCESSABORT:
	हाल SMC_PEERABORTWAIT:
		/* nothing to करो, add tracing in future patch */
		अवरोध;
	पूर्ण

	अगर (old_state != sk->sk_state)
		sk->sk_state_change(sk);
	वापस rc;
पूर्ण

/* Initialize बंद properties on connection establishment. */
व्योम smc_बंद_init(काष्ठा smc_sock *smc)
अणु
	INIT_WORK(&smc->conn.बंद_work, smc_बंद_passive_work);
पूर्ण
