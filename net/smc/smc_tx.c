<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Manage send buffer.
 * Producer:
 * Copy user space data पूर्णांकo send buffer, अगर send buffer space available.
 * Consumer:
 * Trigger RDMA ग_लिखो पूर्णांकo RMBE of peer and send CDC, अगर RMBE space available.
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/net.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/tcp.h>

#समावेश "smc.h"
#समावेश "smc_wr.h"
#समावेश "smc_cdc.h"
#समावेश "smc_close.h"
#समावेश "smc_ism.h"
#समावेश "smc_tx.h"

#घोषणा SMC_TX_WORK_DELAY	0
#घोषणा SMC_TX_CORK_DELAY	(HZ >> 2)	/* 250 ms */

/***************************** sndbuf producer *******************************/

/* callback implementation क्रम sk.sk_ग_लिखो_space()
 * to wakeup sndbuf producers that blocked with smc_tx_रुको().
 * called under sk_socket lock.
 */
अटल व्योम smc_tx_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket *sock = sk->sk_socket;
	काष्ठा smc_sock *smc = smc_sk(sk);
	काष्ठा socket_wq *wq;

	/* similar to sk_stream_ग_लिखो_space */
	अगर (atomic_पढ़ो(&smc->conn.sndbuf_space) && sock) अणु
		clear_bit(SOCK_NOSPACE, &sock->flags);
		rcu_पढ़ो_lock();
		wq = rcu_dereference(sk->sk_wq);
		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible_poll(&wq->रुको,
						   EPOLLOUT | EPOLLWRNORM |
						   EPOLLWRBAND);
		अगर (wq && wq->fasync_list && !(sk->sk_shutकरोwn & SEND_SHUTDOWN))
			sock_wake_async(wq, SOCK_WAKE_SPACE, POLL_OUT);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/* Wakeup sndbuf producers that blocked with smc_tx_रुको().
 * Cf. tcp_data_snd_check()=>tcp_check_space()=>tcp_new_space().
 */
व्योम smc_tx_sndbuf_nonfull(काष्ठा smc_sock *smc)
अणु
	अगर (smc->sk.sk_socket &&
	    test_bit(SOCK_NOSPACE, &smc->sk.sk_socket->flags))
		smc->sk.sk_ग_लिखो_space(&smc->sk);
पूर्ण

/* blocks sndbuf producer until at least one byte of मुक्त space available
 * or urgent Byte was consumed
 */
अटल पूर्णांक smc_tx_रुको(काष्ठा smc_sock *smc, पूर्णांक flags)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा smc_connection *conn = &smc->conn;
	काष्ठा sock *sk = &smc->sk;
	दीर्घ समयo;
	पूर्णांक rc = 0;

	/* similar to sk_stream_रुको_memory */
	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		अगर (sk->sk_err ||
		    (sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
		    conn->समाप्तed ||
		    conn->local_tx_ctrl.conn_state_flags.peer_करोne_writing) अणु
			rc = -EPIPE;
			अवरोध;
		पूर्ण
		अगर (smc_cdc_rxed_any_बंद(conn)) अणु
			rc = -ECONNRESET;
			अवरोध;
		पूर्ण
		अगर (!समयo) अणु
			/* ensure EPOLLOUT is subsequently generated */
			set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			rc = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			rc = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण
		sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		अगर (atomic_पढ़ो(&conn->sndbuf_space) && !conn->urg_tx_pend)
			अवरोध; /* at least 1 byte of मुक्त & no urgent data */
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk_रुको_event(sk, &समयo,
			      sk->sk_err ||
			      (sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
			      smc_cdc_rxed_any_बंद(conn) ||
			      (atomic_पढ़ो(&conn->sndbuf_space) &&
			       !conn->urg_tx_pend),
			      &रुको);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

अटल bool smc_tx_is_corked(काष्ठा smc_sock *smc)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(smc->clcsock->sk);

	वापस (tp->nonagle & TCP_NAGLE_CORK) ? true : false;
पूर्ण

/* sndbuf producer: मुख्य API called by socket layer.
 * called under sock lock.
 */
पूर्णांक smc_tx_sendmsg(काष्ठा smc_sock *smc, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	माप_प्रकार copylen, send_करोne = 0, send_reमुख्यing = len;
	माप_प्रकार chunk_len, chunk_off, chunk_len_sum;
	काष्ठा smc_connection *conn = &smc->conn;
	जोड़ smc_host_cursor prep;
	काष्ठा sock *sk = &smc->sk;
	अक्षर *sndbuf_base;
	पूर्णांक tx_cnt_prep;
	पूर्णांक ग_लिखोspace;
	पूर्णांक rc, chunk;

	/* This should be in poll */
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
		rc = -EPIPE;
		जाओ out_err;
	पूर्ण

	जबतक (msg_data_left(msg)) अणु
		अगर (sk->sk_state == SMC_INIT)
			वापस -ENOTCONN;
		अगर (smc->sk.sk_shutकरोwn & SEND_SHUTDOWN ||
		    (smc->sk.sk_err == ECONNABORTED) ||
		    conn->समाप्तed)
			वापस -EPIPE;
		अगर (smc_cdc_rxed_any_बंद(conn))
			वापस send_करोne ?: -ECONNRESET;

		अगर (msg->msg_flags & MSG_OOB)
			conn->local_tx_ctrl.prod_flags.urg_data_pending = 1;

		अगर (!atomic_पढ़ो(&conn->sndbuf_space) || conn->urg_tx_pend) अणु
			अगर (send_करोne)
				वापस send_करोne;
			rc = smc_tx_रुको(smc, msg->msg_flags);
			अगर (rc)
				जाओ out_err;
			जारी;
		पूर्ण

		/* initialize variables क्रम 1st iteration of subsequent loop */
		/* could be just 1 byte, even after smc_tx_रुको above */
		ग_लिखोspace = atomic_पढ़ो(&conn->sndbuf_space);
		/* not more than what user space asked क्रम */
		copylen = min_t(माप_प्रकार, send_reमुख्यing, ग_लिखोspace);
		/* determine start of sndbuf */
		sndbuf_base = conn->sndbuf_desc->cpu_addr;
		smc_curs_copy(&prep, &conn->tx_curs_prep, conn);
		tx_cnt_prep = prep.count;
		/* determine chunks where to ग_लिखो पूर्णांकo sndbuf */
		/* either unwrapped हाल, or 1st chunk of wrapped हाल */
		chunk_len = min_t(माप_प्रकार, copylen, conn->sndbuf_desc->len -
				  tx_cnt_prep);
		chunk_len_sum = chunk_len;
		chunk_off = tx_cnt_prep;
		smc_sndbuf_sync_sg_क्रम_cpu(conn);
		क्रम (chunk = 0; chunk < 2; chunk++) अणु
			rc = स_नकल_from_msg(sndbuf_base + chunk_off,
					     msg, chunk_len);
			अगर (rc) अणु
				smc_sndbuf_sync_sg_क्रम_device(conn);
				अगर (send_करोne)
					वापस send_करोne;
				जाओ out_err;
			पूर्ण
			send_करोne += chunk_len;
			send_reमुख्यing -= chunk_len;

			अगर (chunk_len_sum == copylen)
				अवरोध; /* either on 1st or 2nd iteration */
			/* prepare next (== 2nd) iteration */
			chunk_len = copylen - chunk_len; /* reमुख्यder */
			chunk_len_sum += chunk_len;
			chunk_off = 0; /* modulo offset in send ring buffer */
		पूर्ण
		smc_sndbuf_sync_sg_क्रम_device(conn);
		/* update cursors */
		smc_curs_add(conn->sndbuf_desc->len, &prep, copylen);
		smc_curs_copy(&conn->tx_curs_prep, &prep, conn);
		/* increased in send tasklet smc_cdc_tx_handler() */
		smp_mb__beक्रमe_atomic();
		atomic_sub(copylen, &conn->sndbuf_space);
		/* guarantee 0 <= sndbuf_space <= sndbuf_desc->len */
		smp_mb__after_atomic();
		/* since we just produced more new data पूर्णांकo sndbuf,
		 * trigger sndbuf consumer: RDMA ग_लिखो पूर्णांकo peer RMBE and CDC
		 */
		अगर ((msg->msg_flags & MSG_OOB) && !send_reमुख्यing)
			conn->urg_tx_pend = true;
		अगर ((msg->msg_flags & MSG_MORE || smc_tx_is_corked(smc)) &&
		    (atomic_पढ़ो(&conn->sndbuf_space) >
						(conn->sndbuf_desc->len >> 1)))
			/* क्रम a corked socket defer the RDMA ग_लिखोs अगर there
			 * is still sufficient sndbuf_space available
			 */
			queue_delayed_work(conn->lgr->tx_wq, &conn->tx_work,
					   SMC_TX_CORK_DELAY);
		अन्यथा
			smc_tx_sndbuf_nonempty(conn);
	पूर्ण /* जबतक (msg_data_left(msg)) */

	वापस send_करोne;

out_err:
	rc = sk_stream_error(sk, msg->msg_flags, rc);
	/* make sure we wake any epoll edge trigger रुकोer */
	अगर (unlikely(rc == -EAGAIN))
		sk->sk_ग_लिखो_space(sk);
	वापस rc;
पूर्ण

/***************************** sndbuf consumer *******************************/

/* sndbuf consumer: actual data transfer of one target chunk with ISM ग_लिखो */
पूर्णांक smcd_tx_ism_ग_लिखो(काष्ठा smc_connection *conn, व्योम *data, माप_प्रकार len,
		      u32 offset, पूर्णांक संकेत)
अणु
	काष्ठा smc_ism_position pos;
	पूर्णांक rc;

	स_रखो(&pos, 0, माप(pos));
	pos.token = conn->peer_token;
	pos.index = conn->peer_rmbe_idx;
	pos.offset = conn->tx_off + offset;
	pos.संकेत = संकेत;
	rc = smc_ism_ग_लिखो(conn->lgr->smcd, &pos, data, len);
	अगर (rc)
		conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;
	वापस rc;
पूर्ण

/* sndbuf consumer: actual data transfer of one target chunk with RDMA ग_लिखो */
अटल पूर्णांक smc_tx_rdma_ग_लिखो(काष्ठा smc_connection *conn, पूर्णांक peer_rmbe_offset,
			     पूर्णांक num_sges, काष्ठा ib_rdma_wr *rdma_wr)
अणु
	काष्ठा smc_link_group *lgr = conn->lgr;
	काष्ठा smc_link *link = conn->lnk;
	पूर्णांक rc;

	rdma_wr->wr.wr_id = smc_wr_tx_get_next_wr_id(link);
	rdma_wr->wr.num_sge = num_sges;
	rdma_wr->remote_addr =
		lgr->rtokens[conn->rtoken_idx][link->link_idx].dma_addr +
		/* RMBE within RMB */
		conn->tx_off +
		/* offset within RMBE */
		peer_rmbe_offset;
	rdma_wr->rkey = lgr->rtokens[conn->rtoken_idx][link->link_idx].rkey;
	rc = ib_post_send(link->roce_qp, &rdma_wr->wr, शून्य);
	अगर (rc)
		smcr_link_करोwn_cond_sched(link);
	वापस rc;
पूर्ण

/* sndbuf consumer */
अटल अंतरभूत व्योम smc_tx_advance_cursors(काष्ठा smc_connection *conn,
					  जोड़ smc_host_cursor *prod,
					  जोड़ smc_host_cursor *sent,
					  माप_प्रकार len)
अणु
	smc_curs_add(conn->peer_rmbe_size, prod, len);
	/* increased in recv tasklet smc_cdc_msg_rcv() */
	smp_mb__beक्रमe_atomic();
	/* data in flight reduces usable snd_wnd */
	atomic_sub(len, &conn->peer_rmbe_space);
	/* guarantee 0 <= peer_rmbe_space <= peer_rmbe_size */
	smp_mb__after_atomic();
	smc_curs_add(conn->sndbuf_desc->len, sent, len);
पूर्ण

/* SMC-R helper क्रम smc_tx_rdma_ग_लिखोs() */
अटल पूर्णांक smcr_tx_rdma_ग_लिखोs(काष्ठा smc_connection *conn, माप_प्रकार len,
			       माप_प्रकार src_off, माप_प्रकार src_len,
			       माप_प्रकार dst_off, माप_प्रकार dst_len,
			       काष्ठा smc_rdma_wr *wr_rdma_buf)
अणु
	काष्ठा smc_link *link = conn->lnk;

	dma_addr_t dma_addr =
		sg_dma_address(conn->sndbuf_desc->sgt[link->link_idx].sgl);
	पूर्णांक src_len_sum = src_len, dst_len_sum = dst_len;
	पूर्णांक sent_count = src_off;
	पूर्णांक srcchunk, dstchunk;
	पूर्णांक num_sges;
	पूर्णांक rc;

	क्रम (dstchunk = 0; dstchunk < 2; dstchunk++) अणु
		काष्ठा ib_sge *sge =
			wr_rdma_buf->wr_tx_rdma[dstchunk].wr.sg_list;

		num_sges = 0;
		क्रम (srcchunk = 0; srcchunk < 2; srcchunk++) अणु
			sge[srcchunk].addr = dma_addr + src_off;
			sge[srcchunk].length = src_len;
			num_sges++;

			src_off += src_len;
			अगर (src_off >= conn->sndbuf_desc->len)
				src_off -= conn->sndbuf_desc->len;
						/* modulo in send ring */
			अगर (src_len_sum == dst_len)
				अवरोध; /* either on 1st or 2nd iteration */
			/* prepare next (== 2nd) iteration */
			src_len = dst_len - src_len; /* reमुख्यder */
			src_len_sum += src_len;
		पूर्ण
		rc = smc_tx_rdma_ग_लिखो(conn, dst_off, num_sges,
				       &wr_rdma_buf->wr_tx_rdma[dstchunk]);
		अगर (rc)
			वापस rc;
		अगर (dst_len_sum == len)
			अवरोध; /* either on 1st or 2nd iteration */
		/* prepare next (== 2nd) iteration */
		dst_off = 0; /* modulo offset in RMBE ring buffer */
		dst_len = len - dst_len; /* reमुख्यder */
		dst_len_sum += dst_len;
		src_len = min_t(पूर्णांक, dst_len, conn->sndbuf_desc->len -
				sent_count);
		src_len_sum = src_len;
	पूर्ण
	वापस 0;
पूर्ण

/* SMC-D helper क्रम smc_tx_rdma_ग_लिखोs() */
अटल पूर्णांक smcd_tx_rdma_ग_लिखोs(काष्ठा smc_connection *conn, माप_प्रकार len,
			       माप_प्रकार src_off, माप_प्रकार src_len,
			       माप_प्रकार dst_off, माप_प्रकार dst_len)
अणु
	पूर्णांक src_len_sum = src_len, dst_len_sum = dst_len;
	पूर्णांक srcchunk, dstchunk;
	पूर्णांक rc;

	क्रम (dstchunk = 0; dstchunk < 2; dstchunk++) अणु
		क्रम (srcchunk = 0; srcchunk < 2; srcchunk++) अणु
			व्योम *data = conn->sndbuf_desc->cpu_addr + src_off;

			rc = smcd_tx_ism_ग_लिखो(conn, data, src_len, dst_off +
					       माप(काष्ठा smcd_cdc_msg), 0);
			अगर (rc)
				वापस rc;
			dst_off += src_len;
			src_off += src_len;
			अगर (src_off >= conn->sndbuf_desc->len)
				src_off -= conn->sndbuf_desc->len;
						/* modulo in send ring */
			अगर (src_len_sum == dst_len)
				अवरोध; /* either on 1st or 2nd iteration */
			/* prepare next (== 2nd) iteration */
			src_len = dst_len - src_len; /* reमुख्यder */
			src_len_sum += src_len;
		पूर्ण
		अगर (dst_len_sum == len)
			अवरोध; /* either on 1st or 2nd iteration */
		/* prepare next (== 2nd) iteration */
		dst_off = 0; /* modulo offset in RMBE ring buffer */
		dst_len = len - dst_len; /* reमुख्यder */
		dst_len_sum += dst_len;
		src_len = min_t(पूर्णांक, dst_len, conn->sndbuf_desc->len - src_off);
		src_len_sum = src_len;
	पूर्ण
	वापस 0;
पूर्ण

/* sndbuf consumer: prepare all necessary (src&dst) chunks of data transmit;
 * usable snd_wnd as max transmit
 */
अटल पूर्णांक smc_tx_rdma_ग_लिखोs(काष्ठा smc_connection *conn,
			      काष्ठा smc_rdma_wr *wr_rdma_buf)
अणु
	माप_प्रकार len, src_len, dst_off, dst_len; /* current chunk values */
	जोड़ smc_host_cursor sent, prep, prod, cons;
	काष्ठा smc_cdc_producer_flags *pflags;
	पूर्णांक to_send, rmbespace;
	पूर्णांक rc;

	/* source: sndbuf */
	smc_curs_copy(&sent, &conn->tx_curs_sent, conn);
	smc_curs_copy(&prep, &conn->tx_curs_prep, conn);
	/* cf. wmem_alloc - (snd_max - snd_una) */
	to_send = smc_curs_dअगरf(conn->sndbuf_desc->len, &sent, &prep);
	अगर (to_send <= 0)
		वापस 0;

	/* destination: RMBE */
	/* cf. snd_wnd */
	rmbespace = atomic_पढ़ो(&conn->peer_rmbe_space);
	अगर (rmbespace <= 0)
		वापस 0;
	smc_curs_copy(&prod, &conn->local_tx_ctrl.prod, conn);
	smc_curs_copy(&cons, &conn->local_rx_ctrl.cons, conn);

	/* अगर usable snd_wnd बंदs ask peer to advertise once it खोलोs again */
	pflags = &conn->local_tx_ctrl.prod_flags;
	pflags->ग_लिखो_blocked = (to_send >= rmbespace);
	/* cf. usable snd_wnd */
	len = min(to_send, rmbespace);

	/* initialize variables क्रम first iteration of subsequent nested loop */
	dst_off = prod.count;
	अगर (prod.wrap == cons.wrap) अणु
		/* the filled destination area is unwrapped,
		 * hence the available मुक्त destination space is wrapped
		 * and we need 2 destination chunks of sum len; start with 1st
		 * which is limited by what's available in sndbuf
		 */
		dst_len = min_t(माप_प्रकार,
				conn->peer_rmbe_size - prod.count, len);
	पूर्ण अन्यथा अणु
		/* the filled destination area is wrapped,
		 * hence the available मुक्त destination space is unwrapped
		 * and we need a single destination chunk of entire len
		 */
		dst_len = len;
	पूर्ण
	/* dst_len determines the maximum src_len */
	अगर (sent.count + dst_len <= conn->sndbuf_desc->len) अणु
		/* unwrapped src हाल: single chunk of entire dst_len */
		src_len = dst_len;
	पूर्ण अन्यथा अणु
		/* wrapped src हाल: 2 chunks of sum dst_len; start with 1st: */
		src_len = conn->sndbuf_desc->len - sent.count;
	पूर्ण

	अगर (conn->lgr->is_smcd)
		rc = smcd_tx_rdma_ग_लिखोs(conn, len, sent.count, src_len,
					 dst_off, dst_len);
	अन्यथा
		rc = smcr_tx_rdma_ग_लिखोs(conn, len, sent.count, src_len,
					 dst_off, dst_len, wr_rdma_buf);
	अगर (rc)
		वापस rc;

	अगर (conn->urg_tx_pend && len == to_send)
		pflags->urg_data_present = 1;
	smc_tx_advance_cursors(conn, &prod, &sent, len);
	/* update connection's cursors with advanced local cursors */
	smc_curs_copy(&conn->local_tx_ctrl.prod, &prod, conn);
							/* dst: peer RMBE */
	smc_curs_copy(&conn->tx_curs_sent, &sent, conn);/* src: local sndbuf */

	वापस 0;
पूर्ण

/* Wakeup sndbuf consumers from any context (IRQ or process)
 * since there is more data to transmit; usable snd_wnd as max transmit
 */
अटल पूर्णांक smcr_tx_sndbuf_nonempty(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_cdc_producer_flags *pflags = &conn->local_tx_ctrl.prod_flags;
	काष्ठा smc_link *link = conn->lnk;
	काष्ठा smc_rdma_wr *wr_rdma_buf;
	काष्ठा smc_cdc_tx_pend *pend;
	काष्ठा smc_wr_buf *wr_buf;
	पूर्णांक rc;

	rc = smc_cdc_get_मुक्त_slot(conn, link, &wr_buf, &wr_rdma_buf, &pend);
	अगर (rc < 0) अणु
		अगर (rc == -EBUSY) अणु
			काष्ठा smc_sock *smc =
				container_of(conn, काष्ठा smc_sock, conn);

			अगर (smc->sk.sk_err == ECONNABORTED)
				वापस sock_error(&smc->sk);
			अगर (conn->समाप्तed)
				वापस -EPIPE;
			rc = 0;
			mod_delayed_work(conn->lgr->tx_wq, &conn->tx_work,
					 SMC_TX_WORK_DELAY);
		पूर्ण
		वापस rc;
	पूर्ण

	spin_lock_bh(&conn->send_lock);
	अगर (link != conn->lnk) अणु
		/* link of connection changed, tx_work will restart */
		smc_wr_tx_put_slot(link,
				   (काष्ठा smc_wr_tx_pend_priv *)pend);
		rc = -ENOLINK;
		जाओ out_unlock;
	पूर्ण
	अगर (!pflags->urg_data_present) अणु
		rc = smc_tx_rdma_ग_लिखोs(conn, wr_rdma_buf);
		अगर (rc) अणु
			smc_wr_tx_put_slot(link,
					   (काष्ठा smc_wr_tx_pend_priv *)pend);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	rc = smc_cdc_msg_send(conn, wr_buf, pend);
	अगर (!rc && pflags->urg_data_present) अणु
		pflags->urg_data_pending = 0;
		pflags->urg_data_present = 0;
	पूर्ण

out_unlock:
	spin_unlock_bh(&conn->send_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक smcd_tx_sndbuf_nonempty(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_cdc_producer_flags *pflags = &conn->local_tx_ctrl.prod_flags;
	पूर्णांक rc = 0;

	spin_lock_bh(&conn->send_lock);
	अगर (!pflags->urg_data_present)
		rc = smc_tx_rdma_ग_लिखोs(conn, शून्य);
	अगर (!rc)
		rc = smcd_cdc_msg_send(conn);

	अगर (!rc && pflags->urg_data_present) अणु
		pflags->urg_data_pending = 0;
		pflags->urg_data_present = 0;
	पूर्ण
	spin_unlock_bh(&conn->send_lock);
	वापस rc;
पूर्ण

पूर्णांक smc_tx_sndbuf_nonempty(काष्ठा smc_connection *conn)
अणु
	पूर्णांक rc;

	अगर (conn->समाप्तed ||
	    conn->local_rx_ctrl.conn_state_flags.peer_conn_पात)
		वापस -EPIPE;	/* connection being पातed */
	अगर (conn->lgr->is_smcd)
		rc = smcd_tx_sndbuf_nonempty(conn);
	अन्यथा
		rc = smcr_tx_sndbuf_nonempty(conn);

	अगर (!rc) अणु
		/* trigger socket release अगर connection is closing */
		काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock,
						    conn);
		smc_बंद_wake_tx_prepared(smc);
	पूर्ण
	वापस rc;
पूर्ण

/* Wakeup sndbuf consumers from process context
 * since there is more data to transmit
 */
व्योम smc_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_connection *conn = container_of(to_delayed_work(work),
						   काष्ठा smc_connection,
						   tx_work);
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);
	पूर्णांक rc;

	lock_sock(&smc->sk);
	अगर (smc->sk.sk_err)
		जाओ out;

	rc = smc_tx_sndbuf_nonempty(conn);
	अगर (!rc && conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked &&
	    !atomic_पढ़ो(&conn->bytes_to_rcv))
		conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked = 0;

out:
	release_sock(&smc->sk);
पूर्ण

व्योम smc_tx_consumer_update(काष्ठा smc_connection *conn, bool क्रमce)
अणु
	जोड़ smc_host_cursor cfed, cons, prod;
	पूर्णांक sender_मुक्त = conn->rmb_desc->len;
	पूर्णांक to_confirm;

	smc_curs_copy(&cons, &conn->local_tx_ctrl.cons, conn);
	smc_curs_copy(&cfed, &conn->rx_curs_confirmed, conn);
	to_confirm = smc_curs_dअगरf(conn->rmb_desc->len, &cfed, &cons);
	अगर (to_confirm > conn->rmbe_update_limit) अणु
		smc_curs_copy(&prod, &conn->local_rx_ctrl.prod, conn);
		sender_मुक्त = conn->rmb_desc->len -
			      smc_curs_dअगरf_large(conn->rmb_desc->len,
						  &cfed, &prod);
	पूर्ण

	अगर (conn->local_rx_ctrl.prod_flags.cons_curs_upd_req ||
	    क्रमce ||
	    ((to_confirm > conn->rmbe_update_limit) &&
	     ((sender_मुक्त <= (conn->rmb_desc->len / 2)) ||
	      conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked))) अणु
		अगर (conn->समाप्तed ||
		    conn->local_rx_ctrl.conn_state_flags.peer_conn_पात)
			वापस;
		अगर ((smc_cdc_get_slot_and_msg_send(conn) < 0) &&
		    !conn->समाप्तed) अणु
			queue_delayed_work(conn->lgr->tx_wq, &conn->tx_work,
					   SMC_TX_WORK_DELAY);
			वापस;
		पूर्ण
	पूर्ण
	अगर (conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked &&
	    !atomic_पढ़ो(&conn->bytes_to_rcv))
		conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked = 0;
पूर्ण

/***************************** send initialize *******************************/

/* Initialize send properties on connection establishment. NB: not __init! */
व्योम smc_tx_init(काष्ठा smc_sock *smc)
अणु
	smc->sk.sk_ग_लिखो_space = smc_tx_ग_लिखो_space;
पूर्ण
