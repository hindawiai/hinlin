<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/*          Fredy Neeser */
/*          Greg Joyce <greg@खोलोgridcomputing.com> */
/* Copyright (c) 2008-2019, IBM Corporation */
/* Copyright (c) 2017, Open Grid Computing, Inc. */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/addrconf.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <linux/inet.h>
#समावेश <linux/tcp.h>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "siw.h"
#समावेश "siw_cm.h"

/*
 * Set to any combination of
 * MPA_V2_RDMA_NO_RTR, MPA_V2_RDMA_READ_RTR, MPA_V2_RDMA_WRITE_RTR
 */
अटल __be16 rtr_type = MPA_V2_RDMA_READ_RTR | MPA_V2_RDMA_WRITE_RTR;
अटल स्थिर bool relaxed_ird_negotiation = true;

अटल व्योम siw_cm_llp_state_change(काष्ठा sock *s);
अटल व्योम siw_cm_llp_data_पढ़ोy(काष्ठा sock *s);
अटल व्योम siw_cm_llp_ग_लिखो_space(काष्ठा sock *s);
अटल व्योम siw_cm_llp_error_report(काष्ठा sock *s);
अटल पूर्णांक siw_cm_upcall(काष्ठा siw_cep *cep, क्रमागत iw_cm_event_type reason,
			 पूर्णांक status);

अटल व्योम siw_sk_assign_cm_upcalls(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_state_change = siw_cm_llp_state_change;
	sk->sk_data_पढ़ोy = siw_cm_llp_data_पढ़ोy;
	sk->sk_ग_लिखो_space = siw_cm_llp_ग_लिखो_space;
	sk->sk_error_report = siw_cm_llp_error_report;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम siw_sk_save_upcalls(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep = sk_to_cep(sk);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	cep->sk_state_change = sk->sk_state_change;
	cep->sk_data_पढ़ोy = sk->sk_data_पढ़ोy;
	cep->sk_ग_लिखो_space = sk->sk_ग_लिखो_space;
	cep->sk_error_report = sk->sk_error_report;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम siw_sk_restore_upcalls(काष्ठा sock *sk, काष्ठा siw_cep *cep)
अणु
	sk->sk_state_change = cep->sk_state_change;
	sk->sk_data_पढ़ोy = cep->sk_data_पढ़ोy;
	sk->sk_ग_लिखो_space = cep->sk_ग_लिखो_space;
	sk->sk_error_report = cep->sk_error_report;
	sk->sk_user_data = शून्य;
पूर्ण

अटल व्योम siw_qp_socket_assoc(काष्ठा siw_cep *cep, काष्ठा siw_qp *qp)
अणु
	काष्ठा socket *s = cep->sock;
	काष्ठा sock *sk = s->sk;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);

	qp->attrs.sk = s;
	sk->sk_data_पढ़ोy = siw_qp_llp_data_पढ़ोy;
	sk->sk_ग_लिखो_space = siw_qp_llp_ग_लिखो_space;

	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम siw_socket_disassoc(काष्ठा socket *s)
अणु
	काष्ठा sock *sk = s->sk;
	काष्ठा siw_cep *cep;

	अगर (sk) अणु
		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		cep = sk_to_cep(sk);
		अगर (cep) अणु
			siw_sk_restore_upcalls(sk, cep);
			siw_cep_put(cep);
		पूर्ण अन्यथा अणु
			pr_warn("siw: cannot restore sk callbacks: no ep\n");
		पूर्ण
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण अन्यथा अणु
		pr_warn("siw: cannot restore sk callbacks: no sk\n");
	पूर्ण
पूर्ण

अटल व्योम siw_rtr_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep;
	काष्ठा siw_qp *qp = शून्य;
	पढ़ो_descriptor_t rd_desc;

	पढ़ो_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	अगर (!cep) अणु
		WARN(1, "No connection endpoint\n");
		जाओ out;
	पूर्ण
	qp = sk_to_qp(sk);

	स_रखो(&rd_desc, 0, माप(rd_desc));
	rd_desc.arg.data = qp;
	rd_desc.count = 1;

	tcp_पढ़ो_sock(sk, &rd_desc, siw_tcp_rx_data);
	/*
	 * Check अगर first frame was successfully processed.
	 * Signal connection full establishment अगर yes.
	 * Failed data processing would have alपढ़ोy scheduled
	 * connection drop.
	 */
	अगर (!qp->rx_stream.rx_suspend)
		siw_cm_upcall(cep, IW_CM_EVENT_ESTABLISHED, 0);
out:
	पढ़ो_unlock(&sk->sk_callback_lock);
	अगर (qp)
		siw_qp_socket_assoc(cep, qp);
पूर्ण

अटल व्योम siw_sk_assign_rtr_upcalls(काष्ठा siw_cep *cep)
अणु
	काष्ठा sock *sk = cep->sock->sk;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_data_पढ़ोy = siw_rtr_data_पढ़ोy;
	sk->sk_ग_लिखो_space = siw_qp_llp_ग_लिखो_space;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम siw_cep_socket_assoc(काष्ठा siw_cep *cep, काष्ठा socket *s)
अणु
	cep->sock = s;
	siw_cep_get(cep);
	s->sk->sk_user_data = cep;

	siw_sk_save_upcalls(s->sk);
	siw_sk_assign_cm_upcalls(s->sk);
पूर्ण

अटल काष्ठा siw_cep *siw_cep_alloc(काष्ठा siw_device *sdev)
अणु
	काष्ठा siw_cep *cep = kzalloc(माप(*cep), GFP_KERNEL);
	अचिन्हित दीर्घ flags;

	अगर (!cep)
		वापस शून्य;

	INIT_LIST_HEAD(&cep->listenq);
	INIT_LIST_HEAD(&cep->devq);
	INIT_LIST_HEAD(&cep->work_मुक्तlist);

	kref_init(&cep->ref);
	cep->state = SIW_EPSTATE_IDLE;
	init_रुकोqueue_head(&cep->रुकोq);
	spin_lock_init(&cep->lock);
	cep->sdev = sdev;
	cep->enhanced_rdma_conn_est = false;

	spin_lock_irqsave(&sdev->lock, flags);
	list_add_tail(&cep->devq, &sdev->cep_list);
	spin_unlock_irqrestore(&sdev->lock, flags);

	siw_dbg_cep(cep, "new endpoint\n");
	वापस cep;
पूर्ण

अटल व्योम siw_cm_मुक्त_work(काष्ठा siw_cep *cep)
अणु
	काष्ठा list_head *w, *पंचांगp;
	काष्ठा siw_cm_work *work;

	list_क्रम_each_safe(w, पंचांगp, &cep->work_मुक्तlist) अणु
		work = list_entry(w, काष्ठा siw_cm_work, list);
		list_del(&work->list);
		kमुक्त(work);
	पूर्ण
पूर्ण

अटल व्योम siw_cancel_mpaसमयr(काष्ठा siw_cep *cep)
अणु
	spin_lock_bh(&cep->lock);
	अगर (cep->mpa_समयr) अणु
		अगर (cancel_delayed_work(&cep->mpa_समयr->work)) अणु
			siw_cep_put(cep);
			kमुक्त(cep->mpa_समयr); /* not needed again */
		पूर्ण
		cep->mpa_समयr = शून्य;
	पूर्ण
	spin_unlock_bh(&cep->lock);
पूर्ण

अटल व्योम siw_put_work(काष्ठा siw_cm_work *work)
अणु
	INIT_LIST_HEAD(&work->list);
	spin_lock_bh(&work->cep->lock);
	list_add(&work->list, &work->cep->work_मुक्तlist);
	spin_unlock_bh(&work->cep->lock);
पूर्ण

अटल व्योम siw_cep_set_inuse(काष्ठा siw_cep *cep)
अणु
	अचिन्हित दीर्घ flags;
retry:
	spin_lock_irqsave(&cep->lock, flags);

	अगर (cep->in_use) अणु
		spin_unlock_irqrestore(&cep->lock, flags);
		रुको_event_पूर्णांकerruptible(cep->रुकोq, !cep->in_use);
		अगर (संकेत_pending(current))
			flush_संकेतs(current);
		जाओ retry;
	पूर्ण अन्यथा अणु
		cep->in_use = 1;
		spin_unlock_irqrestore(&cep->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम siw_cep_set_मुक्त(काष्ठा siw_cep *cep)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cep->lock, flags);
	cep->in_use = 0;
	spin_unlock_irqrestore(&cep->lock, flags);

	wake_up(&cep->रुकोq);
पूर्ण

अटल व्योम __siw_cep_dealloc(काष्ठा kref *ref)
अणु
	काष्ठा siw_cep *cep = container_of(ref, काष्ठा siw_cep, ref);
	काष्ठा siw_device *sdev = cep->sdev;
	अचिन्हित दीर्घ flags;

	WARN_ON(cep->listen_cep);

	/* kमुक्त(शून्य) is safe */
	kमुक्त(cep->mpa.pdata);
	spin_lock_bh(&cep->lock);
	अगर (!list_empty(&cep->work_मुक्तlist))
		siw_cm_मुक्त_work(cep);
	spin_unlock_bh(&cep->lock);

	spin_lock_irqsave(&sdev->lock, flags);
	list_del(&cep->devq);
	spin_unlock_irqrestore(&sdev->lock, flags);

	siw_dbg_cep(cep, "free endpoint\n");
	kमुक्त(cep);
पूर्ण

अटल काष्ठा siw_cm_work *siw_get_work(काष्ठा siw_cep *cep)
अणु
	काष्ठा siw_cm_work *work = शून्य;

	spin_lock_bh(&cep->lock);
	अगर (!list_empty(&cep->work_मुक्तlist)) अणु
		work = list_entry(cep->work_मुक्तlist.next, काष्ठा siw_cm_work,
				  list);
		list_del_init(&work->list);
	पूर्ण
	spin_unlock_bh(&cep->lock);
	वापस work;
पूर्ण

अटल पूर्णांक siw_cm_alloc_work(काष्ठा siw_cep *cep, पूर्णांक num)
अणु
	काष्ठा siw_cm_work *work;

	जबतक (num--) अणु
		work = kदो_स्मृति(माप(*work), GFP_KERNEL);
		अगर (!work) अणु
			अगर (!(list_empty(&cep->work_मुक्तlist)))
				siw_cm_मुक्त_work(cep);
			वापस -ENOMEM;
		पूर्ण
		work->cep = cep;
		INIT_LIST_HEAD(&work->list);
		list_add(&work->list, &cep->work_मुक्तlist);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * siw_cm_upcall()
 *
 * Upcall to IWCM to inक्रमm about async connection events
 */
अटल पूर्णांक siw_cm_upcall(काष्ठा siw_cep *cep, क्रमागत iw_cm_event_type reason,
			 पूर्णांक status)
अणु
	काष्ठा iw_cm_event event;
	काष्ठा iw_cm_id *id;

	स_रखो(&event, 0, माप(event));
	event.status = status;
	event.event = reason;

	अगर (reason == IW_CM_EVENT_CONNECT_REQUEST) अणु
		event.provider_data = cep;
		id = cep->listen_cep->cm_id;
	पूर्ण अन्यथा अणु
		id = cep->cm_id;
	पूर्ण
	/* Signal IRD and ORD */
	अगर (reason == IW_CM_EVENT_ESTABLISHED ||
	    reason == IW_CM_EVENT_CONNECT_REPLY) अणु
		/* Signal negotiated IRD/ORD values we will use */
		event.ird = cep->ird;
		event.ord = cep->ord;
	पूर्ण अन्यथा अगर (reason == IW_CM_EVENT_CONNECT_REQUEST) अणु
		event.ird = cep->ord;
		event.ord = cep->ird;
	पूर्ण
	/* Signal निजी data and address inक्रमmation */
	अगर (reason == IW_CM_EVENT_CONNECT_REQUEST ||
	    reason == IW_CM_EVENT_CONNECT_REPLY) अणु
		u16 pd_len = be16_to_cpu(cep->mpa.hdr.params.pd_len);

		अगर (pd_len) अणु
			/*
			 * hand over MPA निजी data
			 */
			event.निजी_data_len = pd_len;
			event.निजी_data = cep->mpa.pdata;

			/* Hide MPA V2 IRD/ORD control */
			अगर (cep->enhanced_rdma_conn_est) अणु
				event.निजी_data_len -=
					माप(काष्ठा mpa_v2_data);
				event.निजी_data +=
					माप(काष्ठा mpa_v2_data);
			पूर्ण
		पूर्ण
		getname_local(cep->sock, &event.local_addr);
		getname_peer(cep->sock, &event.remote_addr);
	पूर्ण
	siw_dbg_cep(cep, "[QP %u]: reason=%d, status=%d\n",
		    cep->qp ? qp_id(cep->qp) : अच_पूर्णांक_उच्च, reason, status);

	वापस id->event_handler(id, &event);
पूर्ण

/*
 * siw_qp_cm_drop()
 *
 * Drops established LLP connection अगर present and not alपढ़ोy
 * scheduled क्रम dropping. Called from user context, SQ workqueue
 * or receive IRQ. Caller संकेतs अगर socket can be immediately
 * बंदd (basically, अगर not in IRQ).
 */
व्योम siw_qp_cm_drop(काष्ठा siw_qp *qp, पूर्णांक schedule)
अणु
	काष्ठा siw_cep *cep = qp->cep;

	qp->rx_stream.rx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;

	अगर (!qp->cep)
		वापस;

	अगर (schedule) अणु
		siw_cm_queue_work(cep, SIW_CM_WORK_CLOSE_LLP);
	पूर्ण अन्यथा अणु
		siw_cep_set_inuse(cep);

		अगर (cep->state == SIW_EPSTATE_CLOSED) अणु
			siw_dbg_cep(cep, "already closed\n");
			जाओ out;
		पूर्ण
		siw_dbg_cep(cep, "immediate close, state %d\n", cep->state);

		अगर (qp->term_info.valid)
			siw_send_terminate(qp);

		अगर (cep->cm_id) अणु
			चयन (cep->state) अणु
			हाल SIW_EPSTATE_AWAIT_MPAREP:
				siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
					      -EINVAL);
				अवरोध;

			हाल SIW_EPSTATE_RDMA_MODE:
				siw_cm_upcall(cep, IW_CM_EVENT_CLOSE, 0);
				अवरोध;

			हाल SIW_EPSTATE_IDLE:
			हाल SIW_EPSTATE_LISTENING:
			हाल SIW_EPSTATE_CONNECTING:
			हाल SIW_EPSTATE_AWAIT_MPAREQ:
			हाल SIW_EPSTATE_RECVD_MPAREQ:
			हाल SIW_EPSTATE_CLOSED:
			शेष:
				अवरोध;
			पूर्ण
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = शून्य;
			siw_cep_put(cep);
		पूर्ण
		cep->state = SIW_EPSTATE_CLOSED;

		अगर (cep->sock) अणु
			siw_socket_disassoc(cep->sock);
			/*
			 * Immediately बंद socket
			 */
			sock_release(cep->sock);
			cep->sock = शून्य;
		पूर्ण
		अगर (cep->qp) अणु
			cep->qp = शून्य;
			siw_qp_put(qp);
		पूर्ण
out:
		siw_cep_set_मुक्त(cep);
	पूर्ण
पूर्ण

व्योम siw_cep_put(काष्ठा siw_cep *cep)
अणु
	WARN_ON(kref_पढ़ो(&cep->ref) < 1);
	kref_put(&cep->ref, __siw_cep_dealloc);
पूर्ण

व्योम siw_cep_get(काष्ठा siw_cep *cep)
अणु
	kref_get(&cep->ref);
पूर्ण

/*
 * Expects params->pd_len in host byte order
 */
अटल पूर्णांक siw_send_mpareqrep(काष्ठा siw_cep *cep, स्थिर व्योम *pdata, u8 pd_len)
अणु
	काष्ठा socket *s = cep->sock;
	काष्ठा mpa_rr *rr = &cep->mpa.hdr;
	काष्ठा kvec iov[3];
	काष्ठा msghdr msg;
	पूर्णांक rv;
	पूर्णांक iovec_num = 0;
	पूर्णांक mpa_len;

	स_रखो(&msg, 0, माप(msg));

	iov[iovec_num].iov_base = rr;
	iov[iovec_num].iov_len = माप(*rr);
	mpa_len = माप(*rr);

	अगर (cep->enhanced_rdma_conn_est) अणु
		iovec_num++;
		iov[iovec_num].iov_base = &cep->mpa.v2_ctrl;
		iov[iovec_num].iov_len = माप(cep->mpa.v2_ctrl);
		mpa_len += माप(cep->mpa.v2_ctrl);
	पूर्ण
	अगर (pd_len) अणु
		iovec_num++;
		iov[iovec_num].iov_base = (अक्षर *)pdata;
		iov[iovec_num].iov_len = pd_len;
		mpa_len += pd_len;
	पूर्ण
	अगर (cep->enhanced_rdma_conn_est)
		pd_len += माप(cep->mpa.v2_ctrl);

	rr->params.pd_len = cpu_to_be16(pd_len);

	rv = kernel_sendmsg(s, &msg, iov, iovec_num + 1, mpa_len);

	वापस rv < 0 ? rv : 0;
पूर्ण

/*
 * Receive MPA Request/Reply header.
 *
 * Returns 0 अगर complete MPA Request/Reply header including
 * eventual निजी data was received. Returns -EAGAIN अगर
 * header was partially received or negative error code otherwise.
 *
 * Context: May be called in process context only
 */
अटल पूर्णांक siw_recv_mpa_rr(काष्ठा siw_cep *cep)
अणु
	काष्ठा mpa_rr *hdr = &cep->mpa.hdr;
	काष्ठा socket *s = cep->sock;
	u16 pd_len;
	पूर्णांक rcvd, to_rcv;

	अगर (cep->mpa.bytes_rcvd < माप(काष्ठा mpa_rr)) अणु
		rcvd = ksock_recv(s, (अक्षर *)hdr + cep->mpa.bytes_rcvd,
				  माप(काष्ठा mpa_rr) - cep->mpa.bytes_rcvd,
				  0);
		अगर (rcvd <= 0)
			वापस -ECONNABORTED;

		cep->mpa.bytes_rcvd += rcvd;

		अगर (cep->mpa.bytes_rcvd < माप(काष्ठा mpa_rr))
			वापस -EAGAIN;

		अगर (be16_to_cpu(hdr->params.pd_len) > MPA_MAX_PRIVDATA)
			वापस -EPROTO;
	पूर्ण
	pd_len = be16_to_cpu(hdr->params.pd_len);

	/*
	 * At least the MPA Request/Reply header (frame not including
	 * निजी data) has been received.
	 * Receive (or जारी receiving) any निजी data.
	 */
	to_rcv = pd_len - (cep->mpa.bytes_rcvd - माप(काष्ठा mpa_rr));

	अगर (!to_rcv) अणु
		/*
		 * We must have hdr->params.pd_len == 0 and thus received a
		 * complete MPA Request/Reply frame.
		 * Check against peer protocol violation.
		 */
		u32 word;

		rcvd = ksock_recv(s, (अक्षर *)&word, माप(word), MSG_DONTWAIT);
		अगर (rcvd == -EAGAIN)
			वापस 0;

		अगर (rcvd == 0) अणु
			siw_dbg_cep(cep, "peer EOF\n");
			वापस -EPIPE;
		पूर्ण
		अगर (rcvd < 0) अणु
			siw_dbg_cep(cep, "error: %d\n", rcvd);
			वापस rcvd;
		पूर्ण
		siw_dbg_cep(cep, "peer sent extra data: %d\n", rcvd);

		वापस -EPROTO;
	पूर्ण

	/*
	 * At this poपूर्णांक, we must have hdr->params.pd_len != 0.
	 * A निजी data buffer माला_लो allocated अगर hdr->params.pd_len != 0.
	 */
	अगर (!cep->mpa.pdata) अणु
		cep->mpa.pdata = kदो_स्मृति(pd_len + 4, GFP_KERNEL);
		अगर (!cep->mpa.pdata)
			वापस -ENOMEM;
	पूर्ण
	rcvd = ksock_recv(
		s, cep->mpa.pdata + cep->mpa.bytes_rcvd - माप(काष्ठा mpa_rr),
		to_rcv + 4, MSG_DONTWAIT);

	अगर (rcvd < 0)
		वापस rcvd;

	अगर (rcvd > to_rcv)
		वापस -EPROTO;

	cep->mpa.bytes_rcvd += rcvd;

	अगर (to_rcv == rcvd) अणु
		siw_dbg_cep(cep, "%d bytes private data received\n", pd_len);
		वापस 0;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

/*
 * siw_proc_mpareq()
 *
 * Read MPA Request from socket and संकेत new connection to IWCM
 * अगर success. Caller must hold lock on corresponding listening CEP.
 */
अटल पूर्णांक siw_proc_mpareq(काष्ठा siw_cep *cep)
अणु
	काष्ठा mpa_rr *req;
	पूर्णांक version, rv;
	u16 pd_len;

	rv = siw_recv_mpa_rr(cep);
	अगर (rv)
		वापस rv;

	req = &cep->mpa.hdr;

	version = __mpa_rr_revision(req->params.bits);
	pd_len = be16_to_cpu(req->params.pd_len);

	अगर (version > MPA_REVISION_2)
		/* allow क्रम 0, 1, and 2 only */
		वापस -EPROTO;

	अगर (स_भेद(req->key, MPA_KEY_REQ, 16))
		वापस -EPROTO;

	/* Prepare क्रम sending MPA reply */
	स_नकल(req->key, MPA_KEY_REP, 16);

	अगर (version == MPA_REVISION_2 &&
	    (req->params.bits & MPA_RR_FLAG_ENHANCED)) अणु
		/*
		 * MPA version 2 must संकेत IRD/ORD values and P2P mode
		 * in निजी data अगर header flag MPA_RR_FLAG_ENHANCED
		 * is set.
		 */
		अगर (pd_len < माप(काष्ठा mpa_v2_data))
			जाओ reject_conn;

		cep->enhanced_rdma_conn_est = true;
	पूर्ण

	/* MPA Markers: currently not supported. Marker TX to be added. */
	अगर (req->params.bits & MPA_RR_FLAG_MARKERS)
		जाओ reject_conn;

	अगर (req->params.bits & MPA_RR_FLAG_CRC) अणु
		/*
		 * RFC 5044, page 27: CRC MUST be used अगर peer requests it.
		 * siw specअगरic: 'mpa_crc_strict' parameter to reject
		 * connection with CRC अगर local CRC off enक्रमced by
		 * 'mpa_crc_strict' module parameter.
		 */
		अगर (!mpa_crc_required && mpa_crc_strict)
			जाओ reject_conn;

		/* Enable CRC अगर requested by module parameter */
		अगर (mpa_crc_required)
			req->params.bits |= MPA_RR_FLAG_CRC;
	पूर्ण
	अगर (cep->enhanced_rdma_conn_est) अणु
		काष्ठा mpa_v2_data *v2 = (काष्ठा mpa_v2_data *)cep->mpa.pdata;

		/*
		 * Peer requested ORD becomes requested local IRD,
		 * peer requested IRD becomes requested local ORD.
		 * IRD and ORD get limited by global maximum values.
		 */
		cep->ord = ntohs(v2->ird) & MPA_IRD_ORD_MASK;
		cep->ord = min(cep->ord, SIW_MAX_ORD_QP);
		cep->ird = ntohs(v2->ord) & MPA_IRD_ORD_MASK;
		cep->ird = min(cep->ird, SIW_MAX_IRD_QP);

		/* May get overwritten by locally negotiated values */
		cep->mpa.v2_ctrl.ird = htons(cep->ird);
		cep->mpa.v2_ctrl.ord = htons(cep->ord);

		/*
		 * Support क्रम peer sent zero length Write or Read to
		 * let local side enter RTS. Writes are preferred.
		 * Sends would require pre-posting a Receive and are
		 * not supported.
		 * Propose zero length Write अगर none of Read and Write
		 * is indicated.
		 */
		अगर (v2->ird & MPA_V2_PEER_TO_PEER) अणु
			cep->mpa.v2_ctrl.ird |= MPA_V2_PEER_TO_PEER;

			अगर (v2->ord & MPA_V2_RDMA_WRITE_RTR)
				cep->mpa.v2_ctrl.ord |= MPA_V2_RDMA_WRITE_RTR;
			अन्यथा अगर (v2->ord & MPA_V2_RDMA_READ_RTR)
				cep->mpa.v2_ctrl.ord |= MPA_V2_RDMA_READ_RTR;
			अन्यथा
				cep->mpa.v2_ctrl.ord |= MPA_V2_RDMA_WRITE_RTR;
		पूर्ण
	पूर्ण

	cep->state = SIW_EPSTATE_RECVD_MPAREQ;

	/* Keep reference until IWCM accepts/rejects */
	siw_cep_get(cep);
	rv = siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REQUEST, 0);
	अगर (rv)
		siw_cep_put(cep);

	वापस rv;

reject_conn:
	siw_dbg_cep(cep, "reject: crc %d:%d:%d, m %d:%d\n",
		    req->params.bits & MPA_RR_FLAG_CRC ? 1 : 0,
		    mpa_crc_required, mpa_crc_strict,
		    req->params.bits & MPA_RR_FLAG_MARKERS ? 1 : 0, 0);

	req->params.bits &= ~MPA_RR_FLAG_MARKERS;
	req->params.bits |= MPA_RR_FLAG_REJECT;

	अगर (!mpa_crc_required && mpa_crc_strict)
		req->params.bits &= ~MPA_RR_FLAG_CRC;

	अगर (pd_len)
		kमुक्त(cep->mpa.pdata);

	cep->mpa.pdata = शून्य;

	siw_send_mpareqrep(cep, शून्य, 0);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक siw_proc_mpareply(काष्ठा siw_cep *cep)
अणु
	काष्ठा siw_qp_attrs qp_attrs;
	क्रमागत siw_qp_attr_mask qp_attr_mask;
	काष्ठा siw_qp *qp = cep->qp;
	काष्ठा mpa_rr *rep;
	पूर्णांक rv;
	u16 rep_ord;
	u16 rep_ird;
	bool ird_insufficient = false;
	क्रमागत mpa_v2_ctrl mpa_p2p_mode = MPA_V2_RDMA_NO_RTR;

	rv = siw_recv_mpa_rr(cep);
	अगर (rv != -EAGAIN)
		siw_cancel_mpaसमयr(cep);
	अगर (rv)
		जाओ out_err;

	rep = &cep->mpa.hdr;

	अगर (__mpa_rr_revision(rep->params.bits) > MPA_REVISION_2) अणु
		/* allow क्रम 0, 1,  and 2 only */
		rv = -EPROTO;
		जाओ out_err;
	पूर्ण
	अगर (स_भेद(rep->key, MPA_KEY_REP, 16)) अणु
		siw_init_terminate(qp, TERM_ERROR_LAYER_LLP, LLP_ETYPE_MPA,
				   LLP_ECODE_INVALID_REQ_RESP, 0);
		siw_send_terminate(qp);
		rv = -EPROTO;
		जाओ out_err;
	पूर्ण
	अगर (rep->params.bits & MPA_RR_FLAG_REJECT) अणु
		siw_dbg_cep(cep, "got mpa reject\n");
		siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -ECONNRESET);

		वापस -ECONNRESET;
	पूर्ण
	अगर (try_gso && rep->params.bits & MPA_RR_FLAG_GSO_EXP) अणु
		siw_dbg_cep(cep, "peer allows GSO on TX\n");
		qp->tx_ctx.gso_seg_limit = 0;
	पूर्ण
	अगर ((rep->params.bits & MPA_RR_FLAG_MARKERS) ||
	    (mpa_crc_required && !(rep->params.bits & MPA_RR_FLAG_CRC)) ||
	    (mpa_crc_strict && !mpa_crc_required &&
	     (rep->params.bits & MPA_RR_FLAG_CRC))) अणु
		siw_dbg_cep(cep, "reply unsupp: crc %d:%d:%d, m %d:%d\n",
			    rep->params.bits & MPA_RR_FLAG_CRC ? 1 : 0,
			    mpa_crc_required, mpa_crc_strict,
			    rep->params.bits & MPA_RR_FLAG_MARKERS ? 1 : 0, 0);

		siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -ECONNREFUSED);

		वापस -EINVAL;
	पूर्ण
	अगर (cep->enhanced_rdma_conn_est) अणु
		काष्ठा mpa_v2_data *v2;

		अगर (__mpa_rr_revision(rep->params.bits) < MPA_REVISION_2 ||
		    !(rep->params.bits & MPA_RR_FLAG_ENHANCED)) अणु
			/*
			 * Protocol failure: The responder MUST reply with
			 * MPA version 2 and MUST set MPA_RR_FLAG_ENHANCED.
			 */
			siw_dbg_cep(cep, "mpa reply error: vers %d, enhcd %d\n",
				    __mpa_rr_revision(rep->params.bits),
				    rep->params.bits & MPA_RR_FLAG_ENHANCED ?
					    1 :
					    0);

			siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
				      -ECONNRESET);
			वापस -EINVAL;
		पूर्ण
		v2 = (काष्ठा mpa_v2_data *)cep->mpa.pdata;
		rep_ird = ntohs(v2->ird) & MPA_IRD_ORD_MASK;
		rep_ord = ntohs(v2->ord) & MPA_IRD_ORD_MASK;

		अगर (cep->ird < rep_ord &&
		    (relaxed_ird_negotiation == false ||
		     rep_ord > cep->sdev->attrs.max_ird)) अणु
			siw_dbg_cep(cep, "ird %d, rep_ord %d, max_ord %d\n",
				    cep->ird, rep_ord,
				    cep->sdev->attrs.max_ord);
			ird_insufficient = true;
		पूर्ण
		अगर (cep->ord > rep_ird && relaxed_ird_negotiation == false) अणु
			siw_dbg_cep(cep, "ord %d, rep_ird %d\n", cep->ord,
				    rep_ird);
			ird_insufficient = true;
		पूर्ण
		/*
		 * Always report negotiated peer values to user,
		 * even अगर IRD/ORD negotiation failed
		 */
		cep->ird = rep_ord;
		cep->ord = rep_ird;

		अगर (ird_insufficient) अणु
			/*
			 * If the initiator IRD is insuffient क्रम the
			 * responder ORD, send a TERM.
			 */
			siw_init_terminate(qp, TERM_ERROR_LAYER_LLP,
					   LLP_ETYPE_MPA,
					   LLP_ECODE_INSUFFICIENT_IRD, 0);
			siw_send_terminate(qp);
			rv = -ENOMEM;
			जाओ out_err;
		पूर्ण
		अगर (cep->mpa.v2_ctrl_req.ird & MPA_V2_PEER_TO_PEER)
			mpa_p2p_mode =
				cep->mpa.v2_ctrl_req.ord &
				(MPA_V2_RDMA_WRITE_RTR | MPA_V2_RDMA_READ_RTR);

		/*
		 * Check अगर we requested P2P mode, and अगर peer agrees
		 */
		अगर (mpa_p2p_mode != MPA_V2_RDMA_NO_RTR) अणु
			अगर ((mpa_p2p_mode & v2->ord) == 0) अणु
				/*
				 * We requested RTR mode(s), but the peer
				 * did not pick any mode we support.
				 */
				siw_dbg_cep(cep,
					    "rtr mode:  req %2x, got %2x\n",
					    mpa_p2p_mode,
					    v2->ord & (MPA_V2_RDMA_WRITE_RTR |
						       MPA_V2_RDMA_READ_RTR));

				siw_init_terminate(qp, TERM_ERROR_LAYER_LLP,
						   LLP_ETYPE_MPA,
						   LLP_ECODE_NO_MATCHING_RTR,
						   0);
				siw_send_terminate(qp);
				rv = -EPROTO;
				जाओ out_err;
			पूर्ण
			mpa_p2p_mode = v2->ord & (MPA_V2_RDMA_WRITE_RTR |
						  MPA_V2_RDMA_READ_RTR);
		पूर्ण
	पूर्ण
	स_रखो(&qp_attrs, 0, माप(qp_attrs));

	अगर (rep->params.bits & MPA_RR_FLAG_CRC)
		qp_attrs.flags = SIW_MPA_CRC;

	qp_attrs.irq_size = cep->ird;
	qp_attrs.orq_size = cep->ord;
	qp_attrs.sk = cep->sock;
	qp_attrs.state = SIW_QP_STATE_RTS;

	qp_attr_mask = SIW_QP_ATTR_STATE | SIW_QP_ATTR_LLP_HANDLE |
		       SIW_QP_ATTR_ORD | SIW_QP_ATTR_IRD | SIW_QP_ATTR_MPA;

	/* Move socket RX/TX under QP control */
	करोwn_ग_लिखो(&qp->state_lock);
	अगर (qp->attrs.state > SIW_QP_STATE_RTR) अणु
		rv = -EINVAL;
		up_ग_लिखो(&qp->state_lock);
		जाओ out_err;
	पूर्ण
	rv = siw_qp_modअगरy(qp, &qp_attrs, qp_attr_mask);

	siw_qp_socket_assoc(cep, qp);

	up_ग_लिखो(&qp->state_lock);

	/* Send extra RDMA frame to trigger peer RTS अगर negotiated */
	अगर (mpa_p2p_mode != MPA_V2_RDMA_NO_RTR) अणु
		rv = siw_qp_mpa_rts(qp, mpa_p2p_mode);
		अगर (rv)
			जाओ out_err;
	पूर्ण
	अगर (!rv) अणु
		rv = siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, 0);
		अगर (!rv)
			cep->state = SIW_EPSTATE_RDMA_MODE;

		वापस 0;
	पूर्ण

out_err:
	siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -EINVAL);

	वापस rv;
पूर्ण

/*
 * siw_accept_newconn - accept an incoming pending connection
 *
 */
अटल व्योम siw_accept_newconn(काष्ठा siw_cep *cep)
अणु
	काष्ठा socket *s = cep->sock;
	काष्ठा socket *new_s = शून्य;
	काष्ठा siw_cep *new_cep = शून्य;
	पूर्णांक rv = 0; /* debug only. should disappear */

	अगर (cep->state != SIW_EPSTATE_LISTENING)
		जाओ error;

	new_cep = siw_cep_alloc(cep->sdev);
	अगर (!new_cep)
		जाओ error;

	/*
	 * 4: Allocate a sufficient number of work elements
	 * to allow concurrent handling of local + peer बंद
	 * events, MPA header processing + MPA समयout.
	 */
	अगर (siw_cm_alloc_work(new_cep, 4) != 0)
		जाओ error;

	/*
	 * Copy saved socket callbacks from listening CEP
	 * and assign new socket with new CEP
	 */
	new_cep->sk_state_change = cep->sk_state_change;
	new_cep->sk_data_पढ़ोy = cep->sk_data_पढ़ोy;
	new_cep->sk_ग_लिखो_space = cep->sk_ग_लिखो_space;
	new_cep->sk_error_report = cep->sk_error_report;

	rv = kernel_accept(s, &new_s, O_NONBLOCK);
	अगर (rv != 0) अणु
		/*
		 * Connection alपढ़ोy पातed by peer..?
		 */
		siw_dbg_cep(cep, "kernel_accept() error: %d\n", rv);
		जाओ error;
	पूर्ण
	new_cep->sock = new_s;
	siw_cep_get(new_cep);
	new_s->sk->sk_user_data = new_cep;

	अगर (siw_tcp_nagle == false)
		tcp_sock_set_nodelay(new_s->sk);
	new_cep->state = SIW_EPSTATE_AWAIT_MPAREQ;

	rv = siw_cm_queue_work(new_cep, SIW_CM_WORK_MPATIMEOUT);
	अगर (rv)
		जाओ error;
	/*
	 * See siw_proc_mpareq() etc. क्रम the use of new_cep->listen_cep.
	 */
	new_cep->listen_cep = cep;
	siw_cep_get(cep);

	अगर (atomic_पढ़ो(&new_s->sk->sk_rmem_alloc)) अणु
		/*
		 * MPA REQ alपढ़ोy queued
		 */
		siw_dbg_cep(cep, "immediate mpa request\n");

		siw_cep_set_inuse(new_cep);
		rv = siw_proc_mpareq(new_cep);
		siw_cep_set_मुक्त(new_cep);

		अगर (rv != -EAGAIN) अणु
			siw_cep_put(cep);
			new_cep->listen_cep = शून्य;
			अगर (rv)
				जाओ error;
		पूर्ण
	पूर्ण
	वापस;

error:
	अगर (new_cep)
		siw_cep_put(new_cep);

	अगर (new_s) अणु
		siw_socket_disassoc(new_s);
		sock_release(new_s);
		new_cep->sock = शून्य;
	पूर्ण
	siw_dbg_cep(cep, "error %d\n", rv);
पूर्ण

अटल व्योम siw_cm_work_handler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा siw_cm_work *work;
	काष्ठा siw_cep *cep;
	पूर्णांक release_cep = 0, rv = 0;

	work = container_of(w, काष्ठा siw_cm_work, work.work);
	cep = work->cep;

	siw_dbg_cep(cep, "[QP %u]: work type: %d, state %d\n",
		    cep->qp ? qp_id(cep->qp) : अच_पूर्णांक_उच्च,
		    work->type, cep->state);

	siw_cep_set_inuse(cep);

	चयन (work->type) अणु
	हाल SIW_CM_WORK_ACCEPT:
		siw_accept_newconn(cep);
		अवरोध;

	हाल SIW_CM_WORK_READ_MPAHDR:
		अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREQ) अणु
			अगर (cep->listen_cep) अणु
				siw_cep_set_inuse(cep->listen_cep);

				अगर (cep->listen_cep->state ==
				    SIW_EPSTATE_LISTENING)
					rv = siw_proc_mpareq(cep);
				अन्यथा
					rv = -EFAULT;

				siw_cep_set_मुक्त(cep->listen_cep);

				अगर (rv != -EAGAIN) अणु
					siw_cep_put(cep->listen_cep);
					cep->listen_cep = शून्य;
					अगर (rv)
						siw_cep_put(cep);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREP) अणु
			rv = siw_proc_mpareply(cep);
		पूर्ण अन्यथा अणु
			/*
			 * CEP alपढ़ोy moved out of MPA handshake.
			 * any connection management alपढ़ोy करोne.
			 * silently ignore the mpa packet.
			 */
			अगर (cep->state == SIW_EPSTATE_RDMA_MODE) अणु
				cep->sock->sk->sk_data_पढ़ोy(cep->sock->sk);
				siw_dbg_cep(cep, "already in RDMA mode");
			पूर्ण अन्यथा अणु
				siw_dbg_cep(cep, "out of state: %d\n",
					    cep->state);
			पूर्ण
		पूर्ण
		अगर (rv && rv != -EAGAIN)
			release_cep = 1;
		अवरोध;

	हाल SIW_CM_WORK_CLOSE_LLP:
		/*
		 * QP scheduled LLP बंद
		 */
		अगर (cep->qp && cep->qp->term_info.valid)
			siw_send_terminate(cep->qp);

		अगर (cep->cm_id)
			siw_cm_upcall(cep, IW_CM_EVENT_CLOSE, 0);

		release_cep = 1;
		अवरोध;

	हाल SIW_CM_WORK_PEER_CLOSE:
		अगर (cep->cm_id) अणु
			अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREP) अणु
				/*
				 * MPA reply not received, but connection drop
				 */
				siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
					      -ECONNRESET);
			पूर्ण अन्यथा अगर (cep->state == SIW_EPSTATE_RDMA_MODE) अणु
				/*
				 * NOTE: IW_CM_EVENT_DISCONNECT is given just
				 *       to transition IWCM पूर्णांकo CLOSING.
				 */
				siw_cm_upcall(cep, IW_CM_EVENT_DISCONNECT, 0);
				siw_cm_upcall(cep, IW_CM_EVENT_CLOSE, 0);
			पूर्ण
			/*
			 * क्रम other states there is no connection
			 * known to the IWCM.
			 */
		पूर्ण अन्यथा अणु
			अगर (cep->state == SIW_EPSTATE_RECVD_MPAREQ) अणु
				/*
				 * Wait क्रम the ulp/CM to call accept/reject
				 */
				siw_dbg_cep(cep,
					    "mpa req recvd, wait for ULP\n");
			पूर्ण अन्यथा अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREQ) अणु
				/*
				 * Socket बंद beक्रमe MPA request received.
				 */
				siw_dbg_cep(cep, "no mpareq: drop listener\n");
				siw_cep_put(cep->listen_cep);
				cep->listen_cep = शून्य;
			पूर्ण
		पूर्ण
		release_cep = 1;
		अवरोध;

	हाल SIW_CM_WORK_MPATIMEOUT:
		cep->mpa_समयr = शून्य;

		अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREP) अणु
			/*
			 * MPA request समयd out:
			 * Hide any partially received निजी data and संकेत
			 * समयout
			 */
			cep->mpa.hdr.params.pd_len = 0;

			अगर (cep->cm_id)
				siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
					      -ETIMEDOUT);
			release_cep = 1;

		पूर्ण अन्यथा अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREQ) अणु
			/*
			 * No MPA request received after peer TCP stream setup.
			 */
			अगर (cep->listen_cep) अणु
				siw_cep_put(cep->listen_cep);
				cep->listen_cep = शून्य;
			पूर्ण
			release_cep = 1;
		पूर्ण
		अवरोध;

	शेष:
		WARN(1, "Undefined CM work type: %d\n", work->type);
	पूर्ण
	अगर (release_cep) अणु
		siw_dbg_cep(cep,
			    "release: timer=%s, QP[%u]\n",
			    cep->mpa_समयr ? "y" : "n",
			    cep->qp ? qp_id(cep->qp) : अच_पूर्णांक_उच्च);

		siw_cancel_mpaसमयr(cep);

		cep->state = SIW_EPSTATE_CLOSED;

		अगर (cep->qp) अणु
			काष्ठा siw_qp *qp = cep->qp;
			/*
			 * Serialize a potential race with application
			 * closing the QP and calling siw_qp_cm_drop()
			 */
			siw_qp_get(qp);
			siw_cep_set_मुक्त(cep);

			siw_qp_llp_बंद(qp);
			siw_qp_put(qp);

			siw_cep_set_inuse(cep);
			cep->qp = शून्य;
			siw_qp_put(qp);
		पूर्ण
		अगर (cep->sock) अणु
			siw_socket_disassoc(cep->sock);
			sock_release(cep->sock);
			cep->sock = शून्य;
		पूर्ण
		अगर (cep->cm_id) अणु
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = शून्य;
			siw_cep_put(cep);
		पूर्ण
	पूर्ण
	siw_cep_set_मुक्त(cep);
	siw_put_work(work);
	siw_cep_put(cep);
पूर्ण

अटल काष्ठा workqueue_काष्ठा *siw_cm_wq;

पूर्णांक siw_cm_queue_work(काष्ठा siw_cep *cep, क्रमागत siw_work_type type)
अणु
	काष्ठा siw_cm_work *work = siw_get_work(cep);
	अचिन्हित दीर्घ delay = 0;

	अगर (!work) अणु
		siw_dbg_cep(cep, "failed with no work available\n");
		वापस -ENOMEM;
	पूर्ण
	work->type = type;
	work->cep = cep;

	siw_cep_get(cep);

	INIT_DELAYED_WORK(&work->work, siw_cm_work_handler);

	अगर (type == SIW_CM_WORK_MPATIMEOUT) अणु
		cep->mpa_समयr = work;

		अगर (cep->state == SIW_EPSTATE_AWAIT_MPAREP)
			delay = MPAREQ_TIMEOUT;
		अन्यथा
			delay = MPAREP_TIMEOUT;
	पूर्ण
	siw_dbg_cep(cep, "[QP %u]: work type: %d, timeout %lu\n",
		    cep->qp ? qp_id(cep->qp) : -1, type, delay);

	queue_delayed_work(siw_cm_wq, &work->work, delay);

	वापस 0;
पूर्ण

अटल व्योम siw_cm_llp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep;

	पढ़ो_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	अगर (!cep)
		जाओ out;

	siw_dbg_cep(cep, "state: %d\n", cep->state);

	चयन (cep->state) अणु
	हाल SIW_EPSTATE_RDMA_MODE:
	हाल SIW_EPSTATE_LISTENING:
		अवरोध;

	हाल SIW_EPSTATE_AWAIT_MPAREQ:
	हाल SIW_EPSTATE_AWAIT_MPAREP:
		siw_cm_queue_work(cep, SIW_CM_WORK_READ_MPAHDR);
		अवरोध;

	शेष:
		siw_dbg_cep(cep, "unexpected data, state %d\n", cep->state);
		अवरोध;
	पूर्ण
out:
	पढ़ो_unlock(&sk->sk_callback_lock);
पूर्ण

अटल व्योम siw_cm_llp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep = sk_to_cep(sk);

	अगर (cep)
		siw_dbg_cep(cep, "state: %d\n", cep->state);
पूर्ण

अटल व्योम siw_cm_llp_error_report(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep = sk_to_cep(sk);

	अगर (cep) अणु
		siw_dbg_cep(cep, "error %d, socket state: %d, cep state: %d\n",
			    sk->sk_err, sk->sk_state, cep->state);
		cep->sk_error_report(sk);
	पूर्ण
पूर्ण

अटल व्योम siw_cm_llp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep;
	व्योम (*orig_state_change)(काष्ठा sock *s);

	पढ़ो_lock(&sk->sk_callback_lock);

	cep = sk_to_cep(sk);
	अगर (!cep) अणु
		/* endpoपूर्णांक alपढ़ोy disassociated */
		पढ़ो_unlock(&sk->sk_callback_lock);
		वापस;
	पूर्ण
	orig_state_change = cep->sk_state_change;

	siw_dbg_cep(cep, "state: %d\n", cep->state);

	चयन (sk->sk_state) अणु
	हाल TCP_ESTABLISHED:
		/*
		 * handle accepting socket as special हाल where only
		 * new connection is possible
		 */
		siw_cm_queue_work(cep, SIW_CM_WORK_ACCEPT);
		अवरोध;

	हाल TCP_CLOSE:
	हाल TCP_CLOSE_WAIT:
		अगर (cep->qp)
			cep->qp->tx_ctx.tx_suspend = 1;
		siw_cm_queue_work(cep, SIW_CM_WORK_PEER_CLOSE);
		अवरोध;

	शेष:
		siw_dbg_cep(cep, "unexpected socket state %d\n", sk->sk_state);
	पूर्ण
	पढ़ो_unlock(&sk->sk_callback_lock);
	orig_state_change(sk);
पूर्ण

अटल पूर्णांक kernel_bindconnect(काष्ठा socket *s, काष्ठा sockaddr *laddr,
			      काष्ठा sockaddr *raddr, bool afonly)
अणु
	पूर्णांक rv, flags = 0;
	माप_प्रकार size = laddr->sa_family == AF_INET ?
		माप(काष्ठा sockaddr_in) : माप(काष्ठा sockaddr_in6);

	/*
	 * Make address available again asap.
	 */
	sock_set_reuseaddr(s->sk);

	अगर (afonly) अणु
		rv = ip6_sock_set_v6only(s->sk);
		अगर (rv)
			वापस rv;
	पूर्ण

	rv = s->ops->bind(s, laddr, size);
	अगर (rv < 0)
		वापस rv;

	rv = s->ops->connect(s, raddr, size, flags);

	वापस rv < 0 ? rv : 0;
पूर्ण

पूर्णांक siw_connect(काष्ठा iw_cm_id *id, काष्ठा iw_cm_conn_param *params)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(id->device);
	काष्ठा siw_qp *qp;
	काष्ठा siw_cep *cep = शून्य;
	काष्ठा socket *s = शून्य;
	काष्ठा sockaddr *laddr = (काष्ठा sockaddr *)&id->local_addr,
			*raddr = (काष्ठा sockaddr *)&id->remote_addr;
	bool p2p_mode = peer_to_peer, v4 = true;
	u16 pd_len = params->निजी_data_len;
	पूर्णांक version = mpa_version, rv;

	अगर (pd_len > MPA_MAX_PRIVDATA)
		वापस -EINVAL;

	अगर (params->ird > sdev->attrs.max_ird ||
	    params->ord > sdev->attrs.max_ord)
		वापस -ENOMEM;

	अगर (laddr->sa_family == AF_INET6)
		v4 = false;
	अन्यथा अगर (laddr->sa_family != AF_INET)
		वापस -EAFNOSUPPORT;

	/*
	 * Respect any iwarp port mapping: Use mapped remote address
	 * अगर valid. Local address must not be mapped, since siw
	 * uses kernel TCP stack.
	 */
	अगर ((v4 && to_sockaddr_in(id->remote_addr).sin_port != 0) ||
	     to_sockaddr_in6(id->remote_addr).sin6_port != 0)
		raddr = (काष्ठा sockaddr *)&id->m_remote_addr;

	qp = siw_qp_id2obj(sdev, params->qpn);
	अगर (!qp) अणु
		WARN(1, "[QP %u] does not exist\n", params->qpn);
		rv = -EINVAL;
		जाओ error;
	पूर्ण
	siw_dbg_qp(qp, "pd_len %d, laddr %pISp, raddr %pISp\n", pd_len, laddr,
		   raddr);

	rv = sock_create(v4 ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP, &s);
	अगर (rv < 0)
		जाओ error;

	/*
	 * NOTE: For simplअगरication, connect() is called in blocking
	 * mode. Might be reconsidered क्रम async connection setup at
	 * TCP level.
	 */
	rv = kernel_bindconnect(s, laddr, raddr, id->afonly);
	अगर (rv != 0) अणु
		siw_dbg_qp(qp, "kernel_bindconnect: error %d\n", rv);
		जाओ error;
	पूर्ण
	अगर (siw_tcp_nagle == false)
		tcp_sock_set_nodelay(s->sk);
	cep = siw_cep_alloc(sdev);
	अगर (!cep) अणु
		rv = -ENOMEM;
		जाओ error;
	पूर्ण
	siw_cep_set_inuse(cep);

	/* Associate QP with CEP */
	siw_cep_get(cep);
	qp->cep = cep;

	/* siw_qp_get(qp) alपढ़ोy करोne by QP lookup */
	cep->qp = qp;

	id->add_ref(id);
	cep->cm_id = id;

	/*
	 * 4: Allocate a sufficient number of work elements
	 * to allow concurrent handling of local + peer बंद
	 * events, MPA header processing + MPA समयout.
	 */
	rv = siw_cm_alloc_work(cep, 4);
	अगर (rv != 0) अणु
		rv = -ENOMEM;
		जाओ error;
	पूर्ण
	cep->ird = params->ird;
	cep->ord = params->ord;

	अगर (p2p_mode && cep->ord == 0)
		cep->ord = 1;

	cep->state = SIW_EPSTATE_CONNECTING;

	/*
	 * Associate CEP with socket
	 */
	siw_cep_socket_assoc(cep, s);

	cep->state = SIW_EPSTATE_AWAIT_MPAREP;

	/*
	 * Set MPA Request bits: CRC अगर required, no MPA Markers,
	 * MPA Rev. according to module parameter 'mpa_version', Key 'Request'.
	 */
	cep->mpa.hdr.params.bits = 0;
	अगर (version > MPA_REVISION_2) अणु
		pr_warn("Setting MPA version to %u\n", MPA_REVISION_2);
		version = MPA_REVISION_2;
		/* Adjust also module parameter */
		mpa_version = MPA_REVISION_2;
	पूर्ण
	__mpa_rr_set_revision(&cep->mpa.hdr.params.bits, version);

	अगर (try_gso)
		cep->mpa.hdr.params.bits |= MPA_RR_FLAG_GSO_EXP;

	अगर (mpa_crc_required)
		cep->mpa.hdr.params.bits |= MPA_RR_FLAG_CRC;

	/*
	 * If MPA version == 2:
	 * o Include ORD and IRD.
	 * o Indicate peer-to-peer mode, अगर required by module
	 *   parameter 'peer_to_peer'.
	 */
	अगर (version == MPA_REVISION_2) अणु
		cep->enhanced_rdma_conn_est = true;
		cep->mpa.hdr.params.bits |= MPA_RR_FLAG_ENHANCED;

		cep->mpa.v2_ctrl.ird = htons(cep->ird);
		cep->mpa.v2_ctrl.ord = htons(cep->ord);

		अगर (p2p_mode) अणु
			cep->mpa.v2_ctrl.ird |= MPA_V2_PEER_TO_PEER;
			cep->mpa.v2_ctrl.ord |= rtr_type;
		पूर्ण
		/* Remember own P2P mode requested */
		cep->mpa.v2_ctrl_req.ird = cep->mpa.v2_ctrl.ird;
		cep->mpa.v2_ctrl_req.ord = cep->mpa.v2_ctrl.ord;
	पूर्ण
	स_नकल(cep->mpa.hdr.key, MPA_KEY_REQ, 16);

	rv = siw_send_mpareqrep(cep, params->निजी_data, pd_len);
	/*
	 * Reset निजी data.
	 */
	cep->mpa.hdr.params.pd_len = 0;

	अगर (rv >= 0) अणु
		rv = siw_cm_queue_work(cep, SIW_CM_WORK_MPATIMEOUT);
		अगर (!rv) अणु
			siw_dbg_cep(cep, "[QP %u]: exit\n", qp_id(qp));
			siw_cep_set_मुक्त(cep);
			वापस 0;
		पूर्ण
	पूर्ण
error:
	siw_dbg(id->device, "failed: %d\n", rv);

	अगर (cep) अणु
		siw_socket_disassoc(s);
		sock_release(s);
		cep->sock = शून्य;

		cep->qp = शून्य;

		cep->cm_id = शून्य;
		id->rem_ref(id);
		siw_cep_put(cep);

		qp->cep = शून्य;
		siw_cep_put(cep);

		cep->state = SIW_EPSTATE_CLOSED;

		siw_cep_set_मुक्त(cep);

		siw_cep_put(cep);

	पूर्ण अन्यथा अगर (s) अणु
		sock_release(s);
	पूर्ण
	अगर (qp)
		siw_qp_put(qp);

	वापस rv;
पूर्ण

/*
 * siw_accept - Let SoftiWARP accept an RDMA connection request
 *
 * @id:		New connection management id to be used क्रम accepted
 *		connection request
 * @params:	Connection parameters provided by ULP क्रम accepting connection
 *
 * Transition QP to RTS state, associate new CM id @id with accepted CEP
 * and get prepared क्रम TCP input by installing socket callbacks.
 * Then send MPA Reply and generate the "connection established" event.
 * Socket callbacks must be installed beक्रमe sending MPA Reply, because
 * the latter may cause a first RDMA message to arrive from the RDMA Initiator
 * side very quickly, at which समय the socket callbacks must be पढ़ोy.
 */
पूर्णांक siw_accept(काष्ठा iw_cm_id *id, काष्ठा iw_cm_conn_param *params)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(id->device);
	काष्ठा siw_cep *cep = (काष्ठा siw_cep *)id->provider_data;
	काष्ठा siw_qp *qp;
	काष्ठा siw_qp_attrs qp_attrs;
	पूर्णांक rv, max_priv_data = MPA_MAX_PRIVDATA;
	bool रुको_क्रम_peer_rts = false;

	siw_cep_set_inuse(cep);
	siw_cep_put(cep);

	/* Free lingering inbound निजी data */
	अगर (cep->mpa.hdr.params.pd_len) अणु
		cep->mpa.hdr.params.pd_len = 0;
		kमुक्त(cep->mpa.pdata);
		cep->mpa.pdata = शून्य;
	पूर्ण
	siw_cancel_mpaसमयr(cep);

	अगर (cep->state != SIW_EPSTATE_RECVD_MPAREQ) अणु
		siw_dbg_cep(cep, "out of state\n");

		siw_cep_set_मुक्त(cep);
		siw_cep_put(cep);

		वापस -ECONNRESET;
	पूर्ण
	qp = siw_qp_id2obj(sdev, params->qpn);
	अगर (!qp) अणु
		WARN(1, "[QP %d] does not exist\n", params->qpn);
		siw_cep_set_मुक्त(cep);
		siw_cep_put(cep);

		वापस -EINVAL;
	पूर्ण
	करोwn_ग_लिखो(&qp->state_lock);
	अगर (qp->attrs.state > SIW_QP_STATE_RTR) अणु
		rv = -EINVAL;
		up_ग_लिखो(&qp->state_lock);
		जाओ error;
	पूर्ण
	siw_dbg_cep(cep, "[QP %d]\n", params->qpn);

	अगर (try_gso && cep->mpa.hdr.params.bits & MPA_RR_FLAG_GSO_EXP) अणु
		siw_dbg_cep(cep, "peer allows GSO on TX\n");
		qp->tx_ctx.gso_seg_limit = 0;
	पूर्ण
	अगर (params->ord > sdev->attrs.max_ord ||
	    params->ird > sdev->attrs.max_ird) अणु
		siw_dbg_cep(
			cep,
			"[QP %u]: ord %d (max %d), ird %d (max %d)\n",
			qp_id(qp), params->ord, sdev->attrs.max_ord,
			params->ird, sdev->attrs.max_ird);
		rv = -EINVAL;
		up_ग_लिखो(&qp->state_lock);
		जाओ error;
	पूर्ण
	अगर (cep->enhanced_rdma_conn_est)
		max_priv_data -= माप(काष्ठा mpa_v2_data);

	अगर (params->निजी_data_len > max_priv_data) अणु
		siw_dbg_cep(
			cep,
			"[QP %u]: private data length: %d (max %d)\n",
			qp_id(qp), params->निजी_data_len, max_priv_data);
		rv = -EINVAL;
		up_ग_लिखो(&qp->state_lock);
		जाओ error;
	पूर्ण
	अगर (cep->enhanced_rdma_conn_est) अणु
		अगर (params->ord > cep->ord) अणु
			अगर (relaxed_ird_negotiation) अणु
				params->ord = cep->ord;
			पूर्ण अन्यथा अणु
				cep->ird = params->ird;
				cep->ord = params->ord;
				rv = -EINVAL;
				up_ग_लिखो(&qp->state_lock);
				जाओ error;
			पूर्ण
		पूर्ण
		अगर (params->ird < cep->ird) अणु
			अगर (relaxed_ird_negotiation &&
			    cep->ird <= sdev->attrs.max_ird)
				params->ird = cep->ird;
			अन्यथा अणु
				rv = -ENOMEM;
				up_ग_लिखो(&qp->state_lock);
				जाओ error;
			पूर्ण
		पूर्ण
		अगर (cep->mpa.v2_ctrl.ord &
		    (MPA_V2_RDMA_WRITE_RTR | MPA_V2_RDMA_READ_RTR))
			रुको_क्रम_peer_rts = true;
		/*
		 * Signal back negotiated IRD and ORD values
		 */
		cep->mpa.v2_ctrl.ord =
			htons(params->ord & MPA_IRD_ORD_MASK) |
			(cep->mpa.v2_ctrl.ord & ~MPA_V2_MASK_IRD_ORD);
		cep->mpa.v2_ctrl.ird =
			htons(params->ird & MPA_IRD_ORD_MASK) |
			(cep->mpa.v2_ctrl.ird & ~MPA_V2_MASK_IRD_ORD);
	पूर्ण
	cep->ird = params->ird;
	cep->ord = params->ord;

	cep->cm_id = id;
	id->add_ref(id);

	स_रखो(&qp_attrs, 0, माप(qp_attrs));
	qp_attrs.orq_size = cep->ord;
	qp_attrs.irq_size = cep->ird;
	qp_attrs.sk = cep->sock;
	अगर (cep->mpa.hdr.params.bits & MPA_RR_FLAG_CRC)
		qp_attrs.flags = SIW_MPA_CRC;
	qp_attrs.state = SIW_QP_STATE_RTS;

	siw_dbg_cep(cep, "[QP%u]: moving to rts\n", qp_id(qp));

	/* Associate QP with CEP */
	siw_cep_get(cep);
	qp->cep = cep;

	/* siw_qp_get(qp) alपढ़ोy करोne by QP lookup */
	cep->qp = qp;

	cep->state = SIW_EPSTATE_RDMA_MODE;

	/* Move socket RX/TX under QP control */
	rv = siw_qp_modअगरy(qp, &qp_attrs,
			   SIW_QP_ATTR_STATE | SIW_QP_ATTR_LLP_HANDLE |
				   SIW_QP_ATTR_ORD | SIW_QP_ATTR_IRD |
				   SIW_QP_ATTR_MPA);
	up_ग_लिखो(&qp->state_lock);

	अगर (rv)
		जाओ error;

	siw_dbg_cep(cep, "[QP %u]: send mpa reply, %d byte pdata\n",
		    qp_id(qp), params->निजी_data_len);

	rv = siw_send_mpareqrep(cep, params->निजी_data,
				params->निजी_data_len);
	अगर (rv != 0)
		जाओ error;

	अगर (रुको_क्रम_peer_rts) अणु
		siw_sk_assign_rtr_upcalls(cep);
	पूर्ण अन्यथा अणु
		siw_qp_socket_assoc(cep, qp);
		rv = siw_cm_upcall(cep, IW_CM_EVENT_ESTABLISHED, 0);
		अगर (rv)
			जाओ error;
	पूर्ण
	siw_cep_set_मुक्त(cep);

	वापस 0;
error:
	siw_socket_disassoc(cep->sock);
	sock_release(cep->sock);
	cep->sock = शून्य;

	cep->state = SIW_EPSTATE_CLOSED;

	अगर (cep->cm_id) अणु
		cep->cm_id->rem_ref(id);
		cep->cm_id = शून्य;
	पूर्ण
	अगर (qp->cep) अणु
		siw_cep_put(cep);
		qp->cep = शून्य;
	पूर्ण
	cep->qp = शून्य;
	siw_qp_put(qp);

	siw_cep_set_मुक्त(cep);
	siw_cep_put(cep);

	वापस rv;
पूर्ण

/*
 * siw_reject()
 *
 * Local connection reject हाल. Send निजी data back to peer,
 * बंद connection and dereference connection id.
 */
पूर्णांक siw_reject(काष्ठा iw_cm_id *id, स्थिर व्योम *pdata, u8 pd_len)
अणु
	काष्ठा siw_cep *cep = (काष्ठा siw_cep *)id->provider_data;

	siw_cep_set_inuse(cep);
	siw_cep_put(cep);

	siw_cancel_mpaसमयr(cep);

	अगर (cep->state != SIW_EPSTATE_RECVD_MPAREQ) अणु
		siw_dbg_cep(cep, "out of state\n");

		siw_cep_set_मुक्त(cep);
		siw_cep_put(cep); /* put last reference */

		वापस -ECONNRESET;
	पूर्ण
	siw_dbg_cep(cep, "cep->state %d, pd_len %d\n", cep->state,
		    pd_len);

	अगर (__mpa_rr_revision(cep->mpa.hdr.params.bits) >= MPA_REVISION_1) अणु
		cep->mpa.hdr.params.bits |= MPA_RR_FLAG_REJECT; /* reject */
		siw_send_mpareqrep(cep, pdata, pd_len);
	पूर्ण
	siw_socket_disassoc(cep->sock);
	sock_release(cep->sock);
	cep->sock = शून्य;

	cep->state = SIW_EPSTATE_CLOSED;

	siw_cep_set_मुक्त(cep);
	siw_cep_put(cep);

	वापस 0;
पूर्ण

/*
 * siw_create_listen - Create resources क्रम a listener's IWCM ID @id
 *
 * Starts listen on the socket address id->local_addr.
 *
 */
पूर्णांक siw_create_listen(काष्ठा iw_cm_id *id, पूर्णांक backlog)
अणु
	काष्ठा socket *s;
	काष्ठा siw_cep *cep = शून्य;
	काष्ठा siw_device *sdev = to_siw_dev(id->device);
	पूर्णांक addr_family = id->local_addr.ss_family;
	पूर्णांक rv = 0;

	अगर (addr_family != AF_INET && addr_family != AF_INET6)
		वापस -EAFNOSUPPORT;

	rv = sock_create(addr_family, SOCK_STREAM, IPPROTO_TCP, &s);
	अगर (rv < 0)
		वापस rv;

	/*
	 * Allow binding local port when still in TIME_WAIT from last बंद.
	 */
	sock_set_reuseaddr(s->sk);

	अगर (addr_family == AF_INET) अणु
		काष्ठा sockaddr_in *laddr = &to_sockaddr_in(id->local_addr);

		/* For wildcard addr, limit binding to current device only */
		अगर (ipv4_is_zeronet(laddr->sin_addr.s_addr))
			s->sk->sk_bound_dev_अगर = sdev->netdev->अगरindex;

		rv = s->ops->bind(s, (काष्ठा sockaddr *)laddr,
				  माप(काष्ठा sockaddr_in));
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *laddr = &to_sockaddr_in6(id->local_addr);

		अगर (id->afonly) अणु
			rv = ip6_sock_set_v6only(s->sk);
			अगर (rv) अणु
				siw_dbg(id->device,
					"ip6_sock_set_v6only erro: %d\n", rv);
				जाओ error;
			पूर्ण
		पूर्ण

		/* For wildcard addr, limit binding to current device only */
		अगर (ipv6_addr_any(&laddr->sin6_addr))
			s->sk->sk_bound_dev_अगर = sdev->netdev->अगरindex;

		rv = s->ops->bind(s, (काष्ठा sockaddr *)laddr,
				  माप(काष्ठा sockaddr_in6));
	पूर्ण
	अगर (rv) अणु
		siw_dbg(id->device, "socket bind error: %d\n", rv);
		जाओ error;
	पूर्ण
	cep = siw_cep_alloc(sdev);
	अगर (!cep) अणु
		rv = -ENOMEM;
		जाओ error;
	पूर्ण
	siw_cep_socket_assoc(cep, s);

	rv = siw_cm_alloc_work(cep, backlog);
	अगर (rv) अणु
		siw_dbg(id->device,
			"alloc_work error %d, backlog %d\n",
			rv, backlog);
		जाओ error;
	पूर्ण
	rv = s->ops->listen(s, backlog);
	अगर (rv) अणु
		siw_dbg(id->device, "listen error %d\n", rv);
		जाओ error;
	पूर्ण
	cep->cm_id = id;
	id->add_ref(id);

	/*
	 * In हाल of a wildcard rdma_listen on a multi-homed device,
	 * a listener's IWCM id is associated with more than one listening CEP.
	 *
	 * We currently use id->provider_data in three dअगरferent ways:
	 *
	 * o For a listener's IWCM id, id->provider_data poपूर्णांकs to
	 *   the list_head of the list of listening CEPs.
	 *   Uses: siw_create_listen(), siw_destroy_listen()
	 *
	 * o For each accepted passive-side IWCM id, id->provider_data
	 *   poपूर्णांकs to the CEP itself. This is a consequence of
	 *   - siw_cm_upcall() setting event.provider_data = cep and
	 *   - the IWCM's cm_conn_req_handler() setting provider_data of the
	 *     new passive-side IWCM id equal to event.provider_data
	 *   Uses: siw_accept(), siw_reject()
	 *
	 * o For an active-side IWCM id, id->provider_data is not used at all.
	 *
	 */
	अगर (!id->provider_data) अणु
		id->provider_data =
			kदो_स्मृति(माप(काष्ठा list_head), GFP_KERNEL);
		अगर (!id->provider_data) अणु
			rv = -ENOMEM;
			जाओ error;
		पूर्ण
		INIT_LIST_HEAD((काष्ठा list_head *)id->provider_data);
	पूर्ण
	list_add_tail(&cep->listenq, (काष्ठा list_head *)id->provider_data);
	cep->state = SIW_EPSTATE_LISTENING;

	siw_dbg(id->device, "Listen at laddr %pISp\n", &id->local_addr);

	वापस 0;

error:
	siw_dbg(id->device, "failed: %d\n", rv);

	अगर (cep) अणु
		siw_cep_set_inuse(cep);

		अगर (cep->cm_id) अणु
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = शून्य;
		पूर्ण
		cep->sock = शून्य;
		siw_socket_disassoc(s);
		cep->state = SIW_EPSTATE_CLOSED;

		siw_cep_set_मुक्त(cep);
		siw_cep_put(cep);
	पूर्ण
	sock_release(s);

	वापस rv;
पूर्ण

अटल व्योम siw_drop_listeners(काष्ठा iw_cm_id *id)
अणु
	काष्ठा list_head *p, *पंचांगp;

	/*
	 * In हाल of a wildcard rdma_listen on a multi-homed device,
	 * a listener's IWCM id is associated with more than one listening CEP.
	 */
	list_क्रम_each_safe(p, पंचांगp, (काष्ठा list_head *)id->provider_data) अणु
		काष्ठा siw_cep *cep = list_entry(p, काष्ठा siw_cep, listenq);

		list_del(p);

		siw_dbg_cep(cep, "drop cep, state %d\n", cep->state);

		siw_cep_set_inuse(cep);

		अगर (cep->cm_id) अणु
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = शून्य;
		पूर्ण
		अगर (cep->sock) अणु
			siw_socket_disassoc(cep->sock);
			sock_release(cep->sock);
			cep->sock = शून्य;
		पूर्ण
		cep->state = SIW_EPSTATE_CLOSED;
		siw_cep_set_मुक्त(cep);
		siw_cep_put(cep);
	पूर्ण
पूर्ण

पूर्णांक siw_destroy_listen(काष्ठा iw_cm_id *id)
अणु
	अगर (!id->provider_data) अणु
		siw_dbg(id->device, "no cep(s)\n");
		वापस 0;
	पूर्ण
	siw_drop_listeners(id);
	kमुक्त(id->provider_data);
	id->provider_data = शून्य;

	वापस 0;
पूर्ण

पूर्णांक siw_cm_init(व्योम)
अणु
	/*
	 * create_single_workqueue क्रम strict ordering
	 */
	siw_cm_wq = create_singlethपढ़ो_workqueue("siw_cm_wq");
	अगर (!siw_cm_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम siw_cm_निकास(व्योम)
अणु
	अगर (siw_cm_wq) अणु
		flush_workqueue(siw_cm_wq);
		destroy_workqueue(siw_cm_wq);
	पूर्ण
पूर्ण
