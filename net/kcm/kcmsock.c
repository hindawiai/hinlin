<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel Connection Multiplexor
 *
 * Copyright (c) 2016 Tom Herbert <tom@herbertland.com>
 */

#समावेश <linux/bpf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/file.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/kcm.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/kcm.h>

अचिन्हित पूर्णांक kcm_net_id;

अटल काष्ठा kmem_cache *kcm_psockp __पढ़ो_mostly;
अटल काष्ठा kmem_cache *kcm_muxp __पढ़ो_mostly;
अटल काष्ठा workqueue_काष्ठा *kcm_wq;

अटल अंतरभूत काष्ठा kcm_sock *kcm_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा kcm_sock *)sk;
पूर्ण

अटल अंतरभूत काष्ठा kcm_tx_msg *kcm_tx_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा kcm_tx_msg *)skb->cb;
पूर्ण

अटल व्योम report_csk_error(काष्ठा sock *csk, पूर्णांक err)
अणु
	csk->sk_err = EPIPE;
	csk->sk_error_report(csk);
पूर्ण

अटल व्योम kcm_पात_tx_psock(काष्ठा kcm_psock *psock, पूर्णांक err,
			       bool wakeup_kcm)
अणु
	काष्ठा sock *csk = psock->sk;
	काष्ठा kcm_mux *mux = psock->mux;

	/* Unrecoverable error in transmit */

	spin_lock_bh(&mux->lock);

	अगर (psock->tx_stopped) अणु
		spin_unlock_bh(&mux->lock);
		वापस;
	पूर्ण

	psock->tx_stopped = 1;
	KCM_STATS_INCR(psock->stats.tx_पातs);

	अगर (!psock->tx_kcm) अणु
		/* Take off psocks_avail list */
		list_del(&psock->psock_avail_list);
	पूर्ण अन्यथा अगर (wakeup_kcm) अणु
		/* In this हाल psock is being पातed जबतक outside of
		 * ग_लिखो_msgs and psock is reserved. Schedule tx_work
		 * to handle the failure there. Need to commit tx_stopped
		 * beक्रमe queuing work.
		 */
		smp_mb();

		queue_work(kcm_wq, &psock->tx_kcm->tx_work);
	पूर्ण

	spin_unlock_bh(&mux->lock);

	/* Report error on lower socket */
	report_csk_error(csk, err);
पूर्ण

/* RX mux lock held. */
अटल व्योम kcm_update_rx_mux_stats(काष्ठा kcm_mux *mux,
				    काष्ठा kcm_psock *psock)
अणु
	STRP_STATS_ADD(mux->stats.rx_bytes,
		       psock->strp.stats.bytes -
		       psock->saved_rx_bytes);
	mux->stats.rx_msgs +=
		psock->strp.stats.msgs - psock->saved_rx_msgs;
	psock->saved_rx_msgs = psock->strp.stats.msgs;
	psock->saved_rx_bytes = psock->strp.stats.bytes;
पूर्ण

अटल व्योम kcm_update_tx_mux_stats(काष्ठा kcm_mux *mux,
				    काष्ठा kcm_psock *psock)
अणु
	KCM_STATS_ADD(mux->stats.tx_bytes,
		      psock->stats.tx_bytes - psock->saved_tx_bytes);
	mux->stats.tx_msgs +=
		psock->stats.tx_msgs - psock->saved_tx_msgs;
	psock->saved_tx_msgs = psock->stats.tx_msgs;
	psock->saved_tx_bytes = psock->stats.tx_bytes;
पूर्ण

अटल पूर्णांक kcm_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* KCM is पढ़ोy to receive messages on its queue-- either the KCM is new or
 * has become unblocked after being blocked on full socket buffer. Queue any
 * pending पढ़ोy messages on a psock. RX mux lock held.
 */
अटल व्योम kcm_rcv_पढ़ोy(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;
	काष्ठा kcm_psock *psock;
	काष्ठा sk_buff *skb;

	अगर (unlikely(kcm->rx_रुको || kcm->rx_psock || kcm->rx_disabled))
		वापस;

	जबतक (unlikely((skb = __skb_dequeue(&mux->rx_hold_queue)))) अणु
		अगर (kcm_queue_rcv_skb(&kcm->sk, skb)) अणु
			/* Assuming buffer limit has been reached */
			skb_queue_head(&mux->rx_hold_queue, skb);
			WARN_ON(!sk_rmem_alloc_get(&kcm->sk));
			वापस;
		पूर्ण
	पूर्ण

	जबतक (!list_empty(&mux->psocks_पढ़ोy)) अणु
		psock = list_first_entry(&mux->psocks_पढ़ोy, काष्ठा kcm_psock,
					 psock_पढ़ोy_list);

		अगर (kcm_queue_rcv_skb(&kcm->sk, psock->पढ़ोy_rx_msg)) अणु
			/* Assuming buffer limit has been reached */
			WARN_ON(!sk_rmem_alloc_get(&kcm->sk));
			वापस;
		पूर्ण

		/* Consumed the पढ़ोy message on the psock. Schedule rx_work to
		 * get more messages.
		 */
		list_del(&psock->psock_पढ़ोy_list);
		psock->पढ़ोy_rx_msg = शून्य;
		/* Commit clearing of पढ़ोy_rx_msg क्रम queuing work */
		smp_mb();

		strp_unछोड़ो(&psock->strp);
		strp_check_rcv(&psock->strp);
	पूर्ण

	/* Buffer limit is okay now, add to पढ़ोy list */
	list_add_tail(&kcm->रुको_rx_list,
		      &kcm->mux->kcm_rx_रुकोers);
	kcm->rx_रुको = true;
पूर्ण

अटल व्योम kcm_rमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा kcm_sock *kcm = kcm_sk(sk);
	काष्ठा kcm_mux *mux = kcm->mux;
	अचिन्हित पूर्णांक len = skb->truesize;

	sk_mem_unअक्षरge(sk, len);
	atomic_sub(len, &sk->sk_rmem_alloc);

	/* For पढ़ोing rx_रुको and rx_psock without holding lock */
	smp_mb__after_atomic();

	अगर (!kcm->rx_रुको && !kcm->rx_psock &&
	    sk_rmem_alloc_get(sk) < sk->sk_rcvlowat) अणु
		spin_lock_bh(&mux->rx_lock);
		kcm_rcv_पढ़ोy(kcm);
		spin_unlock_bh(&mux->rx_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक kcm_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff_head *list = &sk->sk_receive_queue;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		वापस -ENOMEM;

	अगर (!sk_rmem_schedule(sk, skb, skb->truesize))
		वापस -ENOBUFS;

	skb->dev = शून्य;

	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = kcm_rमुक्त;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	sk_mem_अक्षरge(sk, skb->truesize);

	skb_queue_tail(list, skb);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);

	वापस 0;
पूर्ण

/* Requeue received messages क्रम a kcm socket to other kcm sockets. This is
 * called with a kcm socket is receive disabled.
 * RX mux lock held.
 */
अटल व्योम requeue_rx_msgs(काष्ठा kcm_mux *mux, काष्ठा sk_buff_head *head)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा kcm_sock *kcm;

	जबतक ((skb = __skb_dequeue(head))) अणु
		/* Reset deकाष्ठाor to aव्योम calling kcm_rcv_पढ़ोy */
		skb->deकाष्ठाor = sock_rमुक्त;
		skb_orphan(skb);
try_again:
		अगर (list_empty(&mux->kcm_rx_रुकोers)) अणु
			skb_queue_tail(&mux->rx_hold_queue, skb);
			जारी;
		पूर्ण

		kcm = list_first_entry(&mux->kcm_rx_रुकोers,
				       काष्ठा kcm_sock, रुको_rx_list);

		अगर (kcm_queue_rcv_skb(&kcm->sk, skb)) अणु
			/* Should mean socket buffer full */
			list_del(&kcm->रुको_rx_list);
			kcm->rx_रुको = false;

			/* Commit rx_रुको to पढ़ो in kcm_मुक्त */
			smp_wmb();

			जाओ try_again;
		पूर्ण
	पूर्ण
पूर्ण

/* Lower sock lock held */
अटल काष्ठा kcm_sock *reserve_rx_kcm(काष्ठा kcm_psock *psock,
				       काष्ठा sk_buff *head)
अणु
	काष्ठा kcm_mux *mux = psock->mux;
	काष्ठा kcm_sock *kcm;

	WARN_ON(psock->पढ़ोy_rx_msg);

	अगर (psock->rx_kcm)
		वापस psock->rx_kcm;

	spin_lock_bh(&mux->rx_lock);

	अगर (psock->rx_kcm) अणु
		spin_unlock_bh(&mux->rx_lock);
		वापस psock->rx_kcm;
	पूर्ण

	kcm_update_rx_mux_stats(mux, psock);

	अगर (list_empty(&mux->kcm_rx_रुकोers)) अणु
		psock->पढ़ोy_rx_msg = head;
		strp_छोड़ो(&psock->strp);
		list_add_tail(&psock->psock_पढ़ोy_list,
			      &mux->psocks_पढ़ोy);
		spin_unlock_bh(&mux->rx_lock);
		वापस शून्य;
	पूर्ण

	kcm = list_first_entry(&mux->kcm_rx_रुकोers,
			       काष्ठा kcm_sock, रुको_rx_list);
	list_del(&kcm->रुको_rx_list);
	kcm->rx_रुको = false;

	psock->rx_kcm = kcm;
	kcm->rx_psock = psock;

	spin_unlock_bh(&mux->rx_lock);

	वापस kcm;
पूर्ण

अटल व्योम kcm_करोne(काष्ठा kcm_sock *kcm);

अटल व्योम kcm_करोne_work(काष्ठा work_काष्ठा *w)
अणु
	kcm_करोne(container_of(w, काष्ठा kcm_sock, करोne_work));
पूर्ण

/* Lower sock held */
अटल व्योम unreserve_rx_kcm(काष्ठा kcm_psock *psock,
			     bool rcv_पढ़ोy)
अणु
	काष्ठा kcm_sock *kcm = psock->rx_kcm;
	काष्ठा kcm_mux *mux = psock->mux;

	अगर (!kcm)
		वापस;

	spin_lock_bh(&mux->rx_lock);

	psock->rx_kcm = शून्य;
	kcm->rx_psock = शून्य;

	/* Commit kcm->rx_psock beक्रमe sk_rmem_alloc_get to sync with
	 * kcm_rमुक्त
	 */
	smp_mb();

	अगर (unlikely(kcm->करोne)) अणु
		spin_unlock_bh(&mux->rx_lock);

		/* Need to run kcm_करोne in a task since we need to qcquire
		 * callback locks which may alपढ़ोy be held here.
		 */
		INIT_WORK(&kcm->करोne_work, kcm_करोne_work);
		schedule_work(&kcm->करोne_work);
		वापस;
	पूर्ण

	अगर (unlikely(kcm->rx_disabled)) अणु
		requeue_rx_msgs(mux, &kcm->sk.sk_receive_queue);
	पूर्ण अन्यथा अगर (rcv_पढ़ोy || unlikely(!sk_rmem_alloc_get(&kcm->sk))) अणु
		/* Check क्रम degenerative race with rx_रुको that all
		 * data was dequeued (accounted क्रम in kcm_rमुक्त).
		 */
		kcm_rcv_पढ़ोy(kcm);
	पूर्ण
	spin_unlock_bh(&mux->rx_lock);
पूर्ण

/* Lower sock lock held */
अटल व्योम psock_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा kcm_psock *psock;

	पढ़ो_lock_bh(&sk->sk_callback_lock);

	psock = (काष्ठा kcm_psock *)sk->sk_user_data;
	अगर (likely(psock))
		strp_data_पढ़ोy(&psock->strp);

	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/* Called with lower sock held */
अटल व्योम kcm_rcv_strparser(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा kcm_psock *psock = container_of(strp, काष्ठा kcm_psock, strp);
	काष्ठा kcm_sock *kcm;

try_queue:
	kcm = reserve_rx_kcm(psock, skb);
	अगर (!kcm) अणु
		 /* Unable to reserve a KCM, message is held in psock and strp
		  * is छोड़ोd.
		  */
		वापस;
	पूर्ण

	अगर (kcm_queue_rcv_skb(&kcm->sk, skb)) अणु
		/* Should mean socket buffer full */
		unreserve_rx_kcm(psock, false);
		जाओ try_queue;
	पूर्ण
पूर्ण

अटल पूर्णांक kcm_parse_func_strparser(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा kcm_psock *psock = container_of(strp, काष्ठा kcm_psock, strp);
	काष्ठा bpf_prog *prog = psock->bpf_prog;
	पूर्णांक res;

	res = bpf_prog_run_pin_on_cpu(prog, skb);
	वापस res;
पूर्ण

अटल पूर्णांक kcm_पढ़ो_sock_करोne(काष्ठा strparser *strp, पूर्णांक err)
अणु
	काष्ठा kcm_psock *psock = container_of(strp, काष्ठा kcm_psock, strp);

	unreserve_rx_kcm(psock, true);

	वापस err;
पूर्ण

अटल व्योम psock_state_change(काष्ठा sock *sk)
अणु
	/* TCP only करोes a EPOLLIN क्रम a half बंद. Do a EPOLLHUP here
	 * since application will normally not poll with EPOLLIN
	 * on the TCP sockets.
	 */

	report_csk_error(sk, EPIPE);
पूर्ण

अटल व्योम psock_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा kcm_psock *psock;
	काष्ठा kcm_mux *mux;
	काष्ठा kcm_sock *kcm;

	पढ़ो_lock_bh(&sk->sk_callback_lock);

	psock = (काष्ठा kcm_psock *)sk->sk_user_data;
	अगर (unlikely(!psock))
		जाओ out;
	mux = psock->mux;

	spin_lock_bh(&mux->lock);

	/* Check अगर the socket is reserved so someone is रुकोing क्रम sending. */
	kcm = psock->tx_kcm;
	अगर (kcm && !unlikely(kcm->tx_stopped))
		queue_work(kcm_wq, &kcm->tx_work);

	spin_unlock_bh(&mux->lock);
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम unreserve_psock(काष्ठा kcm_sock *kcm);

/* kcm sock is locked. */
अटल काष्ठा kcm_psock *reserve_psock(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;
	काष्ठा kcm_psock *psock;

	psock = kcm->tx_psock;

	smp_rmb(); /* Must पढ़ो tx_psock beक्रमe tx_रुको */

	अगर (psock) अणु
		WARN_ON(kcm->tx_रुको);
		अगर (unlikely(psock->tx_stopped))
			unreserve_psock(kcm);
		अन्यथा
			वापस kcm->tx_psock;
	पूर्ण

	spin_lock_bh(&mux->lock);

	/* Check again under lock to see अगर psock was reserved क्रम this
	 * psock via psock_unreserve.
	 */
	psock = kcm->tx_psock;
	अगर (unlikely(psock)) अणु
		WARN_ON(kcm->tx_रुको);
		spin_unlock_bh(&mux->lock);
		वापस kcm->tx_psock;
	पूर्ण

	अगर (!list_empty(&mux->psocks_avail)) अणु
		psock = list_first_entry(&mux->psocks_avail,
					 काष्ठा kcm_psock,
					 psock_avail_list);
		list_del(&psock->psock_avail_list);
		अगर (kcm->tx_रुको) अणु
			list_del(&kcm->रुको_psock_list);
			kcm->tx_रुको = false;
		पूर्ण
		kcm->tx_psock = psock;
		psock->tx_kcm = kcm;
		KCM_STATS_INCR(psock->stats.reserved);
	पूर्ण अन्यथा अगर (!kcm->tx_रुको) अणु
		list_add_tail(&kcm->रुको_psock_list,
			      &mux->kcm_tx_रुकोers);
		kcm->tx_रुको = true;
	पूर्ण

	spin_unlock_bh(&mux->lock);

	वापस psock;
पूर्ण

/* mux lock held */
अटल व्योम psock_now_avail(काष्ठा kcm_psock *psock)
अणु
	काष्ठा kcm_mux *mux = psock->mux;
	काष्ठा kcm_sock *kcm;

	अगर (list_empty(&mux->kcm_tx_रुकोers)) अणु
		list_add_tail(&psock->psock_avail_list,
			      &mux->psocks_avail);
	पूर्ण अन्यथा अणु
		kcm = list_first_entry(&mux->kcm_tx_रुकोers,
				       काष्ठा kcm_sock,
				       रुको_psock_list);
		list_del(&kcm->रुको_psock_list);
		kcm->tx_रुको = false;
		psock->tx_kcm = kcm;

		/* Commit beक्रमe changing tx_psock since that is पढ़ो in
		 * reserve_psock beक्रमe queuing work.
		 */
		smp_mb();

		kcm->tx_psock = psock;
		KCM_STATS_INCR(psock->stats.reserved);
		queue_work(kcm_wq, &kcm->tx_work);
	पूर्ण
पूर्ण

/* kcm sock is locked. */
अटल व्योम unreserve_psock(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_psock *psock;
	काष्ठा kcm_mux *mux = kcm->mux;

	spin_lock_bh(&mux->lock);

	psock = kcm->tx_psock;

	अगर (WARN_ON(!psock)) अणु
		spin_unlock_bh(&mux->lock);
		वापस;
	पूर्ण

	smp_rmb(); /* Read tx_psock beक्रमe tx_रुको */

	kcm_update_tx_mux_stats(mux, psock);

	WARN_ON(kcm->tx_रुको);

	kcm->tx_psock = शून्य;
	psock->tx_kcm = शून्य;
	KCM_STATS_INCR(psock->stats.unreserved);

	अगर (unlikely(psock->tx_stopped)) अणु
		अगर (psock->करोne) अणु
			/* Deferred मुक्त */
			list_del(&psock->psock_list);
			mux->psocks_cnt--;
			sock_put(psock->sk);
			fput(psock->sk->sk_socket->file);
			kmem_cache_मुक्त(kcm_psockp, psock);
		पूर्ण

		/* Don't put back on available list */

		spin_unlock_bh(&mux->lock);

		वापस;
	पूर्ण

	psock_now_avail(psock);

	spin_unlock_bh(&mux->lock);
पूर्ण

अटल व्योम kcm_report_tx_retry(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;

	spin_lock_bh(&mux->lock);
	KCM_STATS_INCR(mux->stats.tx_retries);
	spin_unlock_bh(&mux->lock);
पूर्ण

/* Write any messages पढ़ोy on the kcm socket.  Called with kcm sock lock
 * held.  Return bytes actually sent or error.
 */
अटल पूर्णांक kcm_ग_लिखो_msgs(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा sock *sk = &kcm->sk;
	काष्ठा kcm_psock *psock;
	काष्ठा sk_buff *skb, *head;
	काष्ठा kcm_tx_msg *txm;
	अचिन्हित लघु fragidx, frag_offset;
	अचिन्हित पूर्णांक sent, total_sent = 0;
	पूर्णांक ret = 0;

	kcm->tx_रुको_more = false;
	psock = kcm->tx_psock;
	अगर (unlikely(psock && psock->tx_stopped)) अणु
		/* A reserved psock was पातed asynchronously. Unreserve
		 * it and we'll retry the message.
		 */
		unreserve_psock(kcm);
		kcm_report_tx_retry(kcm);
		अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue))
			वापस 0;

		kcm_tx_msg(skb_peek(&sk->sk_ग_लिखो_queue))->sent = 0;

	पूर्ण अन्यथा अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue)) अणु
		वापस 0;
	पूर्ण

	head = skb_peek(&sk->sk_ग_लिखो_queue);
	txm = kcm_tx_msg(head);

	अगर (txm->sent) अणु
		/* Send of first skbuff in queue alपढ़ोy in progress */
		अगर (WARN_ON(!psock)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		sent = txm->sent;
		frag_offset = txm->frag_offset;
		fragidx = txm->fragidx;
		skb = txm->frag_skb;

		जाओ करो_frag;
	पूर्ण

try_again:
	psock = reserve_psock(kcm);
	अगर (!psock)
		जाओ out;

	करो अणु
		skb = head;
		txm = kcm_tx_msg(head);
		sent = 0;

करो_frag_list:
		अगर (WARN_ON(!skb_shinfo(skb)->nr_frags)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		क्रम (fragidx = 0; fragidx < skb_shinfo(skb)->nr_frags;
		     fragidx++) अणु
			skb_frag_t *frag;

			frag_offset = 0;
करो_frag:
			frag = &skb_shinfo(skb)->frags[fragidx];
			अगर (WARN_ON(!skb_frag_size(frag))) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ret = kernel_sendpage(psock->sk->sk_socket,
					      skb_frag_page(frag),
					      skb_frag_off(frag) + frag_offset,
					      skb_frag_size(frag) - frag_offset,
					      MSG_DONTWAIT);
			अगर (ret <= 0) अणु
				अगर (ret == -EAGAIN) अणु
					/* Save state to try again when there's
					 * ग_लिखो space on the socket
					 */
					txm->sent = sent;
					txm->frag_offset = frag_offset;
					txm->fragidx = fragidx;
					txm->frag_skb = skb;

					ret = 0;
					जाओ out;
				पूर्ण

				/* Hard failure in sending message, पात this
				 * psock since it has lost framing
				 * synchronization and retry sending the
				 * message from the beginning.
				 */
				kcm_पात_tx_psock(psock, ret ? -ret : EPIPE,
						   true);
				unreserve_psock(kcm);

				txm->sent = 0;
				kcm_report_tx_retry(kcm);
				ret = 0;

				जाओ try_again;
			पूर्ण

			sent += ret;
			frag_offset += ret;
			KCM_STATS_ADD(psock->stats.tx_bytes, ret);
			अगर (frag_offset < skb_frag_size(frag)) अणु
				/* Not finished with this frag */
				जाओ करो_frag;
			पूर्ण
		पूर्ण

		अगर (skb == head) अणु
			अगर (skb_has_frag_list(skb)) अणु
				skb = skb_shinfo(skb)->frag_list;
				जाओ करो_frag_list;
			पूर्ण
		पूर्ण अन्यथा अगर (skb->next) अणु
			skb = skb->next;
			जाओ करो_frag_list;
		पूर्ण

		/* Successfully sent the whole packet, account क्रम it. */
		skb_dequeue(&sk->sk_ग_लिखो_queue);
		kमुक्त_skb(head);
		sk->sk_wmem_queued -= sent;
		total_sent += sent;
		KCM_STATS_INCR(psock->stats.tx_msgs);
	पूर्ण जबतक ((head = skb_peek(&sk->sk_ग_लिखो_queue)));
out:
	अगर (!head) अणु
		/* Done with all queued messages. */
		WARN_ON(!skb_queue_empty(&sk->sk_ग_लिखो_queue));
		unreserve_psock(kcm);
	पूर्ण

	/* Check अगर ग_लिखो space is available */
	sk->sk_ग_लिखो_space(sk);

	वापस total_sent ? : ret;
पूर्ण

अटल व्योम kcm_tx_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा kcm_sock *kcm = container_of(w, काष्ठा kcm_sock, tx_work);
	काष्ठा sock *sk = &kcm->sk;
	पूर्णांक err;

	lock_sock(sk);

	/* Primarily क्रम SOCK_DGRAM sockets, also handle asynchronous tx
	 * पातs
	 */
	err = kcm_ग_लिखो_msgs(kcm);
	अगर (err < 0) अणु
		/* Hard failure in ग_लिखो, report error on KCM socket */
		pr_warn("KCM: Hard failure on kcm_write_msgs %d\n", err);
		report_csk_error(&kcm->sk, -err);
		जाओ out;
	पूर्ण

	/* Primarily क्रम SOCK_SEQPACKET sockets */
	अगर (likely(sk->sk_socket) &&
	    test_bit(SOCK_NOSPACE, &sk->sk_socket->flags)) अणु
		clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk->sk_ग_लिखो_space(sk);
	पूर्ण

out:
	release_sock(sk);
पूर्ण

अटल व्योम kcm_push(काष्ठा kcm_sock *kcm)
अणु
	अगर (kcm->tx_रुको_more)
		kcm_ग_लिखो_msgs(kcm);
पूर्ण

अटल sमाप_प्रकार kcm_sendpage(काष्ठा socket *sock, काष्ठा page *page,
			    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)

अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा kcm_sock *kcm = kcm_sk(sk);
	काष्ठा sk_buff *skb = शून्य, *head = शून्य;
	दीर्घ समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	bool eor;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	/* No MSG_EOR from splice, only look at MSG_MORE */
	eor = !(flags & MSG_MORE);

	lock_sock(sk);

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	err = -EPIPE;
	अगर (sk->sk_err)
		जाओ out_error;

	अगर (kcm->seq_skb) अणु
		/* Previously खोलोed message */
		head = kcm->seq_skb;
		skb = kcm_tx_msg(head)->last_skb;
		i = skb_shinfo(skb)->nr_frags;

		अगर (skb_can_coalesce(skb, i, page, offset)) अणु
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], size);
			skb_shinfo(skb)->flags |= SKBFL_SHARED_FRAG;
			जाओ coalesced;
		पूर्ण

		अगर (i >= MAX_SKB_FRAGS) अणु
			काष्ठा sk_buff *tskb;

			tskb = alloc_skb(0, sk->sk_allocation);
			जबतक (!tskb) अणु
				kcm_push(kcm);
				err = sk_stream_रुको_memory(sk, &समयo);
				अगर (err)
					जाओ out_error;
			पूर्ण

			अगर (head == skb)
				skb_shinfo(head)->frag_list = tskb;
			अन्यथा
				skb->next = tskb;

			skb = tskb;
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			i = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Call the sk_stream functions to manage the sndbuf mem. */
		अगर (!sk_stream_memory_मुक्त(sk)) अणु
			kcm_push(kcm);
			set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			err = sk_stream_रुको_memory(sk, &समयo);
			अगर (err)
				जाओ out_error;
		पूर्ण

		head = alloc_skb(0, sk->sk_allocation);
		जबतक (!head) अणु
			kcm_push(kcm);
			err = sk_stream_रुको_memory(sk, &समयo);
			अगर (err)
				जाओ out_error;
		पूर्ण

		skb = head;
		i = 0;
	पूर्ण

	get_page(page);
	skb_fill_page_desc(skb, i, page, offset, size);
	skb_shinfo(skb)->flags |= SKBFL_SHARED_FRAG;

coalesced:
	skb->len += size;
	skb->data_len += size;
	skb->truesize += size;
	sk->sk_wmem_queued += size;
	sk_mem_अक्षरge(sk, size);

	अगर (head != skb) अणु
		head->len += size;
		head->data_len += size;
		head->truesize += size;
	पूर्ण

	अगर (eor) अणु
		bool not_busy = skb_queue_empty(&sk->sk_ग_लिखो_queue);

		/* Message complete, queue it on send buffer */
		__skb_queue_tail(&sk->sk_ग_लिखो_queue, head);
		kcm->seq_skb = शून्य;
		KCM_STATS_INCR(kcm->stats.tx_msgs);

		अगर (flags & MSG_BATCH) अणु
			kcm->tx_रुको_more = true;
		पूर्ण अन्यथा अगर (kcm->tx_रुको_more || not_busy) अणु
			err = kcm_ग_लिखो_msgs(kcm);
			अगर (err < 0) अणु
				/* We got a hard error in ग_लिखो_msgs but have
				 * alपढ़ोy queued this message. Report an error
				 * in the socket, but करोn't affect वापस value
				 * from sendmsg
				 */
				pr_warn("KCM: Hard failure on kcm_write_msgs\n");
				report_csk_error(&kcm->sk, -err);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Message not complete, save state */
		kcm->seq_skb = head;
		kcm_tx_msg(head)->last_skb = skb;
	पूर्ण

	KCM_STATS_ADD(kcm->stats.tx_bytes, size);

	release_sock(sk);
	वापस size;

out_error:
	kcm_push(kcm);

	err = sk_stream_error(sk, flags, err);

	/* make sure we wake any epoll edge trigger रुकोer */
	अगर (unlikely(skb_queue_len(&sk->sk_ग_लिखो_queue) == 0 && err == -EAGAIN))
		sk->sk_ग_लिखो_space(sk);

	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक kcm_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा kcm_sock *kcm = kcm_sk(sk);
	काष्ठा sk_buff *skb = शून्य, *head = शून्य;
	माप_प्रकार copy, copied = 0;
	दीर्घ समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
	पूर्णांक eor = (sock->type == SOCK_DGRAM) ?
		  !(msg->msg_flags & MSG_MORE) : !!(msg->msg_flags & MSG_EOR);
	पूर्णांक err = -EPIPE;

	lock_sock(sk);

	/* Per tcp_sendmsg this should be in poll */
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	अगर (sk->sk_err)
		जाओ out_error;

	अगर (kcm->seq_skb) अणु
		/* Previously खोलोed message */
		head = kcm->seq_skb;
		skb = kcm_tx_msg(head)->last_skb;
		जाओ start;
	पूर्ण

	/* Call the sk_stream functions to manage the sndbuf mem. */
	अगर (!sk_stream_memory_मुक्त(sk)) अणु
		kcm_push(kcm);
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err)
			जाओ out_error;
	पूर्ण

	अगर (msg_data_left(msg)) अणु
		/* New message, alloc head skb */
		head = alloc_skb(0, sk->sk_allocation);
		जबतक (!head) अणु
			kcm_push(kcm);
			err = sk_stream_रुको_memory(sk, &समयo);
			अगर (err)
				जाओ out_error;

			head = alloc_skb(0, sk->sk_allocation);
		पूर्ण

		skb = head;

		/* Set ip_summed to CHECKSUM_UNNECESSARY to aव्योम calling
		 * csum_and_copy_from_iter from skb_करो_copy_data_nocache.
		 */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

start:
	जबतक (msg_data_left(msg)) अणु
		bool merge = true;
		पूर्णांक i = skb_shinfo(skb)->nr_frags;
		काष्ठा page_frag *pfrag = sk_page_frag(sk);

		अगर (!sk_page_frag_refill(sk, pfrag))
			जाओ रुको_क्रम_memory;

		अगर (!skb_can_coalesce(skb, i, pfrag->page,
				      pfrag->offset)) अणु
			अगर (i == MAX_SKB_FRAGS) अणु
				काष्ठा sk_buff *tskb;

				tskb = alloc_skb(0, sk->sk_allocation);
				अगर (!tskb)
					जाओ रुको_क्रम_memory;

				अगर (head == skb)
					skb_shinfo(head)->frag_list = tskb;
				अन्यथा
					skb->next = tskb;

				skb = tskb;
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				जारी;
			पूर्ण
			merge = false;
		पूर्ण

		copy = min_t(पूर्णांक, msg_data_left(msg),
			     pfrag->size - pfrag->offset);

		अगर (!sk_wmem_schedule(sk, copy))
			जाओ रुको_क्रम_memory;

		err = skb_copy_to_page_nocache(sk, &msg->msg_iter, skb,
					       pfrag->page,
					       pfrag->offset,
					       copy);
		अगर (err)
			जाओ out_error;

		/* Update the skb. */
		अगर (merge) अणु
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
		पूर्ण अन्यथा अणु
			skb_fill_page_desc(skb, i, pfrag->page,
					   pfrag->offset, copy);
			get_page(pfrag->page);
		पूर्ण

		pfrag->offset += copy;
		copied += copy;
		अगर (head != skb) अणु
			head->len += copy;
			head->data_len += copy;
		पूर्ण

		जारी;

रुको_क्रम_memory:
		kcm_push(kcm);
		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err)
			जाओ out_error;
	पूर्ण

	अगर (eor) अणु
		bool not_busy = skb_queue_empty(&sk->sk_ग_लिखो_queue);

		अगर (head) अणु
			/* Message complete, queue it on send buffer */
			__skb_queue_tail(&sk->sk_ग_लिखो_queue, head);
			kcm->seq_skb = शून्य;
			KCM_STATS_INCR(kcm->stats.tx_msgs);
		पूर्ण

		अगर (msg->msg_flags & MSG_BATCH) अणु
			kcm->tx_रुको_more = true;
		पूर्ण अन्यथा अगर (kcm->tx_रुको_more || not_busy) अणु
			err = kcm_ग_लिखो_msgs(kcm);
			अगर (err < 0) अणु
				/* We got a hard error in ग_लिखो_msgs but have
				 * alपढ़ोy queued this message. Report an error
				 * in the socket, but करोn't affect वापस value
				 * from sendmsg
				 */
				pr_warn("KCM: Hard failure on kcm_write_msgs\n");
				report_csk_error(&kcm->sk, -err);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Message not complete, save state */
partial_message:
		अगर (head) अणु
			kcm->seq_skb = head;
			kcm_tx_msg(head)->last_skb = skb;
		पूर्ण
	पूर्ण

	KCM_STATS_ADD(kcm->stats.tx_bytes, copied);

	release_sock(sk);
	वापस copied;

out_error:
	kcm_push(kcm);

	अगर (copied && sock->type == SOCK_SEQPACKET) अणु
		/* Wrote some bytes beक्रमe encountering an
		 * error, वापस partial success.
		 */
		जाओ partial_message;
	पूर्ण

	अगर (head != kcm->seq_skb)
		kमुक्त_skb(head);

	err = sk_stream_error(sk, msg->msg_flags, err);

	/* make sure we wake any epoll edge trigger रुकोer */
	अगर (unlikely(skb_queue_len(&sk->sk_ग_लिखो_queue) == 0 && err == -EAGAIN))
		sk->sk_ग_लिखो_space(sk);

	release_sock(sk);
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *kcm_रुको_data(काष्ठा sock *sk, पूर्णांक flags,
				     दीर्घ समयo, पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb;

	जबतक (!(skb = skb_peek(&sk->sk_receive_queue))) अणु
		अगर (sk->sk_err) अणु
			*err = sock_error(sk);
			वापस शून्य;
		पूर्ण

		अगर (sock_flag(sk, SOCK_DONE))
			वापस शून्य;

		अगर ((flags & MSG_DONTWAIT) || !समयo) अणु
			*err = -EAGAIN;
			वापस शून्य;
		पूर्ण

		sk_रुको_data(sk, &समयo, शून्य);

		/* Handle संकेतs */
		अगर (संकेत_pending(current)) अणु
			*err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक kcm_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
		       माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा kcm_sock *kcm = kcm_sk(sk);
	पूर्णांक err = 0;
	दीर्घ समयo;
	काष्ठा strp_msg *sपंचांग;
	पूर्णांक copied = 0;
	काष्ठा sk_buff *skb;

	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	lock_sock(sk);

	skb = kcm_रुको_data(sk, flags, समयo, &err);
	अगर (!skb)
		जाओ out;

	/* Okay, have a message on the receive queue */

	sपंचांग = strp_msg(skb);

	अगर (len > sपंचांग->full_len)
		len = sपंचांग->full_len;

	err = skb_copy_datagram_msg(skb, sपंचांग->offset, msg, len);
	अगर (err < 0)
		जाओ out;

	copied = len;
	अगर (likely(!(flags & MSG_PEEK))) अणु
		KCM_STATS_ADD(kcm->stats.rx_bytes, copied);
		अगर (copied < sपंचांग->full_len) अणु
			अगर (sock->type == SOCK_DGRAM) अणु
				/* Truncated message */
				msg->msg_flags |= MSG_TRUNC;
				जाओ msg_finished;
			पूर्ण
			sपंचांग->offset += copied;
			sपंचांग->full_len -= copied;
		पूर्ण अन्यथा अणु
msg_finished:
			/* Finished with message */
			msg->msg_flags |= MSG_EOR;
			KCM_STATS_INCR(kcm->stats.rx_msgs);
			skb_unlink(skb, &sk->sk_receive_queue);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

out:
	release_sock(sk);

	वापस copied ? : err;
पूर्ण

अटल sमाप_प्रकार kcm_splice_पढ़ो(काष्ठा socket *sock, loff_t *ppos,
			       काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा kcm_sock *kcm = kcm_sk(sk);
	दीर्घ समयo;
	काष्ठा strp_msg *sपंचांग;
	पूर्णांक err = 0;
	sमाप_प्रकार copied;
	काष्ठा sk_buff *skb;

	/* Only support splice क्रम SOCKSEQPACKET */

	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	lock_sock(sk);

	skb = kcm_रुको_data(sk, flags, समयo, &err);
	अगर (!skb)
		जाओ err_out;

	/* Okay, have a message on the receive queue */

	sपंचांग = strp_msg(skb);

	अगर (len > sपंचांग->full_len)
		len = sपंचांग->full_len;

	copied = skb_splice_bits(skb, sk, sपंचांग->offset, pipe, len, flags);
	अगर (copied < 0) अणु
		err = copied;
		जाओ err_out;
	पूर्ण

	KCM_STATS_ADD(kcm->stats.rx_bytes, copied);

	sपंचांग->offset += copied;
	sपंचांग->full_len -= copied;

	/* We have no way to वापस MSG_EOR. If all the bytes have been
	 * पढ़ो we still leave the message in the receive socket buffer.
	 * A subsequent recvmsg needs to be करोne to वापस MSG_EOR and
	 * finish पढ़ोing the message.
	 */

	release_sock(sk);

	वापस copied;

err_out:
	release_sock(sk);

	वापस err;
पूर्ण

/* kcm sock lock held */
अटल व्योम kcm_recv_disable(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;

	अगर (kcm->rx_disabled)
		वापस;

	spin_lock_bh(&mux->rx_lock);

	kcm->rx_disabled = 1;

	/* If a psock is reserved we'll करो cleanup in unreserve */
	अगर (!kcm->rx_psock) अणु
		अगर (kcm->rx_रुको) अणु
			list_del(&kcm->रुको_rx_list);
			kcm->rx_रुको = false;
		पूर्ण

		requeue_rx_msgs(mux, &kcm->sk.sk_receive_queue);
	पूर्ण

	spin_unlock_bh(&mux->rx_lock);
पूर्ण

/* kcm sock lock held */
अटल व्योम kcm_recv_enable(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;

	अगर (!kcm->rx_disabled)
		वापस;

	spin_lock_bh(&mux->rx_lock);

	kcm->rx_disabled = 0;
	kcm_rcv_पढ़ोy(kcm);

	spin_unlock_bh(&mux->rx_lock);
पूर्ण

अटल पूर्णांक kcm_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा kcm_sock *kcm = kcm_sk(sock->sk);
	पूर्णांक val, valbool;
	पूर्णांक err = 0;

	अगर (level != SOL_KCM)
		वापस -ENOPROTOOPT;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	valbool = val ? 1 : 0;

	चयन (optname) अणु
	हाल KCM_RECV_DISABLE:
		lock_sock(&kcm->sk);
		अगर (valbool)
			kcm_recv_disable(kcm);
		अन्यथा
			kcm_recv_enable(kcm);
		release_sock(&kcm->sk);
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक kcm_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा kcm_sock *kcm = kcm_sk(sock->sk);
	पूर्णांक val, len;

	अगर (level != SOL_KCM)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));
	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल KCM_RECV_DISABLE:
		val = kcm->rx_disabled;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम init_kcm_sock(काष्ठा kcm_sock *kcm, काष्ठा kcm_mux *mux)
अणु
	काष्ठा kcm_sock *tkcm;
	काष्ठा list_head *head;
	पूर्णांक index = 0;

	/* For SOCK_SEQPACKET sock type, datagram_poll checks the sk_state, so
	 * we set sk_state, otherwise epoll_रुको always वापसs right away with
	 * EPOLLHUP
	 */
	kcm->sk.sk_state = TCP_ESTABLISHED;

	/* Add to mux's kcm sockets list */
	kcm->mux = mux;
	spin_lock_bh(&mux->lock);

	head = &mux->kcm_socks;
	list_क्रम_each_entry(tkcm, &mux->kcm_socks, kcm_sock_list) अणु
		अगर (tkcm->index != index)
			अवरोध;
		head = &tkcm->kcm_sock_list;
		index++;
	पूर्ण

	list_add(&kcm->kcm_sock_list, head);
	kcm->index = index;

	mux->kcm_socks_cnt++;
	spin_unlock_bh(&mux->lock);

	INIT_WORK(&kcm->tx_work, kcm_tx_work);

	spin_lock_bh(&mux->rx_lock);
	kcm_rcv_पढ़ोy(kcm);
	spin_unlock_bh(&mux->rx_lock);
पूर्ण

अटल पूर्णांक kcm_attach(काष्ठा socket *sock, काष्ठा socket *csock,
		      काष्ठा bpf_prog *prog)
अणु
	काष्ठा kcm_sock *kcm = kcm_sk(sock->sk);
	काष्ठा kcm_mux *mux = kcm->mux;
	काष्ठा sock *csk;
	काष्ठा kcm_psock *psock = शून्य, *tpsock;
	काष्ठा list_head *head;
	पूर्णांक index = 0;
	अटल स्थिर काष्ठा strp_callbacks cb = अणु
		.rcv_msg = kcm_rcv_strparser,
		.parse_msg = kcm_parse_func_strparser,
		.पढ़ो_sock_करोne = kcm_पढ़ो_sock_करोne,
	पूर्ण;
	पूर्णांक err = 0;

	csk = csock->sk;
	अगर (!csk)
		वापस -EINVAL;

	lock_sock(csk);

	/* Only allow TCP sockets to be attached क्रम now */
	अगर ((csk->sk_family != AF_INET && csk->sk_family != AF_INET6) ||
	    csk->sk_protocol != IPPROTO_TCP) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Don't allow listeners or बंदd sockets */
	अगर (csk->sk_state == TCP_LISTEN || csk->sk_state == TCP_CLOSE) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	psock = kmem_cache_zalloc(kcm_psockp, GFP_KERNEL);
	अगर (!psock) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	psock->mux = mux;
	psock->sk = csk;
	psock->bpf_prog = prog;

	err = strp_init(&psock->strp, csk, &cb);
	अगर (err) अणु
		kmem_cache_मुक्त(kcm_psockp, psock);
		जाओ out;
	पूर्ण

	ग_लिखो_lock_bh(&csk->sk_callback_lock);

	/* Check अगर sk_user_data is alपढ़ोy by KCM or someone अन्यथा.
	 * Must be करोne under lock to prevent race conditions.
	 */
	अगर (csk->sk_user_data) अणु
		ग_लिखो_unlock_bh(&csk->sk_callback_lock);
		strp_stop(&psock->strp);
		strp_करोne(&psock->strp);
		kmem_cache_मुक्त(kcm_psockp, psock);
		err = -EALREADY;
		जाओ out;
	पूर्ण

	psock->save_data_पढ़ोy = csk->sk_data_पढ़ोy;
	psock->save_ग_लिखो_space = csk->sk_ग_लिखो_space;
	psock->save_state_change = csk->sk_state_change;
	csk->sk_user_data = psock;
	csk->sk_data_पढ़ोy = psock_data_पढ़ोy;
	csk->sk_ग_लिखो_space = psock_ग_लिखो_space;
	csk->sk_state_change = psock_state_change;

	ग_लिखो_unlock_bh(&csk->sk_callback_lock);

	sock_hold(csk);

	/* Finished initialization, now add the psock to the MUX. */
	spin_lock_bh(&mux->lock);
	head = &mux->psocks;
	list_क्रम_each_entry(tpsock, &mux->psocks, psock_list) अणु
		अगर (tpsock->index != index)
			अवरोध;
		head = &tpsock->psock_list;
		index++;
	पूर्ण

	list_add(&psock->psock_list, head);
	psock->index = index;

	KCM_STATS_INCR(mux->stats.psock_attach);
	mux->psocks_cnt++;
	psock_now_avail(psock);
	spin_unlock_bh(&mux->lock);

	/* Schedule RX work in हाल there are alपढ़ोy bytes queued */
	strp_check_rcv(&psock->strp);

out:
	release_sock(csk);

	वापस err;
पूर्ण

अटल पूर्णांक kcm_attach_ioctl(काष्ठा socket *sock, काष्ठा kcm_attach *info)
अणु
	काष्ठा socket *csock;
	काष्ठा bpf_prog *prog;
	पूर्णांक err;

	csock = sockfd_lookup(info->fd, &err);
	अगर (!csock)
		वापस -ENOENT;

	prog = bpf_prog_get_type(info->bpf_fd, BPF_PROG_TYPE_SOCKET_FILTER);
	अगर (IS_ERR(prog)) अणु
		err = PTR_ERR(prog);
		जाओ out;
	पूर्ण

	err = kcm_attach(sock, csock, prog);
	अगर (err) अणु
		bpf_prog_put(prog);
		जाओ out;
	पूर्ण

	/* Keep reference on file also */

	वापस 0;
out:
	sockfd_put(csock);
	वापस err;
पूर्ण

अटल व्योम kcm_unattach(काष्ठा kcm_psock *psock)
अणु
	काष्ठा sock *csk = psock->sk;
	काष्ठा kcm_mux *mux = psock->mux;

	lock_sock(csk);

	/* Stop getting callbacks from TCP socket. After this there should
	 * be no way to reserve a kcm क्रम this psock.
	 */
	ग_लिखो_lock_bh(&csk->sk_callback_lock);
	csk->sk_user_data = शून्य;
	csk->sk_data_पढ़ोy = psock->save_data_पढ़ोy;
	csk->sk_ग_लिखो_space = psock->save_ग_लिखो_space;
	csk->sk_state_change = psock->save_state_change;
	strp_stop(&psock->strp);

	अगर (WARN_ON(psock->rx_kcm)) अणु
		ग_लिखो_unlock_bh(&csk->sk_callback_lock);
		release_sock(csk);
		वापस;
	पूर्ण

	spin_lock_bh(&mux->rx_lock);

	/* Stop receiver activities. After this poपूर्णांक psock should not be
	 * able to get onto पढ़ोy list either through callbacks or work.
	 */
	अगर (psock->पढ़ोy_rx_msg) अणु
		list_del(&psock->psock_पढ़ोy_list);
		kमुक्त_skb(psock->पढ़ोy_rx_msg);
		psock->पढ़ोy_rx_msg = शून्य;
		KCM_STATS_INCR(mux->stats.rx_पढ़ोy_drops);
	पूर्ण

	spin_unlock_bh(&mux->rx_lock);

	ग_लिखो_unlock_bh(&csk->sk_callback_lock);

	/* Call strp_करोne without sock lock */
	release_sock(csk);
	strp_करोne(&psock->strp);
	lock_sock(csk);

	bpf_prog_put(psock->bpf_prog);

	spin_lock_bh(&mux->lock);

	aggregate_psock_stats(&psock->stats, &mux->aggregate_psock_stats);
	save_strp_stats(&psock->strp, &mux->aggregate_strp_stats);

	KCM_STATS_INCR(mux->stats.psock_unattach);

	अगर (psock->tx_kcm) अणु
		/* psock was reserved.  Just mark it finished and we will clean
		 * up in the kcm paths, we need kcm lock which can not be
		 * acquired here.
		 */
		KCM_STATS_INCR(mux->stats.psock_unattach_rsvd);
		spin_unlock_bh(&mux->lock);

		/* We are unattaching a socket that is reserved. Abort the
		 * socket since we may be out of sync in sending on it. We need
		 * to करो this without the mux lock.
		 */
		kcm_पात_tx_psock(psock, EPIPE, false);

		spin_lock_bh(&mux->lock);
		अगर (!psock->tx_kcm) अणु
			/* psock now unreserved in winकरोw mux was unlocked */
			जाओ no_reserved;
		पूर्ण
		psock->करोne = 1;

		/* Commit करोne beक्रमe queuing work to process it */
		smp_mb();

		/* Queue tx work to make sure psock->करोne is handled */
		queue_work(kcm_wq, &psock->tx_kcm->tx_work);
		spin_unlock_bh(&mux->lock);
	पूर्ण अन्यथा अणु
no_reserved:
		अगर (!psock->tx_stopped)
			list_del(&psock->psock_avail_list);
		list_del(&psock->psock_list);
		mux->psocks_cnt--;
		spin_unlock_bh(&mux->lock);

		sock_put(csk);
		fput(csk->sk_socket->file);
		kmem_cache_मुक्त(kcm_psockp, psock);
	पूर्ण

	release_sock(csk);
पूर्ण

अटल पूर्णांक kcm_unattach_ioctl(काष्ठा socket *sock, काष्ठा kcm_unattach *info)
अणु
	काष्ठा kcm_sock *kcm = kcm_sk(sock->sk);
	काष्ठा kcm_mux *mux = kcm->mux;
	काष्ठा kcm_psock *psock;
	काष्ठा socket *csock;
	काष्ठा sock *csk;
	पूर्णांक err;

	csock = sockfd_lookup(info->fd, &err);
	अगर (!csock)
		वापस -ENOENT;

	csk = csock->sk;
	अगर (!csk) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = -ENOENT;

	spin_lock_bh(&mux->lock);

	list_क्रम_each_entry(psock, &mux->psocks, psock_list) अणु
		अगर (psock->sk != csk)
			जारी;

		/* Found the matching psock */

		अगर (psock->unattaching || WARN_ON(psock->करोne)) अणु
			err = -EALREADY;
			अवरोध;
		पूर्ण

		psock->unattaching = 1;

		spin_unlock_bh(&mux->lock);

		/* Lower socket lock should alपढ़ोy be held */
		kcm_unattach(psock);

		err = 0;
		जाओ out;
	पूर्ण

	spin_unlock_bh(&mux->lock);

out:
	sockfd_put(csock);
	वापस err;
पूर्ण

अटल काष्ठा proto kcm_proto = अणु
	.name	= "KCM",
	.owner	= THIS_MODULE,
	.obj_size = माप(काष्ठा kcm_sock),
पूर्ण;

/* Clone a kcm socket. */
अटल काष्ठा file *kcm_clone(काष्ठा socket *osock)
अणु
	काष्ठा socket *newsock;
	काष्ठा sock *newsk;

	newsock = sock_alloc();
	अगर (!newsock)
		वापस ERR_PTR(-ENखाता);

	newsock->type = osock->type;
	newsock->ops = osock->ops;

	__module_get(newsock->ops->owner);

	newsk = sk_alloc(sock_net(osock->sk), PF_KCM, GFP_KERNEL,
			 &kcm_proto, false);
	अगर (!newsk) अणु
		sock_release(newsock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	sock_init_data(newsock, newsk);
	init_kcm_sock(kcm_sk(newsk), kcm_sk(osock->sk)->mux);

	वापस sock_alloc_file(newsock, 0, osock->sk->sk_prot_creator->name);
पूर्ण

अटल पूर्णांक kcm_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SIOCKCMATTACH: अणु
		काष्ठा kcm_attach info;

		अगर (copy_from_user(&info, (व्योम __user *)arg, माप(info)))
			वापस -EFAULT;

		err = kcm_attach_ioctl(sock, &info);

		अवरोध;
	पूर्ण
	हाल SIOCKCMUNATTACH: अणु
		काष्ठा kcm_unattach info;

		अगर (copy_from_user(&info, (व्योम __user *)arg, माप(info)))
			वापस -EFAULT;

		err = kcm_unattach_ioctl(sock, &info);

		अवरोध;
	पूर्ण
	हाल SIOCKCMCLONE: अणु
		काष्ठा kcm_clone info;
		काष्ठा file *file;

		info.fd = get_unused_fd_flags(0);
		अगर (unlikely(info.fd < 0))
			वापस info.fd;

		file = kcm_clone(sock);
		अगर (IS_ERR(file)) अणु
			put_unused_fd(info.fd);
			वापस PTR_ERR(file);
		पूर्ण
		अगर (copy_to_user((व्योम __user *)arg, &info,
				 माप(info))) अणु
			put_unused_fd(info.fd);
			fput(file);
			वापस -EFAULT;
		पूर्ण
		fd_install(info.fd, file);
		err = 0;
		अवरोध;
	पूर्ण
	शेष:
		err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम मुक्त_mux(काष्ठा rcu_head *rcu)
अणु
	काष्ठा kcm_mux *mux = container_of(rcu,
	    काष्ठा kcm_mux, rcu);

	kmem_cache_मुक्त(kcm_muxp, mux);
पूर्ण

अटल व्योम release_mux(काष्ठा kcm_mux *mux)
अणु
	काष्ठा kcm_net *knet = mux->knet;
	काष्ठा kcm_psock *psock, *पंचांगp_psock;

	/* Release psocks */
	list_क्रम_each_entry_safe(psock, पंचांगp_psock,
				 &mux->psocks, psock_list) अणु
		अगर (!WARN_ON(psock->unattaching))
			kcm_unattach(psock);
	पूर्ण

	अगर (WARN_ON(mux->psocks_cnt))
		वापस;

	__skb_queue_purge(&mux->rx_hold_queue);

	mutex_lock(&knet->mutex);
	aggregate_mux_stats(&mux->stats, &knet->aggregate_mux_stats);
	aggregate_psock_stats(&mux->aggregate_psock_stats,
			      &knet->aggregate_psock_stats);
	aggregate_strp_stats(&mux->aggregate_strp_stats,
			     &knet->aggregate_strp_stats);
	list_del_rcu(&mux->kcm_mux_list);
	knet->count--;
	mutex_unlock(&knet->mutex);

	call_rcu(&mux->rcu, मुक्त_mux);
पूर्ण

अटल व्योम kcm_करोne(काष्ठा kcm_sock *kcm)
अणु
	काष्ठा kcm_mux *mux = kcm->mux;
	काष्ठा sock *sk = &kcm->sk;
	पूर्णांक socks_cnt;

	spin_lock_bh(&mux->rx_lock);
	अगर (kcm->rx_psock) अणु
		/* Cleanup in unreserve_rx_kcm */
		WARN_ON(kcm->करोne);
		kcm->rx_disabled = 1;
		kcm->करोne = 1;
		spin_unlock_bh(&mux->rx_lock);
		वापस;
	पूर्ण

	अगर (kcm->rx_रुको) अणु
		list_del(&kcm->रुको_rx_list);
		kcm->rx_रुको = false;
	पूर्ण
	/* Move any pending receive messages to other kcm sockets */
	requeue_rx_msgs(mux, &sk->sk_receive_queue);

	spin_unlock_bh(&mux->rx_lock);

	अगर (WARN_ON(sk_rmem_alloc_get(sk)))
		वापस;

	/* Detach from MUX */
	spin_lock_bh(&mux->lock);

	list_del(&kcm->kcm_sock_list);
	mux->kcm_socks_cnt--;
	socks_cnt = mux->kcm_socks_cnt;

	spin_unlock_bh(&mux->lock);

	अगर (!socks_cnt) अणु
		/* We are करोne with the mux now. */
		release_mux(mux);
	पूर्ण

	WARN_ON(kcm->rx_रुको);

	sock_put(&kcm->sk);
पूर्ण

/* Called by kcm_release to बंद a KCM socket.
 * If this is the last KCM socket on the MUX, destroy the MUX.
 */
अटल पूर्णांक kcm_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा kcm_sock *kcm;
	काष्ठा kcm_mux *mux;
	काष्ठा kcm_psock *psock;

	अगर (!sk)
		वापस 0;

	kcm = kcm_sk(sk);
	mux = kcm->mux;

	sock_orphan(sk);
	kमुक्त_skb(kcm->seq_skb);

	lock_sock(sk);
	/* Purge queue under lock to aव्योम race condition with tx_work trying
	 * to act when queue is nonempty. If tx_work runs after this poपूर्णांक
	 * it will just वापस.
	 */
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);

	/* Set tx_stopped. This is checked when psock is bound to a kcm and we
	 * get a ग_लिखोspace callback. This prevents further work being queued
	 * from the callback (unbinding the psock occurs after canceling work.
	 */
	kcm->tx_stopped = 1;

	release_sock(sk);

	spin_lock_bh(&mux->lock);
	अगर (kcm->tx_रुको) अणु
		/* Take of tx_रुको list, after this poपूर्णांक there should be no way
		 * that a psock will be asचिन्हित to this kcm.
		 */
		list_del(&kcm->रुको_psock_list);
		kcm->tx_रुको = false;
	पूर्ण
	spin_unlock_bh(&mux->lock);

	/* Cancel work. After this poपूर्णांक there should be no outside references
	 * to the kcm socket.
	 */
	cancel_work_sync(&kcm->tx_work);

	lock_sock(sk);
	psock = kcm->tx_psock;
	अगर (psock) अणु
		/* A psock was reserved, so we need to समाप्त it since it
		 * may alपढ़ोy have some bytes queued from a message. We
		 * need to करो this after removing kcm from tx_रुको list.
		 */
		kcm_पात_tx_psock(psock, EPIPE, false);
		unreserve_psock(kcm);
	पूर्ण
	release_sock(sk);

	WARN_ON(kcm->tx_रुको);
	WARN_ON(kcm->tx_psock);

	sock->sk = शून्य;

	kcm_करोne(kcm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proto_ops kcm_dgram_ops = अणु
	.family =	PF_KCM,
	.owner =	THIS_MODULE,
	.release =	kcm_release,
	.bind =		sock_no_bind,
	.connect =	sock_no_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	sock_no_getname,
	.poll =		datagram_poll,
	.ioctl =	kcm_ioctl,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	kcm_setsockopt,
	.माला_लोockopt =	kcm_माला_लोockopt,
	.sendmsg =	kcm_sendmsg,
	.recvmsg =	kcm_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	kcm_sendpage,
पूर्ण;

अटल स्थिर काष्ठा proto_ops kcm_seqpacket_ops = अणु
	.family =	PF_KCM,
	.owner =	THIS_MODULE,
	.release =	kcm_release,
	.bind =		sock_no_bind,
	.connect =	sock_no_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	sock_no_getname,
	.poll =		datagram_poll,
	.ioctl =	kcm_ioctl,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	kcm_setsockopt,
	.माला_लोockopt =	kcm_माला_लोockopt,
	.sendmsg =	kcm_sendmsg,
	.recvmsg =	kcm_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	kcm_sendpage,
	.splice_पढ़ो =	kcm_splice_पढ़ो,
पूर्ण;

/* Create proto operation क्रम kcm sockets */
अटल पूर्णांक kcm_create(काष्ठा net *net, काष्ठा socket *sock,
		      पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);
	काष्ठा sock *sk;
	काष्ठा kcm_mux *mux;

	चयन (sock->type) अणु
	हाल SOCK_DGRAM:
		sock->ops = &kcm_dgram_ops;
		अवरोध;
	हाल SOCK_SEQPACKET:
		sock->ops = &kcm_seqpacket_ops;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	अगर (protocol != KCMPROTO_CONNECTED)
		वापस -EPROTONOSUPPORT;

	sk = sk_alloc(net, PF_KCM, GFP_KERNEL, &kcm_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	/* Allocate a kcm mux, shared between KCM sockets */
	mux = kmem_cache_zalloc(kcm_muxp, GFP_KERNEL);
	अगर (!mux) अणु
		sk_मुक्त(sk);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&mux->lock);
	spin_lock_init(&mux->rx_lock);
	INIT_LIST_HEAD(&mux->kcm_socks);
	INIT_LIST_HEAD(&mux->kcm_rx_रुकोers);
	INIT_LIST_HEAD(&mux->kcm_tx_रुकोers);

	INIT_LIST_HEAD(&mux->psocks);
	INIT_LIST_HEAD(&mux->psocks_पढ़ोy);
	INIT_LIST_HEAD(&mux->psocks_avail);

	mux->knet = knet;

	/* Add new MUX to list */
	mutex_lock(&knet->mutex);
	list_add_rcu(&mux->kcm_mux_list, &knet->mux_list);
	knet->count++;
	mutex_unlock(&knet->mutex);

	skb_queue_head_init(&mux->rx_hold_queue);

	/* Init KCM socket */
	sock_init_data(sock, sk);
	init_kcm_sock(kcm_sk(sk), mux);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family kcm_family_ops = अणु
	.family = PF_KCM,
	.create = kcm_create,
	.owner  = THIS_MODULE,
पूर्ण;

अटल __net_init पूर्णांक kcm_init_net(काष्ठा net *net)
अणु
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);

	INIT_LIST_HEAD_RCU(&knet->mux_list);
	mutex_init(&knet->mutex);

	वापस 0;
पूर्ण

अटल __net_निकास व्योम kcm_निकास_net(काष्ठा net *net)
अणु
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);

	/* All KCM sockets should be बंदd at this poपूर्णांक, which should mean
	 * that all multiplexors and psocks have been destroyed.
	 */
	WARN_ON(!list_empty(&knet->mux_list));
पूर्ण

अटल काष्ठा pernet_operations kcm_net_ops = अणु
	.init = kcm_init_net,
	.निकास = kcm_निकास_net,
	.id   = &kcm_net_id,
	.size = माप(काष्ठा kcm_net),
पूर्ण;

अटल पूर्णांक __init kcm_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	kcm_muxp = kmem_cache_create("kcm_mux_cache",
				     माप(काष्ठा kcm_mux), 0,
				     SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!kcm_muxp)
		जाओ fail;

	kcm_psockp = kmem_cache_create("kcm_psock_cache",
				       माप(काष्ठा kcm_psock), 0,
					SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!kcm_psockp)
		जाओ fail;

	kcm_wq = create_singlethपढ़ो_workqueue("kkcmd");
	अगर (!kcm_wq)
		जाओ fail;

	err = proto_रेजिस्टर(&kcm_proto, 1);
	अगर (err)
		जाओ fail;

	err = रेजिस्टर_pernet_device(&kcm_net_ops);
	अगर (err)
		जाओ net_ops_fail;

	err = sock_रेजिस्टर(&kcm_family_ops);
	अगर (err)
		जाओ sock_रेजिस्टर_fail;

	err = kcm_proc_init();
	अगर (err)
		जाओ proc_init_fail;

	वापस 0;

proc_init_fail:
	sock_unरेजिस्टर(PF_KCM);

sock_रेजिस्टर_fail:
	unरेजिस्टर_pernet_device(&kcm_net_ops);

net_ops_fail:
	proto_unरेजिस्टर(&kcm_proto);

fail:
	kmem_cache_destroy(kcm_muxp);
	kmem_cache_destroy(kcm_psockp);

	अगर (kcm_wq)
		destroy_workqueue(kcm_wq);

	वापस err;
पूर्ण

अटल व्योम __निकास kcm_निकास(व्योम)
अणु
	kcm_proc_निकास();
	sock_unरेजिस्टर(PF_KCM);
	unरेजिस्टर_pernet_device(&kcm_net_ops);
	proto_unरेजिस्टर(&kcm_proto);
	destroy_workqueue(kcm_wq);

	kmem_cache_destroy(kcm_muxp);
	kmem_cache_destroy(kcm_psockp);
पूर्ण

module_init(kcm_init);
module_निकास(kcm_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_KCM);
