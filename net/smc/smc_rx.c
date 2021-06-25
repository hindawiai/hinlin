<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Manage RMBE
 * copy new RMBE data पूर्णांकo user space
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/net.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>

#समावेश "smc.h"
#समावेश "smc_core.h"
#समावेश "smc_cdc.h"
#समावेश "smc_tx.h" /* smc_tx_consumer_update() */
#समावेश "smc_rx.h"

/* callback implementation to wakeup consumers blocked with smc_rx_रुको().
 * indirectly called by smc_cdc_msg_recv_action().
 */
अटल व्योम smc_rx_wake_up(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	/* derived from sock_def_पढ़ोable() */
	/* called alपढ़ोy in smc_listen_work() */
	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLIN | EPOLLPRI |
						EPOLLRDNORM | EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	अगर ((sk->sk_shutकरोwn == SHUTDOWN_MASK) ||
	    (sk->sk_state == SMC_CLOSED))
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	rcu_पढ़ो_unlock();
पूर्ण

/* Update consumer cursor
 *   @conn   connection to update
 *   @cons   consumer cursor
 *   @len    number of Bytes consumed
 *   Returns:
 *   1 अगर we should end our receive, 0 otherwise
 */
अटल पूर्णांक smc_rx_update_consumer(काष्ठा smc_sock *smc,
				  जोड़ smc_host_cursor cons, माप_प्रकार len)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा sock *sk = &smc->sk;
	bool क्रमce = false;
	पूर्णांक dअगरf, rc = 0;

	smc_curs_add(conn->rmb_desc->len, &cons, len);

	/* did we process urgent data? */
	अगर (conn->urg_state == SMC_URG_VALID || conn->urg_rx_skip_pend) अणु
		dअगरf = smc_curs_comp(conn->rmb_desc->len, &cons,
				     &conn->urg_curs);
		अगर (sock_flag(sk, SOCK_URGINLINE)) अणु
			अगर (dअगरf == 0) अणु
				क्रमce = true;
				rc = 1;
				conn->urg_state = SMC_URG_READ;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (dअगरf == 1) अणु
				/* skip urgent byte */
				क्रमce = true;
				smc_curs_add(conn->rmb_desc->len, &cons, 1);
				conn->urg_rx_skip_pend = false;
			पूर्ण अन्यथा अगर (dअगरf < -1)
				/* we पढ़ो past urgent byte */
				conn->urg_state = SMC_URG_READ;
		पूर्ण
	पूर्ण

	smc_curs_copy(&conn->local_tx_ctrl.cons, &cons, conn);

	/* send consumer cursor update अगर required */
	/* similar to advertising new TCP rcv_wnd अगर required */
	smc_tx_consumer_update(conn, क्रमce);

	वापस rc;
पूर्ण

अटल व्योम smc_rx_update_cons(काष्ठा smc_sock *smc, माप_प्रकार len)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	जोड़ smc_host_cursor cons;

	smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
	smc_rx_update_consumer(smc, cons, len);
पूर्ण

काष्ठा smc_spd_priv अणु
	काष्ठा smc_sock *smc;
	माप_प्रकार		 len;
पूर्ण;

अटल व्योम smc_rx_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
				    काष्ठा pipe_buffer *buf)
अणु
	काष्ठा smc_spd_priv *priv = (काष्ठा smc_spd_priv *)buf->निजी;
	काष्ठा smc_sock *smc = priv->smc;
	काष्ठा smc_connection *conn;
	काष्ठा sock *sk = &smc->sk;

	अगर (sk->sk_state == SMC_CLOSED ||
	    sk->sk_state == SMC_PEERFINCLOSEWAIT ||
	    sk->sk_state == SMC_APPFINCLOSEWAIT)
		जाओ out;
	conn = &smc->conn;
	lock_sock(sk);
	smc_rx_update_cons(smc, priv->len);
	release_sock(sk);
	अगर (atomic_sub_and_test(priv->len, &conn->splice_pending))
		smc_rx_wake_up(sk);
out:
	kमुक्त(priv);
	put_page(buf->page);
	sock_put(sk);
पूर्ण

अटल स्थिर काष्ठा pipe_buf_operations smc_pipe_ops = अणु
	.release = smc_rx_pipe_buf_release,
	.get = generic_pipe_buf_get
पूर्ण;

अटल व्योम smc_rx_spd_release(काष्ठा splice_pipe_desc *spd,
			       अचिन्हित पूर्णांक i)
अणु
	put_page(spd->pages[i]);
पूर्ण

अटल पूर्णांक smc_rx_splice(काष्ठा pipe_inode_info *pipe, अक्षर *src, माप_प्रकार len,
			 काष्ठा smc_sock *smc)
अणु
	काष्ठा splice_pipe_desc spd;
	काष्ठा partial_page partial;
	काष्ठा smc_spd_priv *priv;
	पूर्णांक bytes;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->len = len;
	priv->smc = smc;
	partial.offset = src - (अक्षर *)smc->conn.rmb_desc->cpu_addr;
	partial.len = len;
	partial.निजी = (अचिन्हित दीर्घ)priv;

	spd.nr_pages_max = 1;
	spd.nr_pages = 1;
	spd.pages = &smc->conn.rmb_desc->pages;
	spd.partial = &partial;
	spd.ops = &smc_pipe_ops;
	spd.spd_release = smc_rx_spd_release;

	bytes = splice_to_pipe(pipe, &spd);
	अगर (bytes > 0) अणु
		sock_hold(&smc->sk);
		get_page(smc->conn.rmb_desc->pages);
		atomic_add(bytes, &smc->conn.splice_pending);
	पूर्ण

	वापस bytes;
पूर्ण

अटल पूर्णांक smc_rx_data_available_and_no_splice_pend(काष्ठा smc_connection *conn)
अणु
	वापस atomic_पढ़ो(&conn->bytes_to_rcv) &&
	       !atomic_पढ़ो(&conn->splice_pending);
पूर्ण

/* blocks rcvbuf consumer until >=len bytes available or समयout or पूर्णांकerrupted
 *   @smc    smc socket
 *   @समयo  poपूर्णांकer to max seconds to रुको, poपूर्णांकer to value 0 क्रम no समयout
 *   @fcrit  add'l criterion to evaluate as function poपूर्णांकer
 * Returns:
 * 1 अगर at least 1 byte available in rcvbuf or अगर socket error/shutकरोwn.
 * 0 otherwise (nothing in rcvbuf nor समयout, e.g. पूर्णांकerrupted).
 */
पूर्णांक smc_rx_रुको(काष्ठा smc_sock *smc, दीर्घ *समयo,
		पूर्णांक (*fcrit)(काष्ठा smc_connection *conn))
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा smc_cdc_conn_state_flags *cflags =
					&conn->local_tx_ctrl.conn_state_flags;
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक rc;

	अगर (fcrit(conn))
		वापस 1;
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	add_रुको_queue(sk_sleep(sk), &रुको);
	rc = sk_रुको_event(sk, समयo,
			   sk->sk_err ||
			   cflags->peer_conn_पात ||
			   sk->sk_shutकरोwn & RCV_SHUTDOWN ||
			   conn->समाप्तed ||
			   fcrit(conn),
			   &रुको);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_rx_recv_urg(काष्ठा smc_sock *smc, काष्ठा msghdr *msg, पूर्णांक len,
			   पूर्णांक flags)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	जोड़ smc_host_cursor cons;
	काष्ठा sock *sk = &smc->sk;
	पूर्णांक rc = 0;

	अगर (sock_flag(sk, SOCK_URGINLINE) ||
	    !(conn->urg_state == SMC_URG_VALID) ||
	    conn->urg_state == SMC_URG_READ)
		वापस -EINVAL;

	अगर (conn->urg_state == SMC_URG_VALID) अणु
		अगर (!(flags & MSG_PEEK))
			smc->conn.urg_state = SMC_URG_READ;
		msg->msg_flags |= MSG_OOB;
		अगर (len > 0) अणु
			अगर (!(flags & MSG_TRUNC))
				rc = स_नकल_to_msg(msg, &conn->urg_rx_byte, 1);
			len = 1;
			smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
			अगर (smc_curs_dअगरf(conn->rmb_desc->len, &cons,
					  &conn->urg_curs) > 1)
				conn->urg_rx_skip_pend = true;
			/* Urgent Byte was alपढ़ोy accounted क्रम, but trigger
			 * skipping the urgent byte in non-अंतरभूत हाल
			 */
			अगर (!(flags & MSG_PEEK))
				smc_rx_update_consumer(smc, cons, 0);
		पूर्ण अन्यथा अणु
			msg->msg_flags |= MSG_TRUNC;
		पूर्ण

		वापस rc ? -EFAULT : len;
	पूर्ण

	अगर (sk->sk_state == SMC_CLOSED || sk->sk_shutकरोwn & RCV_SHUTDOWN)
		वापस 0;

	वापस -EAGAIN;
पूर्ण

अटल bool smc_rx_recvmsg_data_available(काष्ठा smc_sock *smc)
अणु
	काष्ठा smc_connection *conn = &smc->conn;

	अगर (smc_rx_data_available(conn))
		वापस true;
	अन्यथा अगर (conn->urg_state == SMC_URG_VALID)
		/* we received a single urgent Byte - skip */
		smc_rx_update_cons(smc, 0);
	वापस false;
पूर्ण

/* smc_rx_recvmsg - receive data from RMBE
 * @msg:	copy data to receive buffer
 * @pipe:	copy data to pipe अगर set - indicates splice() call
 *
 * rcvbuf consumer: मुख्य API called by socket layer.
 * Called under sk lock.
 */
पूर्णांक smc_rx_recvmsg(काष्ठा smc_sock *smc, काष्ठा msghdr *msg,
		   काष्ठा pipe_inode_info *pipe, माप_प्रकार len, पूर्णांक flags)
अणु
	माप_प्रकार copylen, पढ़ो_करोne = 0, पढ़ो_reमुख्यing = len;
	माप_प्रकार chunk_len, chunk_off, chunk_len_sum;
	काष्ठा smc_connection *conn = &smc->conn;
	पूर्णांक (*func)(काष्ठा smc_connection *conn);
	जोड़ smc_host_cursor cons;
	पूर्णांक पढ़ोable, chunk;
	अक्षर *rcvbuf_base;
	काष्ठा sock *sk;
	पूर्णांक splbytes;
	दीर्घ समयo;
	पूर्णांक target;		/* Read at least these many bytes */
	पूर्णांक rc;

	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस -EINVAL; /* future work क्रम sk.sk_family == AF_SMC */

	sk = &smc->sk;
	अगर (sk->sk_state == SMC_LISTEN)
		वापस -ENOTCONN;
	अगर (flags & MSG_OOB)
		वापस smc_rx_recv_urg(smc, msg, len, flags);
	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	/* we currently use 1 RMBE per RMB, so RMBE == RMB base addr */
	rcvbuf_base = conn->rx_off + conn->rmb_desc->cpu_addr;

	करो अणु /* जबतक (पढ़ो_reमुख्यing) */
		अगर (पढ़ो_करोne >= target || (pipe && पढ़ो_करोne))
			अवरोध;

		अगर (conn->समाप्तed)
			अवरोध;

		अगर (smc_rx_recvmsg_data_available(smc))
			जाओ copy;

		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
			/* smc_cdc_msg_recv_action() could have run after
			 * above smc_rx_recvmsg_data_available()
			 */
			अगर (smc_rx_recvmsg_data_available(smc))
				जाओ copy;
			अवरोध;
		पूर्ण

		अगर (पढ़ो_करोne) अणु
			अगर (sk->sk_err ||
			    sk->sk_state == SMC_CLOSED ||
			    !समयo ||
			    संकेत_pending(current))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sk->sk_err) अणु
				पढ़ो_करोne = sock_error(sk);
				अवरोध;
			पूर्ण
			अगर (sk->sk_state == SMC_CLOSED) अणु
				अगर (!sock_flag(sk, SOCK_DONE)) अणु
					/* This occurs when user tries to पढ़ो
					 * from never connected socket.
					 */
					पढ़ो_करोne = -ENOTCONN;
					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				पढ़ो_करोne = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
			अगर (!समयo)
				वापस -EAGAIN;
		पूर्ण

		अगर (!smc_rx_data_available(conn)) अणु
			smc_rx_रुको(smc, &समयo, smc_rx_data_available);
			जारी;
		पूर्ण

copy:
		/* initialize variables क्रम 1st iteration of subsequent loop */
		/* could be just 1 byte, even after रुकोing on data above */
		पढ़ोable = atomic_पढ़ो(&conn->bytes_to_rcv);
		splbytes = atomic_पढ़ो(&conn->splice_pending);
		अगर (!पढ़ोable || (msg && splbytes)) अणु
			अगर (splbytes)
				func = smc_rx_data_available_and_no_splice_pend;
			अन्यथा
				func = smc_rx_data_available;
			smc_rx_रुको(smc, &समयo, func);
			जारी;
		पूर्ण

		smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
		/* subsequent splice() calls pick up where previous left */
		अगर (splbytes)
			smc_curs_add(conn->rmb_desc->len, &cons, splbytes);
		अगर (conn->urg_state == SMC_URG_VALID &&
		    sock_flag(&smc->sk, SOCK_URGINLINE) &&
		    पढ़ोable > 1)
			पढ़ोable--;	/* always stop at urgent Byte */
		/* not more than what user space asked क्रम */
		copylen = min_t(माप_प्रकार, पढ़ो_reमुख्यing, पढ़ोable);
		/* determine chunks where to पढ़ो from rcvbuf */
		/* either unwrapped हाल, or 1st chunk of wrapped हाल */
		chunk_len = min_t(माप_प्रकार, copylen, conn->rmb_desc->len -
				  cons.count);
		chunk_len_sum = chunk_len;
		chunk_off = cons.count;
		smc_rmb_sync_sg_क्रम_cpu(conn);
		क्रम (chunk = 0; chunk < 2; chunk++) अणु
			अगर (!(flags & MSG_TRUNC)) अणु
				अगर (msg) अणु
					rc = स_नकल_to_msg(msg, rcvbuf_base +
							   chunk_off,
							   chunk_len);
				पूर्ण अन्यथा अणु
					rc = smc_rx_splice(pipe, rcvbuf_base +
							chunk_off, chunk_len,
							smc);
				पूर्ण
				अगर (rc < 0) अणु
					अगर (!पढ़ो_करोne)
						पढ़ो_करोne = -EFAULT;
					smc_rmb_sync_sg_क्रम_device(conn);
					जाओ out;
				पूर्ण
			पूर्ण
			पढ़ो_reमुख्यing -= chunk_len;
			पढ़ो_करोne += chunk_len;

			अगर (chunk_len_sum == copylen)
				अवरोध; /* either on 1st or 2nd iteration */
			/* prepare next (== 2nd) iteration */
			chunk_len = copylen - chunk_len; /* reमुख्यder */
			chunk_len_sum += chunk_len;
			chunk_off = 0; /* modulo offset in recv ring buffer */
		पूर्ण
		smc_rmb_sync_sg_क्रम_device(conn);

		/* update cursors */
		अगर (!(flags & MSG_PEEK)) अणु
			/* increased in recv tasklet smc_cdc_msg_rcv() */
			smp_mb__beक्रमe_atomic();
			atomic_sub(copylen, &conn->bytes_to_rcv);
			/* guarantee 0 <= bytes_to_rcv <= rmb_desc->len */
			smp_mb__after_atomic();
			अगर (msg && smc_rx_update_consumer(smc, cons, copylen))
				जाओ out;
		पूर्ण
	पूर्ण जबतक (पढ़ो_reमुख्यing);
out:
	वापस पढ़ो_करोne;
पूर्ण

/* Initialize receive properties on connection establishment. NB: not __init! */
व्योम smc_rx_init(काष्ठा smc_sock *smc)
अणु
	smc->sk.sk_data_पढ़ोy = smc_rx_wake_up;
	atomic_set(&smc->conn.splice_pending, 0);
	smc->conn.urg_state = SMC_URG_READ;
पूर्ण
