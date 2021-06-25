<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Connection Data Control (CDC)
 * handles flow control
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/spinlock.h>

#समावेश "smc.h"
#समावेश "smc_wr.h"
#समावेश "smc_cdc.h"
#समावेश "smc_tx.h"
#समावेश "smc_rx.h"
#समावेश "smc_close.h"

/********************************** send *************************************/

/* handler क्रम send/transmission completion of a CDC msg */
अटल व्योम smc_cdc_tx_handler(काष्ठा smc_wr_tx_pend_priv *pnd_snd,
			       काष्ठा smc_link *link,
			       क्रमागत ib_wc_status wc_status)
अणु
	काष्ठा smc_cdc_tx_pend *cdcpend = (काष्ठा smc_cdc_tx_pend *)pnd_snd;
	काष्ठा smc_connection *conn = cdcpend->conn;
	काष्ठा smc_sock *smc;
	पूर्णांक dअगरf;

	अगर (!conn)
		/* alपढ़ोy dismissed */
		वापस;

	smc = container_of(conn, काष्ठा smc_sock, conn);
	bh_lock_sock(&smc->sk);
	अगर (!wc_status) अणु
		dअगरf = smc_curs_dअगरf(cdcpend->conn->sndbuf_desc->len,
				     &cdcpend->conn->tx_curs_fin,
				     &cdcpend->cursor);
		/* sndbuf_space is decreased in smc_sendmsg */
		smp_mb__beक्रमe_atomic();
		atomic_add(dअगरf, &cdcpend->conn->sndbuf_space);
		/* guarantee 0 <= sndbuf_space <= sndbuf_desc->len */
		smp_mb__after_atomic();
		smc_curs_copy(&conn->tx_curs_fin, &cdcpend->cursor, conn);
		smc_curs_copy(&conn->local_tx_ctrl_fin, &cdcpend->p_cursor,
			      conn);
		conn->tx_cdc_seq_fin = cdcpend->ctrl_seq;
	पूर्ण
	smc_tx_sndbuf_nonfull(smc);
	bh_unlock_sock(&smc->sk);
पूर्ण

पूर्णांक smc_cdc_get_मुक्त_slot(काष्ठा smc_connection *conn,
			  काष्ठा smc_link *link,
			  काष्ठा smc_wr_buf **wr_buf,
			  काष्ठा smc_rdma_wr **wr_rdma_buf,
			  काष्ठा smc_cdc_tx_pend **pend)
अणु
	पूर्णांक rc;

	rc = smc_wr_tx_get_मुक्त_slot(link, smc_cdc_tx_handler, wr_buf,
				     wr_rdma_buf,
				     (काष्ठा smc_wr_tx_pend_priv **)pend);
	अगर (conn->समाप्तed) अणु
		/* abnormal termination */
		अगर (!rc)
			smc_wr_tx_put_slot(link,
					   (काष्ठा smc_wr_tx_pend_priv *)pend);
		rc = -EPIPE;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम smc_cdc_add_pending_send(काष्ठा smc_connection *conn,
					    काष्ठा smc_cdc_tx_pend *pend)
अणु
	BUILD_BUG_ON_MSG(
		माप(काष्ठा smc_cdc_msg) > SMC_WR_BUF_SIZE,
		"must increase SMC_WR_BUF_SIZE to at least sizeof(struct smc_cdc_msg)");
	BUILD_BUG_ON_MSG(
		दुरत्वend(काष्ठा smc_cdc_msg, reserved) > SMC_WR_TX_SIZE,
		"must adapt SMC_WR_TX_SIZE to sizeof(struct smc_cdc_msg); if not all smc_wr upper layer protocols use the same message size any more, must start to set link->wr_tx_sges[i].length on each individual smc_wr_tx_send()");
	BUILD_BUG_ON_MSG(
		माप(काष्ठा smc_cdc_tx_pend) > SMC_WR_TX_PEND_PRIV_SIZE,
		"must increase SMC_WR_TX_PEND_PRIV_SIZE to at least sizeof(struct smc_cdc_tx_pend)");
	pend->conn = conn;
	pend->cursor = conn->tx_curs_sent;
	pend->p_cursor = conn->local_tx_ctrl.prod;
	pend->ctrl_seq = conn->tx_cdc_seq;
पूर्ण

पूर्णांक smc_cdc_msg_send(काष्ठा smc_connection *conn,
		     काष्ठा smc_wr_buf *wr_buf,
		     काष्ठा smc_cdc_tx_pend *pend)
अणु
	काष्ठा smc_link *link = conn->lnk;
	जोड़ smc_host_cursor cfed;
	पूर्णांक rc;

	smc_cdc_add_pending_send(conn, pend);

	conn->tx_cdc_seq++;
	conn->local_tx_ctrl.seqno = conn->tx_cdc_seq;
	smc_host_msg_to_cdc((काष्ठा smc_cdc_msg *)wr_buf, conn, &cfed);
	rc = smc_wr_tx_send(link, (काष्ठा smc_wr_tx_pend_priv *)pend);
	अगर (!rc) अणु
		smc_curs_copy(&conn->rx_curs_confirmed, &cfed, conn);
		conn->local_rx_ctrl.prod_flags.cons_curs_upd_req = 0;
	पूर्ण अन्यथा अणु
		conn->tx_cdc_seq--;
		conn->local_tx_ctrl.seqno = conn->tx_cdc_seq;
	पूर्ण

	वापस rc;
पूर्ण

/* send a validation msg indicating the move of a conn to an other QP link */
पूर्णांक smcr_cdc_msg_send_validation(काष्ठा smc_connection *conn,
				 काष्ठा smc_cdc_tx_pend *pend,
				 काष्ठा smc_wr_buf *wr_buf)
अणु
	काष्ठा smc_host_cdc_msg *local = &conn->local_tx_ctrl;
	काष्ठा smc_link *link = conn->lnk;
	काष्ठा smc_cdc_msg *peer;
	पूर्णांक rc;

	peer = (काष्ठा smc_cdc_msg *)wr_buf;
	peer->common.type = local->common.type;
	peer->len = local->len;
	peer->seqno = htons(conn->tx_cdc_seq_fin); /* seqno last compl. tx */
	peer->token = htonl(local->token);
	peer->prod_flags.failover_validation = 1;

	rc = smc_wr_tx_send(link, (काष्ठा smc_wr_tx_pend_priv *)pend);
	वापस rc;
पूर्ण

अटल पूर्णांक smcr_cdc_get_slot_and_msg_send(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_cdc_tx_pend *pend;
	काष्ठा smc_wr_buf *wr_buf;
	काष्ठा smc_link *link;
	bool again = false;
	पूर्णांक rc;

again:
	link = conn->lnk;
	rc = smc_cdc_get_मुक्त_slot(conn, link, &wr_buf, शून्य, &pend);
	अगर (rc)
		वापस rc;

	spin_lock_bh(&conn->send_lock);
	अगर (link != conn->lnk) अणु
		/* link of connection changed, try again one समय*/
		spin_unlock_bh(&conn->send_lock);
		smc_wr_tx_put_slot(link,
				   (काष्ठा smc_wr_tx_pend_priv *)pend);
		अगर (again)
			वापस -ENOLINK;
		again = true;
		जाओ again;
	पूर्ण
	rc = smc_cdc_msg_send(conn, wr_buf, pend);
	spin_unlock_bh(&conn->send_lock);
	वापस rc;
पूर्ण

पूर्णांक smc_cdc_get_slot_and_msg_send(काष्ठा smc_connection *conn)
अणु
	पूर्णांक rc;

	अगर (!conn->lgr || (conn->lgr->is_smcd && conn->lgr->peer_shutकरोwn))
		वापस -EPIPE;

	अगर (conn->lgr->is_smcd) अणु
		spin_lock_bh(&conn->send_lock);
		rc = smcd_cdc_msg_send(conn);
		spin_unlock_bh(&conn->send_lock);
	पूर्ण अन्यथा अणु
		rc = smcr_cdc_get_slot_and_msg_send(conn);
	पूर्ण

	वापस rc;
पूर्ण

अटल bool smc_cdc_tx_filter(काष्ठा smc_wr_tx_pend_priv *tx_pend,
			      अचिन्हित दीर्घ data)
अणु
	काष्ठा smc_connection *conn = (काष्ठा smc_connection *)data;
	काष्ठा smc_cdc_tx_pend *cdc_pend =
		(काष्ठा smc_cdc_tx_pend *)tx_pend;

	वापस cdc_pend->conn == conn;
पूर्ण

अटल व्योम smc_cdc_tx_dismisser(काष्ठा smc_wr_tx_pend_priv *tx_pend)
अणु
	काष्ठा smc_cdc_tx_pend *cdc_pend =
		(काष्ठा smc_cdc_tx_pend *)tx_pend;

	cdc_pend->conn = शून्य;
पूर्ण

व्योम smc_cdc_tx_dismiss_slots(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_link *link = conn->lnk;

	smc_wr_tx_dismiss_slots(link, SMC_CDC_MSG_TYPE,
				smc_cdc_tx_filter, smc_cdc_tx_dismisser,
				(अचिन्हित दीर्घ)conn);
पूर्ण

/* Send a SMC-D CDC header.
 * This increments the मुक्त space available in our send buffer.
 * Also update the confirmed receive buffer with what was sent to the peer.
 */
पूर्णांक smcd_cdc_msg_send(काष्ठा smc_connection *conn)
अणु
	काष्ठा smc_sock *smc = container_of(conn, काष्ठा smc_sock, conn);
	जोड़ smc_host_cursor curs;
	काष्ठा smcd_cdc_msg cdc;
	पूर्णांक rc, dअगरf;

	स_रखो(&cdc, 0, माप(cdc));
	cdc.common.type = SMC_CDC_MSG_TYPE;
	curs.acurs.counter = atomic64_पढ़ो(&conn->local_tx_ctrl.prod.acurs);
	cdc.prod.wrap = curs.wrap;
	cdc.prod.count = curs.count;
	curs.acurs.counter = atomic64_पढ़ो(&conn->local_tx_ctrl.cons.acurs);
	cdc.cons.wrap = curs.wrap;
	cdc.cons.count = curs.count;
	cdc.cons.prod_flags = conn->local_tx_ctrl.prod_flags;
	cdc.cons.conn_state_flags = conn->local_tx_ctrl.conn_state_flags;
	rc = smcd_tx_ism_ग_लिखो(conn, &cdc, माप(cdc), 0, 1);
	अगर (rc)
		वापस rc;
	smc_curs_copy(&conn->rx_curs_confirmed, &curs, conn);
	conn->local_rx_ctrl.prod_flags.cons_curs_upd_req = 0;
	/* Calculate transmitted data and increment मुक्त send buffer space */
	dअगरf = smc_curs_dअगरf(conn->sndbuf_desc->len, &conn->tx_curs_fin,
			     &conn->tx_curs_sent);
	/* increased by confirmed number of bytes */
	smp_mb__beक्रमe_atomic();
	atomic_add(dअगरf, &conn->sndbuf_space);
	/* guarantee 0 <= sndbuf_space <= sndbuf_desc->len */
	smp_mb__after_atomic();
	smc_curs_copy(&conn->tx_curs_fin, &conn->tx_curs_sent, conn);

	smc_tx_sndbuf_nonfull(smc);
	वापस rc;
पूर्ण

/********************************* receive ***********************************/

अटल अंतरभूत bool smc_cdc_beक्रमe(u16 seq1, u16 seq2)
अणु
	वापस (s16)(seq1 - seq2) < 0;
पूर्ण

अटल व्योम smc_cdc_handle_urg_data_arrival(काष्ठा smc_sock *smc,
					    पूर्णांक *dअगरf_prod)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	अक्षर *base;

	/* new data included urgent business */
	smc_curs_copy(&conn->urg_curs, &conn->local_rx_ctrl.prod, conn);
	conn->urg_state = SMC_URG_VALID;
	अगर (!sock_flag(&smc->sk, SOCK_URGINLINE))
		/* we'll skip the urgent byte, so don't account क्रम it */
		(*dअगरf_prod)--;
	base = (अक्षर *)conn->rmb_desc->cpu_addr + conn->rx_off;
	अगर (conn->urg_curs.count)
		conn->urg_rx_byte = *(base + conn->urg_curs.count - 1);
	अन्यथा
		conn->urg_rx_byte = *(base + conn->rmb_desc->len - 1);
	sk_send_sigurg(&smc->sk);
पूर्ण

अटल व्योम smc_cdc_msg_validate(काष्ठा smc_sock *smc, काष्ठा smc_cdc_msg *cdc,
				 काष्ठा smc_link *link)
अणु
	काष्ठा smc_connection *conn = &smc->conn;
	u16 recv_seq = ntohs(cdc->seqno);
	s16 dअगरf;

	/* check that seqnum was seen beक्रमe */
	dअगरf = conn->local_rx_ctrl.seqno - recv_seq;
	अगर (dअगरf < 0) अणु /* dअगरf larger than 0x7fff */
		/* drop connection */
		conn->out_of_sync = 1;	/* prevent any further receives */
		spin_lock_bh(&conn->send_lock);
		conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;
		conn->lnk = link;
		spin_unlock_bh(&conn->send_lock);
		sock_hold(&smc->sk); /* sock_put in पात_work */
		अगर (!queue_work(smc_बंद_wq, &conn->पात_work))
			sock_put(&smc->sk);
	पूर्ण
पूर्ण

अटल व्योम smc_cdc_msg_recv_action(काष्ठा smc_sock *smc,
				    काष्ठा smc_cdc_msg *cdc)
अणु
	जोड़ smc_host_cursor cons_old, prod_old;
	काष्ठा smc_connection *conn = &smc->conn;
	पूर्णांक dअगरf_cons, dअगरf_prod;

	smc_curs_copy(&prod_old, &conn->local_rx_ctrl.prod, conn);
	smc_curs_copy(&cons_old, &conn->local_rx_ctrl.cons, conn);
	smc_cdc_msg_to_host(&conn->local_rx_ctrl, cdc, conn);

	dअगरf_cons = smc_curs_dअगरf(conn->peer_rmbe_size, &cons_old,
				  &conn->local_rx_ctrl.cons);
	अगर (dअगरf_cons) अणु
		/* peer_rmbe_space is decreased during data transfer with RDMA
		 * ग_लिखो
		 */
		smp_mb__beक्रमe_atomic();
		atomic_add(dअगरf_cons, &conn->peer_rmbe_space);
		/* guarantee 0 <= peer_rmbe_space <= peer_rmbe_size */
		smp_mb__after_atomic();
	पूर्ण

	dअगरf_prod = smc_curs_dअगरf(conn->rmb_desc->len, &prod_old,
				  &conn->local_rx_ctrl.prod);
	अगर (dअगरf_prod) अणु
		अगर (conn->local_rx_ctrl.prod_flags.urg_data_present)
			smc_cdc_handle_urg_data_arrival(smc, &dअगरf_prod);
		/* bytes_to_rcv is decreased in smc_recvmsg */
		smp_mb__beक्रमe_atomic();
		atomic_add(dअगरf_prod, &conn->bytes_to_rcv);
		/* guarantee 0 <= bytes_to_rcv <= rmb_desc->len */
		smp_mb__after_atomic();
		smc->sk.sk_data_पढ़ोy(&smc->sk);
	पूर्ण अन्यथा अणु
		अगर (conn->local_rx_ctrl.prod_flags.ग_लिखो_blocked)
			smc->sk.sk_data_पढ़ोy(&smc->sk);
		अगर (conn->local_rx_ctrl.prod_flags.urg_data_pending)
			conn->urg_state = SMC_URG_NOTYET;
	पूर्ण

	/* trigger sndbuf consumer: RDMA ग_लिखो पूर्णांकo peer RMBE and CDC */
	अगर ((dअगरf_cons && smc_tx_prepared_sends(conn)) ||
	    conn->local_rx_ctrl.prod_flags.cons_curs_upd_req ||
	    conn->local_rx_ctrl.prod_flags.urg_data_pending)
		smc_tx_sndbuf_nonempty(conn);

	अगर (dअगरf_cons && conn->urg_tx_pend &&
	    atomic_पढ़ो(&conn->peer_rmbe_space) == conn->peer_rmbe_size) अणु
		/* urg data confirmed by peer, indicate we're पढ़ोy क्रम more */
		conn->urg_tx_pend = false;
		smc->sk.sk_ग_लिखो_space(&smc->sk);
	पूर्ण

	अगर (conn->local_rx_ctrl.conn_state_flags.peer_conn_पात) अणु
		smc->sk.sk_err = ECONNRESET;
		conn->local_tx_ctrl.conn_state_flags.peer_conn_पात = 1;
	पूर्ण
	अगर (smc_cdc_rxed_any_बंद_or_sendकरोne(conn)) अणु
		smc->sk.sk_shutकरोwn |= RCV_SHUTDOWN;
		अगर (smc->clcsock && smc->clcsock->sk)
			smc->clcsock->sk->sk_shutकरोwn |= RCV_SHUTDOWN;
		sock_set_flag(&smc->sk, SOCK_DONE);
		sock_hold(&smc->sk); /* sock_put in बंद_work */
		अगर (!queue_work(smc_बंद_wq, &conn->बंद_work))
			sock_put(&smc->sk);
	पूर्ण
पूर्ण

/* called under tasklet context */
अटल व्योम smc_cdc_msg_recv(काष्ठा smc_sock *smc, काष्ठा smc_cdc_msg *cdc)
अणु
	sock_hold(&smc->sk);
	bh_lock_sock(&smc->sk);
	smc_cdc_msg_recv_action(smc, cdc);
	bh_unlock_sock(&smc->sk);
	sock_put(&smc->sk); /* no मुक्त sk in softirq-context */
पूर्ण

/* Schedule a tasklet क्रम this connection. Triggered from the ISM device IRQ
 * handler to indicate update in the DMBE.
 *
 * Context:
 * - tasklet context
 */
अटल व्योम smcd_cdc_rx_tsklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा smc_connection *conn = from_tasklet(conn, t, rx_tsklet);
	काष्ठा smcd_cdc_msg *data_cdc;
	काष्ठा smcd_cdc_msg cdc;
	काष्ठा smc_sock *smc;

	अगर (!conn || conn->समाप्तed)
		वापस;

	data_cdc = (काष्ठा smcd_cdc_msg *)conn->rmb_desc->cpu_addr;
	smcd_curs_copy(&cdc.prod, &data_cdc->prod, conn);
	smcd_curs_copy(&cdc.cons, &data_cdc->cons, conn);
	smc = container_of(conn, काष्ठा smc_sock, conn);
	smc_cdc_msg_recv(smc, (काष्ठा smc_cdc_msg *)&cdc);
पूर्ण

/* Initialize receive tasklet. Called from ISM device IRQ handler to start
 * receiver side.
 */
व्योम smcd_cdc_rx_init(काष्ठा smc_connection *conn)
अणु
	tasklet_setup(&conn->rx_tsklet, smcd_cdc_rx_tsklet);
पूर्ण

/***************************** init, निकास, misc ******************************/

अटल व्योम smc_cdc_rx_handler(काष्ठा ib_wc *wc, व्योम *buf)
अणु
	काष्ठा smc_link *link = (काष्ठा smc_link *)wc->qp->qp_context;
	काष्ठा smc_cdc_msg *cdc = buf;
	काष्ठा smc_connection *conn;
	काष्ठा smc_link_group *lgr;
	काष्ठा smc_sock *smc;

	अगर (wc->byte_len < दुरत्व(काष्ठा smc_cdc_msg, reserved))
		वापस; /* लघु message */
	अगर (cdc->len != SMC_WR_TX_SIZE)
		वापस; /* invalid message */

	/* lookup connection */
	lgr = smc_get_lgr(link);
	पढ़ो_lock_bh(&lgr->conns_lock);
	conn = smc_lgr_find_conn(ntohl(cdc->token), lgr);
	पढ़ो_unlock_bh(&lgr->conns_lock);
	अगर (!conn || conn->out_of_sync)
		वापस;
	smc = container_of(conn, काष्ठा smc_sock, conn);

	अगर (cdc->prod_flags.failover_validation) अणु
		smc_cdc_msg_validate(smc, cdc, link);
		वापस;
	पूर्ण
	अगर (smc_cdc_beक्रमe(ntohs(cdc->seqno),
			   conn->local_rx_ctrl.seqno))
		/* received seqno is old */
		वापस;

	smc_cdc_msg_recv(smc, cdc);
पूर्ण

अटल काष्ठा smc_wr_rx_handler smc_cdc_rx_handlers[] = अणु
	अणु
		.handler	= smc_cdc_rx_handler,
		.type		= SMC_CDC_MSG_TYPE
	पूर्ण,
	अणु
		.handler	= शून्य,
	पूर्ण
पूर्ण;

पूर्णांक __init smc_cdc_init(व्योम)
अणु
	काष्ठा smc_wr_rx_handler *handler;
	पूर्णांक rc = 0;

	क्रम (handler = smc_cdc_rx_handlers; handler->handler; handler++) अणु
		INIT_HLIST_NODE(&handler->list);
		rc = smc_wr_rx_रेजिस्टर_handler(handler);
		अगर (rc)
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
